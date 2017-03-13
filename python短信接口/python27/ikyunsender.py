import httplib
import md5
import time
import urllib
import urlparse
class IkYunSender:#code by ouyang2008,and it is free
    def __init__(self,apiurl,appid,appkey):
        self.ApiUrl=apiurl
        self.AppID=appid
        self.AppKey=appkey
        self._parseApiUrl()
    def send(self,mobile,extno,msg):
        timestamp=self._getTimeStamp()
        digest=self._signdigest(mobile,timestamp)
        params = {"ac":'sendsms','mobile': mobile,'appid':self.AppID, 'extno': extno, 'msg': msg,'digest':digest,'timestamp':timestamp}
        print params
        return self._post(urllib.urlencode(params))

    def _signdigest(self,mobile,timestamp):
         m = md5.new()
         m.update(self.AppKey)
         appkeydigest=m.hexdigest()
         print appkeydigest
         #print appkedigest
         m2=md5.new()
         m2.update(self.AppID+appkeydigest+timestamp+mobile)
         hashstr=m2.hexdigest()
         return hashstr

    def _post(self,data):
        conn = None
        try:
            headers = {"Content-type": "application/x-www-form-urlencoded;charset=utf8"}
            print self.Host
            conn = httplib.HTTPConnection(self.Host, 80, timeout=200)
            print self.Uri
            conn.request("POST", self.Uri, data, headers)
            response = conn.getresponse()
            retmsg = response.read().decode("utf8")
            conn.close()
            return retmsg
        except Exception, e:
           print e
        finally:
           if conn:
              conn.close()


    def getAmount(self):
        timestamp=self._getTimeStamp()
        digest=self._signdigest('',timestamp)
        params = {"ac":'getamount','appid':self.AppID, 'digest':digest,'timestamp':timestamp}
        print params
        return self._post(urllib.urlencode(params))
    def getReplyMsg(self):
        timestamp=self._getTimeStamp()
        digest=self._signdigest('',timestamp)
        params = {"ac":'fetchreply','appid':self.AppID, 'digest':digest,'timestamp':timestamp}
        print params
        return self._post(urllib.urlencode(params))
    def _getTimeStamp(self):
        return str(long(time.time()))
    def _parseApiUrl(self):
        urltup=urlparse.urlparse(self.ApiUrl)
        self.Host=urltup.hostname
        self.Uri=urltup.path
