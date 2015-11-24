package com.example.malouda.interfacegoogledrive;

import java.util.List;

/**
 * Created by malouda on 22/11/15.
 */
public class Archivos {
    private String Directorio;
    private List<String> Etiquetas;
    private String Extension;
    private String FechaDeModificacion;
    private String ID;
    private String Nombre;
    private String Propietario;
    private String UsuarioQueModifico;
    private String Version;

    public Archivos(){};

    public String getDirectorio(){
        return Directorio;
    }

    public String getNombre(){
        return Nombre;
    }

    public String getExtension(){
        return Extension;
    }

    public String getID(){
        return ID;
    }

    public String getPropietario(){return Propietario;}
}
