package com.example.malouda.interfacegoogledrive;

import java.util.List;

/**
 * Created by malouda on 22/11/15.
 */
public class ResultadoDrive {
    private List<Archivos> Archivos;
    private String Estado;

    public ResultadoDrive(){
        Estado = "";
    }

    public List<Archivos> getArchivos(){
        return Archivos;
    }

    public String getEstado(){
        return Estado;
    }
}
