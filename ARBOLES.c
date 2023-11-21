#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ARBOLES.h"
#include "LISTAS.h"
#include "FuncArchivos.h"

nodoPaciente* inicArbol(){///INICIA EL ARBOL EN NULL
    return NULL;
}

nodoPaciente* crearNodo(paciente dato){///CREA EL NODO DEL ARBOL CON LOS DATOS DEL PACIENTE
    nodoPaciente* nuevo = (nodoPaciente*)malloc(sizeof(nodoPaciente));
    nuevo->dato = dato;
    nuevo->listaIngresos = NULL;
    nuevo->izq = NULL;
    nuevo->der = NULL;

    return nuevo;
}

void inorder(nodoPaciente* arbol){///MUESTRA EL ARBOL EN ORDEN
    if(arbol != NULL){
        inorder(arbol->izq);
        printf("\nNOMBRE Y APELLIDO: %s, ", arbol->dato.NyA);
        printf("EDAD: %d, ",arbol->dato.Edad);
        printf("DNI: %d, ",arbol->dato.DNI);
        printf("DIRECCION: %s, ", arbol->dato.Direccion);
        if(arbol->dato.Eliminado == 0){
        printf("PACIENTE ACTIVO. ");
        }else{
        printf("PACIENTE DADO DE BAJA.");
        }
        inorder(arbol->der);
    }
}

void preorder(nodoPaciente* arbol){
    if(arbol != NULL){
        printf("\nNOMBRE Y APELLIDO: %s, ", arbol->dato.NyA);
        printf("EDAD: %d, ",arbol->dato.Edad);
        printf("DNI: %d, ",arbol->dato.DNI);
        printf("DIRECCION: %s, ", arbol->dato.Direccion);
        if(arbol->dato.Eliminado == 0){
        printf("PACIENTE ACTIVO. ");
        }else{
        printf("PACIENTE DADO DE BAJA.");
        }
        preorder(arbol->izq);
        preorder(arbol->der);
    }
}

void postorder(nodoPaciente* arbol){
    if(arbol != NULL){
        postorder(arbol->izq);
        postorder(arbol->der);
        printf("\nNOMBRE Y APELLIDO: %s, ", arbol->dato.NyA);
        printf("EDAD: %d, ",arbol->dato.Edad);
        printf("DNI: %d, ",arbol->dato.DNI);
        printf("DIRECCION: %s, ", arbol->dato.Direccion);
        if(arbol->dato.Eliminado == 0){
        printf("PACIENTE ACTIVO. ");
        }else{
        printf("PACIENTE DADO DE BAJA.");
        }
    }
}

nodoPaciente* buscarNodoPaciente(nodoPaciente* arbol, int dniBuscado) {
    if (arbol == NULL || arbol->dato.DNI == dniBuscado) {
        return arbol;
    }

    if (dniBuscado < arbol->dato.DNI) {
        return buscarNodoPaciente(arbol->izq, dniBuscado);
    } else {
        return buscarNodoPaciente(arbol->der, dniBuscado);
    }
}

nodoPaciente* insertarEnArbol(nodoPaciente* arbol, nodoPaciente* nuevo) {///INSERTA EL NODO EN EL ARBOL POR DNI
    if (arbol == NULL) {
        arbol=nuevo;
    }

    if (nuevo->dato.DNI < arbol->dato.DNI) {
        arbol->izq = insertarEnArbol(arbol->izq, nuevo);
    } else if (nuevo->dato.DNI > arbol->dato.DNI) {
        arbol->der = insertarEnArbol(arbol->der, nuevo);
    }

    return arbol;
}

nodoPaciente* cargarPacientesDesdeArchivo() {
    FILE* archivo = fopen("pacientes.bin", "rb");
    if (archivo == NULL) {
        printf("\nNO SE PUDO ABRIR EL ARCHIVO DE PACIENTES.");
        return NULL;
    }

    nodoPaciente* arbol = NULL;
    paciente pacienteActual;

    while (fread(&pacienteActual, sizeof(paciente), 1, archivo) == 1) {
        nodoPaciente* nuevoNodo = crearNodo(pacienteActual);
        if (nuevoNodo != NULL) {
            arbol = insertarEnArbol(arbol, nuevoNodo);
        } else {
            // Manejar error de memoria
            printf("\nERROR AL CREAR NODO PARA EL PACIENTE.");
            break;
        }
    }

    fclose(archivo);
    return arbol;
}

