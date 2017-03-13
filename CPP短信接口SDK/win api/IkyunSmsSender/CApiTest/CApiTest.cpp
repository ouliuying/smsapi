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
	 ע�⣺
	 ÿ���û����ύ���Ӳ�ͬ�ģ����뵽�Լ��ʺŵĺ�̨��http://sms.ikyun.net/��
	 ���ʺ����ġ�=>���ҵ���Ϣ��=>��Api�ӿ���Ϣ��
	*/
	context->apiurl = L"http://sms.ikyun.net/apiex/sms/ebpbcons";
	context->appid = L"c0cb7b8ad8e64296a88c99d923345148";
	context->appkey = L"c4d963e9158444b7b71e52fb205eb1c3";
	TCHAR retmsg[2048];
	ZeroMemory(retmsg, 2048 * sizeof(TCHAR));
	TCHAR* msg = L"���ͬѧ���ҿ�ʼ�����ˣ�";
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

