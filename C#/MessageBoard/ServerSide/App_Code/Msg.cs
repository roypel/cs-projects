using System;
using System.Collections.Generic;
using System.Web;

/// <summary>
/// Summary description for Messages
/// </summary>
public class Msg
{
    private string Writer; //כותב
    private string Message; //תוכן
    private string Date; //תאריך
    private string EnDate;
    private string Hour; //שעה
    private int Board; //לוח
    private int Status; //סטטוס
    
	public Msg()
	{
	} //פעולה בונה

    public string Writers
    {
        get
        {
            return this.Writer;
        }
        set
        {
            this.Writer = value;
        }
    } //Writer הפעולה מקבלת ו/או משנה את ערך התכונה

    public string Messages
    {
        get
        {
            return this.Message;
        }
        set
        {
            this.Message = value;
        }
    } //Message הפעולה מקבלת ו/או משנה את ערך התכונה

    public string Dates
    {
        get
        {
            return this.Date;
        }
        set
        {
            this.Date = value;
        }
    } //Date הפעולה מקבלת ו/או משנה את ערך התכונה

    public string EnDates
    {
        get
        {
            return this.EnDate;
        }
        set
        {
            this.EnDate = value;
        }
    }

    public string Hours
    {
        get
        {
            return this.Hour;
        }
        set
        {
            this.Hour = value;
        }
    } //Hour הפעולה מקבלת ו/או משנה את ערך התכונה

    public int Boards
    {
        get
        {
            return this.Board;
        }
        set
        {
            this.Board = value;
        }
    } //Board הפעולה מקבלת ו/או משנה את ערך התכונה

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