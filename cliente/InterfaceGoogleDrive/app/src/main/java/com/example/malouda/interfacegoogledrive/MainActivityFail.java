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


public class MainActivityFail extends Activity {
    String jSon = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main_activity_fail);

        Intent intent;
        intent = getIntent();
        final String MyUrl = intent.getStringExtra("MyUrl");

        final EditText Usua = (EditText) findViewById(R.id.usuario);
        final EditText Contra = (EditText) findViewById(R.id.contra);

        final Button btnC = (Button) findViewById(R.id.buttonCon);
        final Button btnNU = (Button) findViewById(R.id.buttonNU);

        btnC.setOnClickListener(new Button.OnClickListener(){
            @Override
            public void onClick(View v) {

                String clave = Contra.getText().toString();
                String nombre = Usua.getText().toString();
                IniciarSesion ini = new IniciarSesion(clave);

                Gson gson = new Gson();
                jSon = gson.toJson(ini);

                String resultado = "ERROR";


                ConnectivityManager connMgr = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
                NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();

                if(networkInfo!=null && networkInfo.isConnected()) {
                    Globals g = new Globals();
                    String url = MyUrl +"iniciarsesion/"+nombre;
                    regCon con = new regCon();
                    con.execute(url);


                    //Wait until end of the threat
                    try {
                        con.get();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    } catch (ExecutionException e) {
                        e.printStackTrace();
                    }

                    resultado = con.getResultado();

                } else {
                    System.out.println("No network");
                }

                if(resultado.equals("ERROR")){
                    Intent intent = new Intent(MainActivityFail.this, MainActivityFail.class);
                    intent.putExtra("MyUrl", MyUrl);
                    startActivity(intent);
                    setResult(RESULT_OK, intent);
                }
                else {
                    Intent intent = new Intent(MainActivityFail.this, MyDrive.class);
                    intent.putExtra("Usuario", nombre);
                    intent.putExtra("Contra", clave);
                    intent.putExtra("MyUrl", MyUrl);
                    startActivity(intent);
                    setResult(RESULT_OK, intent);
                }

            }
        });


        btnNU.setOnClickListener(new Button.OnClickListener() {

            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivityFail.this, NuevoUsuario.class);
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
                conn.setRequestMethod("POST");
                conn.setDoOutput(true);
                conn.setDoInput(true);

                // Starts the query
                OutputStream printout = conn.getOutputStream();
                byte[] b = jSon.getBytes();
                printout.write(b);
                printout.flush();
                printout.close();


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
