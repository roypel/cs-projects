<%@ Page Language="C#" AutoEventWireup="true" CodeFile="TBoard.aspx.cs" Inherits="TBoard" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title>Untitled Page</title>
</head>
<body dir="rtl" style="font-family: Tahoma; background-color: #84C1FF;">
    <form id="form1" runat="server">
    <center>
        <table style="font-family: Tahoma; background-color: #FFFFFF" width="100%">
            <tr align="center">
                <td>
                    <asp:Label ID="lblT" runat="server" Text="לוח מורים" Font-Size="XX-Large"></asp:Label>
                </td>
            </tr>
            <tr align="center">
                <td>
                    <asp:Label ID="lbl_date" runat="server" Text="Label" onload="lbl_date_Load"></asp:Label>
                    <asp:Label ID="lbl_hour" runat="server" Text="Label" onload="lbl_hour_Load"></asp:Label>
                </td>
            </tr>
            <tr align="center">
                <td>
                    <asp:ScriptManager ID="ScriptManager1" runat="server">
                    </asp:ScriptManager>
                    <asp:Timer ID="Timer1" runat="server" ontick="Timer1_Tick" Interval="3000" 
                        Enabled="False">
                    </asp:Timer>
                    <asp:UpdatePanel ID="UpdatePanel1" runat="server">
                    <ContentTemplate>
                    <asp:DataList ID="dtl1" runat="server" CellPadding="4" ForeColor="#333333" 
                            Width="100%" Font-Size="X-Large" style="direction: rtl" ItemStyle-HorizontalAlign="Center">
                        <FooterStyle BackColor="#5D7B9D" Font-Bold="True" ForeColor="White" />
                        <AlternatingItemStyle BackColor="White" ForeColor="#284775" />
                        <ItemStyle BackColor="#F7F6F3" ForeColor="#333333" />
                        <SelectedItemStyle BackColor="#E2DED6" Font-Bold="True" ForeColor="#333333" />
                        <HeaderStyle BackColor="#5D7B9D" Font-Bold="True" ForeColor="White" />
                    <ItemTemplate>
                        <table border="0" cellpadding="5" cellspacing="0">
                            <tr align="center">
                                <td>
                                    <asp:Label ID="lbl_writer" runat="server" Text='<%# DataBinder.Eval(Container.DataItem,"Writer") %>'></asp:Label>
                                </td>
                                <td>
                                    <asp:Label ID="lbl_date" runat="server" Text='<%# DataBinder.Eval(Container.DataItem,"Date") %>'></asp:Label>
                                </td>
                                <td>
                                    <asp:Label ID="lbl_hour" runat="server" Text='<%# DataBinder.Eval(Container.DataItem,"Hour") %>'></asp:Label>
                                </td>
                            </tr>
                            <tr align="center">
                                <td colspan="3">
                                    <asp:Label ID="lbl_msg" runat="server" Text='<%# DataBinder.Eval(Container.DataItem,"Message") %>'></asp:Label>
                                </td>
                            </tr>
                        </table>
                    </ItemTemplate>
                    </asp:DataList>
                    </ContentTemplate>
                    </asp:UpdatePanel>
                </td>
            </tr>
            <tr align="center">
                <td align="center">
                    <asp:Button ID="btn_add" runat="server" Text="להוספת הודעה חדשה" 
                        onclick="btn_add_Click" Visible="False" />
                </td>
            </tr>
            <tr align="center">
                <td>
                    <asp:LinkButton ID="LB1" runat="server" Text="חזרה לעמוד הראשי" PostBackUrl="Home.aspx"></asp:LinkButton>
                </td>
            </tr>
            <tr align="center">
                <td>
                    <asp:Label ID="lbl_cred" runat="server" 
                    Text="אתר זה נבנה ע''י בוגר מגמת הנדסת תוכנה. כל הזכויות שמורות." 
                    Font-Size="Small" ForeColor="Blue"></asp:Label>
                </td>
            </tr>
        </table>
    </center>
    </form>
</body>
</html>
