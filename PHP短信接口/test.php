<?php
use \ikyun\smsapi as iapi;
error_reporting(E_ALL);
require_once('smssender.php');
$sender=new iapi\SmsSender();
$sender->setAppID("c0cb7b8ad8e64296a88c99d923345148");
$sender->setAppKey("c4d963e9158444b7b71e52fb205eb1c3");
$sender->setApiUrl("http://sms.ikyun.net/apiex/sms/ebpbcons");//ebpbcons 必须被换掉 用户自己的标识
$msg=" 你好！！！";
$ret=$sender->sendSms("186219915xx,186219915xx33",$msg,"88");
if($ret===FALSE)
{
    echo "$ret {$sender->getLastErrorMsg()}";
}
else {
    echo $ret;
}
$ret=$sender->getAmount();
if($ret===FALSE)
{
    echo "$ret {$sender->getLastErrorMsg()}";
}
else {
    echo $ret;
}
$ret=$sender->getReplyMsg();
if($ret===FALSE)
{
    echo "$ret {$sender->getLastErrorMsg()}";
}
else {
    echo $ret;
}
