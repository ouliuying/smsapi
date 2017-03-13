package main
import "ikyunapi"
import "fmt"
/* author:ouyang2008 ,code is free*/
func main(){
    smssender:=ikyunapi.New("http://sms.ikyun.net/apiex/sms/ebpbcons","c0cb7b8ad8e64296a88c99d923345148","c4d963e9158444b7b71e52fb205eb1c3")
    msg :="你好";
    retmsg:=smssender.Send("186219915xx,186219915yy","88",msg)
    fmt.Println(retmsg)
    retmsg=smssender.GetAmount()
    fmt.Println(retmsg)
    retmsg=smssender.GetReplyMsg()
    fmt.Println(retmsg)
    /*fmt.Print("")
    ikyunapi.Test()*/
}
