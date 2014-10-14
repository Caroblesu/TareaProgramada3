
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
 class analiza1{
 
public :
      analiza1(){
		printf("  Escriba la consulta que desee realizar: \n" );
		  
		  tok = 0;

		  programa0();
		}			     //constructor, llama a programa para iniciar el reconocimiento
      void programa0();   //no terminal programa
      void lp0();         //no terminal lista_props
      void prop0();       //no terminal prop
      void izq0();        //no terminal izq
      void lt0();         //no terminal lista_term
      void lt10();        //no terminal lista_term'
      void termino0();    //no terminal termino
      void id0();         //terminal
      void num0();        //terminal
      
private :
      int tok;
};


 
void analiza1::programa0(){    //programa-> lista_prop

	  printf("\n?- ");
      tok = yylex();

      lp0();
}


void analiza1::lp0(){       //lista_prop -> prop lista_prop'
		
      printf("entro a LP y este es mi tok es %s \n", yytext);	
//      printf("este es yytext %s \n", yytext);

      prop0();
      
      tok = yylex();   //**************************************************************

      if (tok != FIN){
      //if(strcmp(yytext, "</define>")!=0)

            //lp1();

      }else{

            printf("\nAnalisis terminado, no se encontraron errores\n");

            exit(0);

      }

}


void analiza1::prop0(){             //prop -> izq :- asig

       printf("entro a PROP y este es mi tok es %s \n", yytext);	
      izq0();
		  
	  if(strcmp(yytext, ".")==0){
			//consulta();														clase de consulta
			programa0();
		}
		else{
            printf("error, revise su programa e intente de nuevo.\n");
            exit(0);}   

}


void analiza1::izq0(){          //izq -> id ( lista_term )

       printf("entro a IZQ y este es mi tok es %s \n", yytext);	

      if(tok != FINLI)                

      {

            id0();

            if(strcmp(yytext, "(")==0)

            {

                  lt0();

                  if(strcmp(yytext, ")")!=0){

                        printf("error, revise su programa e intente de nuevo. \n");

                        exit(0);

                  }
                  else{

					  tok = yylex();
					if (tok != FINLI)
					{
                        printf("error, revise su programa e intente de nuevo. \n");

                        exit(0);					
                    }
                    else{
						printf("Analisis terminado\n");							
						//consulta();											clase de consulta
						programa0();
					}
	  
				  }

            }

            else{
				if(strcmp(yytext, ".")==0) {
					printf("Analisis terminado\n");							

					//consulta();												clase de consulta
					programa0();
				}
				else{

					printf("error, revise su programa e intente de nuevo.\n");

					exit(0);
				}

            }

      }

}

 

void analiza1::lt0(){    //lista_term -> termino lista_termm' | expa lista_term'

                       //aqui mismo se havce la transformación lista_term -> [lista_term]

       printf("entro a LT y este es mi tok es %s \n", yytext);	

      termino0();        

      lt10();

      if(strcmp(yytext, "[")==0)

      {

            lt0();

            if(strcmp(yytext, "]")!=0){

                  printf("error, revise su programa e intente de nuevo.en lt \n");

                  exit(0);

            }

            tok = yylex();

      }

      lt10();

}

 

void analiza1::lt10(){                          //lista_term' -> , termino lista_term' | epsilon

       printf("entro a LT1 y este es mi tok es %s \n", yytext);	
    	//printf("yytext %s y tok es %d", yytext, tok);

      if((strcmp(yytext, ",")==0)){

      termino0();

      lt10();

      if(strcmp(yytext, "[")==0)

      {

            lt0();

            if(strcmp(yytext, "]")==0){

                  printf("error, revise su programa e intente de nuevo. \n");

                  exit(0);

            }

            yylex();

      }

      lt10();

      }
}
 

void analiza1::termino0(){   //termino -> id | numeroo | nl | !

       printf("entro a TERMINO y este es mi tok es %s \n", yytext);	


      if(tok == FIN)
      //if(strcmp(yytext, "</define>")==0)

      {

            printf("\nAnalisis terminado, no se encontraron errores\n");

            exit(0);

      }
		
      tok = yylex();

      if(tok != RAYA){

            id0();

            num0();

      }

      else{

            tok= yylex();

      }

}

 

void analiza1::id0(){        //identificador, es un terminal
       printf("entro a ID y este es mi tok es %s \n", yytext);	

 

      if(tok == FIN)
      //if(strcmp(yytext, "</define>")==0)

      {

            printf("\nAnalisis terminado, no se encontraron errores\n");

            exit(0);

      }



      if(tok != PABREC && tok != PCIERRAC && tok!=ID && tok!=ID2 && tok != PABRE && tok != PCIERRA && tok != FINLI && tok != NUM && tok != OP_SUM)

      {
            printf("error, revise su programa e intente de nuevo.\n");

            exit(0);

      }

    if((tok == ID)){	

            tok = yylex();
	}
}

 

void analiza1::num0(){   //numero, es un terminal

       printf("entro a NUM y este es mi tok es %s \n", yytext);	


      if(tok == FIN)
	  //if(strcmp(yytext, "</define>")==0)
      {

            printf("\nAnalisis terminado, no se encontraron errores\n");

            exit(0);

      }

 

      if(tok != PABREC && tok != PCIERRAC && tok!=NUM && tok != PABRE && tok != PCIERRA && tok != COMA && tok != ID && tok != ID2 && tok != OP_SUM && tok != FINLI )

      {

            printf("error, revise su programa e intente de nuevo.\n");

            exit(0);

      }

      if((tok == ID) | (tok == ID2) | (tok == NUM)){

            tok = yylex();}


}

/*

int main(){    //procedimiento principal.

 

printf("___________________________________________________________________\n\n");

printf("  Escriba la consulta que desee realizar: \n" );

printf("___________________________________________________________________\n\n");


analiza1 a1;


}*/
