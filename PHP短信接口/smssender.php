<?php
/*
author: ouyang2008
 code is free
*/
namespace ikyun\smsapi;
require_once('HttpClient.php');
class SmsSender
{
    private $appid="";
    private $appkey="";
    private $errormsg="";
    public $apiurl="";
    function getLastErrorMsg()
    {
        return $this->errormsg;
    }
    function setAppID($appid)
    {
        $this->appid=$appid;
    }
    function setAppKey($appkey)
    {
        $this->appkey=$appkey;
    }
    function setApiUrl($url)
    {
        $this->apiurl=$url;
    }
    function getUnixTimeStamp()
    {
        $nowUtc = new \DateTime( 'now',  new \DateTimeZone( 'UTC' ) );
        return date_timestamp_get($nowUtc);
    }
    function sendSms($mobile,$msg,$extno)
    {
       $timestamp=$this->getUnixTimeStamp();
       $digest=md5("$this->appid".md5($this->appkey)."$timestamp"."$mobile");
       $pdata="ac=sendsms&mobile=".$mobile."&extno=".$extno."&appid=".$this->appid."&timestamp=".$timestamp."&digest=".$digest."&msg=".$msg;
       $http=new HttpClient();
       $ret=$http->post($this->apiurl,$pdata);
       if(!$ret)
       {
          return FALSE;
       }
       return $ret;
    }
    //获取剩余金额
    function getAmount()
    {
       $timestamp=$this->getUnixTimeStamp();
       $digest=md5("$this->appid".md5($this->appkey)."$timestamp");
       $senddata="ac=getamount&appid=".$this->appid."&timestamp=".$timestamp."&digest=".$digest;
       $http=new HttpClient();
       $ret=$http->post($this->apiurl,$senddata);
       if(!$ret)
       {
          return FALSE;
       }
       return $ret;
    }
    //获取回复信息
    function getReplyMsg()
    {
       $timestamp=$this->getUnixTimeStamp();
       $digest=md5("$this->appid".md5($this->appkey)."$timestamp");
       $senddata="ac=fetchreply&appid=".$this->appid."&timestamp=".$timestamp."&digest=".$digest."&scopetype=0";
       $http=new HttpClient();
       $ret=$http->post($this->apiurl,$senddata);
       if(!$ret)
       {
          return FALSE;
       }
       return $ret;
    }
}
