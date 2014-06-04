#include "CList.h"
#include "FileIO.h"

/* CList */

CList::CList(const char *pszPath)
{
	this->File = new FileIO(pszPath, GENERIC_READ | GENERIC_WRITE, OPEN_ALWAYS);

	if (!this->File->open())
	{		
		m_dwLastError = GetLastError();
		this->File = nullptr;
		return;
	}
			
	m_dwOffset = 0;
	m_dwLastError = 0;
	m_dwSize = this->File->getSize();	
}

CList::~CList()
{
	if (this->File)
		delete this->File;
}

/* CListIn */

CListIn::CListIn(const char *pwszPath) : CList(pwszPath) { }

std::deque<CList::UserData> CListIn::GetChunk(int iChunkSize)
{
	std::deque<UserData> LoginDeque;

	if (!this->File)
		return LoginDeque;

	byte *pszFile = new byte[iChunkSize + 1]();

	if (this->File->read(pszFile, iChunkSize, m_dwOffset))
	{
		int iFilePos = m_dwOffset - 1;
		std::string strFile = reinterpret_cast<char*>(pszFile);

		for (; iFilePos > 0; iFilePos--)
		{
			if (strFile.at(iFilePos) == '\n')
			{
				strFile.at(iFilePos + 1) = '\0';
				strFile.resize(iFilePos + 1);
				
				iChunkSize = strFile.size();

				break;
			}
		}

		if (!iFilePos) 
			return LoginDeque;

		for (iFilePos = 0; iFilePos < iChunkSize; iFilePos++)
		{
			UserData tmpData;

			DWORD dwNameEnd = strFile.find('|', iFilePos) + 1,
				dwPassEnd = strFile.find('|', dwNameEnd) + 1;

			tmpData.strUser = strFile.substr(iFilePos, (dwNameEnd - 1) - iFilePos);
			tmpData.strPass = strFile.substr(dwNameEnd, (dwPassEnd - 1) - dwNameEnd);

			LoginDeque.push_back(tmpData);

			for (int c = 0; strFile.at(iFilePos) != '\n'; c++)
				iFilePos = dwPassEnd + c;
		}

		m_dwOffset += iChunkSize;
	}
	else
	{
		m_dwLastError = GetLastError();
	}

	delete [] pszFile;
	return LoginDeque;
}

/* CListOut */

CListOut::CListOut(const char *pszPath) : CList(pszPath) 
{
	m_dwOffset = m_dwSize;
}

bool CListOut::WriteList(std::deque<UserData> &vData)
{
	if (!this->File)
		return false;

	for (std::deque<UserData>::size_type i = 0; i < vData.size(); i++)
	{
		std::string strTmp = 
			std::string(vData.at(i).strUser).append("|")
				.append(vData.at(i).strPass).append("|")
				.append(vData.at(i).strRegion).append("\r\n");
		
		if (this->File->write(reinterpret_cast<const byte*>(strTmp.c_str()), strTmp.size(), m_dwOffset))
			continue;		

		m_dwLastError = GetLastError();

		return false;
	}

	return true;
}