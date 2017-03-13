// CppTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include"../IkyunSmsSender/IkyunSmsSender.h"
#include<string>
#include<io.h>
#include<iostream>
#include <fcntl.h>
#pragma comment(lib, "../lib/IkyunSmsSender.lib")
int _tmain(int argc, _TCHAR* argv[])
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	/*
	注意：
	每个用户的提交连接不同的，必须到自己帐号的后台【http://sms.ikyun.net/】
	【帐号中心】=>【我的信息】=>【Api接口信息】
	*/
	IkyunApi::CIkyunSmsSender sender(L"http://sms.ikyun.net/apiex/sms/ebpbcons", L"c0cb7b8ad8e64296a88c99d923345148", L"c4d963e9158444b7b71e52fb205eb1c3");
	std::wstring msg = L"你好，中文!!";
	std::wcout << L"你好，中文"<<std::endl;
	std::wstring retmsg=sender.Send(L"186219915xx,186219915yy", L"88", msg);
	std::wcout << retmsg<<std::endl;
	retmsg = sender.GetAmount();
	std::wcout << retmsg << std::endl;
	retmsg = sender.GetReplyMsg();
	std::wcout << retmsg << std::endl;
	std::wstring wait;
	std::wcin >> wait;
	return 0;
}

