package com.example.malouda.interfacegoogledrive;

import java.util.LinkedList;
import java.util.List;

/**
 * Created by malouda on 23/11/15.
 */
public class ClassEnviar {
    private int Espacio;
    private String Directorio;
    private List<String> Etiquetas = new LinkedList<>();
    private String Extension;
    private String Nombre;

    public ClassEnviar(int esp, String dir, String ext, String nom){
        Espacio = esp;
        Directorio = dir;
        Extension = ext;
        Nombre = nom;
    }

}
