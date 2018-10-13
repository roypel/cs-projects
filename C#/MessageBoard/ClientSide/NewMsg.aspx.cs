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

public partial class NewMsg : System.Web.UI.Page
{
    private static bool both = false;
    protected void Page_Load(object sender, EventArgs e)
    {
        if (Session["Rank"] == null)
            Response.Redirect("SignIn.aspx");
        if (Session["Draft"] != null)
        {
            CKE1.Text = Session["Draft"].ToString();
            Session["Draft"] = null;
        }
    }
    protected void btn_snd_Click(object sender, EventArgs e)
    {
        localhost.Msg M = new localhost.Msg();
        if (ddl1.SelectedValue != "3")
            M.Boards = int.Parse(ddl1.SelectedValue);
        else
            both = true;
        M.Dates = DateTime.Today.ToShortDateString();
        if (CB_date.Checked == false)
            M.EnDates = "0";
        else
        {
            if (DateTime.Compare(DateTime.Today, Cnd1.SelectedDate) > 0)
                Response.Write(@"<script language='javascript'>alert('תאריך מחיקת הודעה לא יכול להיות קודם להיום');</script>");
            else
                M.EnDates = Cnd1.SelectedDate.ToShortDateString();
        }
        M.Hours = DateTime.Now.ToShortTimeString();
        M.Messages = CKE1.Text;
        M.Writers = Session["User"].ToString();

        if (CB_draft.Checked == true)
            M.Statuss = -2;
        else
        {
            if (Session["Rank"].ToString() != "3")
                M.Statuss = 1;
            else
                M.Statuss = -1;
        }
        localhost.Service s = new localhost.Service();
        if (both == true)
        {
            if ((s.CheckMsgExist(M.Writers, M.Messages, 1)) || (s.CheckMsgExist(M.Writers, M.Messages, 2)))
            {
                Response.Write(@"<script language='javascript'>alert('הודעה כבר רשומה במערכת');</script>");
                Response.Write(@"<script language='javascript'>alert('במידה וההודעה לא מופיעה בלוח,\n יש לחכות לאישור מנהל');</script>");
            }
            else
            {
                M.Boards = 1;
                s.AddMsg(M);
                M.Boards = 2;
                s.AddMsg(M);
                if (Session["Rank"].ToString() != "3")
                    Response.Write(@"<script language='javascript'>alert('הודעתך הוספה בהצלחה!');</script>");
                else
                    Response.Write(@"<script language='javascript'>alert('הודעתך הוספה בהצלחה!,\n יש לחכות לאישור מנהל');</script>");
            }
        }
        else
        {
            if (s.CheckMsgExist(M.Writers, M.Messages, M.Boards))
            {
                Response.Write(@"<script language='javascript'>alert('הודעה כבר רשומה במערכת');</script>");
                Response.Write(@"<script language='javascript'>alert('במידה וההודעה לא מופיעה בלוח,\n יש לחכות לאישור מנהל');</script>");
            }
            else
            {
                s.AddMsg(M);
                if (Session["Rank"].ToString() != "3")
                    Response.Write(@"<script language='javascript'>alert('הודעתך הוספה בהצלחה!');</script>");
                else
                    Response.Write(@"<script language='javascript'>alert('הודעתך הוספה בהצלחה!,\n יש לחכות לאישור מנהל');</script>");
            }
        }
    }
    protected void CB_date_CheckedChanged(object sender, EventArgs e)
    {
        if (CB_date.Checked == true)
            Cnd1.Visible = true;
        else
            Cnd1.Visible = false;
    }
}
