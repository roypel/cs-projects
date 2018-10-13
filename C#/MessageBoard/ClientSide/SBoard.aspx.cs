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

public partial class SBoard : System.Web.UI.Page
{
    private static int counter;
    private static DataSet ds;
    private static DataTable dt;

    protected void Delete()
    {
        localhost.Service s = new localhost.Service();
        DateTime Today=DateTime.Today;
        for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
        {
            if (DateTime.Compare(Today, (DateTime.Parse(ds.Tables[0].Rows[i][3].ToString()))) > 0 && (ds.Tables[0].Rows[i][3].ToString() != "0"))
            {
                s.EditMessageStatus(ds.Tables[0].Rows[i][0].ToString(), ds.Tables[0].Rows[i][1].ToString(), 2);
                ds.Tables[0].Rows.Remove(ds.Tables[0].Rows[i]);
            }
        }
        
    }

    protected void Loop()
    {
        for (int i = ds.Tables[0].Rows.Count - 1; i > counter; i--)
        {
            dt.ImportRow(ds.Tables[0].Rows[i]);
        }
        dtl1.DataSource = dt;
        dtl1.DataBind();
        if (counter > -1)
            dt.Clear();

    }
    protected void Recycle()
    {
        DataTable dt1;
        dt1 = dt.Clone();
        int i = 0;
        dt1.ImportRow(dt.Rows[dt.Rows.Count - 1]);
        foreach (DataRow dr in dt.Rows)
        {
            dt1.ImportRow(dt.Rows[i]);
            i++;
            if (i == dt.Rows.Count - 1)
                break;
        }
        dt = dt1.Copy();
        dt1.Clear();
        dtl1.DataSource = dt;
        dtl1.DataBind();
    }
    protected void Color()
    {
        foreach (DataListItem item in dtl1.Items)
        {
            string w = ((Label)item.FindControl("lbl_writer")).Text;
            localhost.Service s = new localhost.Service();
            string rank = s.GetRank(w);
            if (rank.Equals("1"))
                ((Label)item.FindControl("lbl_writer")).ForeColor = System.Drawing.Color.Red;
            if (rank.Equals("2"))
                ((Label)item.FindControl("lbl_writer")).ForeColor = System.Drawing.Color.Blue;
            if (rank.Equals("3"))
                ((Label)item.FindControl("lbl_writer")).ForeColor = System.Drawing.Color.DarkGreen;
        }
    }

    protected void Page_Load(object sender, EventArgs e)
    {
        if (Session["Rank"] != null)
            btn_add.Visible = true;
        localhost.Service s = new localhost.Service();
        ds = s.GetCheckedMessages(2);
        if (ds != null)
        {
            Delete();
            counter = ds.Tables[0].Rows.Count - 1;
            dt = ds.Tables[0].Clone();
            Timer1.Enabled = true;
        }
        else
        {
            Response.Write(@"<script language='javascript'>alert('לא נמצאו הודעות פעילות בלוח');</script>");
            Timer1.Enabled = false;
        }
    }
    protected void btn_add_Click(object sender, EventArgs e)
    {
        Response.Redirect("NewMsg.aspx");
    }

    protected void Timer1_Tick(object sender, EventArgs e)
    {
        if (counter > -1)
        {
            counter--;
            Loop();
        }
        else
        {
            Recycle();
        }
        Color();
    }
    protected void lbl_date_Load(object sender, EventArgs e)
    {
        lbl_date.Text = DateTime.Now.Date.ToShortDateString();
    }
    protected void lbl_hour_Load(object sender, EventArgs e)
    {
        lbl_hour.Text = DateTime.Now.TimeOfDay.ToString().Substring(0, 8);
    }
}
