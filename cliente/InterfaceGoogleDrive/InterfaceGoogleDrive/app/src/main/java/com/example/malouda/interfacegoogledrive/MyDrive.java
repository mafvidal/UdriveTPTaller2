package com.example.malouda.interfacegoogledrive;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TableRow;


public class MyDrive extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_my_drive);
        Intent intent;

        intent = getIntent();
        final String usua = intent.getStringExtra("Usuario");
        final String contra = intent.getStringExtra("Contra");

        final Button btnM = (Button) findViewById(R.id.menu);
        final Button btnBuscar = (Button) findViewById(R.id.busca);

        btnM.setOnClickListener(new Button.OnClickListener(){
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MyDrive.this, PaginaMenu.class);

                intent.putExtra("Usuario", usua);
                intent.putExtra("Contra", contra);

                startActivity(intent);
                setResult(RESULT_OK, intent);
            }
        });

        btnBuscar.setOnClickListener(new Button.OnClickListener(){
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MyDrive.this, Search.class);

                intent.putExtra("Usuario", usua);
                intent.putExtra("Contra", contra);

                startActivity(intent);
                setResult(RESULT_OK, intent);
            }
        });



    }
}
