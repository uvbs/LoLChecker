/* Author: S3RB31  */

#include <winhttp.h>
#include <wincrypt.h>

#pragma once
#pragma comment(lib, "winhttp.lib")
#pragma comment(lib, "crypt32.lib")

#pragma warning(disable:4786)

#include <string>

class CHTTP
{
public:


	CHTTP();
	~CHTTP();

	bool Open();
	bool Connect(std::wstring strServerName, int iPort);
	bool SendRequest(std::wstring strVerb, std::wstring strObj, std::wstring strHeader, std::string strBody);

	std::basic_string<byte> GetResponse();
	std::wstring GetResponseHeader();
	int GetLastErrorCode() { return this->lastErrorCode; }
	bool IsOpen() { return this->hInternet > 0; }

	void SetAgentName(std::wstring &strAgentName) { this->strAgentName = strAgentName; }
	void SetFlags(int flags, bool bAdd) { bAdd ? this->iFlags = this->iFlags | flags : this->iFlags = flags; }

private:

	HINTERNET hInternet;
	HINTERNET hRequest;
	HINTERNET hSession;
	
	std::wstring strAgentName;

	int iFlags;
	int lastErrorCode;
};