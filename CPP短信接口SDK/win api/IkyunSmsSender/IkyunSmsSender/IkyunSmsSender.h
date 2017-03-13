// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the IKYUNSMSSENDER_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// IKYUNSMSSENDER_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef IKYUNSMSSENDER_EXPORTS
#define IKYUNSMSSENDER_API __declspec(dllexport)
#else
#define IKYUNSMSSENDER_API __declspec(dllimport)
#endif
#include <string>
#include <map>
#include <sstream>
#include <Windows.h>
/*
author: ouyang2008,code is free
*/
namespace IkyunApi
{
#if UNICODE
#define TString std::wstring
#define TStringStream std::wstringstream
#else
#define TString std::string
#define TStringStream std::stringstream
#endif
	// This class is exported from the IkyunSmsSender.dll
	class IKYUNSMSSENDER_API CIkyunSmsSender {
	public:
		CIkyunSmsSender(const TString& apiurl, const TString& appid, const TString& appkey);
		// TODO: add your methods here.
	public:
		TString Send(const TString& mobile, const TString& extno, const TString& msg);
		TString GetAmount();
		TString GetReplyMsg();
	protected:
		TString signDigest(const TString& mobile, const TString& timestamp);
		TString md5(const TString& src);
		TString getTimeStamp();
		int convertToUTF8(const wchar_t * pStr, char* data, int len);
		TString convertUtf8ToUnicode(char* pdata, int len);
		TString post(std::map<TString, TString>& params);
	protected:
		TString mApiUrl;
		TString mAppID;
		TString mAppKey;
		TString mHost;
		TString mUri;
	};
}
