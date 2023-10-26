#ifndef ARBOLES_H_INCLUDED
#define ARBOLES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct paciente{///DATO PARA EL ARBOL DE PACIENTES
    char NyA[40];
    int Edad;
    int DNI;
    char Direccion[30];
    char telefono[15];
    int Eliminado;
}paciente;

typedef struct nodoPaciente {/// NODO PARA EL ARBOL DE PACIENTES
    paciente dato;
    struct ingresos *listaIngresos; // Puntero a la lista de ingresos asociados a este paciente
    struct paciente *izq; // Puntero al hijo izquierdo en el árbol (menor DNI)
    struct paciente *der; // Puntero al hijo derecho en el árbol (mayor DNI)
}nodoPaciente;

nodoPaciente* inicArbol();
paciente IngresoPaciente();
nodoPaciente* cargoArbol(nodoPaciente* arbol);
nodoPaciente* crearNodo(paciente dato);
nodoPaciente* insertarNodo(nodoPaciente* arbol, nodoPaciente* nuevo);
void inorder(nodoPaciente* arbol);
nodoPaciente* insertarEnArbol(nodoPaciente* arbol, nodoPaciente* nuevo);
nodoPaciente* cargarPacientesDesdeArchivo();

#endif // ARBOLES_H_INCLUDED
