#include <windows.h>
#include "CHTTP.h"

CHTTP::CHTTP()
{
	m_strAgentName = L"Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/29.0.1547.76 Safari/537.36";
	m_iFlags = WINHTTP_FLAG_REFRESH;
}

CHTTP::~CHTTP()
{
	if (m_hRequest)
		WinHttpCloseHandle(m_hRequest);

	if (m_hSession)
		WinHttpCloseHandle(m_hSession);

	if (m_hInternet)
		WinHttpCloseHandle(m_hInternet);
		
	m_hInternet = NULL;
	m_hSession = NULL;
	m_hRequest = NULL;
}

bool CHTTP::Open()
{
	this->m_hInternet = WinHttpOpen(this->m_strAgentName.c_str(), WINHTTP_ACCESS_TYPE_NO_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

	if (!this->m_hInternet)
	{
		this->m_lastErrorCode = GetLastError();		
		return false;
	}

	return true;
}

bool CHTTP::Connect(std::wstring strHost, int iPort)
{
	this->m_hSession = WinHttpConnect(this->m_hInternet, strHost.c_str(), iPort, 0);

	if (!this->m_hSession)
	{
		this->m_lastErrorCode = GetLastError();
		return false;
	}

	return true;
}

bool CHTTP::SendRequest(std::wstring strVerb, std::wstring strObj, std::wstring strHeader, std::string strBody)
{
	this->m_hRequest = WinHttpOpenRequest(this->m_hSession, strVerb.c_str(), strObj.c_str(), 0, 0, 0, this->m_iFlags);

	if (this->m_hRequest)
	{
		if (WinHttpSendRequest(this->m_hRequest, strHeader.c_str(), strHeader.length(), const_cast<char*>(strBody.c_str()), strBody.length(), strBody.length(), 0))
			if (WinHttpReceiveResponse(this->m_hRequest, 0))
				return true;
	}

	this->m_lastErrorCode = GetLastError();

	return false;
}

std::basic_string<byte> CHTTP::GetResponse()
{
	DWORD dwSize = 1, dwRead;
	std::basic_string<byte> strResult;
	
	do 
	{
		if (!WinHttpQueryDataAvailable(this->m_hRequest, &dwSize))
		{
			this->m_lastErrorCode = GetLastError();
			break;
		}
		
		if (dwSize)
		{
			byte *pszTmp = new byte[dwSize + 1]();

			if (WinHttpReadData(this->m_hRequest, reinterpret_cast<LPVOID>(pszTmp), dwSize, &dwRead))
				strResult.append(pszTmp, dwRead);

			delete[] pszTmp;
		}
	} 
	while (dwSize != 0);
	
	return strResult;
}

std::wstring CHTTP::GetResponseHeader()
{
	DWORD dwHeaderLen = 0;

	if (!WinHttpQueryHeaders(this->m_hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, 0, &dwHeaderLen, WINHTTP_NO_HEADER_INDEX))
	{
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
		{
			wchar_t *pszHeaders = new wchar_t[dwHeaderLen]();
			
			if (WinHttpQueryHeaders(this->m_hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, pszHeaders, &dwHeaderLen, WINHTTP_NO_HEADER_INDEX))
			{
				std::wstring strOut = pszHeaders;
				delete [] pszHeaders;
				return strOut;
			}

			delete [] pszHeaders;
		}
	}

	return L"";
}