<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="NewMsg.aspx.cs" Inherits="NewMsg" Title="Untitled Page" %>
<%@ Register Assembly="CKEditor.NET" Namespace="CKEditor.NET" TagPrefix="CKEditor" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <table>
        <tr>
            <td>
                <asp:Label ID="lbl_brd" runat="server" Text="הלוח בו ההודעה תתפרסם"></asp:Label>
            </td>
            <td>
                <asp:DropDownList ID="ddl1" runat="server">
                    <asp:ListItem Value="1">מורים</asp:ListItem>
                    <asp:ListItem Value="2">תלמידים</asp:ListItem>
                    <asp:ListItem Value="3">שני הלוחות</asp:ListItem>
                </asp:DropDownList>
            </td>
            <td rowspan="3">
                <asp:Calendar ID="Cnd1" runat="server" Visible="False"></asp:Calendar>
            </td>
        </tr>
        <tr>
            <td>
                <asp:Label ID="lbl1" runat="server" Text="טיוטה?"></asp:Label>
            </td>
            <td>
                <asp:CheckBox ID="CB_draft" runat="server" />
            </td>
        </tr>
        <tr>
            <td>
                <asp:Label ID="lbl2" runat="server" Text="למחוק הודעה בתאריך מסויים?"></asp:Label>
            </td>
            <td>
                <asp:CheckBox ID="CB_date" runat="server" AutoPostBack="True" 
                    oncheckedchanged="CB_date_CheckedChanged" />
            </td>
        </tr>
        <tr>
            <td colspan="2">
                <CKEditor:CKEditorControl ID="CKE1" runat="server" ResizeEnabled="False" 
                            Toolbar="ToolbarBasic" 
                            ToolbarBasic="Cut|Copy|Paste|-|Print
Undo|Redo|-|Find|Replace|-|SelectAll
/
Bold|Italic|Underline|Strike
JustifyLeft|JustifyCenter|JustifyRight|JustifyBlock
BidiLtr|BidiRtl
Link|Unlink|Anchor
Image|Smiley|SpecialChar|PageBreak|Iframe
/
Styles|Format|Font|FontSize
TextColor|BGColor
About" 
                            ToolbarCanCollapse="False"></CKEditor:CKEditorControl>
            </td>
        </tr>
        <tr>
            <td colspan="2">
                <asp:Button ID="btn_snd" runat="server" Text="שלח הודעה" 
                            onclick="btn_snd_Click" />
            </td>
        </tr>
    </table>
</asp:Content>

