package com.example.malouda.interfacegoogledrive;

import android.app.Activity;
import android.content.Intent;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.TextView;
import android.widget.Toolbar;

import org.w3c.dom.Text;


public class MyDrive extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_my_drive);
        Intent intent;

        intent = getIntent();
        String profil = intent.getStringExtra("Email");
        String mdp = intent.getStringExtra("Mdp");

    }
}
