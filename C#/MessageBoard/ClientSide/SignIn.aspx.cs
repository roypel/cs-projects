using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.HtmlControls;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Xml.Linq;

public partial class SignIn : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void btn_log_Click(object sender, EventArgs e)
    {
        if (Page.IsValid == true)
        {
            localhost.Service CheckUser = new localhost.Service();
            if (CheckUser.SearchSigned(txt_user.Text, txt_pass.Text))
            {
                Session["User"] = txt_user.Text;
                Session["Rank"] = CheckUser.GetRank(txt_user.Text);
                Response.Redirect("Home.aspx");
            }
            Response.Write(@"<script language='javascript'>alert('שם משתמש או סיסמא לא נכונים');</script>");
            Response.Write(@"<script language='javascript'>if(confirm('להרשמה')){document.location='SignUp.aspx'};</script>");
        }
    }
    protected void btn_sign_Click(object sender, EventArgs e)
    {
        Response.Redirect("SignUp.aspx");
    }
}
