
#include <string.h>

#include <stdlib.h>

#include <string.h>

#include "lex.yy.c"

#include <iostream>

#include <stdio.h>


 
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
		  letra = 0;
		  tok = 0;
		  programa();
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
 
 
private :
      int tok;
	  int letra;
};

void analiza::programa(){    //programa-> lista_prop

      tok = yylex();

      lp();
		
}

 

void analiza::lp(){       //lista_prop -> prop lista_prop'

       printf("entro a LP y este es mi tok es %d \n", tok);

      prop();

      tok = yylex();   //**************************************************************

      if (tok != FIN)

            lp1();

      else{

            printf("\nAnalisis terminado, no se encontraron errores\n");

            exit(0);

      }

}

 

void analiza::lp1(){   //lista_prop' -> prop lista_prop'

       printf("entro a LP1 y este es mi tok es %d\n", tok);

      prop();

      tok = yylex();        //*******************************************************

      if (tok != FIN)

            lp1();

      else{

            printf("\nAnalisis terminado, no se encontraron errores\n");

            exit(0);

      }

}

 

 

void analiza::prop(){             //prop -> izq :- asig

       printf("entro a PROP y este es mi tok es %d\n", tok);

      izq();
      


      if(strcmp(yytext, ":-")==0)

      {

            tok = yylex();
            if(tok == NL){
				  printf("error en la linea anterior, revise su programa e intente de nuevo. por \nl \n");

                  exit(0);
			}

            asig();

            if(strcmp(yytext, ".")!=0){

                  printf("error en la linea anterior, revise su programa e intente de nuevo. \n");

                  exit(0);

            }

      }
      else{
		  
		if(strcmp(yytext, ".")==0){
			tok = yylex();
			lp();
		}
		else{
			if (tok == NL){
            printf("error en la linea anterior, revise su programa e intente de nuevo.\n");
            exit(0);}
      }
      
   }

}

 

void analiza::asig(){         //asig-> der , asig' .

       printf("entro a ASIG y este es mi tok es %d\n", tok);

      der();

      if(tok != FINLI && tok == COMA)

      {
	
            tok = yylex();

            asig1();

      }

}

 

void analiza::asig1(){        //asig'-> der , asig' | epsilon

       printf("entro a ASIG1 y este es mi tok es %d\n", tok);

      der();

      if(tok != FINLI && tok == COMA)

      {

            tok = yylex();

            asig1();

      }

}



void analiza::der(){           //der -> ! | nl | expa | izq

       printf("entro a DER y este es mi tok es %d\n", tok);
                               

      if(tok == ADMI || tok == NL)

      {

            tok = yylex();

      }

 

      expa();

 

      izq();

 

}

 

void analiza::izq(){          //izq -> id ( lista_term )

       printf("entro a IZQ y este es mi tok es %d\n", tok);

      if(tok != FINLI)                

      {

                                         // tok = yylex();

            id();

            //tok= yylex();

            if(strcmp(yytext, "(")==0)

            {

                  lt();

                  if(strcmp(yytext, ")")!=0){

                        printf("error en la linea anterior, revise su programa e intente de nuevo. \n");

                        exit(0);

                  }
                  else{

					  tok = yylex();
					if ((tok != FINLI) && (tok != COMA) && (strcmp(yytext, ":-")!=0))
					{
                        printf("error, revise su programa e intente de nuevo. \n");

                        exit(0);					
                        }			  
				  }

            }

            else{

            printf("error en la linea anterior, revise su programa e intente de nuevo.\n");

            exit(0);

            }

            tok = yylex();

      }

}

 

void analiza::lt(){    //lista_term -> termino lista_termm' | expa lista_term'

                       //aqui mismo se havce la transformación lista_term -> [lista_term]

       printf("entro a LT y este es mi tok es %d\n", tok);

      termino();        

      lt1();

      if(strcmp(yytext, "[")==0)

      {

            lt();

            if(strcmp(yytext, "]")!=0){

                  printf("error en la linea anterior, revise su programa e intente de nuevo.en lt \n");

                  exit(0);

            }

            tok = yylex();

      }

      lt1();

}

 

