#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ARBOLES.h"
#include "LISTAS.h"
#include "FuncArchivos.h"
#include "menues.h"

///NODO INGRESOS
nodoIngresos *crearNodoIngresos(ingresos dato){
    nodoIngresos *aux = (nodoIngresos*) malloc(sizeof(nodoIngresos));
    aux->dato = dato;
    aux->siguiente = NULL;
    aux->listaPracticasXingreso = NULL;

    return aux;
}

nodoIngresos *agregarPpioIngresos(nodoIngresos *lista, nodoIngresos *nuevoNodo) {
    if (lista == NULL) {
        lista = nuevoNodo;
    } else {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
    return lista;
}

nodoIngresos *buscarUltimoIngresos(nodoIngresos *lista) {
    nodoIngresos *seg = lista;
    if (seg != NULL) {
        while (seg->siguiente != NULL) {
            seg = seg->siguiente;
        }
    }
    return seg;
}

nodoIngresos *buscarNodoIngresos(nodoIngresos *lista, int nroIngreso) {
    nodoIngresos *seg = lista;
    while (seg != NULL && seg->dato.NroDeIngreso != nroIngreso ){
        seg = seg->siguiente;
    }
    return seg;
}

nodoIngresos *agregarFinalIngresos(nodoIngresos *lista, nodoIngresos *nuevoNodo) {
    if (lista == NULL) {
        lista = nuevoNodo;
    } else {
        nodoIngresos *ultimo = buscarUltimoIngresos(lista);
        ultimo->siguiente = nuevoNodo;
    }
    return lista;
}

nodoIngresos *borrarNodoIngresos(nodoIngresos *lista, int nroIngreso) {
    nodoIngresos *seg;
    nodoIngresos *ante = NULL;

    if (lista != NULL && nroIngreso == lista->dato.NroDeIngreso) {
        nodoIngresos *aux = lista;
        lista = lista->siguiente;
        free(aux);
    } else {
        seg = lista;
        while (seg != NULL && nroIngreso != seg->dato.NroDeIngreso) {
            ante = seg;
            seg = seg->siguiente;
        }
        if (seg != NULL) {
            ante->siguiente = seg->siguiente;
            free(seg);
        }
    }
    return lista;
}

void mostrarUnNodoDeIngresos(nodoIngresos * lista){
    printf("\n---------------------------------------");
    printf("\nDNI: %i",lista->dato.DniPaciente);
    printf("\nNUMERO DE INGRESO: %i",lista->dato.NroDeIngreso);
    printf("\nFECHA DE INGRESO: %d/%d/%d", lista->dato.FechaDeRetiro->dia, lista->dato.FechaDeRetiro->mes, lista->dato.FechaDeRetiro->anio);
    printf("\nFECHA DE RETIRO: %d/%d/%d", lista->dato.FechaDeRetiro->dia, lista->dato.FechaDeRetiro->mes, lista->dato.FechaDeRetiro->anio);
    printf("\nMATRICULA DEL PROFESIONAL: %i",lista->dato.MatriculaDelProfesionalSolicitante);
    if (lista->dato.Eliminado == 0) {
        printf("\nEL INGRESO ESTA ACTIVO.");
    } else {
        printf("\nEL INGRESO ESTA DADO DE BAJA.");
    }
}

void mostrarListaDeIngreso(nodoPaciente *arbol) {
    if (arbol->izq != NULL) {
        mostrarListaDeIngreso(arbol->izq);
    }
    nodoIngresos *aux = arbol->listaIngresos;
    while (aux != NULL) {
        mostrarUnNodoDeIngresos(aux);
        aux = aux->siguiente;
    }
    if (arbol->der != NULL) {
        mostrarListaDeIngreso(arbol->der);
    }
}


///NODO PRAC X INGRESOS

nodoPracXingreso *crearNodoPracXingreso(pracXingreso dato) {
    nodoPracXingreso *aux = (nodoPracXingreso*) malloc(sizeof(nodoPracXingreso));
    aux->dato = dato;
    aux->siguiente = NULL;
    return aux;
}

nodoPracXingreso *agregarPpio(nodoPracXingreso *lista, nodoPracXingreso *nuevoNodo) {
    if (lista == NULL) {
        lista = nuevoNodo;
    } else {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
    return lista;
}

nodoPracXingreso *buscarUltimo(nodoPracXingreso *lista) {
    nodoPracXingreso *seg = lista;
    if (seg != NULL) {
        while (seg->siguiente != NULL) {
            seg = seg->siguiente;
        }
    }
    return seg;
}

nodoPracXingreso *buscarNodo(nodoPracXingreso *lista, int nroDePractica) {
    nodoPracXingreso *seg = lista;
    while (seg != NULL && seg->dato.NroDePractica != nroDePractica) {
        seg = seg->siguiente;
    }
    return seg;
}

nodoPracXingreso *agregarFinal(nodoPracXingreso *lista, nodoPracXingreso *nuevoNodo) {
    if (lista == NULL) {
        lista = nuevoNodo;
    } else {
        nodoPracXingreso *ultimo = buscarUltimo(lista);
        ultimo->siguiente = nuevoNodo;
    }
    return lista;
}

nodoPracXingreso *borrarNodo(nodoPracXingreso *lista, int nroDePractica) {
    nodoPracXingreso *seg;
    nodoPracXingreso *ante = NULL;

    if (lista != NULL && nroDePractica ==  lista->dato.NroDePractica) {
        nodoPracXingreso *aux = lista;
        lista = lista->siguiente;
        free(aux);
    } else {
        seg = lista;
        while (seg != NULL && nroDePractica != seg->dato.NroDePractica) {
            ante = seg;
            seg = seg->siguiente;
        }
        if (seg != NULL) {
            ante->siguiente = seg->siguiente;
            free(seg);
        }
    }
    return lista;
}

void mostrarUnNodoPracXingreso(nodoPracXingreso * lista){
    printf("\n----------------------------------");
    printf("\nNUMERO DE INGRESO: %i",lista->dato.NroDeIngreso);
    printf("\nNUMERO DE PRACTICA: %i",lista->dato.NroDePractica);
    printf("\nRESULTADO: %s",lista->dato.Resultado);
}

void mostrarListaPracXIngreso(nodoPracXingreso * lista){
    nodoPracXingreso * aux = lista;
    while(aux!=NULL){
        mostrarUnNodoPracXingreso(aux);
        aux = aux->siguiente;
    }
}

nodoIngresos * cargarListaDeingresos(nodoIngresos * lista){
    FILE * archivo = fopen("ingresos.bin", "rb");
    ingresos aux;
    if(archivo!=NULL){
        while(fread(&aux,sizeof(ingresos),1,archivo)>0){
            lista = agregarFinal(lista,crearNodoIngresos(aux));
        }
        fclose(archivo);
    }
    return lista;
}

nodoIngresos *cargarListaDePracXingreso(nodoIngresos *lista) {
    FILE *archivo = fopen("pracXingreso.bin", "rb");
    pracXingreso aux;

    if (archivo != NULL) {
        while (fread(&aux, sizeof(pracXingreso), 1, archivo) > 0) {
            nodoIngresos *temp = lista;
            while (temp != NULL) {
                if (aux.NroDeIngreso == temp->dato.NroDeIngreso) {
                    temp->listaPracticasXingreso = agregarFinal(temp->listaPracticasXingreso, crearNodoPracXingreso(aux));
                    break;  // Se encontró el ingreso, salimos del bucle interno
                }
                temp = temp->siguiente;
            }
        }
        fclose(archivo);
    }

    return lista;
}

//nodoIngresos * buscarNumeroDeingreso(nodoIngresos * lista){
//    nodoPaciente * arbol = buscarParaPracticas(arbol);
//    nodoIngresos * aux = arbol->listaIngresos;
//    if(arbol!=NULL){
//    int num;
//    printf("\nIngrese el numero de ingreso a buscar: ");
//    fflush(stdin);
//    scanf("%i",&num);
//    while((aux!=NULL)&&(aux->dato.NroDeIngreso!=num)){
//        aux = aux->siguiente;
//    }
//    if(aux->dato.NroDeIngreso==num){
//        printf("\nSe encontro el numero de ingreso: ");
//        mostrarUnNodoDeIngresos(aux);
//        return aux;
//    }
//    printf("\nno se encontro el numero de ingreso");
//    }
//}
//
//void  buscarNumeroDePractica(){
//    nodoIngresos * aux = buscarNumeroDeingreso(aux);
//    if(aux!=NULL){
//        int num;
//        printf("\nIngrese el numero de practica a buscar: ");
//        fflush(stdin);
//        scanf("%i",&num);
//        nodoPracXingreso * lista = aux->listaPracticasXingreso;
//        while((lista!=NULL)&&(lista->dato.NroDePractica!=num)){
//            lista=lista->siguiente;
//        }
//        if(lista->dato.NroDePractica==num){
//            printf("Se encontro el num de practica: \n");
//            mostrarUnNodoPracXingreso(lista);
//        }else{
//            printf("\nNo se encontro la practica");
//    }
//}
//}
//

nodoPaciente* cargarListaDeIngresosDesdeArbol(nodoPaciente* arbol){
    FILE *archivo = fopen("ingresos.bin","rb");
    ingresos aux;
    if(archivo != NULL){
        while(fread(&aux, sizeof(ingresos),1,archivo)>0){
            if(aux.DniPaciente == arbol->dato.DNI){
                if(arbol->listaIngresos == NULL){
                    arbol->listaIngresos = crearNodoIngresos(aux);
                }else{
                    arbol->listaIngresos = agregarFinal(arbol->listaIngresos, crearNodoIngresos(aux));
                }
            }
        }
        fclose(archivo);
    }
    if(arbol->izq != NULL){
        arbol->izq = cargarListaDeIngresosDesdeArbol(arbol->izq);
    }
    if(arbol->der != NULL){
        arbol->der = cargarListaDeIngresosDesdeArbol(arbol->der);
    }
    return arbol;
}

nodoPaciente* cargarArbolConListas() {
    nodoPaciente* arbolPacientes = cargarPacientesDesdeArchivo();
    if (arbolPacientes == NULL) {
        printf("\nEL ARBOL NO SE CARGO CORRECTAMENTE.");
        return NULL;
    }
    nodoPaciente* temp = arbolPacientes;
    while (temp != NULL) {
        temp->listaIngresos = cargarListaDeingresos(temp->listaIngresos);
        if (temp->listaIngresos == NULL) {
            printf("\nERROR AL CARGAR LA LISTA DE INGRESOS DEL PACIENTE CON DNI: %d", temp->dato.DNI);

        }
        nodoIngresos* tempIngresos = temp->listaIngresos;
        while (tempIngresos != NULL) {
            tempIngresos->listaPracticasXingreso = cargarListaDePracXingreso(tempIngresos->listaPracticasXingreso);
            tempIngresos = tempIngresos->siguiente;
        }

        temp = temp->der;
    }

    return arbolPacientes;
}


void mostrarPacientesConListas(nodoPaciente* arbol) {
    printf("\nPacientes con listas cargadas:\n");
    mostrarPacientesConListasRecursivo(arbol);
}

void mostrarPacientesConListasRecursivo(nodoPaciente* arbol) {
    if (arbol != NULL) {
        if (arbol->listaIngresos != NULL) {
            printf("DNI: %d, Nombre: %s\n", arbol->dato.DNI, arbol->dato.NyA);
        }

        mostrarPacientesConListasRecursivo(arbol->izq);
        mostrarPacientesConListasRecursivo(arbol->der);
    }
}

void mostrarListaDeIngresosDePaciente(nodoPaciente* arbol) {
    int dniBuscado;
    printf("\nIngrese el DNI del paciente cuya lista de ingresos desea ver: ");
    scanf("%d", &dniBuscado);

    nodoPaciente* paciente = buscarNodoPaciente(arbol, dniBuscado);

    if (paciente != NULL) {
        if (paciente->listaIngresos != NULL) {
            printf("\nLista de ingresos para el paciente con DNI %d:\n", dniBuscado);
            mostrarListaDeIngreso(paciente->listaIngresos);
        } else {
            printf("\nEl paciente con DNI %d no tiene ingresos registrados.\n", dniBuscado);
        }
    } else {
        printf("\nPaciente con DNI %d no encontrado.\n", dniBuscado);
    }
}
