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

public partial class UserEdit : System.Web.UI.Page
{
    private static int x;
    protected void Page_Load(object sender, EventArgs e)
    {
        if (Session["User"] == null)
            Response.Redirect("SignIn.aspx");
    }
    protected void btn_show_Click(object sender, EventArgs e)
    {
        lbl_pass.Visible = true;
        btn_show.Visible = false;
        lbl_del.Visible = false;
        lbl_del1.Visible = false;
    }
    protected void lbl_use_Load(object sender, EventArgs e)
    {
        lbl_use.Text = Session["User"].ToString();
        localhost.Service s = new localhost.Service();
        lbl_fir.Text = s.SearchUser(lbl_use.Text).Tables[0].Rows[0][1].ToString();
        lbl_las.Text = s.SearchUser(lbl_use.Text).Tables[0].Rows[0][2].ToString();
        lbl_pass.Text = s.SearchUser(lbl_use.Text).Tables[0].Rows[0][3].ToString();
        lbl_ema.Text = s.SearchUser(lbl_use.Text).Tables[0].Rows[0][4].ToString();
        if (lbl_ema.Text.Equals("0"))
        {
            lbl_ema.Visible = false;
            lbl7.Visible = false;
            x = 0;
        }
        else
            x = 1;

    }
    protected void btn_del_Click(object sender, EventArgs e)
    {
        if (lbl_del.Visible == false)
        {
            lbl_del.Visible = true;
            lbl_del1.Visible = true;
        }
        else
        {
            lbl_del.Visible = false;
            lbl_del1.Visible = false;
            localhost.Service my_Serv = new localhost.Service();
            my_Serv.ChangeUserStatus(Session["User"].ToString(), 0);
            DataSet ds = my_Serv.GetUserMess(Session["User"].ToString());
            for (int i = 0; i < ds.Tables[0].Rows.Count; i++)
            {
                my_Serv.EditMessageStatus(ds.Tables[0].Rows[i][0].ToString(), ds.Tables[0].Rows[i][1].ToString(), 0);
            }
            Session["User"] = null;
            Session["Rank"] = null;
            ((LinkButton)this.Master.FindControl("SignIn")).Visible = true;
            ((LinkButton)this.Master.FindControl("SignOut")).Visible = false;
            Response.Redirect("Home.aspx");
        }
    }
    protected void btn_edit_Click(object sender, EventArgs e)
    {
        lbl_del.Visible = false;
        lbl_del1.Visible = false;

        lbl_use.Visible = false;
        txt_use.Text = lbl_use.Text;
        txt_use.Visible = true;
        lbl_fir.Visible = false;
        txt_fir.Text = lbl_fir.Text;
        txt_fir.Visible = true;
        lbl_las.Visible = false;
        txt_las.Text = lbl_las.Text;
        txt_las.Visible = true;
        if (x == 0)
        {
            lbl7.Visible = true;
            txt_ema.Visible = true;
        }
        else
        {
            lbl_ema.Visible = false;
            txt_ema.Text = lbl_ema.Text;
            txt_ema.Visible = true;
        }

        txt_pass.Visible = true;
        txt_ver.Visible = true;
        btn_show.Visible = false;
        lbl_pass.Visible = false;
        lbl6.Visible = true;
        txt_prev.Visible = true;
        lbl5.Visible = true;

        btn_edit.Visible = false;
        btn_sav.Visible = true;
        btn_can.Visible = true;
    }
    protected void btn_can_Click(object sender, EventArgs e)
    {
        lbl_del.Visible = false;
        lbl_del1.Visible = false;

        lbl_use.Visible = true;
        txt_use.Text = string.Empty;
        txt_use.Visible = false;
        lbl_fir.Visible = true;
        txt_fir.Text = string.Empty;
        txt_fir.Visible = false;
        lbl_las.Visible = true;
        txt_las.Text = string.Empty;
        txt_las.Visible = false;
        if (x != 0)
        {
            lbl_ema.Visible = true;
            txt_ema.Text = string.Empty;
            txt_ema.Visible = false;
        }
        else
        {
            lbl7.Visible = false;
            txt_ema.Visible = false;
            txt_ema.Text = string.Empty;
        }

        txt_pass.Visible = false;
        txt_pass.Text = string.Empty;
        txt_ver.Visible = false;
        txt_ver.Text = string.Empty;
        btn_show.Visible = true;
        lbl6.Visible = false;
        txt_prev.Visible = false;
        txt_prev.Text = string.Empty;
        lbl5.Visible = false;

        btn_edit.Visible = true;
        btn_sav.Visible = false;
        btn_can.Visible = false;
    }
    protected void btn_sav_Click(object sender, EventArgs e)
    {
        localhost.Service s = new localhost.Service();
        if (s.SearchExist(txt_use.Text))
        {
            if (txt_prev.Text.Equals(s.SearchUser(lbl_use.Text).Tables[0].Rows[0][3].ToString()))
            {
                localhost.Users u = new localhost.Users();
                if (txt_ema.Text.Equals(""))
                {
                    u.Emails = "0";
                    u.UserNames = txt_use.Text;
                    u.FirstNames = txt_fir.Text;
                    u.LastNames = txt_las.Text;
                    u.Passwords = txt_pass.Text;

                    s.EditUser(u, lbl_use.Text);
                    Response.Write(@"<script language='javascript'>alert('פרטייך עודכנו בהצלחה!'); document.location='Home.aspx';</script>");
                }
                else
                {
                    if (s.CheckMail(txt_ema.Text))
                    {
                        u.Emails = txt_ema.Text;
                        u.UserNames = txt_use.Text;
                        u.FirstNames = txt_fir.Text;
                        u.LastNames = txt_las.Text;
                        u.Passwords = txt_pass.Text;

                        s.EditUser(u, lbl_use.Text);
                        Response.Write(@"<script language='javascript'>alert('פרטייך עודכנו בהצלחה!'); document.location='Home.aspx';</script>");
                    }
                    else
                        Response.Write(@"<script language='javascript'>alert('כתובת אימייל כבר בשימוש.\nלא בוצעו שינויים');</script>");
                }
            }
            else
            {
                Response.Write(@"<script language='javascript'>alert('הסיסמה שהקלדת אינה סיסמתך הקודמת.\n לא בוצעו שינויים');</script>");
            }
        }
        else
        {
            Response.Write(@"<script language='javascript'>alert('שם המשתמש שבחרת כבר תפוס.\n לא בוצעו שינויים');</script>");
        }

    }
}
