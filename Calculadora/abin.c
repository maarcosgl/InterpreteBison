#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definiciones.h"

/////////////////////REPETIMOS LA DEFINICIÓN DE LOS TIPOS DE DATOS
//abin es un puntero a struct celda
typedef struct celda *abin;
//contenido de cada elemento del árbol
//es un árbol de componentes lexico

typedef struct elemento elemento;

struct elemento{
	int identificador;
	double valor;
	int *funcion;
    char *nombre;
};

/////////////////////ESTRUCTURAS DE DATOS
struct celda{
	elemento info;
	struct celda *izq, *der;
};

///////////////////////FUNCIONES

//Crea el árbol vacío
void crear(abin *A){
	*A=NULL;
}

//Suprime las ramas izquierda y derecha de un nodo del arbol
void supizq(abin *A);
void supder(abin *A);
int comparar_nodos(char* nodo1, char* nodo2);
//Comprueba si un nodo del arbol esta vacío
unsigned esVacio(abin A);

int comparar_nodos(char* nodo1, char* nodo2){
	return strcmp(nodo1, nodo2);
}

void destruir(abin *A){
	abin aux;
	aux=*A;
	if(!esVacio(aux)){
	  supizq(&aux);
	  supder(&aux);
	  free(aux->info.nombre); 
	  free(aux->info.funcion); // Liberar memoria de la cadena de caracteres
	  free(aux);
	  *A=NULL;
	}	
}

//Comprueba si el árbol está vacío
unsigned esVacio(abin A){
	return (A==NULL);
}

//Devuelve el subárbol izquierdo de A
abin izq(abin A){
	return A->izq;
}

//Devuelve el subárbol derecho de A
abin der(abin A){
	return A->der;
}

//Recupera la informacion de la celda de la raiz del arbol
void leer(abin A, elemento *E){
	*E=A->info;
}

//Suprime el subárbol a la izquierda de A
void supizq(abin *A){
	abin aux;
	aux=izq(*A);
	if(!esVacio(aux)){
	  supizq(&aux);
	  supder(&aux);	
	  free(aux->info.nombre); // Liberar memoria de la cadena de caracteres
	  free(aux->info.funcion);
	  (*A)->izq=NULL;
	  free(aux);
	}	
}

//Suprime el subárbol a la derecha de A
void supder(abin *A){
	abin aux;
	aux=der(*A);
	if(!esVacio(aux)){
	  supizq(&aux);
	  supder(&aux);	
	  free(aux->info.nombre); // Liberar memoria de la cadena de caracteres
	free(aux->info.funcion);
	  (*A)->der=NULL;
	  free(aux);
	}	
}

//Recorrido recursivo preorden: R-I-D
void imprimir(abin A) {
    elemento E;
    if (!esVacio(A)) {
        leer(A, &E);
        printf("%d | %s\n", E.identificador, E.nombre);
        imprimir(izq(A));
        imprimir(der(A));
    }
}
void insertar_buscar_variable(abin *A, char *nombre, double valor){
	abin aux;

	//Si un nodo del árbol está vacío, se reserva memoria para el mismo
	//También se reserva memoria suficiente para almacenar el lexema
	if(esVacio(*A)){
		aux=(abin)malloc(sizeof(struct celda));
		aux->info.identificador =  VARIABLE;
		aux->info.valor =  valor;
		aux->info.nombre = (char *)malloc(strlen(nombre)+1);
		//Se copia el contenido del lexema, en el campo correspondiente del componente léxcio
		strcpy(aux->info.nombre, nombre);
		aux->izq=NULL;
		aux->der=NULL;
		*A=aux;
	}
	//Si el nodo no está vacío, hay que comparar si el lexema que se quiere meter, ya está guardado en el árbol
	else{
		if(strcmp(nombre, (*A)->info.nombre) > 0){
			insertar_buscar_variable(&(*A)->der, nombre, valor);
		}
		else{
			insertar_buscar_variable(&(*A)->izq, nombre, valor);
		}
	}
}
void insertar_buscar_constante(abin *A, char *nombre, double valor){
	abin aux;

	//Si un nodo del árbol está vacío, se reserva memoria para el mismo
	//También se reserva memoria suficiente para almacenar el lexema
	if(esVacio(*A)){
		aux=(abin)malloc(sizeof(struct celda));
		aux->info.identificador =  CONSTANTE;
		aux->info.valor =  valor;
		aux->info.nombre = (char *)malloc(strlen(nombre)+1);
		//Se copia el contenido del lexema, en el campo correspondiente del componente léxcio
		strcpy(aux->info.nombre, nombre);
		aux->izq=NULL;
		aux->der=NULL;
		*A=aux;
	}
	//Si el nodo no está vacío, hay que comparar si el lexema que se quiere meter, ya está guardado en el árbol
	else{
		if(strcmp(nombre, (*A)->info.nombre) > 0){
			insertar_buscar_constante(&(*A)->der, nombre, valor);
		}
		else{
			insertar_buscar_constante(&(*A)->izq, nombre, valor);
		}
	}
}
void insertar_buscar_funcion(abin *A, char *nombre, int *funcion){
	abin aux;

	//Si un nodo del árbol está vacío, se reserva memoria para el mismo
	//También se reserva memoria suficiente para almacenar el lexema
	if(esVacio(*A)){
		aux=(abin)malloc(sizeof(struct celda));
		aux->info.identificador =  FUNCION;
		aux->info.funcion =  funcion;
		aux->info.nombre = (char *)malloc(strlen(nombre)+1);
		//Se copia el contenido del lexema, en el campo correspondiente del componente léxcio
		strcpy(aux->info.nombre, nombre);
		aux->izq=NULL;
		aux->der=NULL;
		*A=aux;
	}
	//Si el nodo no está vacío, hay que comparar si el lexema que se quiere meter, ya está guardado en el árbol
	else{
		if(strcmp(nombre, (*A)->info.nombre) > 0){
			insertar_buscar_funcion(&(*A)->der, nombre, funcion);
		}
		else{
			insertar_buscar_funcion(&(*A)->izq, nombre, funcion);
		}
	}
}

int buscarNodo(abin A, char *nombre){
	if(esVacio(A)){
		return 0;
	}

	int comp = comparar_nodos(nombre, A->info.nombre);

	if(comp == 0){
		return 1;
	}
	else if(comp < 0){
		return buscarNodo(A->izq, nombre);
	}
	else{
		return buscarNodo(A->der, nombre);
	}
}

double devolverNodo(abin A, char *nombre){
	if(esVacio(A)){
		return 0;
	}

	int comp = comparar_nodos(nombre, A->info.nombre);

	if(comp == 0){
		return A->info.valor;
	}
	else if(comp < 0){
		return devolverNodo(A->izq, nombre);
	}
	else{
		return devolverNodo(A->der, nombre);
	}
}
