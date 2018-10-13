<%@ Page Language="C#" MasterPageFile="~/MasterPage.master" AutoEventWireup="true" CodeFile="Home.aspx.cs" Inherits="Home" Title="Untitled Page" %>

<asp:Content ID="Content1" ContentPlaceHolderID="head" Runat="Server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder1" Runat="Server">
    <div>
    <center>
        <asp:Label ID="lbl_name" runat="server" Text="שלום " Font-Size="X-Large" 
            onload="lbl_name_Load"></asp:Label>
    </center>
    </div>
</asp:Content>

