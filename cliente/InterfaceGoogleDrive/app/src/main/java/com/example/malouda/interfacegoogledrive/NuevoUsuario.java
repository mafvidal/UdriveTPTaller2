package com.example.malouda.interfacegoogledrive;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.AsyncTask;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;

import com.google.gson.Gson;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.Reader;
import java.io.UnsupportedEncodingException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.concurrent.ExecutionException;


public class NuevoUsuario extends Activity {

    String Usuario = "";
    String Clave = "";
    String Nombre = "";
    String Email = "";
    String jSon = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_nuevo_usuario);

        Intent intent;
        intent = getIntent();
        final String MyUrl = intent.getStringExtra("MyUrl");

        final Button btnReg = (Button) findViewById(R.id.butRegistrar);
        final EditText edNombre = (EditText) findViewById(R.id.editNombre);
        final EditText edNickname = (EditText) findViewById(R.id.editNickname);
        final EditText edPassword = (EditText) findViewById(R.id.editPassword);
        final EditText edEmail = (EditText) findViewById(R.id.editEmail);

        btnReg.setOnClickListener(new Button.OnClickListener(){

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
                System.out.println(jSon);
                String resultado = "ERROR";

                String url = MyUrl;

                ConnectivityManager connMgr = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
                NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();

                if(networkInfo!=null && networkInfo.isConnected()) {
                    url += "usuarios/"+ Nombre;
                    System.out.println("URL : " + url);
                    regCon reg = new regCon();
                    reg.execute(url);
                    try {
                        reg.get();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    } catch (ExecutionException e) {
                        e.printStackTrace();
                    }
                    resultado = reg.resultado;
                } else {
                    System.out.println("No network");
                }

                if(resultado.equals("ERROR")) {
                    Intent intent = new Intent(NuevoUsuario.this, NuevoUsuarioFail.class);
                    intent.putExtra("MyUrl", MyUrl);
                    startActivity(intent);
                    setResult(RESULT_OK, intent);
                } else {
                    Intent intent = new Intent(NuevoUsuario.this, MainActivity.class);
                    intent.putExtra("MyUrl", MyUrl);
                    startActivity(intent);
                    setResult(RESULT_OK, intent);
                }

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
                conn.setRequestMethod("POST");
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

                Gson gson = new Gson();
                ResultadoHttp res = gson.fromJson(r, ResultadoHttp.class);
                this.setResultado(res.getEstado());

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
