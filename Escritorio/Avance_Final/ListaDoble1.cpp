#include <iostream>
#include <string.h>

using namespace std;
 
#define ASCENDENTE 1
#define DESCENDENTE 0

class nodo {
   private:
    int valor;
    string dato;
    string _valor;
    bool cumple; // bandera que almacena si cumple todas las funciones!!!
    
    nodo *Puntero;
    nodo *siguiente;
    nodo *anterior;
   
   
   public:
    nodo(string v, nodo *sig = NULL, nodo *ant = NULL) :
       dato(v), siguiente(sig), anterior(ant) {}
       
	nodo (string Dato, string Valor, nodo *sig= NULL, nodo *ant= NULL):   //Nodo que recibe dos valores de tipo String
		dato(Dato),
		_valor(Valor),
		siguiente(sig),
		anterior(ant) {}
	
	nodo (string Dato, nodo *puntero, bool _cumple, nodo *sig= NULL, nodo *ant= NULL):   //Nodo que recibe dos valores de tipo String
		dato(Dato),
		Puntero(puntero),
		cumple(_cumple),
		siguiente(sig),
		anterior(ant) {}
		
	nodo (nodo *puntero, bool _cumple, nodo *sig= NULL, nodo *ant= NULL ):
		Puntero(puntero),
		cumple(_cumple),
		siguiente(sig),
		anterior(ant) {}
		
	nodo (string Dato, bool _cumple, nodo *sig= NULL, nodo *ant= NULL):
		dato(Dato),
		cumple(_cumple),
		siguiente(sig),
		anterior(ant) {}
		
	nodo (nodo P, bool Cumple, nodo *sig= NULL, nodo *ant= NULL): //Nodo que recibe un dato de tipo noto y el boolean que verifica todas las condiciones
		Puntero (&P),
		cumple (Cumple) //siguiente con valor de nuul
		{}
        
   friend class lista;
};

typedef nodo *pnodo;

class lista {
   
   
   public:
    lista() : plista(NULL) {}
   ~lista();
    void InsertarFinal(string v, string g);
    void Borrar();
    bool ListaVacia() { return plista == NULL; } 
    void Mostrar(int);
    void Siguiente();
    void Anterior();
    void Primero();
    void Ultimo();
    void InsertaFinal2(string, nodo*, bool); 
    void InsertaPila(nodo, bool);
    void ImprimirBool();
    void Imprimir();
    bool Actual() { return plista != NULL; }
    int  ValorActual(); 
    bool VaciaLista();

	
   private:
    pnodo plista;
    nodo *null= NULL;

};



lista::~lista() {
   pnodo aux;
   Primero();
   while(plista) {
	  aux = plista;
      plista = plista->siguiente;
      delete aux;
   }
}


		
void lista::InsertaPila(nodo P, bool cumple) {
	pnodo nuevo;
	
	Primero();
	if (ListaVacia()){	
	  nuevo = new nodo(P, cumple);
      if(!plista) plista = nuevo;
      else plista->anterior = nuevo;
    }
    else{
		while(plista->siguiente != NULL) 
		Siguiente();
      // Creamos un nuevo nodo después del nodo actual
      nuevo = new nodo(P, cumple);
      plista->siguiente = nuevo;
      if(nuevo->siguiente) nuevo->siguiente->anterior = nuevo;
		
	}

}
// se encarga de eliminar el último elemento de la lista //
		

// Inserta a la Base de conocimiento //
		
void lista::InsertaFinal2 (string Dato, nodo *Puntero, bool cumple){
	   pnodo nuevo;
 
		Primero();
		// Si la lista está vacía
		if(ListaVacia()) {
    
		// Asignamos a lista un nuevo nodo de valor v y
		// cuyo siguiente elemento es la lista actual                    
		nuevo = new nodo(Dato, Puntero, cumple, plista);
		if(!plista) plista = nuevo;
		else plista->anterior = nuevo;
	}
	else {
      // Buscar el nodo de valor menor a v 
      // Avanzamos hasta el último elemento o hasta que el siguiente tenga 
      // un valor mayor que v 
      while(plista->siguiente != NULL) 
			Siguiente();
      // Creamos un nuevo nodo después del nodo actual
      nuevo = new nodo(Dato, Puntero, cumple, plista->siguiente, plista);
      plista->siguiente = nuevo;
      if(nuevo->siguiente) nuevo->siguiente->anterior = nuevo;
   }

}
	
