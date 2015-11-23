package com.example.malouda.interfacegoogledrive;

/**
 * Created by malouda on 12/11/15.
 */
public class ResultadoCuenta {
    private String Email;
    private String Nombre;
    private String Foto;
    private String UltimaUbicacion;
    private String Estado;

    public ResultadoCuenta(){
        Email = "";
        Estado = "";
        Nombre = "";
        UltimaUbicacion = "";
        Foto = "";
    }

    public String getEstado(){
        return Estado;
    }

    public String getEmail(){
        return Email;
    }

    public String getNombre(){
        return Nombre;
    }

    public String getFoto(){
        return Foto;
    }

    public String getUltimaUbicacion(){
        return UltimaUbicacion;
    }

}
