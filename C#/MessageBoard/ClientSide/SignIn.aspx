<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="SignIn.aspx.cs" Inherits="SignIn" Title="Untitled Page" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
<center>
<table>
<tr>
<td colspan="3" align="center">
    <asp:Label ID="lbl0" runat="server" Text="התחברות" Font-Names="Tahoma" Font-Size="Large"></asp:Label>
</td>
</tr>
<tr>
  <td>
      <asp:Label ID="lbl1" runat="server" Text="שם משתמש" Font-Names="Tahoma"></asp:Label>
            </td>
<td>
    <asp:TextBox ID="txt_user" runat="server"></asp:TextBox></td>
                <td>
                    <asp:RequiredFieldValidator ID="rfv1" runat="server" 
                        ErrorMessage="RequiredFieldValidator" ControlToValidate="txt_user">לא הוקלד 
                    שם משתמש</asp:RequiredFieldValidator>
                </td>
            </tr>
            <tr>
            <td>
                <asp:Label ID="lbl2" runat="server" Text="סיסמה" Font-Names="Tahoma"></asp:Label>
            </td>
<td>
    <asp:TextBox ID="txt_pass" runat="server" TextMode="Password"></asp:TextBox></td>
        <td>
            <asp:RequiredFieldValidator ID="rfv2" runat="server" 
                ErrorMessage="RequiredFieldValidator" ControlToValidate="txt_pass">לא הוקלדה 
            סיסמה</asp:RequiredFieldValidator>
        </td>
    </tr>
    <tr>
        <td>
                <asp:Button ID="btn_log" runat="server" Text="התחברות" OnClick="btn_log_Click" Font-Names="Tahoma" />
       </td>
       <td>
           <asp:Button ID="btn_sign" runat="server" Text="לדף הרשמה" 
               OnClick="btn_sign_Click" Font-Names="Tahoma" CausesValidation="False" />
        </td>
        <td>
            <asp:HyperLink ID="hl1" runat="server" Text="שכחת פרטייך?" ForeColor="Blue" 
                NavigateUrl="~/Retrive.aspx"></asp:HyperLink>
        </td>
    </tr>
      
    </table>
    </center>
</asp:Content>

