package ikyunapi
import "fmt"
import "time"
import "crypto/md5"
import "encoding/hex"
import "net/http"
import "net/url"
import "strings"
import "io/ioutil"
/* author:ouyang2008 ,code is free*/
type ikyunapicontext struct{
   APIURL string
   APPID string
   APPKEY string
}

/*
 comment test
*/
type SmsSender interface {
     Send(mobile string,extno string,msg string) string
     GetAmount() string
     GetReplyMsg() string
}
/*
 New test
*/
func New(ApiUrl string,AppID string,AppKey string) SmsSender{
    context:=&ikyunapicontext{ApiUrl,AppID,AppKey}
    return context;
}

func (sender *ikyunapicontext) Send(mobile string,extno string,msg string) string{
    params:=map[string]string{}
    params["ac"]="sendsms"
    params["mobile"]=mobile
    params["extno"]=extno
    params["appid"]=sender.APPID
    timestamp:=sender.getTimeStamp()
    digest:=sender.signDigest(mobile,timestamp)
    params["digest"]=digest
    params["timestamp"]=timestamp
    params["msg"]=msg
    fmt.Println("timestamp=",timestamp)
    fmt.Println("digest=",digest)
    return sender.httppost(params)
}
func (sender *ikyunapicontext) GetAmount() string{
    params:=map[string]string{}
    params["ac"]="getamount"
    params["appid"]=sender.APPID
    timestamp:=sender.getTimeStamp()
    digest:=sender.signDigest("",timestamp)
    params["digest"]=digest
    params["timestamp"]=timestamp
    fmt.Println("timestamp=",timestamp)
    fmt.Println("digest=",digest)
    return sender.httppost(params)
}
func (sender *ikyunapicontext) GetReplyMsg() string{
      params:=map[string]string{}
      params["ac"]="fetchreply"
      params["appid"]=sender.APPID
      timestamp:=sender.getTimeStamp()
      digest:=sender.signDigest("",timestamp)
      params["digest"]=digest
      params["timestamp"]=timestamp
      fmt.Println("timestamp=",timestamp)
      fmt.Println("digest=",digest)
      return sender.httppost(params)
}
func (sender *ikyunapicontext) signDigest(mobile string,timestamp string) string{
       fmt.Println(sender.APPKEY)
       h:=md5.New()
       h.Write(([]byte)(sender.APPKEY))
       var appkeymd5=hex.EncodeToString(h.Sum(nil))
       fmt.Println(appkeymd5)
       var ldg=sender.APPID+appkeymd5+timestamp+mobile
       h2:=md5.New()
       h2.Write(([]byte)(ldg))
       return hex.EncodeToString(h2.Sum(nil))
}
func  (sender *ikyunapicontext) getTimeStamp() string{
     return fmt.Sprint(time.Now().Unix())
}
func (sender *ikyunapicontext) httppost(params map[string]string) string{
      client:=&http.Client{}
      pparams := url.Values{}
       for k, v := range params{
          pparams.Add(k,v);
       }
       req, err := http.NewRequest("POST", sender.APIURL, strings.NewReader(pparams.Encode()))
       if err!=nil{
            return ""
       }
       req.Header.Set("Content-Type", "application/x-www-form-urlencoded")
       resp, err := client.Do(req)
       defer resp.Body.Close()
      body, err := ioutil.ReadAll(resp.Body)
      if err != nil {
            // handle error
      }
      return string(body)
}
