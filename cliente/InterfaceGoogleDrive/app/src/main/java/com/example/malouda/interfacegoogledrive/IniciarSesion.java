package com.example.malouda.interfacegoogledrive;

/**
 * Created by malouda on 12/11/15.
 */
public class IniciarSesion {
    private String Clave;

    public IniciarSesion(){
    }

    public IniciarSesion(String clave){
        Clave = clave;
    }

    public void setClave(String clave){
        Clave = clave;
    }

    public String getClave(){
        return Clave;
    }
}
