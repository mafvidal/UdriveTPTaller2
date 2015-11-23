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
import android.widget.TextView;

import com.google.gson.Gson;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.Reader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.concurrent.ExecutionException;


public class ActualizarMetadatos extends Activity {
    private String jSon;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_actualizar_metadatos);

        Intent intent;
        intent = getIntent();
        final String usua = intent.getStringExtra("Usuario");
        final String contra = intent.getStringExtra("Contra");
        final String MyUrl = intent.getStringExtra("MyUrl");
        final String ID = intent.getStringExtra("ID");
        final String Directorio = intent.getStringExtra("DirectorioOriginal");
        final String Extension = intent.getStringExtra("ExtensionOriginal");
        String Fecha = intent.getStringExtra("Fecha");
        final String Nombre = intent.getStringExtra("NombreOriginal");
        final String Propietario = intent.getStringExtra("Propietario");
        String UsuarioQueModifico = usua;
        int Version = intent.getIntExtra("Version", -1);

        final EditText editDirectorio = (EditText) findViewById(R.id.editArchiDirectorio);
        final EditText editExtension = (EditText) findViewById(R.id.editArchiExt);
        final EditText editNombre = (EditText) findViewById(R.id.editArchiNombre);

        final Button archiB = (Button) findViewById(R.id.editArchiBut);

        editDirectorio.setText(Directorio);
        editExtension.setText(Extension);
        editNombre.setText(Nombre);

        archiB.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                NuevoArchivo arch = new NuevoArchivo(Propietario, Directorio, Extension, Nombre, editNombre.getText().toString(),
                        editDirectorio.getText().toString(), editExtension.getText().toString());

                Gson gson = new Gson();
                jSon = gson.toJson(arch);



                String url = MyUrl;


                ConnectivityManager connMgr = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
                NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();

                if (networkInfo != null && networkInfo.isConnected()) {
                    url += "usuarios/" + usua + "/archivos/actualizar";
                    System.out.println("Actu URL : " + url);
                    System.out.println("JSON : "+ jSon);
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

                Intent intent = new Intent(ActualizarMetadatos.this, MenuArchivo.class);
                intent.putExtra("Usuario", usua);
                intent.putExtra("Contra", contra);
                intent.putExtra("MyUrl", MyUrl);
                intent.putExtra("NombreOriginal", editNombre.getText().toString());
                intent.putExtra("Propietario", Propietario);
                intent.putExtra("DirectorioOriginal", editDirectorio.getText().toString());
                intent.putExtra("ExtensionOriginal", editExtension.getText().toString());
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
