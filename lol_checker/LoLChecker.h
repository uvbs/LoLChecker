#include <windows.h>
#include <string>

#include "CHTTP.h"
#include "CList.h"

#pragma once

std::wstring StringToWString(std::string str);

class CLoLChecker
{
public:

	struct LoginResponse
	{
		std::string strError;
		std::string strSuccess;
	};

	struct CaptchaInfo
	{
		std::string strAnswer;
		std::string strChallange;		
	};

	CLoLChecker();
	~CLoLChecker();

	std::string GetCaptcha();
	LoginResponse CheckLogin(CList::UserData LoginData, std::string strRegion);

	void SetCaptcha(std::string strAnswer) { this->captcha.strAnswer = strAnswer; }
	int GetLastErrorCode() { return this->lastErrorCode; }

private:

	CHTTP *HTTP;
	CaptchaInfo captcha;
	
	int lastErrorCode;	
};




