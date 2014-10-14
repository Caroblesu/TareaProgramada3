
#include <string.h>

#include <stdlib.h>

#include <string.h>

#include "lex.yy.c"

#include <iostream>
using namespace std;

#include <stdio.h>

#include <fstream>

 
 #define OP_SUM 331		// "-"
 #define NUM 330		// Numero [0-9]
 #define PABRE 321		// "("
 #define PCIERRA 322	// ")"
 #define ID 328			// Letras
 #define ID2 327		// Letras
 #define IS 333			// is
 #define NL 334			// nl
 #define FINLI 325		// "."		
 #define COMA 326		// ","		
 #define RAYA 336		// "_"
 #define ADMI 335		// "!"
 #define PABREC 323		// [
 #define PCIERRAC 324	// ]
 #define ERROR 666
 #define FIN 332		// "/" 
 
 
 //CLASE ANALIZA
 class analiza{
 
public :
      analiza(){
		  tok = 0;
		  gets(texto);

		if(strcmp(texto, "<define>")==0)
		{ 
			programa();
		}
		else{
			printf("Instruccion invalida, ingrese <define> para iniciar \n");
			analiza();
		}
		  //programa();
		}			     //constructor, llama a programa para iniciar el reconocimiento
      void programa();   //no terminal programa
      void lp();         //no terminal lista_props
      void lp1();        //no terminal lista_props'
      void prop();       //no terminal prop
      void der();        //no terminal der
      void izq();        //no terminal izq
      void lt();         //no terminal lista_term
      void lt1();        //no terminal lista_term'
      void expa();       //no terminal expa
      void arit();       //no terminal arit
      void arit1();      //no terminal arit'
      void termino();    //no terminal termino
      void id();         //terminal
      void num();        //terminal
      void asig();       //no terminal asig
      void asig1();      //no terminal asig'
      void escribir(); 	 //escribir en el archivo .txt
 
private :
      int tok;
      char texto[80];

};

ofstream _Archivo("BC.txt"); //crea el txt


void analiza::escribir(){
// Enviamos una cadena al fichero de salida:
	gets(texto);
	_Archivo << texto << endl;
}

 
void analiza::programa(){    //programa-> lista_prop
	  tok = 0;
      tok = yylex();

      lp();
}


void analiza::lp(){       //lista_prop -> prop lista_prop'
		
//      printf("entro a LP y este es mi tok es %s \n", yytext);	
//      printf("este es yytext %s \n", yytext);

      prop();
      
      _Archivo << yytext << endl;
 //     printf("este es yytext %s1 \n", yytext);

      tok = yylex();   //**************************************************************

      if (tok != FIN)
      //if(strcmp(yytext, "</define>")!=0)

            lp1();

      else{

            printf("\nAnalisis terminado, no se encontraron errores\n");
            printf("  Escriba la consulta que desee realizar: \n" );
            tok = yylex(); 
            tok = yylex(); 
			programa();
            //exit(0);

      }

}


void analiza::lp1(){   //lista_prop' -> prop lista_prop'
	

 //      printf("entro a LP1 y este es mi tok es %s \n", yytext);	

      prop();
      _Archivo << yytext;

//      printf("este es yytext %s 2\n", yytext);
      _Archivo << "   ";

      tok = yylex();        //*******************************************************

      if (tok != FIN){
      //if(strcmp(yytext, "</define>")!=0){
            lp1();
		}
      else{

            printf("\nAnalisis terminado, no se encontraron errores\n");
            printf("  Escriba la consulta que desee realizar: \n" );
            tok = yylex(); 
            tok = yylex(); 
			programa();
            //exit(0);

      }

}


