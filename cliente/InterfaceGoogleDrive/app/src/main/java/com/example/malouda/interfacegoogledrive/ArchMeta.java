package com.example.malouda.interfacegoogledrive;

import java.util.List;

/**
 * Created by malouda on 23/11/15.
 */
public class ArchMeta {
    String Directorio;
    String Extension;
    String Nombre;
    String Propietario;
    String UsuarioQueModifico;
    String ID;
    int Version;

    public ArchMeta(String direc, String ext, String fe, String nom, String prop, String usu, String id, int v) {
        Directorio = direc;
        Extension = ext;
        Nombre = nom;
        Propietario = prop;
        UsuarioQueModifico = usu;
        ID = id;
        Version = v;
    }

    public String getDirectorio(){
        return Directorio;
    }

    public String getExtension(){
        return Extension;
    }

    public String getNombre(){return Nombre;}

    public String getPropietario(){return Propietario;}

    public String getUsuarioQueModifico(){return UsuarioQueModifico;}

    public String getID(){return ID;}

    public int getVersion(){return Version;}

    public ArchMeta(){}

}
