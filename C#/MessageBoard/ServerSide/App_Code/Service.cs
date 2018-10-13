using System;
using System.Web;
using System.Web.Services;
using System.Web.Services.Protocols;
using System.Data;
using System.Data.OleDb;

[WebService(Namespace = "http://tempuri.org/")]
[WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]
public class Service : System.Web.Services.WebService
{
    public Service () 
    {

        //Uncomment the following line if using designed components 
        //InitializeComponent(); 
    }

    [WebMethod]
    public bool SearchExist (string name)
    {
        Connect my_conn=new Connect (Server.MapPath("App_Data/db1.mdb"));

        string sql = "Select * from Users WHERE UserName='" + name + "'";

        DataSet ds = my_conn.MakeConnection(sql, "Users");

        if (ds.Tables[0].Rows.Count == 1)
        
            return true;
        
        return false;
    }
    //הפעולה בודקת אם קיים שם משתמש בשם name, אם כן מחזירה אמת, אחרת מחזירה שקר.

    [WebMethod]
    public bool SearchSigned(string name, string pass)
    {
        Connect my_conn = new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql = "Select * from Users WHERE UserName='" + name + "' And Password='" + pass + "' and Status=1";

        DataSet ds = my_conn.MakeConnection(sql, "Users");

        if (ds.Tables[0].Rows.Count == 1)

            return true;

        return false;
    }
    //הפעולה בודקת אם קיים משתמש אם שם משתמש name וסיסמה pass, אם קיים מחזירה אמת, אחרת
    //מחזירה שקר.

    [WebMethod]
    public void AddUser(Users u)
    {
        Connect my_conn=new Connect (Server.MapPath("App_Data/db1.mdb"));

        string sql = "Insert Into Users (UserName, [Password], FirstName, LastName, Email, Rank,[Status]) Values (@p1, @p2, @p3, @p4, @p5, @p6, @p7)";

        OleDbCommand cmmd = new OleDbCommand(sql);

        cmmd.Parameters.Add(new OleDbParameter("@p1", OleDbType.VarChar));

        cmmd.Parameters["@p1"].Value = u.UserNames;

        cmmd.Parameters.Add(new OleDbParameter("@p2", OleDbType.VarChar));

        cmmd.Parameters["@p2"].Value = u.Passwords;
        
        cmmd.Parameters.Add(new OleDbParameter("@p3", OleDbType.VarChar));

        cmmd.Parameters["@p3"].Value = u.FirstNames;

        cmmd.Parameters.Add(new OleDbParameter("@p4", OleDbType.VarChar));

        cmmd.Parameters["@p4"].Value = u.LastNames;

        cmmd.Parameters.Add(new OleDbParameter("@p5", OleDbType.VarChar));

        cmmd.Parameters["@p5"].Value = u.Emails;

        cmmd.Parameters.Add(new OleDbParameter("@p6", OleDbType.Integer));

        cmmd.Parameters["@p6"].Value = u.Ranks;
        
        cmmd.Parameters.Add(new OleDbParameter("@p7", OleDbType.Integer));

        cmmd.Parameters["@p7"].Value = u.Statuss;

        my_conn.TakeAction(cmmd);
    }
    //הפעולה מקבלת עצם מסוג Users ומוסיפה אותו למסד הנתונים.

    [WebMethod]
    public DataSet SearchUser(string user)
    {
        Connect conn = new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql="";

        sql = "Select * from Users Where UserName='" + user + "'";
        
        DataSet ds = conn.MakeConnection(sql, "Users");

        if (ds.Tables[0].Rows.Count == 0)
            ds = null;

        return ds;
    }
    //הפעולה מחפשת שם משתמש user, אם קיים מחזירה מסד נתונים עם כל נתוניו, אחרת מחזירה מסד 
    //ריק.

    [WebMethod]
    public DataSet GetUsers(int x)
    {
        Connect conn = new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql="";

        switch (x)
        {
            case 0:
                sql = "Select * from Users";
                break;
            case 1:
                sql = "Select * from Users Where Status = 1";
                break;
            case 2:
                sql = "Select * from Users Where Status = 2";
                break;
            case 3:
                sql = "Select * from Users Where Status = 0";
                break;
        }

        DataSet ds = conn.MakeConnection(sql, "Users");

        if (ds.Tables[0].Rows.Count == 0)
            ds = null;

        return ds;
    }
    //הפעולה מחזירה את כל המשתמשים בהתאם ל x (כולם, פעילים, ממתינים לאישור או משתמשים 
    //שנמחקו).

    [WebMethod]
    public DataSet GetCheckedMessages(int x)
    {
        Connect conn = new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql = "";

        switch (x)
        {
            case 1:
                sql = "Select * from Messages Where Board = 1 And Status = 1";
                break;
            case 2:
                sql = "Select * from Messages Where Board = 2 And Status = 1";
                break;
            case 3:
                sql = "Select * from Messages Where Status = 1";
                break;

        }
                DataSet ds = conn.MakeConnection(sql, "Messages");

        if (ds.Tables[0].Rows.Count == 0)
            ds = null;

        return ds;
    }
    //הפעולה מחזירה את כל ההודעות שאושרו מלוח x (לוח כללי, מורים, תלמידים או כל ההודעות).

