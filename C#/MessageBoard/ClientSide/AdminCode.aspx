<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="AdminCode.aspx.cs" Inherits="AdminCode" Title="Untitled Page" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <table>
        <tr>
            <td colspan="2">
                <asp:Label ID="lbl_warn" runat="server" 
        Text="שים לב! קוד זה הוא קוד המאשר הרשמה בתור מנהל!" Font-Bold="True" 
        ForeColor="Red"></asp:Label>
            </td>
        </tr>
        <tr>
            <td>
                <asp:Label ID="lbl_code" runat="server" Text="קוד נוכחי:"></asp:Label>
            </td>
            <td>
                <asp:Label ID="lbl_now" runat="server" onload="lbl_now_Load"></asp:Label>
            </td>
        </tr>
        <tr>
            <td>
                <asp:Label ID="lbl_rep" runat="server" Text="לשינוי הקוד:"></asp:Label>
            </td>
            <td>
                <asp:Button ID="btn_rep" runat="server" Text="לחץ כאן" 
                    onclick="btn_rep_Click" CausesValidation="False" />
            </td>
        </tr>
        <tr>
            <td>
                <asp:Label ID="lbl_pas" runat="server" Text="הכנס סיסמתך:" Visible="False"></asp:Label>
            </td>
            <td>
                <asp:TextBox ID="txt_pas" runat="server" TextMode="Password" Visible="False"></asp:TextBox>
                <asp:RequiredFieldValidator ID="rfv1" runat="server" 
                    ControlToValidate="txt_pas" ErrorMessage="RequiredFieldValidator">נא הקלד 
                סיסמתך</asp:RequiredFieldValidator>
            </td>
        </tr>
        <tr>
            <td>
                <asp:Label ID="lbl_new" runat="server" Text="הכנס קוד חדש:" Visible="False"></asp:Label>
            </td>
            <td>
                <asp:TextBox ID="txt_new" runat="server" Visible="False"></asp:TextBox>
                <asp:RegularExpressionValidator ID="REV1" runat="server" 
                    ControlToValidate="txt_new" ErrorMessage="RegularExpressionValidator" 
                    ValidationExpression="\d{4}">קוד חייב להכיל 4 ספרות</asp:RegularExpressionValidator>
            </td>
        </tr>
        <tr>
            <td>
                <asp:Button ID="btn_exe" runat="server" Text="לשינוי קוד" 
                    onclick="btn_exe_Click" Visible="False" />
            </td>
            <td>
                <asp:Button ID="btn_can" runat="server" Text="לביטול" 
                    CausesValidation="False" onclick="btn_can_Click" Visible="False" />
            </td>
        </tr>
    </table>
    
</asp:Content>

