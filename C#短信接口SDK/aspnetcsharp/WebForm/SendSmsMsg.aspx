<%@ Page Title="" Language="C#" MasterPageFile="~/WebForm/Main.Master" AutoEventWireup="true" CodeBehind="SendSmsMsg.aspx.cs" Inherits="aspnetcsharp.WebForm.SendSmsMsg" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder2" runat="server">
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <h3 class="testheader">发送短信</h3>

        <div class="form-group">
    <label for="">App连接:</label>
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
        <div class="form-group">
    <label for="">手机号:<span class="label label-danger" >多个号码用英文逗号隔开</span></label>
         <asp:TextBox ID="mobile" runat="server" CssClass="form-control"></asp:TextBox>
  </div>

     <div class="form-group">
    <label for="">扩展号:</label>
         <asp:TextBox ID="extno" runat="server" CssClass="form-control"></asp:TextBox>
  </div>
    <div class="form-group">
    <label for="">短信内容:</label>
         <asp:TextBox ID="msg" runat="server" TextMode="MultiLine" CssClass="form-control" style="height:180px;"></asp:TextBox>
  </div>
    <asp:Button ID="Button1" runat="server" Text="确定发送"  CssClass="btn btn-primary" OnClick="Button1_Click"/>
</asp:Content>
<asp:Content ID="Content4" ContentPlaceHolderID="ContentPlaceHolder3" runat="server">
    <label>接口返回信息：</label>
    <asp:TextBox ID="TextBox1" runat="server" TextMode="MultiLine" CssClass="form-control" style="height:180px;"></asp:TextBox>
</asp:Content>