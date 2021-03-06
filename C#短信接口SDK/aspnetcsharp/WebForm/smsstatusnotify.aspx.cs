﻿using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace aspnetcsharp.WebForm
{
    public partial class smsstatusnotify : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            BinaryReader reader = new BinaryReader(Request.InputStream);
            byte[] bts = reader.ReadBytes(Request.ContentLength);
            string msg = System.Text.Encoding.UTF8.GetString(bts);
            Newtonsoft.Json.Linq.JObject jo = Newtonsoft.Json.Linq.JObject.Parse(msg);
            string ac = jo.Value<string>("ac");
            Newtonsoft.Json.Linq.JArray jarr = (Newtonsoft.Json.Linq.JArray)(jo["data"]);
            foreach(var jt in jarr)
            {
                string msgid = jt.Value<string>("msgid");
                string errorcode = jt.Value<string>("errorcode");
                string errormsg = jt.Value<string>("errormsg"); 
            }
            Response.Write("0");
        }
    }
}