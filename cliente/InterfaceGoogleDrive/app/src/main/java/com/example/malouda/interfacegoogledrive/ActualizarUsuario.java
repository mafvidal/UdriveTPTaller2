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
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import com.google.gson.Gson;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.Reader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.concurrent.ExecutionException;


public class ActualizarUsuario extends Activity {

    String Usuario = "";
    String Clave = "";
    String Nombre = "";
    String Email = "";
    String jSon = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_actualizar_usuario);

        Intent intent;
        intent = getIntent();
        final String MyUrl = intent.getStringExtra("MyUrl");

        final Button btnAct = (Button) findViewById(R.id.butActualizar);
        final EditText edNombre = (EditText) findViewById(R.id.actNombre);
        final EditText edNickname = (EditText) findViewById(R.id.actNickname);
        final EditText edPassword = (EditText) findViewById(R.id.actPassword);
        final EditText edEmail = (EditText) findViewById(R.id.actEmail);

        btnAct.setOnClickListener(new Button.OnClickListener() {

            @Override
            public void onClick(View v) {
                Usuario = edNickname.getText().toString();
                Clave = edPassword.getText().toString();
                Email = edEmail.getText().toString();
                Nombre = edNombre.getText().toString();

                Metadatos meta = new Metadatos(Nombre, Email, "", "");
                Usuario usuario = new Usuario(Clave, 10, meta);

                Gson gson = new Gson();
                jSon = gson.toJson(usuario);

                String url = MyUrl;



                ConnectivityManager connMgr = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
                NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();

                if (networkInfo != null && networkInfo.isConnected()) {
                    url += "usuarios/" + Nombre;
                    regCon reg = new regCon();
                    reg.execute(url);

                    try {
                        reg.get();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    } catch (ExecutionException e) {
                        e.printStackTrace();
                    }

                } else {
                    System.out.println("No network");
                }

                Intent intent = new Intent(ActualizarUsuario.this, MainActivity.class);
                intent.putExtra("MyUrl", MyUrl);
                startActivity(intent);
                setResult(RESULT_OK, intent);

            }
        });

    }

    private class regCon extends AsyncTask<String, Void, String> {
        private String resultado = "ERROR";

        public String getResultado(){
            return resultado;
        }

        public void setResultado(String Resultado){
            resultado = Resultado;
        }

        @Override
        protected String doInBackground(String... urls) {

            // params comes from the execute() call: params[0] is the url.
            try {
                URL url = new URL(urls[0]);
                HttpURLConnection conn = (HttpURLConnection) url.openConnection();
                conn.setReadTimeout(10000 /* milliseconds */);
                conn.setConnectTimeout(15000 /* milliseconds */);
                conn.setRequestMethod("PUT");
                conn.setDoOutput(true);
                conn.setDoInput(true);

                // Starts the query
                OutputStream printout = conn.getOutputStream();
                byte[] b = jSon.getBytes();
                printout.write(b);
                printout.flush();
                printout.close();

                //Read the body
                conn.connect();
                InputStream printin = conn.getInputStream();
                Reader r = new InputStreamReader(printin, "UTF-8");

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
