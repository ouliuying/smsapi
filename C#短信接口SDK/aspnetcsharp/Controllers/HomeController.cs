using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Web;
using System.Web.Mvc;

namespace aspnetcsharp.Controllers
{
    public class HomeController : Controller
    {
        public ActionResult Index()
        {
            return View();
        }
        public ActionResult GetReplyMsg()
        {
            return View();
        }
        public ActionResult GetReplyMsgImp()
        {
            string appid = this.Request["appid"];
            string appkey = this.Request["appkey"];
            string apiurl = this.Request["apiurl"];
            string ret = IkyunApiHelper.GetReplyMsg(apiurl, appid, appkey);
            return Content(ret);
        }
        public ActionResult SendSmsMsg()
        {
            return View();
        }
        public ActionResult SendSmsMsgimp()
        {
            string appid = this.Request["appid"];
            string appkey = this.Request["appkey"];
            string mobile = this.Request["mobile"];
            string extno = this.Request["extno"];
            string msgx = this.Request["msg"];
            string apiurl = this.Request["apiurl"];
            string ret = IkyunApiHelper.SendMsg(apiurl,appid, appkey, mobile, extno, msgx);
            return Content(ret);
        }
        public ActionResult GetAmount()
        {
            return View();
        }
        public ActionResult GetAmountimp()
        {
            string appid = this.Request["appid"];
            string appkey = this.Request["appkey"];
            string apiurl = this.Request["apiurl"];
            string ret = IkyunApiHelper.GetSmsAmount(apiurl,appid, appkey);
            return Content(ret);
        }
        public ActionResult smstplchecknotify()  //其他接收，参考此方法
        {
            BinaryReader reader = new BinaryReader(Request.InputStream);
            byte[] bts = reader.ReadBytes(Request.ContentLength);
            string msg = System.Text.Encoding.UTF8.GetString(bts);
            Newtonsoft.Json.Linq.JObject jo = Newtonsoft.Json.Linq.JObject.Parse(msg);
            string ac = jo.Value<string>("ac");
            Newtonsoft.Json.Linq.JArray jarr = (Newtonsoft.Json.Linq.JArray)(jo["data"]);
            foreach (var jt in jarr)
            {
                string msgid = jt.Value<string>("msgid");
                string errorcode = jt.Value<string>("errorcode");
                string errormsg = jt.Value<string>("errormsg");
            }
            return Content("0");
        }
    }
}