// imprime el espacio en el nodo que corresponde al boolean //

void lista::ImprimirBool() {
	pnodo nodo;
	if (ListaVacia()){
		cout << "No puede imprimir nada por que la lista no tiene nada"<< endl;
	}
			
	else {
		Primero();
		nodo = plista;
		while (nodo){ 
			//std::string (aux->dato);
			if(strcmp((nodo->dato).c_str(),(""))){
				cout << nodo->cumple << " "<<endl;
			}
			else cout << nodo->dato << " "<<endl; 
			nodo= nodo->siguiente;
		}
	}
}
		
void lista::InsertarFinal(string Dato, string Valor) {
   pnodo nuevo;
 
   Primero();
   // Si la lista está vacía
   if(ListaVacia()) {
    
      // Asignamos a lista un nuevo nodo de valor v y
      // cuyo siguiente elemento es la lista actual                    
      nuevo = new nodo(Dato, Valor, plista);
      if(!plista) plista = nuevo;
      else plista->anterior = nuevo;
   }
   else {
      // Buscar el nodo de valor menor a v 
      // Avanzamos hasta el último elemento o hasta que el siguiente tenga 
      // un valor mayor que v 
      while(plista->siguiente != NULL) 
			Siguiente();
      // Creamos un nuevo nodo después del nodo actual
      nuevo = new nodo(Dato, Valor, plista->siguiente, plista);
      plista->siguiente = nuevo;
      if(nuevo->siguiente) nuevo->siguiente->anterior = nuevo;
   }
}

void lista::Borrar() {
   pnodo nodo;
   
   nodo = plista;
   if(ListaVacia()){
   		cout << "No hay elementos esta vacia";}
   	else{
		if(nodo->siguiente == null){
			nodo = null;
		}
		else{
			Primero();
			while(nodo->siguiente->siguiente!=null){
				nodo=nodo->siguiente;
			}
			nodo->siguiente=null;
		}
	}
}

void lista::Mostrar(int orden) {
   pnodo nodo;
   if(ListaVacia()){
	   	cout << "La lista esta vacia";
   }
   
   
   if(orden == ASCENDENTE) {
      Primero();
      nodo = plista;
      while(nodo) {
         cout << nodo->dato << " " << nodo-> _valor << "-> ";
         nodo = nodo->siguiente;
      }
   }
   cout << endl;
}

void lista::Siguiente() {
   if(plista) plista = plista->siguiente;
}

void lista::Anterior() {
   if(plista) plista = plista->anterior;
}

void lista::Primero() {
   while(plista && plista->anterior) plista = plista->anterior;
}

void lista::Ultimo() {
   while(plista && plista->siguiente) plista = plista->siguiente;
}

int main() {
   lista Lista;
   
   /*Lista.InsertaFinal("casa","caro");
   Lista.InsertaFinal("perro","moka");
   Lista.InsertaFinal("kenucho","isa");
   Lista.Imprimir();*/
   
   Lista.InsertarFinal("casa", "caro");
   Lista.InsertarFinal("jaja", "reir");
   Lista.InsertarFinal("diay", "maeee");
   Lista.InsertarFinal("pucha", "-.-");
   //Lista.Borrar();

   Lista.Mostrar(ASCENDENTE);
/*
   Lista.Primero();
   cout << "Primero: " << Lista.ValorActual() << endl;
   
   Lista.Ultimo();
   cout << "Ultimo: " << Lista.ValorActual() << endl;
  */ 
   //Lista.Borrar(10);
   /*Lista.Borrar(15);
   Lista.Borrar(45);
   Lista.Borrar(40);
   
   Lista.Mostrar(ASCENDENTE);
   Lista.Mostrar(DESCENDENTE);*/

   return 0;
}
