#ifndef TABLASIMBOLOS_H
#define TABLASIMBOLOS_H

typedef void *tabla; 

//Función para la creación de la tabla de símbolos
void crearTabla();

//Función para la destrucción de la tabla de símbol0s
void destruirTabla();

//Función para imprimir la tabla de símbolos
void imprimirTabla();

void insertar_buscar_tabla_variable(char *nombre, double valor);

void insertar_buscar_tabla_constante(char *nombre, double valor);

void insertar_buscar_tabla_funcion(char *nombre, int * funcion);

int buscarNodoTabla(char *nombre);

double devolverNodoTabla(char *nombre);

#endif  // TABLA_H