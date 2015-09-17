package com.example.malouda.interfacegoogledrive;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;


public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);


        final EditText Email = (EditText) findViewById(R.id.email);
        final EditText Mdp = (EditText) findViewById(R.id.mdp);
        final Button btnC = (Button) findViewById(R.id.buttonCon);

        btnC.setOnClickListener(new Button.OnClickListener(){
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivity.this, MyDrive.class);
                intent.putExtra("Email", Email.getText().toString());
                intent.putExtra("Mdp", Mdp.getText().toString());
                startActivity(intent);
                setResult(RESULT_OK, intent);
            }
        });
    }


}
