/*
author: ouyang2008
 code is free
*/
var IKyunSmsApi={
    create:function(apiurl,appid,appkey){
        var self={};
        self._request=require('requestify'); 
        self._promise=require("promise")
        self._apiurl=apiurl;
        self._appid=appid;
        self._appkey=appkey;
        self.getTimeStamp=function(){
                return Math.round(Date.now() / 1000) ;
        };
        self.send=function(mobile,extno,msg){
            return new self._promise(function (resolve, reject) {
                var timestamp=self.getTimeStamp();
                var digest=self.signDigest(mobile,timestamp);
                var pdata={ac:"sendsms",mobile:mobile,extno:extno,appid:self._appid,timestamp:timestamp,digest:digest,msg:msg};
                self._request.post(self._apiurl,pdata,{dataType:"form-url-encoded"}).then(function(response){
                    response.getBody();
                    resolve(response.body);
                });
            });
        };
        self.getAmount=function(){
             return new self._promise(function (resolve, reject) {
                var timestamp=self.getTimeStamp();
                var digest=self.signDigest("",timestamp);
                var pdata={ac:"getamount",appid:self._appid,timestamp:timestamp,digest:digest};
                self._request.post(self._apiurl,pdata,{dataType:"form-url-encoded"}).then(function(response){
                    response.getBody();
                    resolve(response.body);
                });
            });
        };
         self.getReplyMsg=function(){
             return new self._promise(function (resolve, reject) {
                 var timestamp=self.getTimeStamp();
                var digest=self.signDigest("",timestamp);
                var pdata={ac:"fetchreply",appid:self._appid,timestamp:timestamp,digest:digest};
                self._request.post(self._apiurl,pdata,{dataType:"form-url-encoded"}).then(function(response){
                    response.getBody();
                    resolve(response.body);
                });
            });
        };
        self.signDigest=function(mobile,timestamp){
            return self.md5(self._appid+self.md5(self._appkey)+timestamp+mobile);
        };
        self.md5=function(data){
            var crypto = require('crypto');
            return crypto.createHash('md5').update(data,'utf8').digest("hex");
        };
        return self;
    }
};
var sender=IKyunSmsApi.create("http://sms.ikyun.net/apiex/sms/ebpbcons","c0cb7b8ad8e64296a88c99d923345148","c4d963e9158444b7b71e52fb205eb1c3");
sender.send("186219915xx,186219915yy","88","你好").then(function(retmsg){
   console.log(retmsg);
});
sender.getAmount().then(function(retmsg){
   console.log(retmsg);
});
sender.getReplyMsg().then(function(retmsg){
   console.log(retmsg);
});

