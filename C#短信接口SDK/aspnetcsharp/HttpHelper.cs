using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Net;
using System.Web;

namespace aspnetcsharp
{
    public class HttpHelper
    {
        public static int httpPost(string url, string data, out string result)
        {
            Console.WriteLine(url);
            Console.WriteLine(data);
            HttpWebRequest WebReq = null;
            try
            {
                byte[] bData =System.Text.Encoding.UTF8.GetBytes(data);
                WebReq = (HttpWebRequest)WebRequest.Create(url);
                WebReq.ServicePoint.Expect100Continue = false;
                WebReq.Method = "POST";
                WebReq.ContentType = "application/x-www-form-urlencoded";
                WebReq.ContentLength = bData.Length;
                Stream PostData = WebReq.GetRequestStream();
                PostData.Write(bData, 0, bData.Length);
                PostData.Close();
                HttpWebResponse WebResp = (HttpWebResponse)WebReq.GetResponse();
                Stream Answer = WebResp.GetResponseStream();
                StreamReader _Answer = new StreamReader(Answer, System.Text.Encoding.UTF8);
                result = _Answer.ReadToEnd();
                Answer.Close();
                WebResp.Close();
                return (int)WebResp.StatusCode;
            }
            catch (System.Exception ex)
            {
                if (WebReq != null)
                {
                    WebReq.Abort();
                }
                result = ex.ToString();
                return 0;
            }
        }
    }
}