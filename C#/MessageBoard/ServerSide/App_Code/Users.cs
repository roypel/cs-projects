using System;
using System.Data;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;

/// <summary>
/// Summary description for Users
/// </summary>
public class Users
{
    private string UserName; //שם משתמש
    private string Password; //סיסמה
    private string FirstName; //שם פרטי
    private string LastName; //שם משפחה
    private string Email;
    private int Rank; //דרגה
    private int Status; //סטטוס
    
	public Users()
	{
       
	} //פעולה בונה

    public string UserNames
    {
        get
        {
            return this.UserName;
        }
        set
        {
            this.UserName = value;
        }
        
    } //UserName הפעולה מקבלת ו/או משנה את ערך התכונה

    public string Passwords
    {
        get
        {
            return this.Password;
        }
        set
        {
            this.Password = value;
        }

    } //Password הפעולה מקבלת ו/או משנה את ערך התכונה

    public string FirstNames
    {
        get
        {
            return this.FirstName;
        }
        set
        {
            this.FirstName = value;
        }

    } //FirstName הפעולה מקבלת ו/או משנה את ערך התכונה

    public string LastNames
    {
        get
        {
            return this.LastName;
        }
        set
        {
            this.LastName = value;
        }

    } //LastName הפעולה מקבלת ו/או משנה את ערך התכונה

    public string Emails
    {
        get
        {
            return this.Email;
        }
        set
        {
            this.Email = value;
        }
    }

    public int Ranks
    {
        get
        {
            return this.Rank;
        }
        set
        {
            this.Rank = value;
        }
    } //Rank הפעולה מקבלת ו/או משנה את ערך התכונה

    public int Statuss
    {
        get
        {
            return this.Status;
        }
        set
        {
            this.Status = value;
        }
    } //Status הפעולה מקבלת ו/או משנה את ערך התכונה
}
