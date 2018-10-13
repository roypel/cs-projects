using System;
using System.Data;
using System.Data.OleDb;
using System.Configuration;
using System.Web;
using System.Web.Security;
using System.Web.UI;
using System.Web.UI.WebControls;
using System.Web.UI.WebControls.WebParts;
using System.Web.UI.HtmlControls;


public class Connect
{
    private string my_path;

   private  OleDbConnection my_con;
    //------------------------------------------------------------------

	public Connect(string path)
	{
      this.my_path = @"Provider=Microsoft.Jet.OleDb.4.0;Data Source=" + path;

      this.my_con = new OleDbConnection(this.my_path);
	}
//------------------------------------------------------------------
    public DataSet MakeConnection(string my_sql,string tableName)
    {
        
        DataSet ds = new DataSet();

        OleDbCommand cmmd = new OleDbCommand(my_sql, this.my_con);

        OleDbDataAdapter da = new OleDbDataAdapter(cmmd);

        da.Fill(ds, tableName);

        return (ds);
    }
    //------------------------------------------------------------------
    public void TakeAction(OleDbCommand cmmd)
    {
        cmmd.Connection = this.my_con;

        this.my_con.Open();

        cmmd.ExecuteNonQuery();

        this.my_con.Close();
    }
    //------------------------------------------------------------------
    public int NumberOfRows(string sql)
    {
        OleDbCommand cmmd = new OleDbCommand(sql, my_con);

        this.my_con.Open();

        int result =(int) cmmd.ExecuteScalar();

        this.my_con.Close();

        return (result);
    }
   
}
