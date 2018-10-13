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

public partial class UserMess : System.Web.UI.Page
{
    protected void Show()
    {
        localhost.Service my_Serv = new localhost.Service();
        DataSet ds=my_Serv.GetUserMess(Session["User"].ToString());
        if (ds==null)
        {
            Response.Write(@"<script language='javascript'>alert('לא נמצאו הודעות');</script>");
        }
        else
        {
            dtl1.DataSource = ds;
            dtl1.DataBind();
            MsgStatus();
        }
    }
    protected void Page_Load(object sender, EventArgs e)
    {
        if (Session["User"] == null)
            Response.Redirect("SignIn.aspx");
        Show();
    }
    protected void MsgStatus()
    {
        foreach (DataListItem item in dtl1.Items)
        {
            string stat;
            stat=((Label)item.FindControl("lbl_status")).Text;
            if (stat.Equals("-2"))
            {
                ((Label)item.FindControl("lbl_status")).Text = "טיוטה";
                ((LinkButton)item.FindControl("lb2")).Visible = true;
                ((LinkButton)item.FindControl("lb3")).Visible = true;
            }
            if (stat.Equals("-1"))
            {
                ((Label)item.FindControl("lbl_status")).Text = "טרם אושרה";
            }
            if (stat.Equals("0"))
            {
                ((Label)item.FindControl("lbl_status")).Text = "נמחקה";
            }
            if (stat.Equals("1"))
            {
                ((Label)item.FindControl("lbl_status")).Text = "מופיעה";
                ((LinkButton)item.FindControl("lb1")).Visible = true;
            }
        }
    }
    protected void dtl1_ItemCommand(object source, DataListCommandEventArgs e)
    {
        if (e.CommandArgument.ToString().Equals("del"))
        {
            localhost.Service s = new localhost.Service();
            s.EditMessageStatus(((Label)e.Item.FindControl("lbl_user")).Text, ((Label)e.Item.FindControl("lbl_msg")).Text, 0);
            Show();
        }
        if (e.CommandArgument.ToString().Equals("dra"))
        {
            localhost.Service s = new localhost.Service();
            s.EditMessageStatus(((Label)e.Item.FindControl("lbl_user")).Text, ((Label)e.Item.FindControl("lbl_msg")).Text, -1);
            Show();
        }
        if (e.CommandArgument.ToString().Equals("sen"))
        {
            Session["Draft"] = (((Label)e.Item.FindControl("lbl_msg")).Text);
            Response.Redirect("NewMsg.aspx");
        }
    }
}
