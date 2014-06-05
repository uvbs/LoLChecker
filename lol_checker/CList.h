/* Author: S3RB31 */

#include <string>
#include <deque>

#include "FileIO.h"

#pragma once

class CList
{
public:
	
	

	struct UserData
	{
		std::string strUser;
		std::string strPass;
		std::string strRegion;
	};

	int GetSize() { return m_dwSize; }
	int GetLastErrorCode() { return m_dwLastError; }
	
protected:

	CList(const char *pszPath);
	~CList();
	
	FileIO *File;

	DWORD m_dwSize;
	DWORD m_dwOffset;
	DWORD m_dwLastError;
};

class CListIn : public CList
{
public:

	CListIn(const char *pszPath);
	std::deque<UserData> GetChunk(int iChunkSize);
};

class CListOut : public CList
{
public:

	CListOut(const char *pszPath);
	bool WriteList(std::deque<UserData> &vData);
};