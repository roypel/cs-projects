<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="SignUp.aspx.cs" Inherits="SignUp" Title="Untitled Page" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <center>
    <table style="font-family: Tahoma">
    <tr>
    <td colspan="3">
        <asp:Label ID="lbl1" runat="server" Text="הרשמה" Font-Size="X-Large" Font-Names="Tahoma"></asp:Label>
    </td>
    </tr>
        <tr>
        <td>
            <asp:Label ID="lbl2" runat="server" Text="שם משתמש" Font-Names="Tahoma"></asp:Label>
        </td>
        <td> 
            <asp:TextBox ID="txt_user" runat="server"></asp:TextBox>
        </td>
        <td>
            <asp:RequiredFieldValidator ID="rf1" runat="server" ErrorMessage="RequiredFieldValidator" ControlToValidate="txt_user">הכנס שם משתמש</asp:RequiredFieldValidator>
        </td>
        </tr>
        <tr>
        <td>
            <asp:Label ID="lbl3" runat="server" Text="סיסמה" Font-Names="Tahoma"></asp:Label>
        </td>
        <td>
            <asp:TextBox ID="txt_pass" runat="server" TextMode="Password"></asp:TextBox>
        </td>
        <td>
            <asp:RequiredFieldValidator ID="rf2" runat="server" ErrorMessage="RequiredFieldValidator" ControlToValidate="txt_pass">הכנס סיסמה</asp:RequiredFieldValidator>
        </td>
        </tr>
        <tr>
        <td>
            <asp:Label ID="lbl4" runat="server" Text="אימות סיסמה" Font-Names="Tahoma"></asp:Label>
        </td>
        <td>
            <asp:TextBox ID="txt_ver" runat="server" TextMode="Password"></asp:TextBox>
        </td>
        <td>
            <asp:CompareValidator ID="cv1" runat="server" ErrorMessage="CompareValidator" ControlToCompare="txt_pass" ControlToValidate="txt_ver">סיסמאות לא תואמות</asp:CompareValidator>
        </td>
        </tr>
        <tr>
        <td>
            <asp:Label ID="lbl5" runat="server" Text="שם פרטי" Font-Names="Tahoma"></asp:Label>
            
        </td>
        <td>
            <asp:TextBox ID="txt_fir" runat="server"></asp:TextBox>
        </td>
        <td>
            <asp:RequiredFieldValidator ID="rf3" runat="server" ErrorMessage="RequiredFieldValidator" ControlToValidate="txt_fir">הכנס שם פרטי</asp:RequiredFieldValidator>
        </td>
        </tr>
        <tr>
        <td>
            <asp:Label ID="lbl6" runat="server" Text="שם משפחה" Font-Names="Tahoma"></asp:Label>
        </td>
        <td>
            <asp:TextBox ID="txt_las" runat="server"></asp:TextBox>
        </td>
        <td>
            <asp:RequiredFieldValidator ID="rf4" runat="server" 
                ErrorMessage="RequiredFieldValidator" ControlToValidate="txt_las">הכנס שם משפחה</asp:RequiredFieldValidator>
        </td>
        </tr>
        <tr>
        <td>
            <asp:Label ID="lbl_email" runat="server" Text="כתובת אימייל*"></asp:Label>
        </td>
        <td>
            <asp:TextBox ID="txt_ema" runat="server"></asp:TextBox>
        </td>
        <td>
            <asp:RegularExpressionValidator ID="rev1" runat="server" 
                ErrorMessage="RegularExpressionValidator" ControlToValidate="txt_ema" 
                ValidationExpression="\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*">כתובת לא 
            תקינה</asp:RegularExpressionValidator>
        </td>
        </tr>
        <tr>
        <td colspan="3">
        <br />
            <asp:RadioButtonList ID="rbl1" runat="server" OnSelectedIndexChanged="rbl1_SelectedIndexChanged" Font-Names="Tahoma" AutoPostBack="True">
                <asp:ListItem Value="3" Selected="True">תלמיד</asp:ListItem>
                <asp:ListItem Value="2">מורה</asp:ListItem>
                <asp:ListItem Value="1">מנהל</asp:ListItem>
            </asp:RadioButtonList>
        </td>
        </tr>
        <tr>
        <td>
            <asp:Label ID="lbl7" runat="server" Text="קוד אישור" Visible="False" Font-Names="Tahoma"></asp:Label>
        </td>
        <td>
            <asp:TextBox ID="txt_pre" runat="server" Visible="False" TextMode="Password" Font-Names="Tahoma"></asp:TextBox>
        </td>
        <td>
            <asp:RangeValidator ID="rv1" runat="server" ErrorMessage="RangeValidator" ControlToValidate="txt_pre" MaximumValue="9999" MinimumValue="0">מספר לא תקין</asp:RangeValidator>
        </td>
        </tr>
        <tr>
        <td colspan="3">
            <asp:Label ID="lbl_exp" runat="server" 
                Text="*ללא כתובת אימייל אין אפשרות לשחזר פרטי משתמש"></asp:Label>
        </td>
        </tr>
        <tr>
        <td>
            <asp:Button ID="btn_send" runat="server" Text="שליחה" OnClick="btn_send_Click" Font-Names="Tahoma" />
        </td>
        <td>
            &nbsp;<asp:Button ID="btn_erase" runat="server" Font-Names="Tahoma" OnClick="btn_erase_Click"
                Text="מחיקה" CausesValidation="False" />
        </td>
        <td>
            <asp:Button ID="btn_back" runat="server" Text="חזרה" onclick="btn_back_Click" 
                style="font-family: Tahoma" CausesValidation="False" />
        </td>
        </tr>
        <tr>
        <td colspan="3">
            <asp:Label ID="lbl8" runat="server" Text="קוד אישור שגוי" Visible="False" Font-Bold="True" Font-Names="Tahoma" Font-Size="Medium" ForeColor="Red"></asp:Label>
            <asp:Label ID="lbl9" runat="server" Text="שם משתמש תפוס" Visible="False" Font-Bold="True" Font-Names="Tahoma" Font-Size="Medium" ForeColor="Red"></asp:Label>
            <asp:Label ID="lbl10" runat="server" Text="כתובת אימייל בשימוש" Visible="False" ForeColor="Red" Font-Bold="True"></asp:Label>
        </td>
        </tr>        
</table>
</center>
</asp:Content>

