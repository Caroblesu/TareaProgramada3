#include <iostream>
#include <stdio.h>
#include <string.h>
#include "/home/carol/Documentos/Progra_2/FINAL/ListaDoble1.cpp"
	
class Consulta {
	
	public:
	bool Es_hecho, Es_regla;
	nodo Pred_Valido;
	lista Resultado;
	lista BC;//lexico.bc
	void Consultar(lista L);
	bool Buscar_BC(lista L, lista BC);
	bool unifica (nodo BC, nodo Consultar);
	void VerificarRegla (lista Pila, lista BC);
	void Validez ();
	bool Operar(bool ant, string ope, bool suc);
	void esMayuscula(char x);
	
};	
	
	void Consulta::esMayuscula(char x) { 
		int asciiValue = x; 
		if(asciiValue <= 91){ 
			cout << "Es mayuscula"; 
		} else if(asciiValue >=97 ){ 
				cout << "Es minuscula"; 
						} 
		}
	
	void Consulta::Consultar (lista L) {
		if (Buscar_BC(L,BC) && Es_hecho){
			//Resultado.InsertaBool("", true);
			if (!Es_regla){
				Validez();
			}
			Es_hecho= false;
			Es_regla= false;
		}
		else if (Buscar_BC(L,BC) && !Es_hecho) {
			
			lista Pila;
			lista ListaInsertada;
			ListaInsertada.InsertaFinal(Pred_valido.dato , Pred_Valido.valor);
			
			nodo *aux = Pred_Valido.Puntero;
			
			while (aux != null){
				if (strcmp(aux->dato,":")){
					
					Pila.InsertaPila(ListaInsertada.Primero, false);					
					ListaInsertada.Primero =  null;
					aux = aux->siguiente;
				}
				else{
					 if (strcmp(aux->dato,",") || strcmp(aux->dato,";") || strcmp(aux->dato,".")) {
					
					Pila.InsertaPila(ListaInsertada.Primero, false);
					Pila.InsertaPila(aux, false);
					ListaInsertada.Primero =  null;
					
					//Resultado.InsertaBool(aux.dato, true);
					
				}
			}
				else {
					ListaInsertada.InsertaFinal(aux->dato, aux->valor);
				    
				}			
				aux = aux->siguiente;
			}
			//AQUI VA VERIFICAR REGLA
			//Pila.imprimirListaAdyacencia();
			VerificarRegla (Pila, BC);
		}
		else {
			Resultado.InsertaBool("", false);
			if (!Es_regla){
				//Consultar(L);
				Validez();
				
			}
			Es_regla = false;
			//System.out.println ("NO");
		}
	}
	
	bool Consulta::Buscar_BC (lista L, lista BC){
		
		nodo aux_BC = BC.Primero;
		bool valido = true;
		
		while (aux_BC != null) {
			
			//System.out.println(aux_BC.dato +" " +aux_BC.cumple + " " + aux_BC.Puntero.siguiente.dato);
			
			if (strcmp(aux_BC.dato,L.Primero.dato) /*& aux_BC.cumple*/){
				
				//System.out.println(aux_BC.dato + cont);
				
				valido = true;
				nodo auxBC_P = aux_BC.Puntero; 
				nodo auxConsulta = L.Primero.siguiente;
				
				
				while (auxConsulta != null && auxBC_P != null && valido ) {
					
					//System.out.println("Dato entrante BC " + auxBC_P.dato + "Dato entrante Consulta " + "    " + auxConsulta.dato);
					
					if (!strcmp(auxBC_P.dato,"(") && !strcmp(auxBC_P.dato,")") && !strcmp(auxBC_P.dato,",") && !strcmp(auxBC_P.dato,".")){    
						
						//System.out.println("Entre :p"); 
						
						if (!unifica(auxBC_P, auxConsulta)) {
							valido = false;
						}
					}
					else if (strcmp(auxBC_P.dato,")") ) {
						if (strcmp(auxBC_P.siguiente -> dato,".")) Es_hecho = true;
						else Es_regla = true;
						if (strcmp(!auxConsulta.dato,")")) valido = false; 
					}
					
					else if (strcmp(auxConsulta.dato,")") ) {
						if (!strcmp(auxBC_P.dato,")")) valido = false; 
					}
					auxBC_P = auxBC_P.siguiente;
					auxConsulta = auxConsulta.siguiente;
				}
				
				if (valido) break;
			}
			aux_BC = aux_BC.siguiente;
		}
		
		if (valido && aux_BC != null){
			Pred_Valido = aux_BC;
			//aux_BC.cumple = false;
			return true;
		}
		else if (aux_BC == null) {
			//System.out.println("NO SE ENCUENTRA EN LA BC"); 
			return false;
		}
		else return false;
		
	}
	
	bool Consulta::unifica (nodo BC, nodo Consultar) {
		
		//System.out.println("BC " + BC.dato + " Consulta " + Consulta.dato);
		
		char iBC = BC.dato.charAt(0);
		char iCon = Consultar.dato.charAt(0);
		
		if (Character.esMayuscula(iBC) && Character.esMayuscula(iCon)) 
			Consultar.valor = BC.valor;
		
		else if (!Character.esMayuscula(iBC) && !Character.esMayuscula(iCon)) {
			if (strcmpr(BC.dato,Consultar.dato)){
				Consultar.valor = Consultar.dato;
				BC.valor = BC.dato; // Prueba (hay que desunificar si no funciona)
			}
			else return false;
		}
		
		else if (Character.esMayuscula(iBC) && !Character.esMayuscula(iCon))
			BC.valor = Consultar.dato;
		
		else 
			Consultar.valor = BC.dato;
		
		return true;
	}
	
	void Consulta::VerificarRegla (lista Pila, lista BC){
		
		//System.out.println("vr");
		
		Nodo predAux = Pila.Ultimo-> anterior;
		while (predAux != Pila.Primero){
			
			Lista ListaAux = new Lista();
			Nodo aux = predAux.Puntero;
			
			if (strcmp(aux.dato,",") || strcmp(aux.dato,";") || strcmp(aux.dato,".") ){
				Resultado.InsertaBool(aux.dato, true);
			}
			else {
				
				while (aux != null){
					ListaAux.InsertaFinal(aux.dato, aux.valor);
					aux = aux.siguiente;
				}
				//ListaAux.Imprimir();
				if (strcmp(ListaAux.Primero.dato,"write")){
					cout << ListaAux.Primero.siguiente.siguiente.siguiente.dato>>;
					Resultado.InsertaBool("", true);
				}
				else if(strcmp(ListaAux.Primero.dato,"nl")){
					cout<<"">>;
					Resultado.InsertaBool("", true);
				}
				else if (strcmp(ListaAux.Primero.dato,"fail")){
					Resultado.InsertaBool("", false);
				}
				else{
					Consultar(ListaAux);
				}
			}
			predAux = predAux.anterior;
		}
		Validez();
		//Resultado.Primero = null;
		//Resultado.ImprimirBool();
	}
	
	void Consulta::Validez (){
		
		//System.out.print("si");
		if (Resultado.ListaVacia()){ /*System.out.print("estpy vacia");*/return;}
		//Resultado.ImprimirBool(); //System.out.println("jujuju");
		if (Resultado.Primero.siguiente == null || strcmp(Resultado.Primero.siguiente->dato,".")){
			if(Resultado.Primero.cumple) System.out.println("YES");
			else cout<<"NO">>;
			
		}
		
		else{
			if (Resultado.Primero.siguiente.siguiente == null) return;
			bool resultado = Operar(Resultado.Primero.cumple, Resultado.Primero.siguiente.dato, Resultado.Primero.siguiente.siguiente.cumple);
			
			nodo aux = Resultado.Primero.siguiente.siguiente.siguiente;
			while (aux != null ){
				//System.out.println(aux.dato);
				if (!strcmp(aux.dato,""))
				resultado = Operar(resultado, aux.dato, aux.siguiente.cumple) ;
				aux = aux->siguiente;
			}
			if (resultado){ 
				cout <<"YES">>;
			}
			else {
				cout<<"NO">>;
			}
		}
		Resultado.Primero = NULL;
		
		//Resultado.ImprimirBool();
	}
	
	bool Consulta::Operar(bool ant, string ope, bool suc){
		
		//System.out.println(ant+ope+suc);
		if (strcmp(ope.c_str(),","))
			return ant && suc;
		
		if (strcmp(ope.c_str(),";")==0)
			return ant || suc;
		return true;
	}
	
	

		
