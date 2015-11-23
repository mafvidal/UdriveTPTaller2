package com.example.malouda.interfacegoogledrive;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;

import org.w3c.dom.Text;


public class MetadatosArchivo extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_metadatos_archivo);

        Intent intent;
        intent = getIntent();
        final String usua = intent.getStringExtra("Usuario");
        final String contra = intent.getStringExtra("Contra");
        final String MyUrl = intent.getStringExtra("MyUrl");
        final String Directorio = intent.getStringExtra("DirectorioOriginal");
        final String Extension = intent.getStringExtra("ExtensionOriginal");
        final String aNombre = intent.getStringExtra("NombreOriginal");
        final String Propietario = intent.getStringExtra("Propietario");

        final TextView ArchiExt = (TextView) findViewById(R.id.ArchiExt);
        final TextView ArchiNombre = (TextView) findViewById(R.id.ArchiNombre);
        final TextView ArchiDirectorio = (TextView) findViewById(R.id.ArchiDirectorio);
        final TextView ArchiProp = (TextView) findViewById(R.id.ArchiProp);
        final Button MetaButt = (Button) findViewById(R.id.MetaButt);

        ArchiExt.setText(Extension);
        ArchiNombre.setText(aNombre);
        ArchiDirectorio.setText(Directorio);
        ArchiProp.setText(Propietario);

        MetaButt.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MetadatosArchivo.this, MyDrive.class);
                intent.putExtra("Usuario", usua);
                intent.putExtra("Contra", contra);
                intent.putExtra("MyUrl", MyUrl);
                startActivity(intent);
                setResult(RESULT_OK, intent);
            }
        });

    }

}
