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
	int GetLastErrorCode() { return m_lastErrorCode; }
	bool IsOpen() { return this->m_hInternet > 0; }

	void SetAgentName(std::wstring &strAgentName) { m_strAgentName = strAgentName; }
	void SetFlags(int flags, bool bAdd) { bAdd ? m_iFlags = m_iFlags | flags : m_iFlags = flags; }

private:

	HINTERNET m_hInternet;
	HINTERNET m_hRequest;
	HINTERNET m_hSession;
	
	std::wstring m_strAgentName;

	int m_iFlags;
	int m_lastErrorCode;
};