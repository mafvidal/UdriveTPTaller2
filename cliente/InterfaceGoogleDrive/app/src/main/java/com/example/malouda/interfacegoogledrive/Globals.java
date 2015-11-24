package com.example.malouda.interfacegoogledrive;

/**
 * Created by malouda on 06/10/15.
 */
public class Globals {
    private String myUrl = "http://192.168.1.42:8080/";
    private String IP = "192.168.1.42";

    public Globals(){
    }


    public String getMyUrl(){
        return myUrl;
    }

    public String getIP(){
        return IP;
    }

    public void setIP(String ip){
        IP = ip;
    }

    public void actualizar(){
        myUrl = "http://" + IP + ":8000/";
    }

    public void setMyUrl(String url){
        myUrl = url;
    }
}
