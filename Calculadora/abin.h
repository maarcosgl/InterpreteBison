#ifndef ABIN_H
#define ABIN_H

typedef void *abin; 

typedef struct elemento elemento;

struct elemento{
	int identificador;
	double valor;
	int *funcion;
    char *nombre;
};


/////////////////////////////// FUNCIONES
/*
 * Crea el arbol vacio.
 * @param A Puntero al arbol. Debe estar inicializado.
 */
void crear(abin *A);

/*
 * Destruye el arbol recursivamente
 * @param A El arbol que queremos destruir
 */
void destruir(abin *A);

/**
 * Comprueba si el arbol esta vacio
 * @param A El arbol binario
 */
unsigned esVacio(abin A);

/**
 * Devuelve el subarbol izquierdo de A
 * @param A - Arbol original
 */
abin izq(abin A);

/**
 * Devuelve el subarbol derecho de A
 * @param A - Arbol original
 */
abin der(abin A);

/**
 * Recupera la informacion de la celda de la raiz del arbol
 * @param A
 * @param E Puntero al elemento que apuntara a la informacion
 */
void leer(abin A, elemento *E);

/**
 * Imprime todo el contenido del arbol mediante un recorrido recursivo preorden
 * @param A arbol que se quiere imprimir
 */
void imprimir(abin A);

/**
 * Busca si un lexema de un componente lexico esta en el arbol
 * Si no está, lo inserta
 * Devuelve un entero que se corresponderá con el componente léxico que se inserta
 * Sirve para diferencia cadenas alfanuméricas de palabras reservadas
 * @param A
 * @param E Puntero al elemento que apuntara a la informacion
 */
void insertar_buscar_variable(abin *A, char *nombre, double valor);
void insertar_buscar_constante(abin *A, char *nombre, double valor);
void insertar_buscar_funcion(abin *A, char *nombre, int *funcion);
int buscarNodo(abin A, char *nombre);
double devolverNodo(abin A, char *nombre);

#endif	// ABIN_H

