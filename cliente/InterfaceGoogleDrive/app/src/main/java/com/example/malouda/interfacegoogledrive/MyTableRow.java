package com.example.malouda.interfacegoogledrive;

import android.content.Context;
import android.widget.TableRow;

/**
 * Created by malouda on 22/11/15.
 */
public class MyTableRow extends TableRow {
    private long ID;
    private Archivos archivos;

    public MyTableRow(Context context) {
        super(context);
    }

    public void setID(long id){
        ID = id;
    }

    public void setArchivos(Archivos arch){archivos = arch;}

    public Archivos getArchivos(){
        return archivos;
    }

    public long getID(){
        return ID;
    }
}
