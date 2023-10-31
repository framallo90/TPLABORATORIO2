#include "ARBOLES.h"

nodoPaciente* inicArbol(){///INICIA EL ARBOL EN NULL
    return NULL;
}

nodoPaciente* crearNodo(paciente dato){///CREA EL NODO DEL ARBOL CON LOS DATOS DEL PACIENTE
    nodoPaciente* nuevo = (nodoPaciente*)malloc(sizeof(nodoPaciente));
    nuevo->dato = dato;
    nuevo->listaIngresos = NULL;
    nuevo->izq = NULL;
    nuevo->der = NULL;
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

nodoPaciente* buscar(nodoPaciente* arbol, int dni){///BUSCA PACIENTE POR DNI EN EL ARBOL
    nodoPaciente * rta=NULL;
    if(arbol!=NULL){
        if(dni == arbol->dato.DNI){
            printf("\nEL DATO SE ENCUENTRA EN EL ARBOL.\n");
            rta = arbol;
        }else
            if(dni>arbol->dato.DNI){
                rta = buscar(arbol->der, dni);
            }else{
                rta = buscar(arbol->izq, dni);
            }
    }else{
        printf("\nEL DATO NO SE ENCUENTRA EN EL ARBOL.\n");
    }
    return rta;
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

nodoPaciente* cargarPacientesDesdeArchivo() {///LEE EL ARCHIVO PACIENTES COPIANDO LOS DATOS DE LOS QUE ESTAN GUARDADOS, LLAMA A INSERTAR Y LOS GUARDA EN EL ARBOL
    FILE *archivo = fopen("pacientes.bin", "rb");
    if (archivo == NULL) {
        printf("\nNO SE PUDO ABRIR EL ARCHIVO DE PACIENTES.");
        return NULL;
    }

    nodoPaciente* arbol = NULL;
    paciente pacienteActual;

    while (fread(&pacienteActual, sizeof(paciente), 1, archivo) == 1) {
        arbol = insertarEnArbol(arbol, crearNodo(pacienteActual));
    }

    fclose(archivo);
    return arbol;
}
