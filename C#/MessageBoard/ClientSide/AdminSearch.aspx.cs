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

public partial class AdminSearch : System.Web.UI.Page
{
    private static int index = -1;
    private static int appind = -1;
    private static int y;
    public void Show(int y)
    {
        DataSet ds = new DataSet();

        localhost.Service s = new localhost.Service();

        int x = int.Parse(ddl1.SelectedValue.ToString());

        if (y == 1)
        {
            ds = s.SearchUser(txt1.Text);
        }

        if (y == 2)
        {
            ds = s.GetUsers(x);
        }

        for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
        {
            if (ds.Tables[0].Rows[i][0].ToString().Equals(Session["User"].ToString()))
                ds.Tables[0].Rows.Remove(ds.Tables[0].Rows[i]);
        }
        if (ds.Tables[0].Rows.Count==0)
            ds = null;

        if (ds == null)
        {
            Response.Write(@"<script language='javascript'>alert('לא נמצאו משתמשים');</script>");
        }

        gr1.DataSource = ds;

        gr1.DataBind();

    }
    protected void Page_Load(object sender, EventArgs e)
    {
        if (Session["Rank"] == null)
            Response.Redirect("SignIn.aspx");
        if (!Session["Rank"].Equals("1"))
            Response.Redirect("SignIn.aspx");
        if (Page.IsPostBack == false)
        {
            index = -1;
            y = 0;
            appind = -1;
        }
    }
    protected void btn_ShowAll_Click(object sender, EventArgs e)
    {
        y = 2;
        Show(y);
    }
    protected void btn1_Click(object sender, EventArgs e)
    {
        y = 1;
        Show(y);
    }
    protected void gr1_RowCommand(object sender, GridViewCommandEventArgs e)
    {
        if (e.CommandName.Equals("Select"))
        {
            if (index == -1)
            {
                index = int.Parse(e.CommandArgument.ToString());
            }
            else
            {
                ((Button)gr1.Rows[index].FindControl("btn_pass")).Visible = true;
                ((Label)gr1.Rows[index].FindControl("lbl_pass")).Visible = false;
                index = int.Parse(e.CommandArgument.ToString());
            }
            ((Button)gr1.Rows[index].FindControl("btn_pass")).Visible = false;
            ((Label)gr1.Rows[index].FindControl("lbl_pass")).Visible = true;
        }
        if (e.CommandName.Equals("App"))
        {
            appind = int.Parse(e.CommandArgument.ToString());
            localhost.Service s = new localhost.Service();
            s.ChangeUserStatus(gr1.Rows[appind].Cells[0].Text, 1);
            Show(y);
        }
        if (e.CommandName.Equals("Del"))
        {
            appind = int.Parse(e.CommandArgument.ToString());
            localhost.Service s = new localhost.Service();
            s.ChangeUserStatus(gr1.Rows[appind].Cells[0].Text, 0);
            DataSet ds = s.GetUserMess(gr1.Rows[appind].Cells[0].Text);
            for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
            {
                s.EditMessageStatus(ds.Tables[0].Rows[i][0].ToString(), ds.Tables[0].Rows[i][1].ToString(), 0);
            }
            Show(y);
        }
        if (e.CommandName.Equals("Ret"))
        {
            appind = int.Parse(e.CommandArgument.ToString());
            localhost.Service s = new localhost.Service();
            s.ChangeUserStatus(gr1.Rows[appind].Cells[0].Text, 1);
            Show(y);
        }
    }
    protected void gr1_PageIndexChanging(object sender, GridViewPageEventArgs e)
    {
        gr1.PageIndex = e.NewPageIndex;
        Show(y);
    }
    protected void gr1_DataBound(object sender, EventArgs e)
    {
        foreach (GridViewRow row in gr1.Rows)
        {
            if ((((Label)row.FindControl("lbl_stat")).Text == "2") || (((Label)row.FindControl("lbl_stat")).Text == "1") || (((Label)row.FindControl("lbl_stat")).Text == "0"))
            {
                if (((Label)row.FindControl("lbl_stat")).Text == "2")
                {
                    ((Button)row.FindControl("btn_app")).Visible = true;
                    ((Button)row.FindControl("btn_app")).Text = "אישור";
                    ((Button)row.FindControl("btn_app")).CommandName = "App";
                    ((Label)row.FindControl("lbl_stat")).Text = "ממתין לאישור";
                }

                if (((Label)row.FindControl("lbl_stat")).Text == "1")
                {
                    ((Button)row.FindControl("btn_app")).Visible = true;
                    ((Button)row.FindControl("btn_app")).Text = "השהייה";
                    ((Button)row.FindControl("btn_app")).CommandName = "Del";
                    ((Label)row.FindControl("lbl_stat")).Text = "פעיל";
                }

                if (((Label)row.FindControl("lbl_stat")).Text == "0")
                {
                    ((Button)row.FindControl("btn_app")).Visible = true;
                    ((Button)row.FindControl("btn_app")).Text = "שחזור";
                    ((Button)row.FindControl("btn_app")).CommandName = "Ret";
                    ((Label)row.FindControl("lbl_stat")).Text = "נמחק";
                }
            }
            else
            {
                ((Button)row.FindControl("btn_app")).Visible = false;
            }
            if (row.Cells[4].Text.Equals("1"))
                row.Cells[4].Text = "מנהל";
            if (row.Cells[4].Text.Equals("2"))
                row.Cells[4].Text = "מורה";
            if (row.Cells[4].Text.Equals("3"))
                row.Cells[4].Text = "תלמיד";
        }
    }
}
