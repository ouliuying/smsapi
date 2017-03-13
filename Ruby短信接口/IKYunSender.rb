require 'time'
require 'digest'
require 'net/https'
class IKYunSender#No indent python example writen by ouyang2008
    def initialize(apiurl,appid,appkey)
        @mapiurl=apiurl
        @mappid=appid
        @mappkey=appkey
    end
    def send(mobile,extno,msg)
        timestamp=self._getTimeStamp()
        puts(timestamp)
        digest=self._signDigest(mobile,timestamp)
        params={"ac":"sendsms","mobile":mobile,"extno":extno,"appid":@mappid,"digest":digest,"msg":msg,"timestamp":timestamp}
        puts(params)
        uri = URI(@mapiurl)
        ret=Net::HTTP.post_form(uri,params)
        return ret.body
    end
    def getAmount()
        timestamp=self._getTimeStamp()
        puts(timestamp)
        digest=self._signDigest("",timestamp)
        params={"ac":"getamount","appid":@mappid,"digest":digest,"timestamp":timestamp}
        puts(params)
        uri = URI(@mapiurl)
        ret=Net::HTTP.post_form(uri,params)
        return ret.body
    end
    def getReplyMsg()
        timestamp=self._getTimeStamp()
        puts(timestamp)
        digest=self._signDigest("",timestamp)
        params={"ac":"fetchreply","appid":@mappid,"digest":digest,"timestamp":timestamp}
        uri = URI(@mapiurl)
        ret=Net::HTTP.post_form(uri,params)
        return ret.body
    end
    def _signDigest(mobile,timestamp)
        m1=Digest::MD5.new
        m1.update(@mappkey.encode("utf-8"))
        digestappkey=m1.hexdigest
        puts(digestappkey)
        srcd=@mappid+digestappkey+timestamp+mobile
        puts(srcd)
        m2=Digest::MD5.new
        m2.update(srcd.encode("utf-8"))
        return m2.hexdigest
    end
    def _getTimeStamp()
        return Time.now.utc.to_i.to_s
    end
    def test
    puts "rb test !"
    end
end
