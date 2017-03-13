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
	ע�⣺
	ÿ���û����ύ���Ӳ�ͬ�ģ����뵽�Լ��ʺŵĺ�̨��http://sms.ikyun.net/��
	���ʺ����ġ�=>���ҵ���Ϣ��=>��Api�ӿ���Ϣ��
	*/
	IkyunApi::CIkyunSmsSender sender(L"http://sms.ikyun.net/apiex/sms/ebpbcons", L"c0cb7b8ad8e64296a88c99d923345148", L"c4d963e9158444b7b71e52fb205eb1c3");
	std::wstring msg = L"��ã�����!!";
	std::wcout << L"��ã�����"<<std::endl;
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

