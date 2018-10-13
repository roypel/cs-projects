<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="AdminBoard.aspx.cs" Inherits="AdminBoard" Title="Untitled Page" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <center>
    <table>
        <tr>
            <td>
                <asp:Label ID="lbl1" runat="server" Text="בחר סוג לוח: "></asp:Label>
                <asp:DropDownList ID="ddl1" runat="server" AutoPostBack="True" 
                    onselectedindexchanged="ddl1_SelectedIndexChanged">
                    <asp:ListItem Value="1">מורים</asp:ListItem>
                    <asp:ListItem Value="2">תלמידים</asp:ListItem>
                    <asp:ListItem Value="3">הצג את כל ההודעות</asp:ListItem>
                    <asp:ListItem Selected="True" Value="4">--בחר סוג--</asp:ListItem>
                </asp:DropDownList>
            </td>
        </tr>
        <tr>
            <td>
                <asp:Label ID="lbl2" runat="server" Text="הצג:"></asp:Label>
                <asp:DropDownList ID="ddl2" runat="server" AutoPostBack="True" Enabled="False" 
                    onselectedindexchanged="ddl2_SelectedIndexChanged">
                    <asp:ListItem Value="0">כל ההודעות</asp:ListItem>
                    <asp:ListItem Value="1">הודעות שנקראו</asp:ListItem>
                    <asp:ListItem Value="2">הודעות שלא נקראו</asp:ListItem>
                    <asp:ListItem Value="3">הודעות שנמחקו</asp:ListItem>
                    <asp:ListItem Value="4">טיוטות</asp:ListItem>
                    <asp:ListItem Selected="True" Value="5">--בחר סוג--</asp:ListItem>
                </asp:DropDownList>
            </td>
        </tr>
        <tr>
            <td>
    <asp:DataList ID="dtl1" runat="server" CellPadding="4" ForeColor="#333333" 
                    onitemcommand="dtl1_ItemCommand">
        <AlternatingItemStyle BackColor="White" ForeColor="#284775" />
        <FooterStyle BackColor="#5D7B9D" Font-Bold="True" ForeColor="White" />
        <HeaderStyle BackColor="#5D7B9D" Font-Bold="True" ForeColor="White" />
        <ItemStyle BackColor="#F7F6F3" ForeColor="#333333" />
    <ItemTemplate>
        <table>
            <tr>
                <td>
                    <asp:Label ID="lbl_user" runat="server" 
                        Text='<%# DataBinder.Eval(Container.DataItem, "Writer") %>'></asp:Label>
                </td>
                <td>
                    <asp:Label ID="lbl_date" runat="server" 
                        Text='<%# DataBinder.Eval(Container.DataItem, "Date") %>'></asp:Label>
                </td>
                <td>
                    <asp:Label ID="lbl_time" runat="server" 
                        Text='<%# DataBinder.Eval(Container.DataItem, "Hour") %>'></asp:Label>
                </td>
                <td>
                    <asp:Label ID="lbl_untill" runat="server" Text="עד לתאריך:"></asp:Label>
                    <asp:Label ID="lbl_EnDate" runat="server" Text='<%# DataBinder.Eval(Container.DataItem, "EnDate") %>'></asp:Label>
                </td>
                <td>
                    <asp:Button ID="btn_del" runat="server" Text="מחק הודעה" 
                        CommandArgument="del" />
                     <asp:Button ID="btn_del1" runat="server" Text="מחק הודעה" CommandArgument="del1"
                        Visible="False" />
                    <asp:Button ID="btn_ret" runat="server" Text="שחזר הודעה" CommandArgument="ret" 
                        Visible="False" />
                </td>
            </tr>
            <tr align="center">
                <td colspan="3">
                    <asp:Label ID="lbl_msg" runat="server" 
                        Text='<%# DataBinder.Eval(Container.DataItem, "Message") %>'></asp:Label>
                </td>
                <td>
                    <asp:Label ID="lbl_board" runat="server" 
                        Text='<%# DataBinder.Eval(Container.DataItem, "Board") %>'></asp:Label>
                </td>
                <td>
                    <asp:Button ID="btn_chk" runat="server" Text="אשר הודעה" 
                        CommandArgument="chk" Visible="False" />
                    <asp:Label ID="lbl_draft" runat="server" Text="הודעת טיוטה" Visible="False"></asp:Label>
                </td>
            </tr>
             <tr>
                <td colspan="6">
                    <asp:Label ID="lbl_del1" runat="server" Text="שים לב! מחיקת הודעה זו תמחק אותה לצמיתות!" Visible="False" Font-Bold="True" ForeColor="Red"></asp:Label>
                </td>
            </tr>
        </table>
    </ItemTemplate>
        <SelectedItemStyle BackColor="#E2DED6" Font-Bold="True" ForeColor="#333333" />
    </asp:DataList>
            </td>
        </tr>
    </table>
    </center>
</asp:Content>

