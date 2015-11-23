package com.example.malouda.interfacegoogledrive;

import android.app.Activity;
import android.app.DownloadManager;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.Uri;
import android.os.AsyncTask;
import android.os.Bundle;
import android.support.v4.content.ContextCompat;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

import com.google.gson.Gson;

import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.List;
import java.util.concurrent.ExecutionException;


public class MyDrive extends Activity {
    private TableRow.LayoutParams layoutParams = new TableRow.LayoutParams(70,70);

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_my_drive);
        Intent intent;

        intent = getIntent();
        final String usua = intent.getStringExtra("Usuario");
        final String contra = intent.getStringExtra("Contra");
        final String MyUrl = intent.getStringExtra("MyUrl");

        final Button btnM = (Button) findViewById(R.id.menu);
        final Button btnBuscar = (Button) findViewById(R.id.busca);

        TableLayout tableLayout = (TableLayout) findViewById(R.id.tableLayout);


        int nbDocumentos = 0;

        btnM.setOnClickListener(new Button.OnClickListener(){
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MyDrive.this, PaginaMenu.class);

                intent.putExtra("Usuario", usua);
                intent.putExtra("Contra", contra);
                intent.putExtra("MyUrl", MyUrl);

                startActivity(intent);
                setResult(RESULT_OK, intent);
            }
        });

        btnBuscar.setOnClickListener(new Button.OnClickListener(){
            @Override
            public void onClick(View v) {
                Intent intent = new Intent(MyDrive.this, Search.class);

                intent.putExtra("Usuario", usua);
                intent.putExtra("Contra", contra);
                intent.putExtra("MyUrl", MyUrl);

                startActivity(intent);
                setResult(RESULT_OK, intent);
            }
        });


        ConnectivityManager connMgr = (ConnectivityManager) getSystemService(Context.CONNECTIVITY_SERVICE);
        NetworkInfo networkInfo = connMgr.getActiveNetworkInfo();

        if(networkInfo!=null && networkInfo.isConnected()) {
            String url = MyUrl+"usuarios/"+ usua + "/archivos";
            driveCon con = new driveCon();
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

            //We check each archive
            ResultadoDrive res;
            res = con.getRes();
            List<Archivos> misArchivos = res.getArchivos();
            nbDocumentos = misArchivos.size();

            //For each archive, we check the extension and add an image in the view
            for(int i = 0; i<nbDocumentos;i++){
                Archivos miArchivo = misArchivos.get(i);
                String Extension = miArchivo.getExtension();

                if(Extension.equals("pdf")){
                    addPdf(tableLayout, MyUrl, usua, miArchivo, contra);
                }
                else{
                    addDoc(tableLayout, MyUrl, usua, miArchivo, contra);
                }
            }

        } else {
            System.out.println("No network");
        }

    }

    private class driveCon extends AsyncTask<String, Void, String> {
        private ResultadoDrive res = new ResultadoDrive();

        public ResultadoDrive getRes(){
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
                res = gson.fromJson(r, ResultadoDrive.class);
                List<Archivos> arch = res.getArchivos();

                System.out.println("Estado : " + res.getEstado() + "///" + "RES : " + arch.get(0).getNombre());

            } catch (IOException e) {

                return "Unable to retrieve web page. URL may be invalid.  \n" + "Error : " + e;
            }
            return "Enviado : ";
        }
        // onPostExecute displays the results of the AsyncTask.
        @Override
        protected void onPostExecute(String result) {
        }
    }

    private class archivoCon extends AsyncTask<String, Void, String> {

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

            } catch (IOException e) {

                return "Unable to retrieve web page. URL may be invalid.  \n" + "Error : " + e;
            }
            return "Enviado : ";
        }
        // onPostExecute displays the results of the AsyncTask.
        @Override
        protected void onPostExecute(String result) {
        }
    }




    private void addPdf (TableLayout tl, final String MyUrl, final String usua, Archivos archivos, final String contra){
        final String Nombre = archivos.getNombre();
        final String ID = archivos.getID();
        final String Propietario = archivos.getPropietario();
        final String DirectorioOriginal = archivos.getDirectorio();
        final String ExtensionOriginal = archivos.getExtension();
        final String NombreOriginal = archivos.getNombre();

        ImageView imgPdf = new ImageView(MyDrive.this);
        imgPdf.setLayoutParams(layoutParams);
        int imgPdfId = R.drawable.pdf;
        imgPdf.setBackground(ContextCompat.getDrawable(this, imgPdfId));

        TextView txtArchivo = new TextView(MyDrive.this);
        txtArchivo.setTextColor(Color.BLACK);
        txtArchivo.setTextSize(30);
        txtArchivo.setText(Nombre + ".pdf");

        MyTableRow tr = new MyTableRow(MyDrive.this);
        tr.setID(Long.parseLong(ID));
        tr.setArchivos(archivos);
        tr.addView(imgPdf);
        tr.addView(txtArchivo);
        tr.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String url = MyUrl + "usuarios/" + usua + "/archivofisico/" + ID;
                archivoCon con = new archivoCon();
                con.execute(url);

                //Wait until end of the thread
                try {
                    con.get();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                } catch (ExecutionException e) {
                    e.printStackTrace();
                }
                abrirArchivo(url, Nombre);

                Intent intent = new Intent(MyDrive.this, MenuArchivo.class);

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
        tl.addView(tr);
    }

    private void addDoc (TableLayout tl, final String MyUrl, final String usua, Archivos archivos, final String contra){
       /* final String Nombre = archivos.getNombre();
        final String ID = archivos.getID();
        final String Propietario = archivos.getPropietario();
        final String DirectorioOriginal = archivos.getDirectorio();
        final String ExtensionOriginal = archivos.getExtension();
        final String NombreOriginal = archivos.getNombre();

        ImageView imgDoc = new ImageView(MyDrive.this);
        int imgDocId = R.drawable.doc;
        imgDoc.setBackground(ContextCompat.getDrawable(this, imgDocId));
        imgDoc.setLayoutParams(layoutParams);

        TextView txtArchivo = new TextView(MyDrive.this);
        txtArchivo.setTextColor(Color.BLACK);
        txtArchivo.setTextSize(30);
        txtArchivo.setText(Nombre + ".doc");

        MyTableRow tr = new MyTableRow(MyDrive.this);
        tr.setID(Long.parseLong(ID));
        tr.setArchivos(archivos);
        tr.addView(imgDoc);
        tr.addView(txtArchivo);
        tr.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String url = MyUrl + "usuarios/" + usua + "/archivofisico/" + ID;
                archivoCon con = new archivoCon();
                con.execute(url);

                //Wait until end of the thread
                try {
                    con.get();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                } catch (ExecutionException e) {
                    e.printStackTrace();
                }
                abrirArchivo(url, Nombre);

                Intent intent = new Intent(MyDrive.this, MenuArchivo.class);

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
        tl.addView(tr);*/
        final String Nombre = archivos.getNombre();
        final String ID = archivos.getID();
        final String Propietario = archivos.getPropietario();
        final String DirectorioOriginal = archivos.getDirectorio();
        final String ExtensionOriginal = archivos.getExtension();
        final String NombreOriginal = archivos.getNombre();

        ImageView imgDoc = new ImageView(MyDrive.this);
        imgDoc.setLayoutParams(layoutParams);
        int imgDocId = R.drawable.doc;
        imgDoc.setBackground(ContextCompat.getDrawable(this, imgDocId));

        TextView txtArchivo = new TextView(MyDrive.this);
        txtArchivo.setTextColor(Color.BLACK);
        txtArchivo.setTextSize(30);
        txtArchivo.setText(Nombre + ".doc");

        MyTableRow tr = new MyTableRow(MyDrive.this);
        tr.setID(Long.parseLong(ID));
        tr.setArchivos(archivos);
        tr.addView(imgDoc);
        tr.addView(txtArchivo);
        tr.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                String url = MyUrl + "usuarios/" + usua + "/archivofisico/" + ID;
                archivoCon con = new archivoCon();
                con.execute(url);

                //Wait until end of the thread
                try {
                    con.get();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                } catch (ExecutionException e) {
                    e.printStackTrace();
                }
                abrirArchivo(url, Nombre);

                Intent intent = new Intent(MyDrive.this, MenuArchivo.class);

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
        tl.addView(tr);
    }

    private void abrirArchivo(String url, String nombre){
        DownloadManager manager = (DownloadManager) getSystemService(DOWNLOAD_SERVICE);
        DownloadManager.Request request = new DownloadManager.Request(Uri.parse(url));
        request.setTitle(nombre);
        manager.enqueue(request);
    }
}
