/* Author: S3RB31  */
#include <windows.h>

#pragma once

class FileIO
{

private:

	HANDLE hFile;
	const char *pName;

	DWORD dwError;
	DWORD dwAccess, dwMode;
	DWORD dwShareMode, dwFlags;

public:

	~FileIO();
	FileIO(const char *pName, DWORD dwAccess, DWORD dwMode, DWORD dwShareMode = 0, DWORD dwFlags = 0);

	bool open();
	void close();

	bool read(BYTE *pData, DWORD dwBufSize, DWORD &dwPos);
	bool write(const BYTE *pData, DWORD dwBufSize, DWORD &dwPos);

	size_t getSize();
	DWORD getError();
};
