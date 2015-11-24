package com.example.malouda.interfacegoogledrive;

import java.util.LinkedList;
import java.util.List;

/**
 * Created by malouda on 23/11/15.
 */
public class NuevoArchivo {
    String Propietario;
    String DirectorioOriginal;
    String ExtensionOriginal;
    String NombreOriginal;
    String NombreNuevo;
    String DirectorioNuevo;
    String ExtensionNueva;


    List<String> Etiquetas = new LinkedList<>();
    List<String> EtiquetasNuevas = new LinkedList<>();
    List<String> EtiquetasEliminadas = new LinkedList<>();

    public NuevoArchivo(String prop, String directorioOriginal,String extensionOriginal, String nombreOriginal, String nombreNuevo, String directorioNuevo, String extensionNueva){
        Propietario = prop;
        DirectorioOriginal = directorioOriginal;
        ExtensionOriginal = extensionOriginal;
        NombreOriginal = nombreOriginal;
        NombreNuevo = nombreNuevo;
        DirectorioNuevo = directorioNuevo;
        ExtensionNueva = extensionNueva;
        Etiquetas.add("Marron");
        Etiquetas.add("Yellow");
        EtiquetasNuevas.add("Blue");
        EtiquetasNuevas.add("Marron");
        EtiquetasEliminadas.add("Yellow");
    }
}
