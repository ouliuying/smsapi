VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "Sheet1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = True
Sub IKYUN_SMS_SENDER()
 Dim iksender As New SmsSender
 Dim retmsg As String
 Dim msg As String
 Dim msgitem1 As String
 Dim msgitem2 As String
 Dim mobile As String
 
   For r = 1 To Worksheets(1).UsedRange.Rows.Count
        mobile = Worksheets(1).Cells(r, 1).value
        msgitem1 = Worksheets(1).Cells(r, 2).value
        msgitem2 = Worksheets(1).Cells(r, 3).value
         msg = msgitem1 & "你好" & msgitem2
         iksender.ApiUrl = "http://sms.ikyun.net/apiex/sms/ebpbcons" ' 这个连接必须替换成你帐号的连接
         iksender.AppID = "c0cb7b8ad8e64296a88c99d923345148" ' 替换成你添加的APPID
         iksender.AppKey = "c4d963e9158444b7b71e52fb205eb1c3" ' 替换成你添加APPID的appkey
         '参数c4d963e9158444b7b71e52fb205eb1c3 是短信模版，要替换成自己添加的
         retmsg = iksender.Send(mobile, "88", msg)
         MsgBox retmsg
   Next
   

End Sub
