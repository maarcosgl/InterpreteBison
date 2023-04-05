#include <stdlib.h>
#include <stdio.h>
#include "definiciones.h"
#include "abin.h"

//Constante que indica el número de palabras reservadas presentes en el código
#define palabrasReservadas 8

//Se define la tabla como un arbol binario
abin tablaSimbolos; 

/*
Una tabla es una arbol binario, 
asi que lo que recibe crearTabla() es un 
puntero a arbolBinario
*/
void insertar_buscar_tabla_variable(char *nombre, double valor){
    insertar_buscar_variable(&tablaSimbolos, nombre, valor);
}

void insertar_buscar_tabla_constante(char *nombre, double valor){
    insertar_buscar_constante(&tablaSimbolos, nombre, valor);
}
void insertar_buscar_tabla_funcion(char *nombre, int * funcion){
    insertar_buscar_funcion(&tablaSimbolos, nombre, funcion);
}

void crearTabla(){
    crear(&tablaSimbolos);
    insertar_buscar_tabla_constante("pi", 3.14159265359);
    insertar_buscar_tabla_constante("e", 2.71828182845);
}

void destruirTabla(){
    destruir(&tablaSimbolos);
}

void imprimirTabla(){
    imprimir(tablaSimbolos);
}

int buscarNodoTabla(char *nombre){
    return buscarNodo(tablaSimbolos, nombre);
}

double devolverNodoTabla(char *nombre){
    return devolverNodo(tablaSimbolos, nombre);
}

