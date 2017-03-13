using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace aspnetcsharp.WebForm
{
    public partial class SendSmsMsg : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if(!this.IsPostBack)
            {
                this.appid.Text = "7ad27c449a214e25baf554d385808b7c";
                this.appkey.Text = "eba0bbe07e544293a05481b813a5b149";
                this.mobile.Text = "18621991588";
                this.extno.Text = "88";
                this.msg.Text = "短信内容！！";
            }
        }
        protected void Button1_Click(object sender, EventArgs e)
        {
            string varappid = this.appid.Text.Trim();
            string varappkey = this.appkey.Text.Trim();
            string varmobile = this.mobile.Text.Trim();
            string varextno = this.extno.Text.Trim();
            string varmsg = this.msg.Text.Trim();
            string apiurlx = this.apiurl.Text.Trim();
            string ret = IkyunApiHelper.SendMsg(apiurlx, varappid, varappkey, varmobile, varextno, varmsg);
            this.TextBox1.Text = ret;
        }
    }
}