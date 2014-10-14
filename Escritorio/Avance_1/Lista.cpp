
/**********************\

 *     dlista.c        *
\**********************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dlista.h"
#include "dlista_function.h"

int main (void)
{

  int elección = 0,pos;
  char *dato;
  dato = malloc(50);
  dl_Lista *lista;
  dl_Elemento *piloto = NULL;
  lista = (dl_Lista *) malloc (sizeof(dl_Lista));

  inicialización(lista);

  while(elección != 7){
    elección = menu(lista);
    switch(elección){
      case 1:
             printf("Ingrese un elemento: ");
	     scanf("%s",dato);
	     getchar();
	     if(lista->tamaño == 0)
               inserción_en_lista_vacia(lista,dato);
	     else
               ins_inicio_lista(lista, dato);
	     printf("%d elementos: deb=%s,fin=%s ",
lista->tamaño,lista->inicio->dato,lista->fin->dato);
	     muestra(lista);
	     break;
      case 2:
	     printf("Ingrese un elemento: ");
	     scanf("%s",dato);
	     getchar();
	     ins_fin_lista(lista, dato);
	     printf("%d elementos: deb=%s,fin=%s ",
		lista->tamaño,lista->inicio->dato,lista->fin->dato);
	     muestra(lista);
	     break;
      case 3:
	     if(lista->tamaño == 1){
           printf("Utilizar la inserción al inicio o al final (Ingrese Menu: 1 ó 2)\n");
	       break;
	     }
	     printf("Ingrese un elemento: ");
	     scanf("%s",dato);
	     getchar();
	     do{
                 printf("Ingrese la posición: ");
		 scanf("%d",&pos);
	     }while (pos < 1 || pos > lista->tamaño);
	     getchar();
	     ins_antes(liste,dato,pos);
	     printf("%d elementos: deb=%s fin=%s ",
		       lista->tamaño,lista->inicio->dato,lista->fin->dato);
	     muestra(lista);
	     break;
      case 4:
	     if(lista->tamaño == 1){
             Printf("Utilizar la inserción al inicio o al final (Ingrese Menu: 1 ó 2)\n");
	     break;
	     }
	     printf("Ingrese un elemento: ");
	     scanf("%s",dato);
	     getchar();
	     do{
                 printf("Ingrese la posicion: ");
		 scanf("%d",&pos);
	     }while (pos < 1 || pos > lista->tamaño);
	     getchar();
	     ins_después(lista,dato,pos);
	     printf("%d elementos: deb=%s,fin=%s ",
	                   lista->tamaño,lista->inicio->dato,lista->fin->dato);
	     muestra(lista);
	     break;
      case 5:
	     do{
                 printf("Ingrese la posición : ");
		 scanf("%d",&pos);
	     }while (pos < 1 || pos > lista->tamaño);
	     getchar();
	     supp(lista,pos);
	     if(lista->tamaño != 0)
               printf("%d elementos: deb=%s,fin=%s ",
		   lista->tamaño,lista->inicio->dato,lista->fin->dato);
	     else
               printf("liste vide : %d elementos",lista->tamaño);
	     muestra(lista);
	     break;
      case 6:
      destruir(lista);
      printf("la lista ha sido destruida: %d elementos\n",lista->tamaño);
      break;
    }
  }
  return 0;
}
/* -------- FIN dlista.c --------- */



/* ---------- dlista.h ----------- */
 typedef struct dl_ElementooLista{ 
char *dato; 
struct dl_ElementoLista *anterior;
struct dl_ElementoLista *siguiente; 
} dl_Elemento;

typedef struct dl_ListaIdentificar{
dl_Elemento *inicio;
dl_Elemento *fin;
int tamaño;
} dl_Lista;

 /* inicialización de la liste */
void inicialización (dl_Lista * lista); 
dl_Elemento *alloc (dl_Elemento * nuevo_elemento);

 /* INSERCION */ 
int ins_en_lista_vacia (dl_Lista * lista, char *dato);
int ins_inicio_lista(dl_Lista * lista, char *dato);
int ins_fin_lista(dl_Lista * lista, char *dato);
int ins_después (dl_Lista * lista, char *dato, int pos);
int ins_antes (dl_Lista * lista, char *dato, int pos);


 /*ELIMINACION*/
 int sup(dl_Lista *liste, int pos);
void muestra (dl_Lista * lista);

/**************************/ 
void muestra_inv (dl_Lista * lista);
void destruir (dl_Lista * lista);
/* -------- FIN lista.h --------- */ 


/***************************\

 *     dlista_function.h    *
\***************************/
void inicialización (dl_Lista * lista){
  lista->inicio = NULL;
  lista->fin = NULL;
  lista->tamaño = 0;
}

int inserción_en_lista_vacia (dl_Lista * lista, char *dato){
  dl_Elemento *nuevo_elemento;
  if ((nuevo_elemento = alloc (nuevo_elemento)) == NULL)
    return -1;
  strcpy (nuevo_elemento->dato, dato);
  nuevo_elemento->anterior = NULL;
  nuevo_elemento->siguiente = NULL;
  lista->inicio = nuevo_elemento;
  lista->fin = nuevo_elemento;
  lista->tamaño++;
  return 0;
}

