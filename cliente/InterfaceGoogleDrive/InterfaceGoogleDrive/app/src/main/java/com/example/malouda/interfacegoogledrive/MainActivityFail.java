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


public class MainActivityFail extends Activity {
    String jSon = "";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main_activity_fail);


        final EditText Usua = (EditText) findViewById(R.id.usuario);
        final EditText Contra = (EditText) findViewById(R.id.contra);

        final Button btnC = (Button) findViewById(R.id.buttonCon);
        final Button btnNU = (Button) findViewById(R.id.buttonNU);

        btnC.setOnClickListener(new Button.OnClickListener(){
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivityFail.this, MyDrive.class);

                Usuario u = new Usuario();
                u.setClave(Contra.getText().toString());
                u.setUsuario(Usua.getText().toString());
                Gson gson = new Gson();
                jSon = gson.toJson(u);

                System.out.println(jSon);

                ConnectivityManager connMgr = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
                NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();

                if(networkInfo!=null && networkInfo.isConnected()) {
                    Globals g = new Globals();
                    new sendCon().execute(g.getMyUrl());
                    recCon respuesta = new recCon();

                } else {
                    System.out.println("No network");
                }





                //intent.putExtra("Email", Usuario.getText().toString());
                //intent.putExtra("Mdp", Contra.getText().toString());
                startActivity(intent);
                setResult(RESULT_OK, intent);
            }
        });


        btnNU.setOnClickListener(new Button.OnClickListener(){

            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MainActivityFail.this, NuevoUsuario.class);
                startActivity(intent);
                setResult(RESULT_OK, intent);
            }
        });
    }

    private class sendCon extends AsyncTask<String, Void, String> {
        @Override
        protected String doInBackground(String... urls) {

            // params comes from the execute() call: params[0] is the url.
            try {
                URL url = new URL(urls[0]);
                HttpURLConnection conn = (HttpURLConnection) url.openConnection();
                conn.setReadTimeout(10000 /* milliseconds */);
                conn.setConnectTimeout(15000 /* milliseconds */);
                conn.setRequestMethod("Get");
                conn.setDoInput(true);

                // Starts the query
                OutputStream printout = conn.getOutputStream();
                byte[] b = jSon.getBytes();
                printout.write(b);
                printout.flush();
                printout.close();


                conn.connect();
                int response = conn.getResponseCode();
                System.out.println( "The response is: " + response);
            } catch (IOException e) {
                return "Unable to retrieve web page. URL may be invalid.  \n" + "Error : " + e;
            }
            return "Enviado : " + jSon;
        }
        // onPostExecute displays the results of the AsyncTask.
        @Override
        protected void onPostExecute(String result) {
            System.out.println("PostExecute : " + result);
        }
    }


    private class recCon2 extends AsyncTask<String, Void, String> {
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

                // Starts the query
                OutputStream printout = conn.getOutputStream();
                byte[] b = jSon.getBytes();
                printout.write(b);
                printout.flush();
                printout.close();


                conn.connect();
                int response = conn.getResponseCode();
                System.out.println( "The response is: " + response);
            } catch (IOException e) {
                return "Unable to retrieve web page. URL may be invalid.  \n" + "Error : " + e;
            }
            return "Enviado : " + jSon;
        }
        // onPostExecute displays the results of the AsyncTask.
        @Override
        protected void onPostExecute(String result) {
            System.out.println("PostExecute : " + result);
        }
    }


    private class recCon extends AsyncTask<String, Void, String> {
        @Override
        protected String doInBackground(String... urls) {

            // params comes from the execute() call: params[0] is the url.
            try {
                return downloadUrl(urls[0]);
            } catch (IOException e) {
                return "Unable to retrieve web page. URL may be invalid.  \n" + "Error : " + e;
            }
        }
        // onPostExecute displays the results of the AsyncTask.
        @Override
        protected void onPostExecute(String result) {
            System.out.println("PostExecute : " + result);
        }
    }


    private String downloadUrl(String myurl) throws IOException {
        InputStream is = null;
        // Only display the first 500 characters of the retrieved
        // web page content.
        int len = 500;

        try {
            URL url = new URL(myurl);
            HttpURLConnection conn = (HttpURLConnection) url.openConnection();
            conn.setReadTimeout(10000 /* milliseconds */);
            conn.setConnectTimeout(15000 /* milliseconds */);
            conn.setRequestMethod("GET");
            conn.setDoInput(true);
            // Starts the query
            conn.connect();
            int response = conn.getResponseCode();
            System.out.println( "The response is: " + response);
            is = conn.getInputStream();

            // Convert the InputStream into a string
            String contentAsString = readIt(is, len);
            return contentAsString;

            // Makes sure that the InputStream is closed after the app is
            // finished using it.
        } finally {
            if (is != null) {
                is.close();
            }
        }
    }

    public String readIt(InputStream stream, int len) throws IOException, UnsupportedEncodingException {
        Reader reader = null;
        reader = new InputStreamReader(stream, "UTF-8");
        char[] buffer = new char[len];
        reader.read(buffer);
        return new String(buffer);
    }


}
