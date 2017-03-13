<?php
/*
author: ouyang2008
 code is free
*/
 namespace ikyun\smsapi;
 class HttpClient
 {
    private $contenttype="application/x-www-form-urlencoded";
    private $clientcharset="utf-8";
    private $servercharset="utf-8";
    private $useragent="ikyun.net php api/sdk";
    private $accept="text/xml,application/xml,application/xhtml+xml,application/json,text/html;q=0.9,text/plain;q=0.8,*/*;q=0.1";
    private $uripath;
    private $host;
    private $port;
    private $errormsg="";
    function setContentType($string)
    {
        $this->contenttype=$string;
    }
    function setClientCharset($string)
    {
      $this->clientcharset=$string;
    }
    function setServerCharset($string)
    {
    $this->servercharset=$string;
    }
    function setUserAgent($string)
    {
        $this->useragent=$string;
    }
    function post($url,$data)
    {
        return $this->request($url,"POST",$data);
    }
    function get($url)
    {
        return $this->request($url,"GET","");
    }
    function request($url,$method,$postdata)
    {
        if(!$this->parseurl($url))
        {
            return FALSE;
        }
       // debug_zval_dump($url);
        $fsock_exists = function_exists('fsockopen');
        $curl_exists = function_exists('curl_init');
        if($curl_exists)
        {
            return $this->curlrequest($url,$method,$postdata);
        }
        else if($fsock_exists)
        {
           //    echo "socket\n";
            return $this->fsocketrequest($url,$method,$postdata);
        }
        else {
           $this->errormsg="php 配置中没有既没有开放curl,也没有开放fsocket权限！";
           return FALSE;
        }
    }
    function fsocketrequest($url,$method,$postdata)
    {
        //debug_zval_dump($this->port.$this->host);
        if(!($fp=@fsockopen($this->host,$this->port,$error,$errormsg,600)))
        {
            $this->errormsg="初始化套接字失败！";
            return FALSE;
        }
        socket_set_timeout($fp,600);
      //  debug_zval_dump($postdata);
        $reqdata=$this->buildrequestdata($method,$postdata);
       // debug_zval_dump($reqdata);
        if(!@fwrite($fp,$reqdata))
        {
         $this->errormsg="请求失败！";
         return FALSE;
        }
        $respone="";
        while (!feof($fp))
        {
            $respone .= fgets($fp);
        }
        if (!$respone)
        {
            $this->errormsg="服务器无应答！";
            return FALSE;
        }
        $separator = '/\r\n\r\n/';
        list($header, $body) = preg_split($separator, $respone, 2);
        
        return $this->converttoclientcharset($body);
    }
    function buildrequestdata($method,$postdata="")
    {
        $postdata=$this->buildquerystring($postdata);
        $postdata=$this->converttoservercharset($postdata);
        $headers = array();
        $headers[] = "$method {$this->uripath} HTTP/1.0"; 
        $headers[] = "Host: {$this->host}";
        $headers[] = "User-Agent: {$this->useragent}";
        $headers[] = "Accept: {$this->accept}";
    	if ($postdata!="") {
    	    $headers[] = "Content-Type: {$this->contenttype}";
    	    $headers[] = "Content-Length: ".strlen($postdata);
    	}
    	$request = implode("\r\n", $headers)."\r\n\r\n".$postdata;
    	return $request;
    }
    function converttoservercharset($data)
    {
        if($this->clientcharset==$this->servercharset)
        {
            return $data;
        }
        else {
            return mb_convert_encoding($data,$this->servercharset,$this->clientcharset);
        }
    }
    function converttoclientcharset($data)
    {
       if($this->clientcharset==$this->servercharset)
        {
            return $data;
        }
        else {
            return mb_convert_encoding($data,$this->clientcharset,$this->servercharset);
        }
    }
    function buildquerystring($data)
    {
       // echo "\n11".$data;
        $querystring = '';
        if ($data && is_array($data))
        {
            foreach ($data AS $key => $value)
            {
                $querystring .= '&' . $key . '=' . $value;
            }
            $querystring = preg_replace('/^&/', '', $querystring);
        }
        else
        {
            $querystring=$data;
        }
    	return $querystring;
    }
    function curlrequest($url,$method,$postdata)
    {
        $curl_session = @curl_init();
        if(!$curl_session)
        {
           
            $this->errormsg="初始化 curl 失败！";
            return FALSE;
        }
        curl_setopt($curl_session, CURLOPT_FORBID_REUSE, true); 
        curl_setopt($curl_session, CURLOPT_HEADER, true);
        curl_setopt($curl_session, CURLOPT_RETURNTRANSFER, true);
        curl_setopt($curl_session, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_1_0);
        $postdata=$this->buildquerystring($postdata);
        $postdata=$this->converttoservercharset($postdata);
        $header = array();
        $header[] = "Host: {$this->host}";
        $headers[] = "User-Agent: {$this->useragent}";
        $headers[] = "Accept: {$this->accept}";
        if ($postdata && is_array($postdata))
        {
            foreach ($postdata AS $key => $value)
            {
                $header[] = $key . ': ' . $value;
            }
        }

        if ($method === 'GET')
        {
            curl_setopt($curl_session, CURLOPT_HTTPGET, true);
        }
        else
        {
            curl_setopt($curl_session, CURLOPT_POST, true);
            $header[] = "Content-Type: {$this->contenttype}";
            $header[] = 'Content-Length: ' . strlen($postdata);
            curl_setopt($curl_session, CURLOPT_POSTFIELDS, $postdata);
        }
        curl_setopt($curl_session, CURLOPT_URL, $url);

        curl_setopt($curl_session, CURLOPT_HTTPHEADER, $header);

        curl_setopt($curl_session, CURLOPT_CONNECTTIMEOUT, 0);

        curl_setopt($curl_session, CURLOPT_TIMEOUT,0);

        $respone = curl_exec($curl_session);

        if (curl_errno($curl_session) != 0)
        {
            $this->errormsg="服务器无应答！";
            return FALSE;
        }
        $separator = '/\r\n\r\n/';
        list($headerx, $bodyx) = preg_split($separator, $respone, 2);
        curl_close($curl_session);
        $this->errormsg="";
        return $this->converttoclientcharset($bodyx);
    }
    function parseurl($url)
    {
        if(strpos($url,'://')===FALSE)
        {
            $url="http://"+$url;
        }
        $urlsecs=parse_url($url);
       // debug_zval_dump($urlsecs);
        if($urlsecs===FALSE)
        {
            $this->errormsg="指定链接不合法！";
            return FALSE;
        }
        $this->host=$urlsecs["host"];
        if(isset($urlsecs["path"]))
        {
            $this->uripath=$urlsecs["path"];
        }
        if(isset($urlsecs["query"]))
        {
            $this->uripath+="?"+$urlsecs["query"];
        }
        if(isset($urlsecs["port"]))
        {
           $this->port=$urlsecs["port"];
        }
        else
        {
            $this->port="80";
        }
        return TRUE;
    }
    function getLastErrorMsg()
    {
        return $this->errormsg;
    }
 }