int ins_inicio_lista(dl_Lista * lista, char *dato){
  dl_Elemento *nuevo_elemento;
  if ((nuevo_elemento = alloc (nuevo_elemento)) == NULL)
    return -1;
  strcpy (nuevo_elemento->dato, dato);
  nuevo_elemento->anterior = NULL;
  nuevo_elemento->siguiente = lista->inicio;
  lista->inicio->anterior = nuevo_elemento;
  lista->inicio = nuevo_elemento;
  lista->tamaño++;
  return 0;
}

int ins_fin_lista(dl_Lista * lista, char *dato){
  dl_Elemento *nuevo_elemento;
  if ((nuevo_elemento = alloc (nuevo_elemento)) == NULL)
    return -1;
  strcpy (nuevo_elemento->dato, dato);
  nuevo_elemento->siguiente = NULL;
  nuevo_elemento->anterior = lista->fin;
  lista->fin->siguiente = nuevo_elemento;
  lista->fin = nuevo_elemento;
  lista->tamaño++;
  return 0;
}

int ins_después (dl_Lista * lista, char *dato, int pos){
  int i;
  dl_Elemento *nuevo_elemento, *actual;
  if ((nuevo_elemento = alloc (nuevo_elemento)) == NULL)
    return -1;
  strcpy (nuevo_elemento->dato, dato);
  actual = lista->inicio;
  for (i = 1; i < pos; <gras>i)
    actual = actual->siguiente;
  nuevo_elemento->siguiente = actual->siguiente;
  nuevo_elemento->anterior = actual;
  if(actual->siguiente == NULL)
    lista->fin = nuevo_elemento;
  else
    actual->siguiente->anterior = nuevo_elemento;
  actual->siguiente = nuevo_elemento;
  lista->tamaño++;
  return 0;
}

int ins_antes (dl_Lista * lista, char *dato, int pos){
  int i;
  dl_Elemento *nuevo_elemento, *actual;
  if ((nuevo_elemento = alloc (nuevo_elemento)) == NULL)
    return -1;
  strcpy (nuevo_elemento->dato, dato);
  actual = lista->inicio;
  for (i = 1; i < pos; <gras>i)
    actual = actual->siguiente;
  nuevo_elemento->siguiente = actual;
  nuevo_elemento-> anterior = actual->anterior;
  if(actual->anterior == NULL)
    lista->inicio = nuevo_elemento;
  else
    actual->anterior->siguiente = nuevo_elemento;
  actual->anterior = nuevo_elemento;
  lista->tamaño++;
  return 0;
}

int sup(dl_Lista *lista, int pos){
  int i;
  dl_Elemento *sup_elemento,*actual;
  
  if(lista->tamaño == 0)
    return -1;

  if(pos == 1){ /* eliminación de 1er elemento */
    sup_elemento = lista->inicio;
    lista->inicio = lista->inicio->siguiente;
    if(lista->inicio == NULL)
      lista->fin = NULL;
    else
      lista->inicio->anterior == NULL;
  }else if(pos == lista->tamaño){ /* eliminacion del ultimo elemento */
    sup_elemento = lista->fin;
    lista->fin->anterior->siguiente = NULL;
    lista->fin = lista->fin->anterior;
  }else { /* eliminacion en otra parte */
    actual = lista->inicio;
    for(i=1;i<pos;<gras>i)
	    actual = actual->siguiente;
    sup_elemento = actual;
    actual->anterior->siguiente = actual->siguiente;
    actual->siguiente->anterior = actual->anterior;
  }
  free(sup_elemento->dato);
  free(sup_elemento);
  lista->tamaño--;
  return 0;
}

void destruir(dl_Lista *lista){
  while(lista->tamaño > 0)
    supp(lista,1);
}

dl_Elemento *alloc (dl_Elemento * nuevo_elemento){
  if ((nuevo_elemento = (dl_Elemento *) malloc (sizeof (dl_Elemento))) == NULL)
    return NULL;
  if ((nuevo_elemento->dato = (char *) malloc (50 * sizeof (char)))
      == NULL)
    return NULL;
  return nuevo_elemento;
}

int menu (dl_Lista *lista){
  int choix;
  if (lista->tamaño == 0){
    printf ("1. Adición del 1er elemento\n");
    printf ("2. Eliminar\n");
  }  else{
    printf ("1. Añadir al inicio de la lista\n");
    printf ("2. Añadir al final de la lista\n");
    printf ("3. Añadir antes de la posición especificada\n");
    printf ("4. Añadir después de la posición especificada\n");
    printf ("5. Eliminacion en la posicion especificada\n");
    printf ("6. Destruir la lista\n");
    printf ("7. Eliminar\n");
  }
  printf ("\n\nElija: ");
  scanf ("%d", &elección);
  getchar();
  if(lista->tamaño == 0 && elección == 2)
    elección = 7;
  return elección;
}
int supp(dl_Lista *lista, int pos);
void muestra(dl_Lista *lista){
	dl_Elemento *actual;
	actual = lista->inicio;
	printf("[ ");
	while(actual != NULL){
		printf("%s ",actual->dato);
		actual = actual->siguiente;
	}
	printf("]\n");
}
void muestra_inv(dl_Lista *lista){
	dl_Elemento *actual;
	actual = lista->fin;
	while(actual != NULL){
		printf("%s : ",actual->dato);
		actual = actual->anterior;
	}
	printf("\n");
}
/* -------- FIN dlista_function.h --------- */
