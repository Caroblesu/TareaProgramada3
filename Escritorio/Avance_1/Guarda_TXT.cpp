#include <iostream>
#include <fstream>
#include <string.h>

using namespace std;

int main() {
	char cadena[3128];
	char linea[50][3000];
	string texto;
	string lineacadena;
	int a=0;
	int b=0;
// Crea un fichero de salida
	ofstream _Archivo("nombre.txt"); //crea el txt
	string mensaje="hola esto es un mensaje\0";
	
// Enviamos una cadena al fichero de salida:
	_Archivo << mensaje << endl;
	_Archivo.close();	// Cerrar el fichero,
						// para luego poder abrirlo para lectura:
// Abre un fichero de entrada
	ifstream fe("nombre.txt");

// Leeremos mediante getline, si lo hiciéramos
// mediante el operador << sólo leeríamos
// parte de la cadena:

	a=-1;
	while (!fe.eof()){
		fe.getline(cadena,3000);
		a++;
		string lineacadena (cadena); // añadido: convierto array de char a cadena
		texto +=lineacadena + '\n';  // añado a la cadena texto.
		strcat(linea[a],cadena); //añadido trabajando con cadenas 
		cout<<"-------"<<endl;
		cout<<linea[a]<< endl;
		cout << cadena << endl; // añadido: escribo.
		}
	
	
	for(b=0;b<=a;b++){
	cout << linea[b]; // coge linea por linea del txt
	cout << "\n";
	}
	
	cout <<"----------------------------------------\n";
	cout <<"imprimo una cadena\n";
	cout <<"----------------------------------------\n";
	cout << texto;
	return 0;
	}
	
/*int main ()
{
	char nombre[] = "<define>";
  char input[20];
  do {
     printf ("Escriba <define> para comenzar \n");
     gets (input);
  } while (strcmp (szKey,szInput) != 0);
  puts ("Correct answer!");
  return 0;
	
}*/