    [WebMethod]
    public DataSet GetAllMessages(int x)
    {
        Connect conn = new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql = "Select * from Messages";

        switch (x)
        {
            case 1:
                sql += " Where Board = 1";
                break;
            case 2:
                sql += " Where Board = 2";
                break;
        }
        DataSet ds = conn.MakeConnection(sql, "Messages");

        if (ds.Tables[0].Rows.Count == 0)
            ds = null;

        return ds;
    }
    //הפעולה מחזירה את כל ההודעות מלוח x (לוח כללי, מורים או תלמידים).

    [WebMethod]
    public DataSet GetUnCheckedMessages(int x)
    {
        Connect conn = new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql = "";

        switch (x)
        {
            case 1:
                sql = "Select * from Messages Where Board = 1 And Status = -1";
                break;
            case 2:
                sql = "Select * from Messages Where Board = 2 And Status = -1";
                break;
            case 3:
                sql = "Select * from Messages Where Status = -1";
                break;
        }

        DataSet ds = conn.MakeConnection(sql, "Messages");

        if (ds.Tables[0].Rows.Count == 0)
            ds = null;

        return ds;
    }
    //הפעולה מחזירה את כל ההודעות שלא אושרו מלוח x (לוח כללי, מורים, תלמידים או כל ההודעות).

    [WebMethod]
    public DataSet GetDeletedMessages(int x)
    {
        Connect conn = new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql = "";

        switch (x)
        {
            case 1:
                sql = "Select * from Messages Where Board = 1 And Status = 0";
                break;
            case 2:
                sql = "Select * from Messages Where Board = 2 And Status = 0";
                break;
            case 3:
                sql = "Select * from Messages Where Status = 0";
                break;
        }

        DataSet ds = conn.MakeConnection(sql, "Messages");

        if (ds.Tables[0].Rows.Count == 0)
            ds = null;

        return ds;
    }
    //הפעולה מחזירה את כל ההודעות שנמחקו מלוח x (לוח כללי, מורים, תלמידים או כל ההודעות).
   
    [WebMethod]
    public DataSet GetDraftMessages(int x)
    {
        Connect conn = new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql = "";

        switch (x)
        {
            case 1:
                sql = "Select * from Messages Where Board = 1 And Status = -2";
                break;
            case 2:
                sql = "Select * from Messages Where Board = 2 And Status = -2";
                break;
            case 3:
                sql = "Select * from Messages Where Status = -2";
                break;
        }

        DataSet ds = conn.MakeConnection(sql, "Messages");

        if (ds.Tables[0].Rows.Count == 0)
            ds = null;

        return ds;
    }

    [WebMethod]
    public DataSet GetMsgStatus(string w, string m)
    {
        Connect my_conn = new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql = "Select [Status] from Messages WHERE Message='" + m + "' And Writer='" + w + "'";

        DataSet ds = my_conn.MakeConnection(sql, "Messages");

        if (ds.Tables[0].Rows.Count == 0)

            ds = null;

        return ds;
    }
    //הפעולה מחזירה מסד ובו סטטוס ההודעה שכתב  w ותוכנה m, אם ההודעה לא קיימת הפעולה תחזיר 
    //מסד ריק.

