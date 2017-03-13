#include "stdafx.h"
#include "IkyunSmsSenderC.h"
#include "IkyunSmsSender.h"
using namespace IkyunApi;
int SendSms(IKYunApiContext* context, LPTSTR mobile, LPTSTR extno, LPTSTR msg, TCHAR* retmsg, int tcharcnt)
{
	IkyunApi::CIkyunSmsSender sender(context->apiurl, context->appid, context->appkey);
	std::map<TString, TString> tmsgs;
	TString retmsgx = sender.Send(mobile, extno, msg);
#ifdef UNICODE
	wmemcpy_s(retmsg, tcharcnt,retmsgx.c_str(),retmsgx.size());
#else
	memcpy_s(retmsg, tcharcnt, retmsgx.c_str(), retmsgx.size());
#endif
	if (tcharcnt < retmsgx.size())
	{
		return -1;
	}
	return retmsgx.size();
}
int GetAmount(IKYunApiContext* context, TCHAR* retmsg, int tcharcnt)
{
	IkyunApi::CIkyunSmsSender sender(context->apiurl, context->appid, context->appkey);
	TString retmsgx = sender.GetAmount();
#ifdef UNICODE
	wmemcpy_s(retmsg, tcharcnt, retmsgx.c_str(), retmsgx.size());
#else
	memcpy_s(retmsg, tcharcnt, retmsgx.c_str(), retmsgx.size());
#endif
	if (tcharcnt < retmsgx.size())
	{
		return -1;
	}
	return retmsgx.size();
}
int GetReplyMsg(IKYunApiContext* context, TCHAR* retmsg, int tcharcnt)
{
	IkyunApi::CIkyunSmsSender sender(context->apiurl, context->appid, context->appkey);
	TString retmsgx = sender.GetReplyMsg();
#ifdef UNICODE
	wmemcpy_s(retmsg, tcharcnt, retmsgx.c_str(), retmsgx.size());
#else
	memcpy_s(retmsg, tcharcnt, retmsgx.c_str(), retmsgx.size());
#endif
	if (tcharcnt < retmsgx.size())
	{
		return -1;
	}
	return retmsgx.size();
}