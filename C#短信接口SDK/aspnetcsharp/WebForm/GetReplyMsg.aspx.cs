using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace aspnetcsharp.WebForm
{
    public partial class GetReplyMsg : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if (!this.IsPostBack)
            {
                this.appid.Text = "7ad27c449a214e25baf554d385808b7c";
                this.appkey.Text = "eba0bbe07e544293a05481b813a5b149";
            }

        }
        protected void Button1_Click(object sender, EventArgs e)
        {
            string varappid = this.appid.Text.Trim();
            string varappkey = this.appkey.Text.Trim();
            string apiurlx = this.apiurl.Text.Trim();
            string ret = IkyunApiHelper.GetReplyMsg(apiurlx, varappid, varappkey);
            this.TextBox1.Text = ret;
        }
    }
}