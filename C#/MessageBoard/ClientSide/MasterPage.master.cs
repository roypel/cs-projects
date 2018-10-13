using System;
using System.Collections;
using System.Configuration;
using System.Data;
using System.Linq;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;
using System.Xml.Linq;

public partial class MasterPage : System.Web.UI.MasterPage
{
    protected void Page_Load(object sender, EventArgs e)
    {
        if (Session["User"] == null)
        {
            SignIn.Visible = true;
            SignOut.Visible = false;
        }
        else
        {
            SignOut.Visible = true;
            SignIn.Visible = false;
        }
    }
    protected void SignIn_Click(object sender, EventArgs e)
    {
        Response.Redirect("SignIn.aspx");
    }
    protected void SignOut_Click(object sender, EventArgs e)
    {
        SignIn.Visible = true;
        SignOut.Visible = false;
        Session["User"] = null;
        Session["Rank"] = null;
        Response.Redirect("Home.aspx");
    }
    protected void SignUp_Click(object sender, EventArgs e)
    {
        Response.Redirect("SignUp.aspx");
    }
    protected void Pnl1_Load(object sender, EventArgs e)
    {
        if (Session["Rank"] == null)
        {
            Pnl1.Visible = false;
        }
        else
        {
            if (Session["Rank"].ToString() != "1")
                Pnl1.Visible = true;
        }
    }

    protected void Pnl2_Load(object sender, EventArgs e)
    {
        if (Session["Rank"] == null)
        {
            Pnl2.Visible = false;
        }
        else
        {
            if (Session["Rank"].ToString() == "1")
                Pnl2.Visible = true;
        }
    }
    protected void IB1_Click(object sender, ImageClickEventArgs e)
    {
        //Response.Write(@"<script language='javascript'>location.href='http://www.schooly.co.il/mekif_rl'");
        Response.Redirect("Home.aspx");
    }
    protected void EditDetails_Click(object sender, EventArgs e)
    {
        Response.Redirect("UserEdit.aspx");
    }
    protected void ShowMess_Click(object sender, EventArgs e)
    {
        Response.Redirect("UserMess.aspx");
    }
    protected void AdmBoa_Click(object sender, EventArgs e)
    {
        Response.Redirect("AdminBoard.aspx");
    }
    protected void AdmSea_Click(object sender, EventArgs e)
    {
        Response.Redirect("AdminSearch.aspx");
    }
    protected void AdmEdi_Click(object sender, EventArgs e)
    {
        Response.Redirect("UserEdit.aspx");
    }
    protected void AdmCod_Click(object sender, EventArgs e)
    {
        Response.Redirect("AdminCode.aspx");
    }
    protected void TBoard_Click(object sender, EventArgs e)
    {
        Response.Redirect("TBoard.aspx");
    }
    protected void SBoard_Click(object sender, EventArgs e)
    {
        Response.Redirect("SBoard.aspx");
    }
}