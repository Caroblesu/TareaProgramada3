#include <iostream>

/*struct nodo {
   int dato;
   struct nodo *siguiente;
   struct nodo *anterior;
};
typedef struct _nodo {
   int dato;
   struct _nodo *siguiente;
   struct _nodo *anterior;
} tipoNodo;
 
typedef tipoNodo *pNodo;
typedef tipoNodo *Lista;
*/		//por si quiero hacer el nodo con structs...
	
class Consulta {
	static bool Es_hecho, Es_regla;
	static nodo Pred_Valido;
	static Lista Resultado = new Lista();
	static Lista BC = //lexico.BC
	
	
	static void Consultar (Lista L) {
		if (Buscar_BC(L,BC) && Es_hecho){
			Resultado.InsertaBool("", true);
			if (!Es_regla){
				Validez();
			}
			Es_hecho= false;
			Es_regla= false;
		}
		else if (Buscar_BC(L,BC) && !Es_hecho) {
			
			Lista Pila = new Lista();
			Lista ListaInsertada =  new Lista();
			ListaInsertada.InsertaFinal(Pred_valido.dato , Pred_Valido.valor);
			
			struct Nodo *aux = Pred_Valido.Puntero;
			
			while (aux != null){
				if (strcmp(aux.dato,":")){
					
					Pila.InsertaPila(ListaInsertada.Primero, false);					
					ListaInsertada.Primero =  null;
					aux = aux.siguiente;
				}
				else if (aux.dato.equals(",") || aux.dato.equals(";") || aux.dato.equals(".")) {
					
					Pila.InsertaPila(ListaInsertada.Primero, false);
					Pila.InsertaPila(aux, false);
					ListaInsertada.Primero =  null;
					
					//Resultado.InsertaBool(aux.dato, true);
					
				}
				else {
					ListaInsertada.InsertaFinal(aux.dato, aux.valor);
				}			
				aux = aux.siguiente;
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
	
	static boolean Buscar_BC (Lista L, Lista BC){
		
		Nodo aux_BC = BC.Primero;
		boolean valido = true;
		
		while (aux_BC != null) {
			
			//System.out.println(aux_BC.dato +" " +aux_BC.cumple + " " + aux_BC.Puntero.siguiente.dato);
			
			if (aux_BC.dato.equals(L.Primero.dato) /*& aux_BC.cumple*/){
				
				//System.out.println(aux_BC.dato + cont);
				
				valido = true;
				Nodo auxBC_P = aux_BC.Puntero; 
				Nodo auxConsulta = L.Primero.siguiente;
				
				
				while (auxConsulta != null && auxBC_P != null && valido ) {
					
					//System.out.println("Dato entrante BC " + auxBC_P.dato + "Dato entrante Consulta " + "    " + auxConsulta.dato);
					
					if (!auxBC_P.dato.equals("(") && !auxBC_P.dato.equals(")") && !auxBC_P.dato.equals(",") && !auxBC_P.dato.equals(".")){    
						
						//System.out.println("Entre :p"); 
						
						if (!unifica(auxBC_P, auxConsulta)) {
							valido = false;
						}
					}
					else if (auxBC_P.dato.equals(")") ) {
						if (auxBC_P.siguiente.dato.equals(".")) Es_hecho = true;
						else Es_regla = true;
						if (!auxConsulta.dato.equals(")")) valido = false; 
					}
					
					else if (auxConsulta.dato.equals(")") ) {
						if (!auxBC_P.dato.equals(")")) valido = false; 
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
	
	static boolean unifica (Nodo BC, Nodo Consulta) {
		
		//System.out.println("BC " + BC.dato + " Consulta " + Consulta.dato);
		
		char iBC = BC.dato.charAt(0);
		char iCon = Consulta.dato.charAt(0);
		
		if (Character.isUpperCase(iBC) && Character.isUpperCase(iCon)) 
			Consulta.valor = BC.valor;
		
		else if (Character.isLowerCase(iBC) && Character.isLowerCase(iCon)) {
			if (BC.dato.equals(Consulta.dato)) {
				Consulta.valor = Consulta.dato;
				BC.valor = BC.dato; // Prueba (hay que desunificar si no funciona)
			}
			else return false;
		}
		
		else if (Character.isUpperCase(iBC) && Character.isLowerCase(iCon))
			BC.valor = Consulta.dato;
		
		else 
			Consulta.valor = BC.dato;
		
		return true;
	}
	
	static void VerificarRegla (Lista Pila, Lista BC){
		
		//System.out.println("vr");
		
		Nodo predAux = Pila.Ultimo.anterior;
		while (predAux != Pila.Primero){
			
			Lista ListaAux = new Lista();
			Nodo aux = predAux.Puntero;
			
			if (aux.dato.equals(",") || aux.dato.equals(";") || aux.dato.equals(".") ){
				Resultado.InsertaBool(aux.dato, true);
			}
			else {
				
				while (aux != null){
					ListaAux.InsertaFinal(aux.dato, aux.valor);
					aux = aux.siguiente;
				}
				//ListaAux.Imprimir();
				if (ListaAux.Primero.dato.equals("write")){
					System.out.println(ListaAux.Primero.siguiente.siguiente.siguiente.dato);
					Resultado.InsertaBool("", true);
				}
				else if(ListaAux.Primero.dato.equals("nl")){
					System.out.println("");
					Resultado.InsertaBool("", true);
				}
				else if (ListaAux.Primero.dato.equals("fail")){
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
	
	static void Validez (){
		
		//System.out.print("si");
		if (Resultado.VaciaLista()){ /*System.out.print("estpy vacia");*/return;}
		//Resultado.ImprimirBool(); //System.out.println("jujuju");
		if (Resultado.Primero.siguiente == null || Resultado.Primero.siguiente.dato.equals(".")){
			if(Resultado.Primero.cumple) System.out.println("YES");
			else System.out.println("NO");
			
		}
		
		else{
			if (Resultado.Primero.siguiente.siguiente == null) return;
			boolean resultado = Operar(Resultado.Primero.cumple, Resultado.Primero.siguiente.dato, Resultado.Primero.siguiente.siguiente.cumple);
			
			Nodo aux = Resultado.Primero.siguiente.siguiente.siguiente;
			while (aux != null ){
				//System.out.println(aux.dato);
				if (!aux.dato.equals(""))resultado = Operar(resultado, aux.dato, aux.siguiente.cumple) ;
				aux = aux.siguiente;
			}
			if (resultado) System.out.println("YES");
			else System.out.println("NO");
		}
		Resultado.Primero = null;
		
		//Resultado.ImprimirBool();
	}
	
	static boolean Operar(boolean ant, String ope, boolean suc){
		
		//System.out.println(ant+ope+suc);
		if (ope.equals(","))
			return ant && suc;
		
		if (ope.equals(";"))
			return ant || suc;
		return true;
	}
	
	
}
		
