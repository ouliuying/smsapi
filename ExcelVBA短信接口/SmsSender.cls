VERSION 1.0 CLASS
BEGIN
  MultiUse = -1  'True
END
Attribute VB_Name = "SmsSender"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = False
Attribute VB_Exposed = False
Option Explicit



Private mApiUrl As String
Private mAppKey As String
Private mAppID As String
Private Declare Function WideCharToMultiByte Lib "kernel32" ( _
    ByVal CodePage As Long, _
    ByVal dwFlags As Long, _
    ByVal lpWideCharStr As Long, _
    ByVal cchWideChar As Long, _
    ByVal lpMultiByteStr As Long, _
    ByVal cbMultiByte As Long, _
    ByVal lpDefaultChar As Long, _
    ByVal lpUsedDefaultChar As Long) As Long
    
' CodePage constant for UTF-8
Private Const CP_UTF8 = 65001

''' Return byte array with VBA "Unicode" string encoded in UTF-8
Public Function Utf8BytesFromString(strInput As String) As Variant
    Dim nBytes As Long
    Dim abBuffer() As Byte
    ' Get length in bytes *including* terminating null
    nBytes = WideCharToMultiByte(CP_UTF8, 0&, ByVal StrPtr(strInput), -1, vbNull, 0&, 0&, 0&)
    ' We don't want the terminating null in our byte array, so ask for `nBytes-1` bytes
    ReDim abBuffer(nBytes - 2)  ' NB ReDim with one less byte than you need
    nBytes = WideCharToMultiByte(CP_UTF8, 0&, ByVal StrPtr(strInput), -1, ByVal VarPtr(abBuffer(0)), nBytes - 1, 0&, 0&)
    Utf8BytesFromString = abBuffer
End Function

Public Property Let ApiUrl(ByRef apiurlval As String)
    mApiUrl = apiurlval
End Property

Public Property Let AppKey(ByRef appkeyval As String)
    mAppKey = appkeyval
    
End Property
Public Property Let AppID(ByRef appidval As String)
    mAppID = appidval
End Property

Private Function pvToByteArray(sText As String) As Byte()
   pvToByteArray = Utf8BytesFromString(sText)
End Function

Public Function Send(ByRef mobile As String, ByRef extno As String, ByRef msg As String) As String


             Dim postdata As String
             Dim objHttp
             Dim retmsg
             Dim digest
             On Error Resume Next
             Dim timestamp As String
             timestamp = getTimeStamp()
             digest = signDigest(mobile, timestamp)
             postdata = "ac=sendsms&mobile=" & mobile & "&extno=" & extno & "&appid=" & mAppID & "&digest=" & digest & "&timestamp=" & timestamp & "&msg=" & msg
        
  
            MsgBox postdata
            Dim HttpClient As Object
            Set HttpClient = CreateObject("Microsoft.XMLHTTP")
            HttpClient.Open "POST", mApiUrl, False
            HttpClient.setRequestHeader "Content-type", "application/x-www-form-urlencoded"
            HttpClient.setRequestHeader "CharSet", "UTF-8"
            HttpClient.Send pvToByteArray(postdata)
            retmsg = Trim(HttpClient.responseText)
            Set HttpClient = Nothing
            Send = retmsg

End Function
Private Function signDigest(mobile As String, timestamp As String) As String
signDigest = LCase(MD5(mAppID & MD5(mAppKey) & timestamp & mobile))
End Function

Private Function MD5(val As String) As String
 MD5 = LCase(BasMD5.MD5_string(val))
End Function

Private Function getTimeStamp() As String
 Dim utcnow
 utcnow = DateAdd("h", -8, Now)
getTimeStamp = DateDiff("s", "01/01/1970 00:00:00", utcnow)

End Function

Public Function GetAmount() As String
  Dim postdata As String
             Dim objHttp
             Dim retmsg
             Dim digest
             On Error Resume Next
             Dim timestamp As String
             timestamp = getTimeStamp()
             digest = signDigest("", timestamp)
             postdata = "ac=getamount&appid=" & mAppID & "&digest=" & digest & "&timestamp=" & timestamp
        
            MsgBox postdata
            Dim HttpClient As Object
            Set HttpClient = CreateObject("Microsoft.XMLHTTP")
            HttpClient.Open "POST", mApiUrl, False
            HttpClient.setRequestHeader "Content-type", "application/x-www-form-urlencoded"
            HttpClient.setRequestHeader "CharSet", "UTF-8"
            HttpClient.Send pvToByteArray(postdata)
            retmsg = Trim(HttpClient.responseText)
            Set HttpClient = Nothing
            GetAmount = retmsg

End Function
Public Function GetReplyMsg() As String
             Dim postdata As String
             Dim objHttp
             Dim retmsg
             Dim digest
             On Error Resume Next
             Dim timestamp As String
             timestamp = getTimeStamp()
             digest = signDigest("", timestamp)
             postdata = "ac=fetchreply&appid=" & mAppID & "&digest=" & digest & "&timestamp=" & timestamp
        
            MsgBox postdata
            Dim HttpClient As Object
            Set HttpClient = CreateObject("Microsoft.XMLHTTP")
            HttpClient.Open "POST", mApiUrl, False
            HttpClient.setRequestHeader "Content-type", "application/x-www-form-urlencoded"
            HttpClient.setRequestHeader "CharSet", "UTF-8"
            HttpClient.Send pvToByteArray(postdata)
            retmsg = Trim(HttpClient.responseText)
            Set HttpClient = Nothing
            GetReplyMsg = retmsg

End Function

