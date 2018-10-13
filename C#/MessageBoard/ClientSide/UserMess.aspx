<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="UserMess.aspx.cs" Inherits="UserMess" Title="Untitled Page" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
<center>
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
                    <asp:Label ID="lbl_stat" runat="server" Text="מצב הודעה"></asp:Label>
                </td>
            </tr>
            <tr align="center">
                <td colspan="3">
                    <asp:Label ID="lbl_msg" runat="server" 
                        Text='<%# DataBinder.Eval(Container.DataItem, "Message") %>'></asp:Label>
                </td>
                <td>
                    <asp:Label ID="lbl_status" runat="server" 
                        Text='<%# DataBinder.Eval(Container.DataItem, "Status") %>'></asp:Label>
                    <asp:LinkButton ID="lb1" runat="server" CommandArgument="del" Visible="False">למחיקת 
                    הודעה</asp:LinkButton>
                    <asp:LinkButton ID="lb2" runat="server" CommandArgument="dra" Visible="False">לפרסום 
                    הודעה</asp:LinkButton>
                    <asp:LinkButton ID="lb3" runat="server" CommandArgument="sen" Visible="False">לעריכת 
                    הודעה</asp:LinkButton>
                </td>
            </tr>
        </table>
    </ItemTemplate>
        <SelectedItemStyle BackColor="#E2DED6" Font-Bold="True" ForeColor="#333333" />
    </asp:DataList>
</center>
</asp:Content>

