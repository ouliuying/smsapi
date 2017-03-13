<%@ Page Title="" Language="C#" MasterPageFile="~/WebForm/Main.Master" AutoEventWireup="true" CodeBehind="updatesmstpl.aspx.cs" Inherits="aspnetcsharp.WebForm.updatesmstpl" %>
<asp:Content ID="Content1" ContentPlaceHolderID="head" runat="server">
</asp:Content>
<asp:Content ID="Content2" ContentPlaceHolderID="ContentPlaceHolder2" runat="server">
</asp:Content>
<asp:Content ID="Content3" ContentPlaceHolderID="ContentPlaceHolder1" runat="server">
    <h3 class="testheader">更新短信模版 <span class="label label-danger">参考JSON接口，精简接口不提供该功能</span></h3>
     <div class="form-group">
    <label for="">AppID:</label>
         <asp:TextBox ID="appid" runat="server" CssClass="form-control"></asp:TextBox>
  </div>
    <div class="form-group">
    <label for="">AppKey:</label>
         <asp:TextBox ID="appkey" runat="server" CssClass="form-control"></asp:TextBox>
  </div>
   <div class="form-group">
    <label for="">要更新模版标识:</label>
         <asp:TextBox ID="smstpltag" runat="server" CssClass="form-control"></asp:TextBox>
  </div>
    <div class="form-group">
    <label for="">模版内容:</label>
         <asp:TextBox ID="smstpl" runat="server" TextMode="MultiLine" CssClass="form-control" style="height:180px;"></asp:TextBox>
  </div>
    <asp:Button ID="Button1" runat="server" Text="确定"  CssClass="btn btn-primary" OnClick="Button1_Click"/>
</asp:Content>
<asp:Content ID="Content4" ContentPlaceHolderID="ContentPlaceHolder3" runat="server">
    <label>接口返回信息：</label>
    <asp:TextBox ID="TextBox1" runat="server" TextMode="MultiLine" CssClass="form-control" style="height:180px;"></asp:TextBox>
</asp:Content>
