package com.example.malouda.interfacegoogledrive;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TableRow;


public class PaginaMenu extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_pagina_menu);

        Intent intent;
        intent = getIntent();
        final String MyUrl = intent.getStringExtra("MyUrl");
        final String usua = intent.getStringExtra("Usuario");
        final String contra = intent.getStringExtra("Contra");

        final TableRow trConfig = (TableRow) findViewById(R.id.trConfig);
        final TableRow trCuenta = (TableRow) findViewById(R.id.trCuenta);
        final TableRow trAmigos = (TableRow) findViewById(R.id.trAmigos);

        final Button Desco = (Button) findViewById(R.id.buttDesc);

        Desco.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(PaginaMenu.this, MainActivity.class);
                intent.putExtra("MyUrl", MyUrl);
                startActivity(intent);
                setResult(RESULT_OK, intent);
            }
        });


        trConfig.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(PaginaMenu.this, Configuracion.class);

                intent.putExtra("Usuario", usua);
                intent.putExtra("Contra", contra);
                intent.putExtra("MyUrl", MyUrl);

                startActivity(intent);
                setResult(RESULT_OK, intent);
            }
        });

        trAmigos.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(PaginaMenu.this, PaginaMenu.class);

                intent.putExtra("Usuario", usua);
                intent.putExtra("Contra", contra);
                intent.putExtra("MyUrl", MyUrl);

                startActivity(intent);
                setResult(RESULT_OK, intent);
            }
        });



        trCuenta.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(PaginaMenu.this, MiCuenta.class);

                intent.putExtra("Usuario", usua);
                intent.putExtra("Contra", contra);
                intent.putExtra("MyUrl", MyUrl);

                startActivity(intent);
                setResult(RESULT_OK, intent);
            }
        });
    }
}
