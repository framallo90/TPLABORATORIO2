#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BORRAR_PANTALLA system("cls");

typedef struct persona {
     char nombre[20];
     int edad;
} persona;

typedef struct nodo {
     persona dato;
     struct nodo *siguiente;
} nodo;

nodo *inicLista();
nodo *crearNodo(persona dato);
nodo *agregarPpio(nodo *lista, nodo *nuevoNodo);
nodo *buscarUltimo(nodo *lista);
nodo *buscarNodo(nodo *lista, char nombre[20]);
nodo *agregarFinal(nodo *lista, nodo *nuevoNodo);
nodo *agregarEnOrden(nodo *lista, nodo *nuevoNodo);
nodo *borrarNodo(nodo *lista, char nombre[20]);
nodo *borrarTodaLaLista(nodo *lista);
void mostrarUnNodo(nodo *aux);
void mostrarLista(nodo *lista);
persona creoPersona();

///CON ARCHIVOS
void cargarPersona(char archivo[]);
nodo *pasoAlista(char archivo[],nodo *lista);
void pasoAlistaREF(char archivo[],nodo **lista);

///borro nodo con recursividad
nodo *borroRecursivo(nodo *lista);

#endif // LISTAS_H_INCLUDED
