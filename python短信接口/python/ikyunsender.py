import http.client
import hashlib
import time
import urllib
import urllib.parse
class IkYunSender:#code by ouyang2008,and it is free
    def __init__(self,apiurl,appid,appkey):
        self.ApiUrl=apiurl
        self.AppID=appid
        self.AppKey=appkey
        self._parseApiUrl()
    def send(self,mobile,extno,msg):
        timestamp=self._getTimeStamp()
        digest=self._signdigest(mobile,timestamp)
        params = {"ac":'sendsms','mobile': mobile,'appid':self.AppID, 'extno': extno,'digest':digest,'timestamp':timestamp,'msg':msg}
        print(params)
        return self._post(urllib.parse.urlencode(params))

    def _signdigest(self,mobile,timestamp):
         m = hashlib.md5()
         m.update(self.AppKey.encode("utf-8"))
         appkeydigest=m.hexdigest()
         print(appkeydigest)
         #print appkedigest
         m2=hashlib.md5()
         m2.update((self.AppID+appkeydigest+timestamp+mobile).encode("utf-8"))
         hashstr=m2.hexdigest()
         return hashstr

    def _post(self,data):
        conn = None
        try:
            headers = {"Content-type": "application/x-www-form-urlencoded;charset=utf8"}
            print(self.Host)
            conn = http.client.HTTPConnection(self.Host, 80, timeout=200)
            print(self.Uri)
            conn.request("POST", self.Uri, data, headers)
            response = conn.getresponse()
            retmsg = response.read().decode("utf8")
            conn.close()
            return retmsg
        except  e:
           print(e)
        finally:
           if conn:
              conn.close()

    def getAmount(self):
        timestamp=self._getTimeStamp()
        digest=self._signdigest('',timestamp)
        params = {"ac":'getamount','appid':self.AppID, 'digest':digest,'timestamp':timestamp}
        print(params)
        return self._post(urllib.parse.urlencode(params))
    def getReplyMsg(self):
        timestamp=self._getTimeStamp()
        digest=self._signdigest('',timestamp)
        params = {"ac":'fetchreply','appid':self.AppID, 'digest':digest,'timestamp':timestamp}
        print(params)
        return self._post(urllib.parse.urlencode(params))
    def _getTimeStamp(self):
        return str(int(time.time()))
    def _parseApiUrl(self):
        urltup=urllib.parse.urlparse(self.ApiUrl)
        self.Host=urltup.hostname
        self.Uri=urltup.path
