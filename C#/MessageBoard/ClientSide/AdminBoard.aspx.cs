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

public partial class AdminBoard : System.Web.UI.Page
{
    private static int x;
    private static int y;
    public void Show(int x, int y)
    {
        localhost.Service s = new localhost.Service();
        DataSet ds = new DataSet();
        switch (y)
        {
            case 0:
                ds = s.GetAllMessages(x);
                break;
            case 1:
                ds = s.GetCheckedMessages(x);
                break;
            case 2:
                ds = s.GetUnCheckedMessages(x);
                break;
            case 3:
                ds = s.GetDeletedMessages(x);
                break;
            case 4:
                ds = s.GetDraftMessages(x);
                break;
        }
        dtl1.DataSource = ds;
        dtl1.DataBind();
        BtnCng();
        Color();
        Board();
        Date();
    }
    protected void Page_Load(object sender, EventArgs e)
    {
        if (Session["Rank"] == null)
            Response.Redirect("SignIn.aspx");
        if (!Session["Rank"].Equals("1"))
            Response.Redirect("SignIn.aspx");
        if (Page.IsPostBack == false)
        {
            x = -1;
            y = -1;
        }
    }
    protected void ddl1_SelectedIndexChanged(object sender, EventArgs e)
    {
        if (ddl1.SelectedIndex != 4)
        {
            x = ddl1.SelectedIndex;
            ddl2.Enabled = true;
        }
    }
    protected void ddl2_SelectedIndexChanged(object sender, EventArgs e)
    {
        if (ddl2.SelectedIndex != 5)
        {
            y = ddl2.SelectedIndex;
            Show(x, y);
        }
    }
    protected void dtl1_ItemCommand(object sender, DataListCommandEventArgs e)
    {
        if (e.CommandArgument.ToString().Equals("chk"))
        {
            localhost.Service s = new localhost.Service();
            s.EditMessageStatus(((Label)dtl1.Items[e.Item.ItemIndex].FindControl("lbl_user")).Text, ((Label)dtl1.Items[e.Item.ItemIndex].FindControl("lbl_msg")).Text, 1);
            Show(x, y);
        }
        if (e.CommandArgument.ToString().Equals("del"))
        {
            localhost.Service s = new localhost.Service();
            s.EditMessageStatus(((Label)dtl1.Items[e.Item.ItemIndex].FindControl("lbl_user")).Text, ((Label)dtl1.Items[e.Item.ItemIndex].FindControl("lbl_msg")).Text, 0);
            Show(x, y);
        }
        if (e.CommandArgument.ToString().Equals("ret"))
        {
            localhost.Service s = new localhost.Service();
            s.EditMessageStatus(((Label)dtl1.Items[e.Item.ItemIndex].FindControl("lbl_user")).Text, ((Label)dtl1.Items[e.Item.ItemIndex].FindControl("lbl_msg")).Text, 1);
            Show(x, y);
        }
        if (e.CommandArgument.ToString().Equals("del1"))
        {
            localhost.Service s = new localhost.Service();
            s.DeleteMsg(((Label)dtl1.Items[e.Item.ItemIndex].FindControl("lbl_user")).Text, ((Label)dtl1.Items[e.Item.ItemIndex].FindControl("lbl_msg")).Text);
            Response.Write(@"<script language='javascript'>alert('הודעה נמחקה בהצלחה!');</script>");
            Show(x, y);
        }
    }
    protected void BtnCng()
    {
        localhost.Service s = new localhost.Service();
        foreach (DataListItem item in dtl1.Items)
        {
            DataSet ds = s.GetMsgStatus(((Label)item.FindControl("lbl_user")).Text, ((Label)item.FindControl("lbl_msg")).Text);
            if (ds.Tables[0].Rows[0][0].ToString() == "-1")
            {
                ((Button)item.FindControl("btn_chk")).Visible = true;
            }
            if (ds.Tables[0].Rows[0][0].ToString() == "0")
            {
                ((Button)item.FindControl("btn_del")).Visible = false;
                ((Button)item.FindControl("btn_ret")).Visible = true;
                ((Label)item.FindControl("lbl_del1")).Visible = true;
                ((Button)item.FindControl("btn_del1")).Visible = true;
            }
            if ((ds.Tables[0].Rows[0][0].ToString() == "-2"))
            {
                ((Button)item.FindControl("btn_del")).Visible = false;
                ((Label)item.FindControl("lbl_draft")).Visible=true;
            }
        }
    }
    protected void Color()
    {
        foreach (DataListItem item in dtl1.Items)
        {
            string w = ((Label)item.FindControl("lbl_user")).Text;
            localhost.Service s = new localhost.Service();
            string rank = s.GetRank(w);
            if (rank.Equals("1"))
                ((Label)item.FindControl("lbl_user")).ForeColor = System.Drawing.Color.Red;
            if (rank.Equals("2"))
                ((Label)item.FindControl("lbl_user")).ForeColor = System.Drawing.Color.Blue;
            if (rank.Equals("3"))
                ((Label)item.FindControl("lbl_user")).ForeColor = System.Drawing.Color.DarkGreen;
        }
    }
    protected void Board()
    {
        foreach (DataListItem item in dtl1.Items)
        {
            string b = ((Label)item.FindControl("lbl_board")).Text;
            if (b.Equals("1"))
                ((Label)item.FindControl("lbl_board")).Text = "מורים";
            if (b.Equals("2"))
                ((Label)item.FindControl("lbl_board")).Text = "תלמידים";
        }
    }
    protected void Date()
    {
        foreach (DataListItem item in dtl1.Items)
        {
            if (((Label)item.FindControl("lbl_EnDate")).Text.Equals("0"))
                ((Label)item.FindControl("lbl_EnDate")).Text = "לא מוגבל";
        }
    }
}
