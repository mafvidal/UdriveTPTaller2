package com.example.malouda.interfacegoogledrive;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.AsyncTask;
import android.support.v7.app.ActionBarActivity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.widget.EditText;
import android.widget.TextView;

import com.google.gson.Gson;

import org.w3c.dom.Text;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.Reader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.concurrent.ExecutionException;


public class MiCuenta extends Activity {
    String jSon = "";
    String Nombre = "";
    String Foto = "";
    String Email = "";
    String UltimaUbicacion = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_mi_cuenta);

        Intent intent;
        intent = getIntent();
        final String nombre = intent.getStringExtra("Usuario");
        final String contra = intent.getStringExtra("Contra");
        final String MyUrl = intent.getStringExtra("MyUrl");

        final TextView NombreTxt = (TextView) findViewById(R.id.MiNombre);
        final TextView FotoTxt = (TextView) findViewById(R.id.MiFoto);
        final TextView EmailTxt = (TextView) findViewById(R.id.MiEmail);
        final TextView UbicaTxt = (TextView) findViewById(R.id.MiUbica);

        ConnectivityManager connMgr = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();

        if(networkInfo!=null && networkInfo.isConnected()) {
            String url = MyUrl+"usuarios/"+nombre;
            cuentaCon con = new cuentaCon();
            con.execute(url);


            //Wait until end of the thread
            try {
                con.get();
            } catch (InterruptedException e) {
                e.printStackTrace();
            } catch (ExecutionException e) {
                e.printStackTrace();
            }

            System.out.println("URL : " + url);

            ResultadoCuenta res;
            res = con.getRes();
            Nombre = res.getNombre();
            Email = res.getEmail();
            Foto = res.getFoto();
            UltimaUbicacion = res.getUltimaUbicacion();

            NombreTxt.setText(Nombre);
            EmailTxt.setText(Email);
            FotoTxt.setText(Foto);
            UbicaTxt.setText(UltimaUbicacion);

        } else {
            System.out.println("No network");
        }
    }

    private class cuentaCon extends AsyncTask<String, Void, String> {
        private ResultadoCuenta res = new ResultadoCuenta();

        public ResultadoCuenta getRes(){
            return res;
        }

        @Override
        protected String doInBackground(String... urls) {

            // params comes from the execute() call: params[0] is the url.
            try {
                URL url = new URL(urls[0]);
                HttpURLConnection conn = (HttpURLConnection) url.openConnection();
                conn.setReadTimeout(10000 /* milliseconds */);
                conn.setConnectTimeout(15000 /* milliseconds */);
                conn.setRequestMethod("GET");
                conn.setDoInput(true);

                //Read the body
                conn.connect();
                InputStream printin = conn.getInputStream();
                Reader r = new InputStreamReader(printin, "UTF-8");

                Gson gson = new Gson();
                res = gson.fromJson(r, ResultadoCuenta.class);
                //System.out.println(res.toString());

            } catch (IOException e) {

                return "Unable to retrieve web page. URL may be invalid.  \n" + "Error : " + e;
            }
            return "Enviado : " + jSon;
        }
        // onPostExecute displays the results of the AsyncTask.
        @Override
        protected void onPostExecute(String result) {
        }
    }

}
