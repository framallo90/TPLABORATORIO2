#ifndef FUNCARCHIVOS_H_INCLUDED
#define FUNCARCHIVOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ARBOLES.h"

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

typedef struct empleados_laboratorio {///USUARIOS QUE VAN A LOGUEAR
    int DNI;
    char NyA[40];
    char Usuario[20];
    char constrasena[20];
    char perfil[20];
} empleados_laboratorio;

typedef struct ingresos{///DATO PARA LISTA DE INGRESOS
     int NroDeIngreso;
    char FechaDeIngreso[10];
    char FechaDeRetiro[10];
    int DniPaciente;
    int MatriculaDelProfesionalSolicitante;
    int Eliminado;
}ingresos;

typedef struct nodoIngresos {///PRIMERA LISTA DE INGRESOS QUE SE DESPRENDE DEL ARBOL DE PACIENTES
    ingresos dato;
    struct pracXingreso *listaPracticasXingreso; // Puntero a la lista de prácticas asociadas a este ingreso
    struct ingresos *siguiente; // Puntero al siguiente ingreso en la lista de ingresos
} nodoIngresos;

typedef struct practicas {
    int NroDePractica;
    char NombreDePractica[30];
    int Eliminado;
} practicas;

typedef struct pracXingreso {///DATO PARA PRACTICA POR INGRESO
    int NroDeIngreso;
    int NroDePractica;
    char Resultado[40];
}pracXingreso;

typedef struct nodoPracXingreso {///SEGUNDA LISTA DE PRACTICAS POR INGRESO QUE SE DESPRENDE DE LA LISTA DE INGRESOS
    pracXingreso dato;
    struct pracXingreso *siguiente;
} nodoPracXingreso;

/// FUNCIONES PARA ARCHIVO EMPLEADOS
empleados_laboratorio ingresoEmpleado();
bool empleadoExiste(int dni);
void altaEmpleado();
void mostrarEmpleadosEnArchivo();
void borrarEmpleadoPorDNI();
void modificarEmpleadoPorDNI();

/// FUNCIONES PARA ARCHIVO PACIENTES
paciente IngresoPaciente();
bool pacienteExiste(int dni);
void altaPaciente();
void mostrarPacientes();
void modificarPacientePorDNI();
///FALTA BAJA PACIENTE


///FUNCIONES PARA ARCHIVO DE PRACTICAS
practicas ingresoPracticas();
void altaDePracticas();
void mostrarPracticas();
void modificarPracticaPorNumero();

///FUNCIONES PARA ARCHIVO DE PRACTICAS X INGRESO
pracXingreso nuevaPracticaXingreso();

///FUNCIONES PARA ARCHIVO DE INGRESOS
ingresos nuevoIngreso();

#endif // FUNCARCHIVOS_H_INCLUDED
