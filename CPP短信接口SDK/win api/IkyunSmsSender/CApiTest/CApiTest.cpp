// CApiTest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <fcntl.h>
#include<io.h>
#include "../IkyunSmsSender/IkyunSmsSenderC.h"
#pragma comment(lib, "../lib/IkyunSmsSender.lib")
int _tmain(int argc, _TCHAR* argv[])
{
	_setmode(_fileno(stdout), _O_U16TEXT);
	IKYunApiContext* context = new IKYunApiContext;
	/*
	 注意：
	 每个用户的提交连接不同的，必须到自己帐号的后台【http://sms.ikyun.net/】
	 【帐号中心】=>【我的信息】=>【Api接口信息】
	*/
	context->apiurl = L"http://sms.ikyun.net/apiex/sms/ebpbcons";
	context->appid = L"c0cb7b8ad8e64296a88c99d923345148";
	context->appkey = L"c4d963e9158444b7b71e52fb205eb1c3";
	TCHAR retmsg[2048];
	ZeroMemory(retmsg, 2048 * sizeof(TCHAR));
	TCHAR* msg = L"你好同学，我开始发功了！";
	int count = SendSms(context, L"186219915xx,186219915yy", L"88", msg, retmsg, 2048);
	wprintf(retmsg);
	wprintf(L"\n");
	ZeroMemory(retmsg, 2048 * sizeof(TCHAR));
	count = GetAmount(context, retmsg, 2048);
	wprintf(retmsg);
	wprintf(L"\n");
	TCHAR* bigretmsg = new TCHAR[204800];
	ZeroMemory(bigretmsg, 204800 * sizeof(TCHAR));
	count = GetReplyMsg(context, bigretmsg, 2004800);
	wprintf(bigretmsg);
	wprintf(L"\n");
	delete context;
	delete[] bigretmsg;
	return 0;
}

