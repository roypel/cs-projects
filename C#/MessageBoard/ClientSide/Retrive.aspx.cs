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
using System.Web.Mail;

public partial class Retrive : System.Web.UI.Page
{
    protected void Page_Load(object sender, EventArgs e)
    {

    }
    protected void btn_send_Click(object sender, EventArgs e)
    {
        //localhost.Service s = new localhost.Service();
        //DataSet ds = s.PassRecov(txt_ema.Text);
        //if (ds==null)
        //    Response.Write(@"<script language='javascript'>alert('כתובת אימייל לא קיימת במערכת');</script>");
        //else
        //{
        //    MailMessage mm = new MailMessage();
        //    mm.From = "ro_pe@walla.com";
        //    mm.To = txt_ema.Text;
        //    mm.Subject = "שיחזור פרטים";
        //    mm.BodyFormat=MailFormat.Html;

        //    string body = "<html><body>שם משתמש:" + ds.Tables[0].Rows[0][0] +
        //                    "<br/> סיסמה:" + ds.Tables[0].Rows[0][3] + "</body></html>";
        //    mm.Body=body;
        //    SmtpMail.Send(mm);
        //    Response.Write(@"<script language='javascript'>alert('פרטייך נשלחו בהצלחה./n במידה ונתקלת בתקלה, פנה למנהל האתר');</script>");
        }
    }
