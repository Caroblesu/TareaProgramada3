package com.example.caroprogra3.stack_overflowtp3;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.Toast;
import org.apache.http.HttpResponse;
import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.impl.client.DefaultHttpClient;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import org.json.JSONException;
import org.json.JSONObject;

public class Login_main extends Activity {
    EditText usuario, contrasena;
    Button ingresar;
    String name="kenneth";
    String version="isa";

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_login_main);
        usuario= (EditText) findViewById(R.id.etusuario);
        contrasena=(EditText) findViewById(R.id.etcontrasena);
        ingresar= (Button) findViewById(R.id.ingresar);
        ingresar.setOnClickListener(new View.OnClickListener() {
        @Override
        public void onClick(View view) {
           String user =usuario.getText().toString();
           String pass = contrasena.getText().toString();


              if (user.equals( name )&& pass.equals(version)){
                 Toast.makeText(getBaseContext(),"Usuario correcto", Toast.LENGTH_SHORT).show();}
                 //Intent ir_a_main= new Intent("android.intent.action.Preguntas");
                 //startActivity(ir_a_main);}
              else {
                 Toast.makeText(getBaseContext(),"Usuario incorrecto", Toast.LENGTH_SHORT).show();
               }
           }
        });


        /*HttpClient httpClient = new DefaultHttpClient();
        HttpPost httpPost = new HttpPost("http://localhost:9000");
        try
        {
            HttpResponse response = httpClient.execute(httpPost);
            String jsonResult = inputStreamToString(response.getEntity().getContent()).toString();
            JSONObject object = new JSONObject(jsonResult);

            name = object.getString("nombre");
            version = object.getString("blog")

        }
        catch(JSONException e)
        {
            Toast.makeText(getBaseContext(),
                    "Ocurrio un error 1.." + e.getMessage(), Toast.LENGTH_SHORT)
                    .show();
            e.printStackTrace();
        }
        catch(ClientProtocolException e)
        {
            Toast.makeText(getBaseContext(),
                    "Ocurrio un error 2.." + e.getMessage(), Toast.LENGTH_SHORT)
                    .show();
            e.printStackTrace();
        }
        catch(IOException e)
        {
            Toast.makeText(getBaseContext(),
                    "Ocurrio un error 3" + e.getMessage(), Toast.LENGTH_SHORT)
                    .show();
            e.printStackTrace();

        }*/


    }



    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.login_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        if (id == R.id.action_settings) {
            return true;
        }
        return super.onOptionsItemSelected(item);
    }

    /*private StringBuilder inputStreamToString (InputStream para_stream)  //funcion que recibe un inputStream y devuelve un stringBuilder
    {  String rLine = " "; // variable que se va a estar leyendo.
        StringBuilder answer = new StringBuilder();
        BufferedReader rd = new BufferedReader(new InputStreamReader(para_stream));

        try
        {
            while ((rLine = rd.readLine()) != null)   // leemos el bufferedreader
            {
                answer.append(rLine);  // se lee y se "abre" el Streambuilder
            }
        }

        catch (IOException e)
        {
            e.printStackTrace();
        }
        return answer;
    }*/
}
