#ifndef ARBOLES_H_INCLUDED
#define ARBOLES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ARBOLES.h"
#include "LISTAS.h"
#include "FuncArchivos.h"


nodoPaciente* inicArbol();
paciente IngresoPaciente();
nodoPaciente* cargoArbol(nodoPaciente* arbol);
nodoPaciente* crearNodo(paciente dato);
nodoPaciente* insertarNodo(nodoPaciente* arbol, nodoPaciente* nuevo);
void inorder(nodoPaciente* arbol);
nodoPaciente* insertarEnArbol(nodoPaciente* arbol, nodoPaciente* nuevo);
nodoPaciente* cargarPacientesDesdeArchivo();

#endif // ARBOLES_H_INCLUDED
