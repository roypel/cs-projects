<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="Retrive.aspx.cs" Inherits="Retrive" Title="Untitled Page" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <table>
        <tr>
            <td colspan="3">
                <asp:Label ID="lbl1" runat="server" 
                Text="הכנס כאן את כתובת האימייל שנרשמת איתה ופרטייך ישלחו אלייה!"></asp:Label>
            </td>
        </tr>
        <tr>
            <td>
                <asp:RegularExpressionValidator ID="rev1" runat="server" 
                    ErrorMessage="RegularExpressionValidator" ControlToValidate="txt_ema" 
                    ValidationExpression="\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*">כתובת לא 
                תקינה</asp:RegularExpressionValidator>
            </td>
            <td>
                <asp:TextBox ID="txt_ema" runat="server"></asp:TextBox>
            </td>
            <td>
                <asp:Button ID="btn_send" runat="server" Text="לשליחה" 
                    onclick="btn_send_Click" />
            </td>
        </tr>
    </table>
    <form runat="server" id="form2" visible="false" method="get">
    
    </form>       
</asp:Content>

