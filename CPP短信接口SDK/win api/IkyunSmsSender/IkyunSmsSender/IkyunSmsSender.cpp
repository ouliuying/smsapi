// IkyunSmsSender.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "IkyunSmsSender.h"
#include <Wincrypt.h>
#include <Windows.h>
#include <comutil.h>
#include <winhttp.h>
#include <algorithm>
#include <regex>
#include <iostream>
#include <cctype>
#include <iomanip>
#include <sstream>
/*
author: ouyang2008,code is free
*/
namespace IkyunApi
{

	CIkyunSmsSender::CIkyunSmsSender(const TString& apiurl, const TString& appid, const TString& appkey)
		:mApiUrl(apiurl), mAppID(appid), mAppKey(appkey)
	{
		size_t pos = 0;
		TString tapiurl(apiurl);
		std::transform(tapiurl.begin(), tapiurl.end(), tapiurl.begin(), ::tolower);

#ifdef UNICODE
		//TString tapiurl(apiurl);
		pos=tapiurl.find_first_of(L"http://");
		tapiurl = tapiurl.substr(7);
		pos = tapiurl.find_first_of(L"/");
		this->mHost = tapiurl.substr(0, pos);
		this->mUri = tapiurl.substr(pos);
#else
		TString tapiurl(apiurl);
		pos = tapiurl.find_first_of("http://");
		tapiurl = tapiurl.substr(7);
		pos = tapiurl.find_first_of("/");
		this->mHost = tapiurl.substr(0, pos);
		this->mUri = tapiurl.substr(pos);
#endif
		
	}
	TString CIkyunSmsSender::Send(const TString& mobile, const TString& extno, const TString& msg)
	{
		TString timestamp = this->getTimeStamp();
		TString digest = this->signDigest(mobile, timestamp);
		std::wcout << digest << std::endl;
		std::map<TString, TString> params;
		params[TEXT("ac")] = TEXT("sendsms");
		params[TEXT("mobile")] = mobile;
		params[TEXT("extno")] = extno;
		params[TEXT("msg")] = msg;
		params[TEXT("appid")] = this->mAppID;
		params[TEXT("digest")] = digest;
		params[TEXT("timestamp")] = timestamp;
		return this->post(params);
	}

	TString CIkyunSmsSender::GetAmount()
	{
		TString timestamp = this->getTimeStamp();
		TString digest = this->signDigest(TEXT(""), timestamp);
		std::wcout << digest << std::endl;
		std::map<TString, TString> params;
		params[TEXT("ac")] = TEXT("getamount");
		params[TEXT("appid")] = this->mAppID;
		params[TEXT("digest")] = digest;
		params[TEXT("timestamp")] = timestamp;
		return this->post(params);
	}
	TString CIkyunSmsSender::GetReplyMsg()
	{
		TString timestamp = this->getTimeStamp();
		TString digest = this->signDigest(TEXT(""), timestamp);
		std::wcout << digest << std::endl;
		std::map<TString, TString> params;
		params[TEXT("ac")] = TEXT("fetchreply");
		params[TEXT("appid")] = this->mAppID;
		params[TEXT("digest")] = digest;
		params[TEXT("timestamp")] = timestamp;
		return this->post(params);
	}

