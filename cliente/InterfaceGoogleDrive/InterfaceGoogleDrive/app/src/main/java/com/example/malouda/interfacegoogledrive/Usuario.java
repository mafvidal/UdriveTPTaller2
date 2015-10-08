package com.example.malouda.interfacegoogledrive;

public class Usuario {
    private String Usuario;
    private String Clave;
    private float Cuota;
    private String Nombre;
    private String Email;
    private String Foto;
    private String UltimaUbicacion;

    public Usuario(){
        Usuario = "";
        Clave = "";
        Email = "";
        Foto = "";
        Cuota = 10;
        UltimaUbicacion ="";
    }

    public Usuario(String Nick, String Pass, String Nom, String Em, String Fo, String Ubi){
        Usuario = Nick;
        Clave = Pass;
        Nombre = Nom;
        Email = Em;
        Foto = Fo;
        UltimaUbicacion = Ubi;
        Cuota = 10;

    }

    public void setUsuario(String Nick){
        Usuario = Nick;
    }

    public void setClave(String Pass){
        Clave = Pass;
    }
}
