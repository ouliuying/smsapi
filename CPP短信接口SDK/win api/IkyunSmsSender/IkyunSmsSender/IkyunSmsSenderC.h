#ifndef _IKYUN_SMS_SENDER_H
#define _IKYUN_SMS_SENDER_H
#include<windows.h>
struct IKYunApiContext
{
	LPTSTR apiurl;
	LPTSTR appid;
	LPTSTR appkey;
};
extern "C" int SendSms(IKYunApiContext* context, LPTSTR mobile, LPTSTR extno, LPTSTR msg,  TCHAR* retmsg, int tcharcnt);
extern "C" int GetAmount(IKYunApiContext* context, TCHAR* retmsg, int tcharcnt);
extern "C" int GetReplyMsg(IKYunApiContext* context, TCHAR* retmsg, int tcharcnt);
#endif