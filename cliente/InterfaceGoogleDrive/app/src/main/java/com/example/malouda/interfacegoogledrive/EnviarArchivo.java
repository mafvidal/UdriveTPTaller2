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
import android.widget.TextView;
import android.widget.Toast;

import com.google.gson.Gson;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.Reader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.concurrent.ExecutionException;


public class EnviarArchivo extends Activity {
    private String jSon = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_enviar_archivo);

        Intent intent;
        intent = getIntent();
        final String MyUrl = intent.getStringExtra("MyUrl");
        final String usua = intent.getStringExtra("Usuario");
        final String contra = intent.getStringExtra("Contra");

        final TextView ArchivoEspacio = (TextView) findViewById(R.id.ArchivoEspacio);
        final TextView ArchivoDir = (TextView) findViewById(R.id.ArchivoDir);
        final TextView ArchivoNom = (TextView) findViewById(R.id.ArchivoNom);
        final TextView ArchivoExt = (TextView) findViewById(R.id.ArchivoExt);

        final Button Enviar = (Button) findViewById(R.id.buttEnviar);

        Enviar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String archNomb = ArchivoNom.getText().toString();
                String archExt = ArchivoExt.getText().toString();
                int archEspacio = Integer.parseInt(ArchivoEspacio.getText().toString());
                String archDir = ArchivoDir.getText().toString();

                ClassEnviar env = new ClassEnviar(archEspacio, archDir, archExt, archNomb);

                Gson gson = new Gson();
                jSon = gson.toJson(env);

                String url = MyUrl;

                ConnectivityManager connMgr = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
                NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();

                if (networkInfo != null && networkInfo.isConnected()) {
                    url += "usuarios/" + usua +"/archivos";
                    regCon reg = new regCon();
                    reg.execute(url);

                    try {
                        reg.get();
                    } catch (InterruptedException e) {
                        e.printStackTrace();
                    } catch (ExecutionException e) {
                        e.printStackTrace();
                    }

                    String resultado = reg.getResultado();

                    if(resultado.equals("ERROR")){
                        Toast.makeText(getApplicationContext(), "No funciono",
                                Toast.LENGTH_LONG).show();
                    }
                    else {
                        String ID = reg.getMensaje();
                        url = MyUrl;
                        url += "usuarios/" + usua +"/archivofisico/"+ID;
                        reg = new regCon();
                        reg.execute(url);

                        try {
                            reg.get();
                        } catch (InterruptedException e) {
                            e.printStackTrace();
                        } catch (ExecutionException e) {
                            e.printStackTrace();
                        }

                        String estado = reg.getResultado();
                        Toast.makeText(getApplicationContext(), estado,
                                Toast.LENGTH_LONG).show();
                        Intent intent = new Intent(EnviarArchivo.this, MyDrive.class);
                        intent.putExtra("Usuario", usua);
                        intent.putExtra("Contra", contra);
                        intent.putExtra("MyUrl", MyUrl);
                        startActivity(intent);
                        setResult(RESULT_OK, intent);
                    }

                } else {
                    System.out.println("No network");
                }


            }
        });

    }

    private class regCon extends AsyncTask<String, Void, String> {
        private String estado = "ERROR";
        private String mensaje = "";

        public String getResultado(){
            return estado;
        }

        public String getMensaje(){
            return mensaje;
        }

        public void setResultado(String Resultado){
            estado = Resultado;
        }

        public void setMensaje(String msj){mensaje = msj;}

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
                this.setMensaje(res.getMensaje());

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
