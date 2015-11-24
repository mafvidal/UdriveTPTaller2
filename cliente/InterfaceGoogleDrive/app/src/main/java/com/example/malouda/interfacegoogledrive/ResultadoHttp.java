package com.example.malouda.interfacegoogledrive;

/**
 * Created by malouda on 12/11/15.
 */
public class ResultadoHttp {
    private String Estado;
    private String Mensaje;

    public ResultadoHttp(){
        Estado = "";
        Mensaje = "";
    }

    public String getEstado(){
        return Estado;
    }

    public String getMensaje(){return Mensaje;}
}
