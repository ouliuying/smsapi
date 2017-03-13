#!/usr/bin/env python
# -*- coding: utf-8 -*-
import ikyunsender
sender=ikyunsender.IkYunSender("http://sms.ikyun.net/abcapi/sms/ebpbcons","c0cb7b8ad8e64296a88c99d923345148","c4d963e9158444b7b71e52fb205eb1c3")
msgs="你哄啊！！！"
retmsg=sender.send("186219915xx,186219915yy","88",msg)
print retmsg
retmsg=sender.getAmount()
print retmsg
retmsg=sender.getReplyMsg()
print retmsg
