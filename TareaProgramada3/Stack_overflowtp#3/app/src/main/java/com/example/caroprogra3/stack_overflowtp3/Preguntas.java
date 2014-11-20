package com.example.caroprogra3.stack_overflowtp3;

import android.app.Activity;
import android.app.Dialog;
import android.os.Bundle;
import android.view.ContextMenu;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.EditText;
import android.widget.ListView;
import android.widget.SimpleAdapter;
import android.widget.TextView;
import android.widget.Toast;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;


public class Preguntas extends Activity {

   //Dato que se muestra
    List<Map<String, String>> questionList = new ArrayList<Map<String,String>>();

    SimpleAdapter simpleAdpt = new SimpleAdapter(this, questionList, android.R.layout.simple_list_item_1, new String[] {"pregunta"}, new int[] {android.R.id.text1});


    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_preguntas);

        initList();

        //Obtenemos el componente del ListView
        ListView lv = (ListView) findViewById(R.id.listView);


        simpleAdpt = new SimpleAdapter(this, questionList, android.R.layout.simple_list_item_1, new String[] {"pregunta"}, new int[] {android.R.id.text1});


        lv.setAdapter(simpleAdpt);

        //Obtiene los clicks del usuario
        lv.setOnItemClickListener(new AdapterView.OnItemClickListener() {

            public void onItemClick(AdapterView<?> parentAdapter, View view, int position,
                                    long id) {


                // We know the View is a TextView so we can cast it
                TextView clickedView = (TextView) view;

                Toast.makeText(Preguntas.this, "Item with id [" + id + "] - Position [" + position + "] - Pregunta [" + clickedView.getText() + "]", Toast.LENGTH_SHORT).show();

            }
        });


    }

    //Creacion de un menu cuando el usuario hace click en un item
    @Override
    public void onCreateContextMenu(ContextMenu menu, View v,
                                    ContextMenu.ContextMenuInfo menuInfo) {

        super.onCreateContextMenu(menu, v, menuInfo);
        AdapterView.AdapterContextMenuInfo aInfo = (AdapterView.AdapterContextMenuInfo) menuInfo;

        // We know that each row in the adapter is a Map
        HashMap map =  (HashMap) simpleAdpt.getItem(aInfo.position);

        menu.setHeaderTitle("Options for " + map.get("pregunta"));
        menu.add(1, 1, 1, "Agregar pregunta");
        menu.add(1, 2, 2, "Delete");

    }

    private void initList() {
    //Preguntas
        questionList.add(createPlanet("pregunta", "Como se hace una aplicacion en Android?"));
        questionList.add(createPlanet("pregunta", "Para que sirve Play Framework?"));



    }

    private HashMap<String, String> createPlanet(String key, String name) {
        HashMap<String, String> pregunta = new HashMap<String, String>();
        pregunta.put(key, name);

        return pregunta;
    }

   /* public void addPlanet(View view) {

        final Dialog d = new Dialog(this);

        d.setContentView(R.layout.dialog);

        d.setTitle("Add planet");

        d.setCancelable(true);

        final EditText edit = (EditText) d.findViewById(R.id.editTextPlanet);

        Button b = (Button) d.findViewById(R.id.button1);

        b.setOnClickListener(new View.OnClickListener() {

            public void onClick(View v) {

                String planetName = edit.getText().toString();

                Preguntas.this.questionList.add(planetName);

                // We notify the data model is changed
                Preguntas.this.simpleAdpt.notifyDataSetChanged();

                d.dismiss();

            }

        });

        d.show();

    }*/

}
