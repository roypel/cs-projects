using System;
using System.Collections;
using System.Collections.ObjectModel;
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

public partial class SignUp : System.Web.UI.Page
{
    private Collection<TextBox> t = new Collection<TextBox>();
    private bool CheckPremission()
    {
        if (int.Parse(rbl1.SelectedValue.ToString()) == 1)
        {
            if (txt_pre.Text == Application["Code"].ToString())
                return true;
            else
                return false;
        }
        return true;
    }
    protected void Page_Load(object sender, EventArgs e)
    {
        if (t.Count == 0)
        {
            t.Add(txt_user);
            t.Add(txt_pass);
            t.Add(txt_fir);
            t.Add(txt_las);
            t.Add(txt_pre);
        }

        t[0] = txt_user;
        t[1] = txt_pass;
        t[2] = txt_fir;
        t[3] = txt_las;
        t[4] = txt_pre;
    }
    protected void btn_send_Click(object sender, EventArgs e)
    {
        if (Page.IsValid == true)
        {
            localhost.Users u = new localhost.Users();
            u.UserNames = txt_user.Text;
            u.Passwords = txt_pass.Text;
            u.FirstNames = txt_fir.Text;
            u.LastNames = txt_las.Text;
            if (txt_ema.Text.Equals(""))
                u.Emails = "0";
            else
                u.Emails = txt_ema.Text;
            u.Ranks = int.Parse(rbl1.SelectedValue.ToString());
            u.Statuss = 2;

            localhost.Service s = new localhost.Service();

            if (CheckPremission())
            {
                if (s.SearchExist(u.UserNames))
                {
                    Response.Write(@"<script language='javascript'>alert('שם משתמש כבר קיים');</script>");
                    lbl9.Visible = true;
                }
                else
                {
                    if (s.CheckMail(u.Emails))
                    {
                        s.AddUser(u);
                        Response.Write(@"<script language='javascript'>alert('ההרשמה בוצעה בהצלחה! \nאנא המתן לאישור מנהל'); document.location='Home.aspx';</script>");
                    }
                    else
                    {
                        Response.Write(@"<script language='javascript'>alert('כתובת אימייל כבר קיימת');</script>");
                        lbl10.Visible = true;
                    }
                }
            }
            else
            {
                lbl8.Visible = true;
            }
        }
    }
    protected void rbl1_SelectedIndexChanged(object sender, EventArgs e)
    {
        if (int.Parse(rbl1.SelectedValue.ToString()) == 1)
        {
            lbl7.Visible = true;
            txt_pre.Visible = true;
        }
        else
        {
            lbl7.Visible = false;
            txt_pre.Visible = false;
        }
    }
    protected void btn_erase_Click(object sender, EventArgs e)
    {
        for (int i = 0; i < t.Count; i++)
            t[i].Text = string.Empty;
        rbl1.SelectedIndex = 0;
        lbl7.Visible = false;
        txt_pre.Visible = false;
        lbl8.Visible = false;
    }
    protected void btn_back_Click(object sender, EventArgs e)
    {
        Response.Redirect("Home.aspx");
    }
}