	TString CIkyunSmsSender::post(std::map<TString, TString>& params)
	{
		DWORD dwSize = 0;
		DWORD dwDownloaded = 0;
		LPSTR pszOutBuffer;
		BOOL  bResults = FALSE;
		HINTERNET  hSession = NULL,
			hConnect = NULL,
			hRequest = NULL;

		// Use WinHttpOpen to obtain a session handle.
		hSession = WinHttpOpen(L"IKYun.NET API/1.0",
			WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
			WINHTTP_NO_PROXY_NAME,
			WINHTTP_NO_PROXY_BYPASS, 0);

		// Specify an HTTP server.
		if (hSession)
			hConnect = WinHttpConnect(hSession, _bstr_t(this->mHost.c_str()),
			INTERNET_DEFAULT_HTTP_PORT,0);

		// Create an HTTP request handle.
		if (hConnect)
			hRequest = WinHttpOpenRequest(hConnect, L"POST", _bstr_t(this->mUri.c_str()),
			NULL, WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,0);

		// Send a request.
		//std::wstring header = L"Content-Type: application/x-www-form-urlencoded;charset=utf8;\r\n";
		std::map<TString, TString>::iterator itend = params.end();
		std::wstring pdata;
		bool firstflag = true;
		for (std::map<TString, TString>::iterator it = params.begin(); it != itend; it++)
		{
			if (!firstflag)
			{
				pdata.append(L"&");
				pdata.append(_bstr_t(it->first.c_str()));
				pdata.append(L"=");
				pdata.append(_bstr_t(it->second.c_str()));
			}
			else
			{
				firstflag = false;
				pdata.append(std::wstring(_bstr_t((it->first).c_str())));
				pdata.append(L"=");
				pdata.append(_bstr_t(it->second.c_str()));
			}
		}
		if (pdata.empty())
		{
			if (hRequest)
				bResults = WinHttpSendRequest(hRequest,
				WINHTTP_NO_ADDITIONAL_HEADERS, 0,
				WINHTTP_NO_REQUEST_DATA, 0,
				0, 0);
		}
		else
		{
			int dlen = pdata.length() * 6;
			char* data = new char[dlen];
			ZeroMemory(data, dlen);
			int len = this->convertToUTF8(pdata.c_str(), data, dlen);
			if (len > 0)
			{
				std::wstringstream strlen;
				strlen.imbue(std::locale("C"));
				strlen << len;
				std::wstring header = std::wstring(L"content-type:application/x-www-form-urlencoded;charset=utf-8;\r\n");
				if (hRequest)
					bResults = WinHttpSendRequest(hRequest,
					header.c_str(), -1,
					data, len , len, 0);
			}
			else
			{
				if (hRequest)
					bResults = WinHttpSendRequest(hRequest,
					WINHTTP_NO_ADDITIONAL_HEADERS, 0,
					WINHTTP_NO_REQUEST_DATA, 0,
					0, 0);
			}
		}

		// End the request.
		if (bResults)
			bResults = WinHttpReceiveResponse(hRequest, NULL);
		std::string retmsg;
		// Keep checking for data until there is nothing left.
		if (bResults)
		{
			do
			{
				// Check for available data.
				dwSize = 0;
				if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
					printf("Error %u in WinHttpQueryDataAvailable.\n",
					GetLastError());

				// Allocate space for the buffer.
				pszOutBuffer = new char[dwSize + 1];
				ZeroMemory(pszOutBuffer, dwSize + 1);
				if (!pszOutBuffer)
				{
					printf("Out of memory\n");
					dwSize = 0;
				}
				else
				{
					// Read the data.
					ZeroMemory(pszOutBuffer, dwSize + 1);

					if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,
						dwSize, &dwDownloaded))
						printf("Error %u in WinHttpReadData.\n", GetLastError());

					retmsg.append(std::string(pszOutBuffer));
					delete[] pszOutBuffer;
				}
			} while (dwSize > 0);
		}


		// Report any errors.
		if (!bResults)
			//printf("Error %d has occurred.\n", GetLastError());

		// Close any open handles.
		if (hRequest) WinHttpCloseHandle(hRequest);
		if (hConnect) WinHttpCloseHandle(hConnect);
		if (hSession) WinHttpCloseHandle(hSession);
		return this->convertUtf8ToUnicode((char*)retmsg.c_str(), retmsg.length());
	}
	TString CIkyunSmsSender::signDigest(const TString& mobile, const TString& timestamp)
	{
		TString appkeydigest = this->md5(this->mAppKey);
		return this->md5(this->mAppID + appkeydigest + timestamp + mobile);
	}
	int CIkyunSmsSender::convertToUTF8(const wchar_t * pStr, char* data, int len) {
		 return ::WideCharToMultiByte(CP_UTF8, 0, pStr, _bstr_t(pStr).length(), data, len, NULL, NULL);
	}
	TString CIkyunSmsSender::convertUtf8ToUnicode(char* pdata,int len)
	{
		int wchars_num = MultiByteToWideChar(CP_UTF8, 0, pdata, len, NULL, 0);
		wchar_t* wstr = new wchar_t[wchars_num+10];
		ZeroMemory(wstr, (wchars_num + 10) * 2);
		MultiByteToWideChar(CP_UTF8, 0, pdata, len, wstr, wchars_num);
		// do whatever with wstr
		TString str = (_bstr_t(wstr));
		delete[] wstr;
		return str;
	}
	TString CIkyunSmsSender::md5(const TString& src)
	{
		DWORD dwStatus = 0;
		DWORD cbHash = 16;
		int i = 0;
		HCRYPTPROV cryptProv;
		HCRYPTHASH cryptHash;
		BYTE hash[16];
		TCHAR *hex = TEXT("0123456789abcdef");
		int srclen = src.length();
		char* data = new char[srclen * 4];
		int len = 0;
		if ((len = convertToUTF8(_bstr_t(src.c_str()), data, srclen * 4)) < 1)
			return TEXT("");
		if (!CryptAcquireContext(&cryptProv, NULL, MS_DEF_PROV, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
		{
			return TEXT("");
		}
		if (!CryptCreateHash(cryptProv, CALG_MD5, 0, 0, &cryptHash))
		{
			dwStatus = GetLastError();
			printf("CryptCreateHash failed: %d\n", dwStatus);
			CryptReleaseContext(cryptProv, 0);
			return TEXT("");
		}
		if (!CryptHashData(cryptHash, (BYTE*)data, len, 0))
		{
			dwStatus = GetLastError();
			printf("CryptHashData failed: %d\n", dwStatus);
			CryptReleaseContext(cryptProv, 0);
			CryptDestroyHash(cryptHash);
			return TEXT("");
		}
		if (!CryptGetHashParam(cryptHash, HP_HASHVAL, hash, &cbHash, 0))
		{
			dwStatus = GetLastError();
			printf("CryptGetHashParam failed: %d\n", dwStatus);
			CryptReleaseContext(cryptProv, 0);
			CryptDestroyHash(cryptHash);
			return TEXT("");
		}
		TString res;
		for (i = 0; i < cbHash; i++)
		{
			res.push_back(hex[hash[i] >> 4]);
			res.push_back(hex[hash[i] & 0xF]);
		}
		CryptReleaseContext(cryptProv, 0);
		CryptDestroyHash(cryptHash);
		return res;
	}
	TString CIkyunSmsSender::getTimeStamp()
	{
		SYSTEMTIME lt;
		GetLocalTime(&lt);
		SYSTEMTIME utc;
		TzSpecificLocalTimeToSystemTime(NULL, &lt, &utc);
		FILETIME ft;
		SystemTimeToFileTime(&utc, &ft);
		LARGE_INTEGER date, adjust;
		date.HighPart = ft.dwHighDateTime;
		date.LowPart = ft.dwLowDateTime;
		adjust.QuadPart = 11644473600000 * 10000;
		date.QuadPart -= adjust.QuadPart;
		TStringStream xdor;
		xdor.imbue(std::locale("C"));
		long timestamp = (date.QuadPart / 10000000);
		xdor << timestamp;
		return  xdor.str();
	}
}
