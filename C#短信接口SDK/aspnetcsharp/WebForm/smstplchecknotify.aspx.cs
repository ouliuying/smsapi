using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace aspnetcsharp.WebForm
{
    public partial class smstplchecknotify : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            BinaryReader reader = new BinaryReader(Request.InputStream);
            byte[] bts = reader.ReadBytes(Request.ContentLength);
            string msg = System.Text.Encoding.UTF8.GetString(bts);
            Newtonsoft.Json.Linq.JObject jo = Newtonsoft.Json.Linq.JObject.Parse(msg);
            string ac = jo.Value<string>("ac");
            Newtonsoft.Json.Linq.JToken data = jo["data"];
            string smstpltag = data.Value<string>("smstpltag");
            string status = data.Value<string>("status"); //0 通过，非0 未通过
            string description = data.Value<string>("description"); //原因
            Response.Write("0");
        }
    }
}