void analiza::prop(){             //prop -> izq :- asig

 //      printf("entro a PROP y este es mi tok es %s \n", yytext);	
      //escribir();
      izq();

      if(strcmp(yytext, ":-")==0)

      {
		  _Archivo << yytext;

//		  printf("estoy en prop con :- \n");

            tok = yylex();
            if(tok == NL){
				  printf("error, revise su programa e intente de nuevo. \n");

                  exit(0);
			}

            asig();

            if(strcmp(yytext, ".")!=0){

                  printf("error, revise su programa e intente de nuevo. \n");

                  exit(0);

            }
            else{
            //printf("este es yytext primero %s \n", yytext);
			}

      }
      else{
		  
		if(strcmp(yytext, ".")==0){
			_Archivo << yytext << endl;

//			printf("este es yytext segundo %s \n", yytext);

			programa();
		}
		else{
			if (tok == NL){
            printf("error, revise su programa e intente de nuevo.\n");
            exit(0);}
      }
      
   }

}


void analiza::asig(){         //asig-> der , asig' .

  //     printf("entro a ASIG y este es mi tok es %s \n", yytext);	
      der();

      if(tok != FINLI && tok == COMA)

      {
		    _Archivo << yytext;

//			printf("este es yytext4 %s \n", yytext);
	
            tok = yylex();

            asig1();

      }

}

 

void analiza::asig1(){        //asig'-> der , asig' | epsilon

//       printf("entro a ASIG1 y este es mi tok es %s \n", yytext);	

      der();

      if(tok != FINLI && tok == COMA)

      {
		    _Archivo << yytext;

//			printf("este es yytext5 %s \n", yytext);

            tok = yylex();

            asig1();

      }

}



void analiza::der(){           //der -> ! | nl | expa | izq

 //      printf("entro a DER y este es mi tok es %s \n", yytext);	
                               

      if(tok == ADMI || tok == NL)

      {
		    _Archivo << yytext;

//			printf("este es yytext6 %s \n", yytext);

            tok = yylex();

      }

 

      expa();

 

      izq();

 

}

 
void analiza::izq(){          //izq -> id ( lista_term )

  //     printf("entro a IZQ y este es mi tok es %s \n", yytext);	

      if(tok != FINLI)                

      {

                                         // tok = yylex();

            id();

            //tok= yylex();

            if(strcmp(yytext, "(")==0)

            {

                  lt();

                  if(strcmp(yytext, ")")!=0){

                        printf("error, revise su programa e intente de nuevo. \n");

                        exit(0);

                  }
                  else{
					    _Archivo << yytext;

//						printf("este es yytext %s7 \n", yytext);

					  tok = yylex();
					if ((tok != FINLI) && (tok != COMA) && (strcmp(yytext, ":-")!=0))
					{
                        printf("error, revise su programa e intente de nuevo. \n");

                        exit(0);					
                        }
	  
				  }

            }

            else{
				if (strcmp(yytext, ":-")==0){
//					printf("si es :-\n");
				}
				else{

					printf("error, revise su programa e intente de nuevo.\n");

					exit(0);
				}

            }

            //tok = yylex();

      }

}

 

void analiza::lt(){    //lista_term -> termino lista_termm' | expa lista_term'

                       //aqui mismo se havce la transformación lista_term -> [lista_term]

 //      printf("entro a LT y este es mi tok es %s \n", yytext);	

      termino();        

      lt1();

      if(strcmp(yytext, "[")==0)

      {

            lt();

            if(strcmp(yytext, "]")!=0){

                  printf("error, revise su programa e intente de nuevo.en lt \n");

                  exit(0);

            }
            _Archivo << yytext;

//			printf("este es yytext %s8 \n", yytext);

            tok = yylex();

      }

      lt1();

}

 

void analiza::lt1(){                          //lista_term' -> , termino lista_term' | epsilon

 //      printf("entro a LT1 y este es mi tok es %s \n", yytext);	
    	//printf("yytext %s y tok es %d", yytext, tok);

      if((strcmp(yytext, ",")==0)){

      termino();

      lt1();

      if(strcmp(yytext, "[")==0)

      {

            lt();

            if(strcmp(yytext, "]")==0){

                  printf("error, revise su programa e intente de nuevo. \n");

                  exit(0);

            }
            _Archivo << yytext;

	//		printf("este es yytext %s9 \n", yytext);

            yylex();

      }

      lt1();

      }
      /*if(strcmp(yytext, ")")==0){
	  termino();
	  }*/

}
 

