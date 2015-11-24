package com.example.malouda.interfacegoogledrive;

/**
 * Created by malouda on 11/11/15.
 */
public class Metadatos {
    private String Nombre;
    private String Email;
    private String Foto;
    private String UltimaUbicacion;

    public Metadatos() {
        Nombre = "";
        Email = "";
        Foto = "";
        UltimaUbicacion = "";
    }

    public Metadatos(String nombre, String email, String foto, String ultimaUbicacion){
        Nombre = nombre;
        Email = email;
        Foto = foto;
        UltimaUbicacion = ultimaUbicacion;
    }

    public String toString(){
        return "Nombre : "+ Nombre + " Email : " + Email + " Foto : " + Foto;
    }

    public String getNombre(){
        return Nombre;
    }

    public String getEmail(){
        return Email;
    }

    public String getFoto(){
        return Foto;
    }

    public String getUltimaUbicacion(){
        return UltimaUbicacion;
    }

    public void setNombre(String nom){
        Nombre = nom;
    }

    public void setEmail(String email){
        Email = email;
    }

    public void setFoto(String foto){
        Foto = foto;
    }

    public void setUltimaUbicacion(String ubi){
        UltimaUbicacion = ubi;
    }
}
