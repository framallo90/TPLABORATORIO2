#include "LISTAS.h"


nodo *inicLista() {
   return NULL;
}

nodo *crearNodo(persona dato) {
    nodo *aux = (nodo*) malloc(sizeof(nodo));
    aux->dato = dato;
    aux->siguiente = NULL;
    return aux;
}

nodo *agregarPpio(nodo *lista, nodo *nuevoNodo) {
    if (lista == NULL) {
        lista = nuevoNodo;
    } else {
        nuevoNodo->siguiente = lista;
        lista = nuevoNodo;
    }
    return lista;
}

nodo *buscarUltimo(nodo *lista) {
    nodo *seg = lista;
    if (seg != NULL) {
        while (seg->siguiente != NULL) {
            seg = seg->siguiente;
        }
    }
    return seg;
}

nodo *buscarNodo(nodo *lista, char nombre[20]) {
    nodo *seg = lista;
    while (seg != NULL && strcmp(nombre, seg->dato.nombre) != 0) {
        seg = seg->siguiente;
    }
    return seg;
}

nodo *agregarFinal(nodo *lista, nodo *nuevoNodo) {
    if (lista == NULL) {
        lista = nuevoNodo;
    } else {
        nodo *ultimo = buscarUltimo(lista);
        ultimo->siguiente = nuevoNodo;
    }
    return lista;
}

nodo *agregarEnOrden(nodo *lista, nodo *nuevoNodo){
    if(lista == NULL){
        lista = nuevoNodo;
    }else{
        if(strcmp(nuevoNodo->dato.nombre,lista->dato.nombre)<0){
            lista = agregarPpio(lista, nuevoNodo);
        }else{
            nodo *ante = lista;
            nodo *seg = lista->siguiente;
            while((seg != NULL)&&(strcmp(nuevoNodo->dato.nombre,seg->dato.nombre)>0)){
                ante = seg;
                seg = seg->siguiente;
            }
            nuevoNodo->siguiente = seg;
            ante->siguiente = nuevoNodo;
        }
    }
    return lista;
}

nodo *borrarNodo(nodo *lista, char nombre[20]) {
    nodo *seg;
    nodo *ante = NULL;

    if (lista != NULL && strcmp(nombre, lista->dato.nombre) == 0) {
        nodo *aux = lista;
        lista = lista->siguiente;
        free(aux);
    } else {
        seg = lista;
        while (seg != NULL && strcmp(nombre, seg->dato.nombre) != 0) {
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

nodo *borrarTodaLaLista(nodo * lista){
    nodo *proximo;
    nodo *seg;
    seg = lista;
    while(seg != NULL)
    {
        proximo = seg->siguiente;
        free(seg);
        seg = proximo;
    }
    return seg;
}

void mostrarUnNodo(nodo *aux){
    if (aux != NULL){
        printf("\nNombre: %s", aux->dato.nombre);
        printf("\nEdad: %d", aux->dato.edad);
    }else{
        printf("\nNodo no válido.");
    }
}

void mostrarLista(nodo *lista){
    nodo * aux=lista;
    while(aux != NULL){
        mostrarUnNodo(aux);
        aux = aux->siguiente;
    }
}

persona creoPersona(){
    persona personaNueva;
    puts("\n-----------------------------");
    printf("\n Ingrese nombre: ");
    fflush(stdin);
    scanf("%s",&personaNueva.nombre);
    printf("\n Ingrese edad: ");
    scanf("%i",&personaNueva.edad);
    puts("\n-----------------------------");
    return personaNueva;
}

///CON ARCHIVOS
void cargarPersona(char archivo[]){
    persona personaNueva;
    char letra = 's';
    FILE *archi = fopen(archivo, "w");
    if(archi!=NULL){
       printf("\nDesea ingresar una persona?: (s/n) ");
       fflush(stdin);
       scanf("%c", &letra);
       while (letra == 's' || letra == 'S'){

                puts("\n-----------------------------");
                printf("\n Ingrese nombre: ");
                fflush(stdin);
                scanf("%s",&personaNueva.nombre);
                printf("\n Ingrese edad: ");
                scanf("%i",&personaNueva.edad);
                puts("\n-----------------------------");

                fwrite(&personaNueva, sizeof(personaNueva),1 , archi);

                printf("\n Desea ingresar otra persona? s/n: ");
                fflush(stdin);
                scanf("%c",&letra);
        }
        fclose(archi);
        BORRAR_PANTALLA;
    }
}

nodo *pasoAlista(char archivo[],nodo *lista){
    FILE *archi=fopen(archivo,"r");
    persona personaNueva;
    rewind(archi);
    if(archi != NULL){
        while(fread(&personaNueva, sizeof(personaNueva), 1, archi)>0){
                lista = agregarEnOrden(lista,crearNodo(personaNueva));
        }
        fclose(archi);
    }
    return lista;
}

void pasoAlistaREF(char archivo[],nodo **lista){
    FILE *archi=fopen(archivo,"r");
    persona personaNueva;
    rewind(archi);
    if(archi != NULL){
        while(fread(&personaNueva, sizeof(personaNueva), 1, archi)>0){
                *lista = agregarEnOrden(*lista,crearNodo(personaNueva));
        }
        fclose(archi);
    }
}

///borro nodo con recursividad
nodo *borroRecursivo(nodo *lista){
    nodo *prox;
    if(lista !=NULL){
        prox = lista->siguiente;
        free(lista);
        lista = borroRecursivo(prox);
    }
    return lista;
}

