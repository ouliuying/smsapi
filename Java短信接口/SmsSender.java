package com.company.xy;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import  java.nio.charset.*;
import java.net.*;
import java.security.MessageDigest;
import java.time.Instant;
import java.util.ArrayList;
import java.util.Date;
import java.util.Map;

/**
 * Created by ouayng2008 on 2016/4/28.
 */
public class SmsSender {
    private static String digits = "0123456789abcdef";
    private String _content_type="application/x-www-form-urlencoded";
    private  String _appid="";
    private  String _apiurl="";
    private  String _appkey="";
    public  void SetAppID(String appid)
    {
        this._appid=appid;
    }
    public  void SetApiUrl(String apiurl)
    {
        this._apiurl=apiurl;
    }
    public  void SetAppKey(String appkey)
    {
        this._appkey=appkey;
    }
    protected  String getUnixTimeStamp()
    {
        long unixTimestamp = Instant.now().getEpochSecond();
        return Long.toString(unixTimestamp);
    }
    protected  String toHexString(byte[] bts)
    {
        if(bts==null)
        {
            return "";
        }
        StringBuilder sb=new StringBuilder();
        for (byte b : bts)
        {
            int v = (b & 0xff);
            sb.append(digits.charAt(v >> 4));
            sb.append(digits.charAt(v & 0xf));
        }
        return sb.toString();
    }
    protected byte[] md5(String val)
    {
        try
        {
            byte[] btsofval = val.getBytes("UTF-8");
            MessageDigest md = MessageDigest.getInstance("MD5");
            byte[] bts = md.digest(btsofval);
            return bts;
        }
        catch (java.io.UnsupportedEncodingException ex)
        {
            return null;
        }
        catch (java.security.NoSuchAlgorithmException ex)
        {
            return null;
        }
    }
    protected String signDigest(String appid,String appkey,String mobile,String timestamp)
    {
        StringBuilder sb=new StringBuilder();
        sb.append(appid);
        sb.append(toHexString(md5(appkey)));
        sb.append(timestamp);
        sb.append(mobile);
        return toHexString(md5(sb.toString()));
    }
    public String Send(String mobile,String msg,String extno)
    {
        String timestamp=getUnixTimeStamp();
        String digest=signDigest(this._appid,this._appkey,mobile,timestamp);
        String data=String.format("ac=sendsms&mobile=%s&extno=%s&appid=%s&digest=%s&timestamp=%s&msg=%s",mobile,extno,this._appid,digest,msg);
        String retmsg=_post(data);
        return retmsg;
    }
    public  String GetAmont()
    {
        String timestamp=getUnixTimeStamp();
        String digest=signDigest(this._appid,this._appkey,"",timestamp);
        String postdata = String.format("ac=getamount&appid=%s&digest=%s&timestamp=%s", this._appid, digest, timestamp);
        String retmsg=_post(postdata);
        return retmsg;
    }

    public  String GetReplyMsg()
    {
        String timestamp=getUnixTimeStamp();
        String digest=signDigest(this._appid,this._appkey,"",timestamp);
        String postdata = String.format("ac=fetchreply&appid=%s&digest=%s&timestamp=%s", this._appid, digest, timestamp);
        String retmsg=_post(postdata);
        return retmsg;
    }
    protected  String _post(String data)
    {
        System.out.print(data);
        try
        {
            URL url = new URL(this._apiurl);
            URLConnection con = url.openConnection();
            HttpURLConnection http = (HttpURLConnection)con;
            http.setRequestMethod("POST");
            http.setDoOutput(true);
            byte[] out = data.getBytes("UTF-8");
            int length = out.length;
            http.setFixedLengthStreamingMode(length);
            http.setRequestProperty("Content-Type",this._content_type);
            http.setConnectTimeout(1000*120);
            http.connect();
            OutputStream outstream=http.getOutputStream();
            outstream.write(out);
            InputStream instream= http.getInputStream();
            ByteArrayOutputStream bts = new ByteArrayOutputStream();
            byte[] buffer = new byte[1024];
            int rlen = 0;
            while ((rlen = instream.read(buffer)) != -1) {
                bts.write(buffer, 0, rlen);
            }
            return new String(bts.toByteArray(),"UTF-8");
        }
        catch (java.net.MalformedURLException ex)
        {
            return "";
        }
        catch (java.io.IOException ex)
        {
            return "";
        }
    }
}
