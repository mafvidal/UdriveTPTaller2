package com.example.malouda.interfacegoogledrive;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;


public class EligirIP extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_eligir_ip);

        final EditText IpAdress = (EditText) findViewById(R.id.IpAdress);
        Button IpButton = (Button) findViewById(R.id.IpButton);

        final Globals g = new Globals();
        final String ip = g.getIP();

        IpAdress.setText(ip);

        IpButton.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String newIp = IpAdress.getText().toString();
                g.setIP(newIp);
                g.actualizar();

                System.out.println("MyURL : " + g.getMyUrl());
                Intent intent = new Intent(EligirIP.this, MainActivity.class);
                intent.putExtra("MyUrl", g.getMyUrl());
                startActivity(intent);
                setResult(RESULT_OK, intent);

            }
        });
    }

}