void analiza::expa(){           //expa -> id is arit

 //      printf("entro a EXPA y este es mi tok es %s \n", yytext);	


		if(tok != FINLI){

            id();

            if(strcmp(yytext, "is")==0){

                  arit();
			}
            else{

                  if(tok != PABREC && tok != PCIERRAC &&tok != PABRE && tok != PCIERRA && tok != FINLI)

                  {printf("error, revise su programa e intente de nuevo. \n");

                  exit(0);}

            }

 

            if(tok != PABREC && tok != PABRE)

            {
				_Archivo << yytext;

				printf("este es yytext %s10 \n", yytext);

                  tok = yylex();

            }

 }

 

}

 

void analiza::arit(){    //arit -> termino arit'

//       printf("entro a ARIT y este es mi tok es %s \n", yytext);	


      termino();

      arit1();

}

 

void analiza::arit1(){   //arit' -> termino arit' | epsilon
 //      printf("entro a ARIT1 y este es mi tok es %s \n", yytext);	

 

      if(strcmp(yytext, "-")==0)

      {

            termino();

            arit1();

      }

}

 

void analiza::termino(){   //termino -> id | numeroo | nl | !

 //      printf("entro a TERMINO y este es mi tok es %s \n", yytext);	


      if(tok == FIN)
      //if(strcmp(yytext, "</define>")==0)

      {

            printf("\nAnalisis terminado, no se encontraron errores\n");
            printf("  Escriba la consulta que desee realizar: \n" );
			tok = yylex(); 
			tok = yylex(); 
			programa();
            //exit(0);

      }
      _Archivo << yytext;

//	  printf("este es yytext11 %s \n", yytext);
		
      tok = yylex();

      if(tok != RAYA){

            id();

			//tok = yylex();

            num();

      }

      else{
			//printf("este es yytext12 %s \n", yytext);

            tok= yylex();

      }

}

 

void analiza::id(){        //identificador, es un terminal
 //      printf("entro a ID y este es mi tok es %s \n", yytext);	

 

      if(tok == FIN)
      //if(strcmp(yytext, "</define>")==0)

      {

            printf("\nAnalisis terminado, no se encontraron errores\n");
            printf("  Escriba la consulta que desee realizar: \n" );
			tok = yylex(); 
			tok = yylex(); 
			programa();
            //exit(0);

      }



      if(tok != PABREC && tok != PCIERRAC && tok!=ID && tok!=ID2 && tok != PABRE && tok != PCIERRA && tok != FINLI && tok != NUM && tok != OP_SUM)

      {
//		    printf("mi tok es %d\n",tok);

            printf("error, revise su programa e intente de nuevo.\n");

            exit(0);

      }

    if((tok == ID)){	
		    _Archivo << yytext;
																				 
	//		printf("este es yytext13 %s \n", yytext);

            tok = yylex();
	}
}

 

void analiza::num(){   //numero, es un terminal

  //     printf("entro a NUM y este es mi tok es %s \n", yytext);	


      if(tok == FIN)
	  //if(strcmp(yytext, "</define>")==0)
      {

            printf("\nAnalisis terminado, no se encontraron errores\n");
            printf("  Escriba la consulta que desee realizar: \n" );
			tok = yylex(); 
			tok = yylex(); 
			programa();
            //exit(0);

      }

 

      if(tok != PABREC && tok != PCIERRAC && tok!=NUM && tok != PABRE && tok != PCIERRA && tok != COMA && tok != ID && tok != ID2 && tok != OP_SUM && tok != FINLI )

      {

            printf("error, revise su programa e intente de nuevo.\n");

            exit(0);

      }

      if((tok == ID) | (tok == ID2) | (tok == NUM)){
		    _Archivo << yytext;

//			printf("este es yytext14 %s \n", yytext);

            tok = yylex();}


}



int main(){    //procedimiento principal.

 

printf("___________________________________________________________________\n\n");

printf("  Digite '<define>' para ingresar y digite el codigo de su programa:\n" );
printf("                                                                    \n" );
printf("  Digite '</define>' salir                                          \n" );

printf("___________________________________________________________________\n\n");


analiza a1;

_Archivo.close();	// Cerrar el fichero,

}
