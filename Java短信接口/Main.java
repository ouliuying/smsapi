package com.company.xy;

import java.util.HashMap;
import java.util.Map;

public class Main {

    public static void main(String[] args) {
	// write your code here
        SmsSender sender=new SmsSender();
        sender.SetApiUrl("http://sms.ikyun.net/apiex/sms/ebpbcons");
        sender.SetAppID("c0cb7b8ad8e64296a88c99d923345148");
        sender.SetAppKey("c4d963e9158444b7b71e52fb205eb1c3");
        String msg="你好！！！";
        String retmsg= sender.Send("18621991588",msg,"88");
        System.out.println(retmsg);
        retmsg= sender.GetAmont();
        System.out.println(retmsg);
        retmsg= sender.GetReplyMsg();
        System.out.println(retmsg);

    }
}
