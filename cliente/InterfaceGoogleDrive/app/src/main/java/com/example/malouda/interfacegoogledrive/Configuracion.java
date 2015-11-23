package com.example.malouda.interfacegoogledrive;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.TableRow;


public class Configuracion extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_configuracion);

        Intent intent;
        intent = getIntent();
        final String usua = intent.getStringExtra("Usuario");
        final String contra = intent.getStringExtra("Contra");
        final String MyUrl = intent.getStringExtra("MyUrl");

        final TableRow trActua = (TableRow) findViewById(R.id.trActua);

        trActua.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(Configuracion.this, ActualizarUsuario.class);

                intent.putExtra("Usuario", usua);
                intent.putExtra("Contra", contra);
                intent.putExtra("MyUrl", MyUrl);

                startActivity(intent);
                setResult(RESULT_OK, intent);
            }
        });
    }


}
