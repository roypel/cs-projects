<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="UserEdit.aspx.cs" Inherits="UserEdit" Title="Untitled Page" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <center>
    <div>
    <table>
        <tr>
            <td>
                <asp:Label ID="lbl1" runat="server" Text="שם משתמש"></asp:Label>
            </td>
            <td>
                <asp:Label ID="lbl_use" runat="server" onload="lbl_use_Load"></asp:Label>
                <asp:TextBox ID="txt_use" runat="server" Visible="False"></asp:TextBox>
            </td>
            <td>
                <asp:RequiredFieldValidator ID="rfv1" runat="server" 
                    ErrorMessage="RequiredFieldValidator" ControlToValidate="txt_use">יש להכניס 
                שם משתמש</asp:RequiredFieldValidator>
            </td>
        </tr>
        <tr>
            <td>
                <asp:Label ID="lbl2" runat="server" Text="שם פרטי"></asp:Label>
            </td>
            <td>
                <asp:Label ID="lbl_fir" runat="server" Text="Label"></asp:Label>
                <asp:TextBox ID="txt_fir" runat="server" Visible="False"></asp:TextBox>
            </td>
            <td>
                <asp:RequiredFieldValidator ID="rfv2" runat="server" 
                    ErrorMessage="RequiredFieldValidator" ControlToValidate="txt_fir">יש לכניס 
                שם פרטי</asp:RequiredFieldValidator>
            </td>
        </tr>
        <tr>
            <td>
                <asp:Label ID="lbl3" runat="server" Text="שם משפחה"></asp:Label>
            </td>
            <td>
                <asp:Label ID="lbl_las" runat="server" Text="Label"></asp:Label>
                <asp:TextBox ID="txt_las" runat="server" Visible="False"></asp:TextBox>
            </td>
            <td>
                <asp:RequiredFieldValidator ID="rfv3" runat="server" 
                    ErrorMessage="RequiredFieldValidator" ControlToValidate="txt_las">יש להכניס 
                שם משפחה</asp:RequiredFieldValidator>
            </td>
        </tr>
        <tr>
            <td>
                <asp:Label ID="lbl4" runat="server" Text="סיסמא"></asp:Label><br />
            </td>
            <td>
                <asp:Button ID="btn_show" runat="server" Text="להצגת סיסמא" 
                    onclick="btn_show_Click" CausesValidation="False" />
                <asp:Label ID="lbl_pass" runat="server" Text="Label" Visible="false"></asp:Label>
                <asp:TextBox ID="txt_pass" runat="server" Visible="false" TextMode="Password"></asp:TextBox><br />
            </td>
            <td>
                <asp:RequiredFieldValidator ID="rfv4" runat="server" 
                    ErrorMessage="RequiredFieldValidator" ControlToValidate="txt_pass">יש לכניס 
                סיסמה חדשה</asp:RequiredFieldValidator>
            </td>
        </tr>
        <tr>
            <td>
                <asp:Label ID="lbl5" runat="server" Text="אימות סיסמה" Visible="False"></asp:Label>
            </td>
            <td>
                <asp:TextBox ID="txt_ver" runat="server" Visible="false" TextMode="Password"></asp:TextBox>
            </td>
            <td>
                <asp:CompareValidator ID="CV1" runat="server" ControlToCompare="txt_ver" 
                    ControlToValidate="txt_pass" ErrorMessage="CompareValidator">סיסמאות לא 
                תואמות</asp:CompareValidator>
            </td>
        </tr>
        <tr>
            <td>
                <asp:Label ID="lbl6" runat="server" Text="הקלד סיסמה ישנה" Visible="False"></asp:Label>
            </td>
            <td>
                <asp:TextBox ID="txt_prev" runat="server" TextMode="Password" Visible="False"></asp:TextBox>
            </td>
            <td>
                <asp:RequiredFieldValidator ID="rfv5" runat="server" 
                    ErrorMessage="RequiredFieldValidator" ControlToValidate="txt_prev">יש להכניס 
                סיסמה ישנה</asp:RequiredFieldValidator>
            </td>
        </tr>
        <tr>
            <td>
                <asp:Label ID="lbl7" runat="server" Text="כתובת אימייל"></asp:Label>
            </td>
            <td>
                <asp:Label ID="lbl_ema" runat="server" Text="Label"></asp:Label>
                <asp:TextBox ID="txt_ema" runat="server" Visible="False"></asp:TextBox>
            </td>
            <td>
                <asp:RegularExpressionValidator ID="rev1" runat="server" 
                    ErrorMessage="RegularExpressionValidator" ControlToValidate="txt_ema" 
                    ValidationExpression="\w+([-+.']\w+)*@\w+([-.]\w+)*\.\w+([-.]\w+)*">כתובת 
                אימייל לא תקינה</asp:RegularExpressionValidator>
            </td>
        </tr>
        <tr>
            <td>
                <asp:Button ID="btn_del" runat="server" Text="מחיקת משתמש" 
                    onclick="btn_del_Click" CausesValidation="False" />
            </td>
            <td>
                <asp:Label ID="lbl_del" runat="server" 
                    Text="שים לב! שחזור משתמש יוכל להתבצע רק על ידי מנהל!" 
                    Font-Bold="True" ForeColor="Red" Visible="False"></asp:Label>
            </td>
        </tr>
        <tr>
            <td>
                <asp:Button ID="btn_edit" runat="server" Text="לעריכת פרטים" 
                    onclick="btn_edit_Click" CausesValidation="False" />
                <asp:Button ID="btn_sav" runat="server" Text="שמירה" Visible="False" 
                    onclick="btn_sav_Click" />
                <br />
                <asp:Button ID="btn_can" runat="server" Text="ביטול" Visible="False" 
                    onclick="btn_can_Click" CausesValidation="False" />
            </td>
            <td>
                   <asp:Label ID="lbl_del1" runat="server" 
                    Text="בנוסף לא ניתן להירשם שנית עם שם משתמש שנמחק" 
                    Font-Bold="True" ForeColor="Red" Visible="False"></asp:Label>
            </td>
        </tr>
        </table>
    </div>
    </center>
</asp:Content>

