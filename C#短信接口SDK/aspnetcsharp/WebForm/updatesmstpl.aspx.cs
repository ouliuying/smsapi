﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Web;
using System.Web.UI;
using System.Web.UI.WebControls;

namespace aspnetcsharp.WebForm
{
    public partial class updatesmstpl : System.Web.UI.Page
    {
        protected void Page_Load(object sender, EventArgs e)
        {
            if(!this.IsPostBack)
            {
                this.appid.Text = "7ad27c449a214e25baf554d385808b7c";
                this.appkey.Text = "eba0bbe07e544293a05481b813a5b149";
                this.smstpl.Text = "尊敬的{{公司}}的{{客户姓名}}{{职位}}，您申请开通爱客云短信的申请已经被接受，我们客服将在您接收到短信后联系您，谢谢！";
                this.smstpltag.Text = "d8299b3eca7048bbbc2e7e55bb90737f";
            }
           
        }

        protected void Button1_Click(object sender, EventArgs e)
        {
            string varappid = this.appid.Text.Trim();
            string varappkey = this.appkey.Text.Trim();
            string varsmstpl = this.smstpl.Text.Trim();
            string varsmstpltag = this.smstpltag.Text.Trim();
        }
    }
}