#include <windows.h>
#include "CHTTP.h"

CHTTP::CHTTP()
{
	this->strAgentName = L"Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/29.0.1547.76 Safari/537.36";
	this->iFlags = WINHTTP_FLAG_REFRESH;
}

CHTTP::~CHTTP()
{
	if (this->hRequest)
		WinHttpCloseHandle(this->hRequest);

	if (this->hSession)
		WinHttpCloseHandle(this->hSession);

	if (this->hInternet)
		WinHttpCloseHandle(this->hInternet);
		
	this->hInternet = NULL;
	this->hSession = NULL;
	this->hRequest = NULL;
}

bool CHTTP::Open()
{
	this->hInternet = WinHttpOpen(this->strAgentName.c_str(), WINHTTP_ACCESS_TYPE_NO_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);

	if (!this->hInternet)
	{
		this->lastErrorCode = GetLastError();		
		return false;
	}

	return true;
}

bool CHTTP::Connect(std::wstring strHost, int iPort)
{
	this->hSession = WinHttpConnect(this->hInternet, strHost.c_str(), iPort, 0);

	if (!this->hSession)
	{
		this->lastErrorCode = GetLastError();
		return false;
	}

	return true;
}

bool CHTTP::SendRequest(std::wstring strVerb, std::wstring strObj, std::wstring strHeader, std::string strBody)
{
	this->hRequest = WinHttpOpenRequest(this->hSession, strVerb.c_str(), strObj.c_str(), 0, 0, 0, this->iFlags);

	if (this->hRequest)
	{
		if (WinHttpSendRequest(this->hRequest, strHeader.c_str(), strHeader.length(), const_cast<char*>(strBody.c_str()), strBody.length(), strBody.length(), 0))
			if (WinHttpReceiveResponse(this->hRequest, 0))
				return true;
	}

	this->lastErrorCode = GetLastError();

	return false;
}

std::basic_string<byte> CHTTP::GetResponse()
{
	DWORD dwSize = 1, dwRead;
	std::basic_string<byte> strResult;
	
	do 
	{
		if (!WinHttpQueryDataAvailable(this->hRequest, &dwSize))
		{
			this->lastErrorCode = GetLastError();
			break;
		}
		
		if (dwSize)
		{
			byte *pszTmp = new byte[dwSize + 1]();

			if (WinHttpReadData(this->hRequest, reinterpret_cast<LPVOID>(pszTmp), dwSize, &dwRead))
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

	if (!WinHttpQueryHeaders(this->hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, 0, &dwHeaderLen, WINHTTP_NO_HEADER_INDEX))
	{
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
		{
			wchar_t *pszHeaders = new wchar_t[dwHeaderLen]();
			
			if (WinHttpQueryHeaders(this->hRequest, WINHTTP_QUERY_RAW_HEADERS_CRLF, WINHTTP_HEADER_NAME_BY_INDEX, pszHeaders, &dwHeaderLen, WINHTTP_NO_HEADER_INDEX))
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