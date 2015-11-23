package com.example.malouda.interfacegoogledrive;


public class Usuario {
    private String Clave;
    private float Cuota;
    private Metadatos MetaDatos;

    public Usuario(){
        Cuota = 10;
        Clave = "";
        MetaDatos = new Metadatos();
    }

    public Usuario(String clave, float cuota, Metadatos meta){
        Clave = clave;
        Cuota = cuota;
        MetaDatos = meta;

    }

    public Metadatos getMeta(){
        return MetaDatos;
    }

    public void setMeta(Metadatos meta){
        MetaDatos = meta;
    }

    public void setClave(String Pass){
        Clave = Pass;
    }
}
