using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Web;

namespace aspnetcsharp
{
    public class IkyunApiHelper
    {
        public static string SendMsg(string apiurl,string appid,string appkey,string mobile,string extno,string  msg)
        {
            string timestamp = TimeHelper.GetUnixTimestampFromLocalTime();
            string digest = MD5Hash.HashString(appid + MD5Hash.HashString(appkey) + timestamp+mobile);
            StringBuilder sb = new StringBuilder();
            sb.AppendFormat("ac=sendsms&mobile={0}&extno={1}&appid={2}&digest={3}&timestamp={4}&msg={5}",mobile,extno,appid,digest,timestamp,msg);
            string postdata = sb.ToString();
            string outdata;
            HttpHelper.httpPost(apiurl, postdata, out outdata);
            return outdata;
        }
        public static string GetSmsAmount(string apiurl,string appid,string appkey)
        {
            string timestamp = TimeHelper.GetUnixTimestampFromLocalTime();
            string digest = MD5Hash.HashString(appid + MD5Hash.HashString(appkey) + timestamp);
            string postdata = String.Format("ac=getamount&appid={0}&digest={1}&timestamp={2}", appid, digest, timestamp);
            string outdata;
            HttpHelper.httpPost(apiurl, postdata, out outdata);
            return outdata;
        }
        public static string GetReplyMsg(string apiurl,string appid,string appkey)
        {
            string timestamp = TimeHelper.GetUnixTimestampFromLocalTime();
            string digest = MD5Hash.HashString(appid + MD5Hash.HashString(appkey) + timestamp);
            string postdata = String.Format("ac=fetchreply&appid={0}&digest={1}&timestamp={2}", appid, digest, timestamp);
            string outdata;
            HttpHelper.httpPost(apiurl, postdata, out outdata);
            return outdata;
        }
    }
}