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

public partial class AdminCode : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (Session["Rank"] == null)
            Response.Redirect("SignIn.aspx");
        if (!Session["Rank"].Equals("1"))
            Response.Redirect("SignIn.aspx");
    }
    protected void lbl_now_Load(object sender, EventArgs e)
    {
        lbl_now.Text = Application["Code"].ToString();
    }
    protected void btn_rep_Click(object sender, EventArgs e)
    {
        lbl_rep.Visible = false;
        btn_rep.Visible = false;
        lbl_pas.Visible = true;
        txt_pas.Visible = true;
        lbl_new.Visible = true;
        txt_new.Visible = true;
        btn_can.Visible = true;
        btn_exe.Visible = true;
    }
    protected void btn_exe_Click(object sender, EventArgs e)
    {
        if (Page.IsValid == true)
        {
            localhost.Service serv = new localhost.Service();
            if (serv.CheckPass(Session["User"].ToString(), txt_pas.Text))
            {
                Application["Code"] = txt_new.Text;
                Response.Write(@"<script language='javascript'>alert('הקוד שונה בהצלחה');document.location='Home.aspx';</script>");
            }
            else
                Response.Write(@"<script language='javascript'>alert('סיסמתך לא נכונה, קוד לא השתנה');</script>");
        }
    }
    protected void btn_can_Click(object sender, EventArgs e)
    {
        lbl_rep.Visible = true;
        btn_rep.Visible = true;
        lbl_pas.Visible = false;
        txt_pas.Text = string.Empty;
        txt_pas.Visible = false;
        lbl_new.Visible = false;
        txt_new.Text = string.Empty;
        txt_new.Visible = false;
        btn_exe.Visible = false;
        btn_can.Visible = false;
    }
}