    [WebMethod]
    public string GetRank(string UserName)
    {
        Connect conn = new Connect(Server.MapPath("App_Data/db1.mdb"));
        DataSet ds = new DataSet();
        string sql = "Select Rank From Users Where UserName='" + UserName + "'";
        ds = conn.MakeConnection(sql, "Users");
        return ds.Tables[0].Rows[0][0].ToString();
    }
    //הפעולה מחזירה את דרגת המשתמש UserName.
    [WebMethod]
    public void AddMsg(Msg M)
    {
        Connect my_conn = new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql = "Insert Into Messages ([Writer], [Message], [Date], EnDate, [Hour], [Board],[Status]) Values (@p1, @p2, @p3, @p4, @p5, @p6, @p7)";

        OleDbCommand cmmd = new OleDbCommand(sql);

        cmmd.Parameters.Add(new OleDbParameter("@p1", OleDbType.VarChar));

        cmmd.Parameters["@p1"].Value = M.Writers;

        cmmd.Parameters.Add(new OleDbParameter("@p2", OleDbType.VarChar));

        cmmd.Parameters["@p2"].Value = M.Messages;

        cmmd.Parameters.Add(new OleDbParameter("@p3", OleDbType.VarChar));

        cmmd.Parameters["@p3"].Value = M.Dates;
        
        cmmd.Parameters.Add(new OleDbParameter("@p4", OleDbType.VarChar));

        cmmd.Parameters["@p4"].Value = M.EnDates;

        cmmd.Parameters.Add(new OleDbParameter("@p5", OleDbType.VarChar));

        cmmd.Parameters["@p5"].Value = M.Hours;

        cmmd.Parameters.Add(new OleDbParameter("@p6", OleDbType.Integer));

        cmmd.Parameters["@p6"].Value = M.Boards;

        cmmd.Parameters.Add(new OleDbParameter("@p7", OleDbType.Integer));

        cmmd.Parameters["@p7"].Value = M.Statuss;
        
        my_conn.TakeAction(cmmd);
    }
    //הפעולה מקבלת עצם מסוג Msg ומוסיפה אותו למסד הנתונים.
    [WebMethod]
    public void EditMessageStatus(string w, string m, int x)
    {
        Connect my_conn = new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql = "Update Messages Set [Status]=" + x + " Where Writer='" + w + "' And Message='" + m +"'";

        OleDbCommand cmmd = new OleDbCommand(sql);

        my_conn.TakeAction(cmmd);
    }
    //הפעולה משנה את סטטוס ההודעה שכתב w ותוכנה m ל x (פעיל, מחוק, לא מאושר).
    [WebMethod]
    public bool CheckMsgExist(string w, string m, int b)
    {
        Connect C=new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql = "Select * From Messages Where Writer='" + w + "' And Message ='" + m + "' And Board=" + b;

        DataSet ds = C.MakeConnection(sql, "Messages");

        if (ds.Tables[0].Rows.Count == 1)
            return true;
        return false;
    }
    //הפעולה בודקת אם קיימת במסד הודעה שכתבw  ותוכנה m, אם קיימת מחזירה אמת, אחרת מחזירה 
    //שקר.

    [WebMethod]
    public void EditUser(Users u, string uname)
    {
        Connect my_conn = new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql = "Update [Users] Set UserName='" + u.UserNames + "', [Password]='" + u.Passwords + "', FirstName='" + u.FirstNames + "', LastName='" + u.LastNames + "', Email='" + u.Emails + "' Where UserName='" + uname + "'";

        OleDbCommand cmmd = new OleDbCommand(sql);

        my_conn.TakeAction(cmmd);
    }

    [WebMethod]
    public void ChangeUserStatus(string u, int s)
    {
        Connect my_conn = new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql = "Update [Users] Set [Status]=" + s + " Where UserName='" + u + "'";

        OleDbCommand cmmd = new OleDbCommand(sql);

        my_conn.TakeAction(cmmd);
    }
    //הפעולה משנה את סטטוס המשתמש u ל s.
    [WebMethod]
    public DataSet GetUserMess(string w)
    {
        Connect conn = new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql = "";

        sql = "Select * from Messages Where Writer ='" + w + "'";

        DataSet ds = conn.MakeConnection(sql, "Messages");

        if (ds.Tables[0].Rows.Count == 0)
            ds = null;

        return ds;
    }
    //הפעולה מחזירה את כל ההודעות שכתב w.
    [WebMethod]
    public bool CheckPass(string u, string pass)
    {
        Connect conn = new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql = "";

        sql = "Select * from Users Where UserName ='" + u + "' And Password='" + pass + "'";

        DataSet ds = conn.MakeConnection(sql, "Users");

        if (ds.Tables[0].Rows.Count == 0)
            return false;

        return true;
    }
    //הפעולה בודקת אם סיסמת המשתמש u היא pass, אם כן מחזירה אמת, אחרת מחזירה שקר.

    [WebMethod]
    public string GetEma(string u)
    {
        Connect conn = new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql = "";

        sql = "Select Email from Users Where UserName ='" + u + "'";

        DataSet ds = conn.MakeConnection(sql, "Users");

        return ds.Tables[0].Rows[0][0].ToString();
    }

    [WebMethod]
    public DataSet PassRecov(string e)
    {
        Connect conn = new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql = "";

        sql = "Select * from Users Where Email ='" + e + "'";

        DataSet ds = conn.MakeConnection(sql, "Users");

        if (ds.Tables[0].Rows.Count == 0)
            ds = null;

        return ds;
    }

    [WebMethod]
    public bool CheckMail(string m)
    {
        Connect conn = new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql = "";

        sql = "Select * from Users Where Email ='" + m + "'";

        DataSet ds = conn.MakeConnection(sql, "Users");

        if (ds.Tables[0].Rows.Count == 0)
            return true;

        return false;
    }

    [WebMethod]
    public void DeleteMsg(string w, string m)
    {
        Connect conn = new Connect(Server.MapPath("App_Data/db1.mdb"));

        string sql = "";

        sql = "Delete  from Messages Where Writer ='" + w + "' And Message ='" + m + "'";

        OleDbCommand cmmd = new OleDbCommand(sql);

        conn.TakeAction(cmmd);
    }
}
