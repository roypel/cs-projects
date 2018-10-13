<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="AdminSearch.aspx.cs" Inherits="AdminSearch" Title="Untitled Page" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <center>
    <table>
        <tr>
            <td>
                <asp:Label ID="lbl1" runat="server" Text="בחר סוג משתמשים להצגה:" Font-Names="Tahoma"></asp:Label>
            </td>
            <td colspan="2">
                <asp:DropDownList ID="ddl1" runat="server" AutoPostBack="True" Font-Names="Tahoma">
                    <asp:ListItem Selected="True" Value="0">להצגת כל המשתמשים</asp:ListItem>
                    <asp:ListItem Value="1">להצגת משתמשים פעילים</asp:ListItem>
                    <asp:ListItem Value="2">להצגת משתמשים הממתינים לאישור</asp:ListItem>
                    <asp:ListItem Value="3">להצגת משתמשים לא פעילים</asp:ListItem>
                </asp:DropDownList>
            </td>
        </tr>
        <tr>
           <td colspan="3">
                <asp:Label ID="lbl2" runat="server" Text="להצגת כל המשתמשים לחץ " Font-Names="Tahoma"></asp:Label>
                <asp:Button ID="btn_ShowAll" runat="server" Text="כאן" 
                    onclick="btn_ShowAll_Click" Font-Names="Tahoma" />
            </td>
        </tr>
        <tr>
            <td>
                <asp:Label ID="lbl3" runat="server" Text="הזן שם משתמש לחיפוש" Font-Names="Tahoma"></asp:Label>
            </td>
            <td>
                <asp:TextBox ID="txt1" runat="server" Font-Names="Tahoma"></asp:TextBox>
            </td>
            <td>
                <asp:Button ID="btn1" runat="server" Text="חפש" onclick="btn1_Click" Font-Names="Tahoma" />
            </td>
        </tr>
        <tr>
            <td colspan="3">
                &nbsp;<asp:GridView 
                    ID="gr1" runat="server" AutoGenerateColumns="False" Font-Names="Tahoma" 
                    onrowcommand="gr1_RowCommand" AllowPaging="True" 
                    onpageindexchanging="gr1_PageIndexChanging" PageSize="5" 
                    ondatabound="gr1_DataBound">
                    <Columns>
                        <asp:BoundField DataField="UserName" HeaderText="שם משתמש" />
                        <asp:TemplateField HeaderText="סיסמא">
                            <ItemTemplate>
                                <asp:Button ID="btn_pass" runat="server" 
                                    CommandArgument="<%# ((GridViewRow) Container).RowIndex %>" CommandName="Select"
                                    Font-Names="Tahoma" Text="להצגת סיסמא" />
                                <asp:Label ID="lbl_pass" runat="server" Text='<%# DataBinder.Eval(Container.DataItem, "Password") %>'
                                    Visible="False"></asp:Label>
                            </ItemTemplate>
                        </asp:TemplateField>
                        <asp:BoundField DataField="FirstName" HeaderText="שם פרטי" />
                        <asp:BoundField DataField="LastName" HeaderText="שם משפחה" />
                        <asp:BoundField DataField="Rank" HeaderText="תפקיד" />
                        <asp:TemplateField HeaderText="סטטוס">
                            <ItemTemplate>
                                <asp:Label ID="lbl_stat" runat="server" 
                                    Text='<%# DataBinder.Eval(Container.DataItem, "Status") %>'></asp:Label>
                                <asp:Button ID="btn_app" runat="server" CommandArgument="<%# ((GridViewRow) Container).RowIndex %>" 
                                    CommandName="App" Text="אישור" Visible="False" />
                            </ItemTemplate>
                        </asp:TemplateField>
                    </Columns>
                </asp:GridView>
            </td>
        </tr>
    </table>
    </center>
</asp:Content>

