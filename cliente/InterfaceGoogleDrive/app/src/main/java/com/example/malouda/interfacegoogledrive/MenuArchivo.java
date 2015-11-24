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
import android.widget.TableRow;

import com.google.gson.Gson;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.Reader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.concurrent.ExecutionException;


public class MenuArchivo extends Activity {
    private String jSon;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_menu_archivo);

        Intent intent;
        intent = getIntent();
        final String usua = intent.getStringExtra("Usuario");
        final String contra = intent.getStringExtra("Contra");
        final String MyUrl = intent.getStringExtra("MyUrl");
        final String DirectorioOriginal = intent.getStringExtra("DirectorioOriginal");
        final String ExtensionOriginal = intent.getStringExtra("ExtensionOriginal");
        final String NombreOriginal = intent.getStringExtra("NombreOriginal");
        final String Propietario = intent.getStringExtra("Propietario");

        final TableRow Actualizar = (TableRow) findViewById(R.id.trActuMeta);
        final TableRow Eliminar = (TableRow) findViewById(R.id.trEliminar);
        final TableRow Ver = (TableRow) findViewById(R.id.trVerMeta);

        final Button Volver = (Button) findViewById(R.id.buttVolver);

        Volver.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MenuArchivo.this, MyDrive.class);
                intent.putExtra("Usuario", usua);
                intent.putExtra("Contra", contra);
                intent.putExtra("MyUrl", MyUrl);
                startActivity(intent);
                setResult(RESULT_OK, intent);
            }
        });

        Ver.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MenuArchivo.this, MetadatosArchivo.class);

                intent.putExtra("Usuario", usua);
                intent.putExtra("Contra", contra);
                intent.putExtra("MyUrl", MyUrl);
                intent.putExtra("NombreOriginal", NombreOriginal);
                intent.putExtra("Propietario", Propietario);
                intent.putExtra("DirectorioOriginal", DirectorioOriginal);
                intent.putExtra("ExtensionOriginal", ExtensionOriginal);
                startActivity(intent);
                setResult(RESULT_OK, intent);

            }
        });

        Eliminar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                ClassEliminar classEliminar = new ClassEliminar(Propietario,DirectorioOriginal,ExtensionOriginal,NombreOriginal);


                Gson gson = new Gson();
                jSon = gson.toJson(classEliminar);

                String url = MyUrl;


                ConnectivityManager connMgr = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
                NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();

                if (networkInfo != null && networkInfo.isConnected()) {
                    url += "usuarios/" + usua + "/archivos";
                    regCon reg = new regCon();
                    System.out.println("DEL URL : " + url);
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

                Intent intent = new Intent(MenuArchivo.this, MyDrive.class);
                intent.putExtra("Usuario", usua);
                intent.putExtra("Contra", contra);
                intent.putExtra("MyUrl", MyUrl);
                startActivity(intent);
                setResult(RESULT_OK, intent);

            }
        });

        Actualizar.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent;
                intent = new Intent(MenuArchivo.this, ActualizarMetadatos.class);
                intent.putExtra("Usuario", usua);
                intent.putExtra("Contra", contra);
                intent.putExtra("MyUrl", MyUrl);
                intent.putExtra("NombreOriginal", NombreOriginal);
                intent.putExtra("Propietario", Propietario);
                intent.putExtra("DirectorioOriginal", DirectorioOriginal);
                intent.putExtra("ExtensionOriginal", ExtensionOriginal);
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
                conn.setRequestMethod("DELETE");
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
