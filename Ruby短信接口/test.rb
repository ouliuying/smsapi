require './IKYunSender'
sender=IKYunSender.new("http://sms.ikyun.net/apiex/sms/ebpbcons","c0cb7b8ad8e64296a88c99d923345148","c4d963e9158444b7b71e52fb205eb1c3")
msg="ruby!"
retmsg=sender.send("186219915xx,186219915yy","88",msg)
puts(retmsg)
retmsg=sender.getAmount()
puts(retmsg)
retmsg=sender.getReplyMsg()
puts(retmsg)
