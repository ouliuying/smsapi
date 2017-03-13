<%@ Page Title="" Language="C#" MasterPageFile="~/WebForm/Main.Master" AutoEventWireup="true" CodeBehind="GetReplyMsg.aspx.cs" Inherits="aspnetcsharp.WebForm.GetReplyMsg" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder2" runat="server">
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <h3 class="testheader">获取剩余金额</h3>
      <div class="form-group">
    <label for="">接口连接:</label>
         <asp:TextBox ID="apiurl" runat="server" CssClass="form-control"></asp:TextBox>
  </div>
     <div class="form-group">
    <label for="">AppID:</label>
         <asp:TextBox ID="appid" runat="server" CssClass="form-control"></asp:TextBox>
  </div>
    <div class="form-group">
    <label for="">AppKey:</label>
         <asp:TextBox ID="appkey" runat="server" CssClass="form-control"></asp:TextBox>
  </div>
    <asp:Button ID="Button1" runat="server" Text="确定"  CssClass="btn btn-primary" OnClick="Button1_Click"/>
</asp:Content>
<asp:Content ID="Content4" ContentPlaceHolderID="ContentPlaceHolder3" runat="server">
    <label>接口返回信息：</label>
    <asp:TextBox ID="TextBox1" runat="server" TextMode="MultiLine" CssClass="form-control" style="height:180px;"></asp:TextBox>
</asp:Content>


