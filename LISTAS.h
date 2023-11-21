#ifndef LISTAS_H_INCLUDED
#define LISTAS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ARBOLES.h"
#include "LISTAS.h"
#include "FuncArchivos.h"
#define BORRAR_PANTALLA system("cls");


///General
nodoPaciente* cargarArbolConListas();
void mostrarListasDeTodosLosPacientes(nodoPaciente* arbol);
void mostrarListaDeIngresosDePaciente(nodoPaciente* arbol) ;
void mostrarPacientesConListasRecursivo(nodoPaciente* arbol);
void mostrarPacientesConListas(nodoPaciente* arbol);

///Nodo Ingresos

nodoIngresos *crearNodoIngresos(ingresos dato);
nodoIngresos *agregarPpioIngresos(nodoIngresos *lista, nodoIngresos *nuevoNodo);
nodoIngresos *buscarUltimoIngresos(nodoIngresos *lista);
nodoIngresos *buscarNodoIngresos(nodoIngresos *lista, int nroIngreso);
nodoIngresos *agregarFinalIngresos(nodoIngresos *lista, nodoIngresos *nuevoNodo);
nodoIngresos *borrarNodoIngresos(nodoIngresos *lista, int nroIngreso);
nodoIngresos * cargarListaDeingresos(nodoIngresos * lista);
void mostrarUnNodoDeIngresos(nodoIngresos * lista);
void mostrarListaDeIngreso(nodoPaciente *arbol);

///NODO PRAC X INGRESOS

nodoPracXingreso *crearNodoPracXingreso(pracXingreso dato);
nodoPracXingreso *agregarPpio(nodoPracXingreso *lista, nodoPracXingreso *nuevoNodo);
nodoPracXingreso *buscarUltimo(nodoPracXingreso *lista);
nodoPracXingreso *buscarNodo(nodoPracXingreso *lista, int nroDePractica);
nodoPracXingreso *agregarFinal(nodoPracXingreso *lista, nodoPracXingreso *nuevoNodo);
nodoPracXingreso *borrarNodo(nodoPracXingreso *lista, int nroDePractica);
void mostrarUnNodoPracXingreso(nodoPracXingreso * lista);
void mostrarListaPracXIngreso(nodoPracXingreso * lista);
nodoIngresos * cargarListaDePracXingreso(nodoIngresos * lista);
nodoPaciente* cargarListaDeIngresosDesdeArbol(nodoPaciente* arbol);
#endif // LISTAS_H_INCLUDED