void analiza::lt1(){                          //lista_term' -> , termino lista_term' | epsilon

      printf("entro a LT1 y este es mi tok es %d\n", tok);
//	printf("yytext %s y tok es %d", yytext, tok);

      if((strcmp(yytext, ",")==0)){

      termino();

      lt1();

      if(strcmp(yytext, "[")==0)

      {

            lt();

            if(strcmp(yytext, "]")==0){

                  printf("error en la linea anterior, revise su programa e intente de nuevo. \n");

                  exit(0);

            }

            yylex();

      }

      lt1();

      }
      /*if(strcmp(yytext, ")")==0){
	  termino();
	  }*/

}
 

void analiza::expa(){           //expa -> id is arit

       printf("entro a EXPA y este es mi tok es %d\n", tok);


 if(tok != FINLI){

            id();

            if(strcmp(yytext, "is")==0)

                  arit();

            else{

                  if(tok != PABREC && tok != PCIERRAC &&tok != PABRE && tok != PCIERRA && tok != FINLI)

                  {printf("error en la linea anterior, revise su programa e intente de nuevo. \n");

                  exit(0);}

            }

 

            if(tok != PABREC && tok != PABRE)

            {

                  tok = yylex();

            }

 }

 

}

 

void analiza::arit(){    //arit -> termino arit'

       printf("entro a ARIT y este es mi tok es %d\n", tok);


      termino();

      arit1();

}

 

 

void analiza::arit1(){   //arit' -> termino arit' | epsilon
       printf("entro a ARIT1 y este es mi tok es %d\n", tok);

 

      if(strcmp(yytext, "-")==0)

      {

            termino();

            arit1();

      }

}

 

void analiza::termino(){   //termino -> id | numeroo | nl | !

       printf("entro a TERMINO y este es mi tok es %d\n", tok);


      if(tok == FIN)

      {

            printf("\nAnalisis terminado, no se encontraron errores\n");

            exit(0);

      }

      tok = yylex();

      if(tok != RAYA){

            id();

			//tok = yylex();

            num();

      }

      else{

            tok= yylex();

      }

}

 

void analiza::id(){        //identificador, es un terminal
       printf("entro a ID y este es mi tok es %d\n", tok);

 

      if(tok == FIN)

      {

            printf("\nAnalisis terminado, no se encontraron errores\n");

            exit(0);

      }



      if(tok != PABREC && tok != PCIERRAC && tok!=ID && tok!=ID2 && tok != PABRE && tok != PCIERRA && tok != FINLI && tok != NUM && tok != OP_SUM)

      {
		  printf("mi tok es %d\n",tok);

            printf("error en la linea anterior, revise su programa e intente de nuevo.\n");

            exit(0);

      }

    if((tok == ID))																					 

            tok = yylex();

}

 

void analiza::num(){   //numero, es un terminal

       printf("entro a NUM y este es mi tok es %d\n", tok);


      if(tok == FIN)

      {

            printf("\nAnalisis terminado, no se encontraron errores\n");

            exit(0);

      }

 

      if(tok != PABREC && tok != PCIERRAC && tok!=NUM && tok != PABRE && tok != PCIERRA && tok != COMA && tok != ID && tok != ID2 && tok != OP_SUM && tok != FINLI )

      {

            printf("error en la linea anterior, revise su programa e intente de nuevo.\n");

            exit(0);

      }

      if((tok == ID) | (tok == ID2) | (tok == NUM))
			if(tok == ID2){
				letra = 1;
			}
			else{
				letra = 0;
			}

            tok = yylex();

}



int main(){    //procedimiento principal.

 

printf("________________________________________________________________\n\n");

printf("Digite el codigo de su programa (para terminar, digite '/'):\n");

printf("________________________________________________________________\n\n");

 

analiza a1;

}
