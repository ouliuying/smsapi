VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "Form1"
   ClientHeight    =   5175
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   11490
   LinkTopic       =   "Form1"
   ScaleHeight     =   5175
   ScaleWidth      =   11490
   StartUpPosition =   3  '´°¿ÚÈ±Ê¡
   Begin VB.CommandButton Command1 
      Caption         =   "²âÊÔ"
      Height          =   615
      Left            =   3720
      TabIndex        =   0
      Top             =   2280
      Width           =   2055
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Sub Command1_Click()
 Dim iksender As New SmsSender
 Dim retmsg As String
 Dim msg As String
 msg = "ÄãºÃ"
 iksender.ApiUrl = "http://sms.ikyun.net/apiex/sms/ebpbcons"
 iksender.AppID = "c0cb7b8ad8e64296a88c99d923345148"
 iksender.AppKey = "c4d963e9158444b7b71e52fb205eb1c3"

 retmsg = iksender.Send("186219915xx,186219915uu", "88", msg)
 MsgBox retmsg
 
 retmsg = iksender.GetAmount()
 MsgBox retmsg
  retmsg = iksender.GetReplyMsg()
 MsgBox retmsg
 
 
End Sub
