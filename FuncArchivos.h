#ifndef FUNCARCHIVOS_H_INCLUDED
#define FUNCARCHIVOS_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ARBOLES.h"
#include "LISTAS.h"
#include "FuncArchivos.h"
#include "menues.h"

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
    struct nodoIngresos *listaIngresos; // Puntero a la lista de ingresos asociados a este paciente
    struct paciente *izq; // Puntero al hijo izquierdo en el �rbol (menor DNI)
    struct paciente *der; // Puntero al hijo derecho en el �rbol (mayor DNI)
}nodoPaciente;

typedef struct empleados_laboratorio {///USUARIOS QUE VAN A LOGUEAR
    int DNI;
    char NyA[40];
    char Usuario[20];
    char constrasena[20];
    char perfil[20];
} empleados_laboratorio;

typedef struct fecha { //ESTRUCTURA DE FECHA
    int dia;
    int mes;
    int anio;
} fecha;

typedef struct ingresos{///DATO PARA LISTA DE INGRESOS
    int NroDeIngreso;
    fecha FechaDeIngreso[10];
    fecha FechaDeRetiro[10];
    int DniPaciente;
    int MatriculaDelProfesionalSolicitante;
    int Eliminado;
}ingresos;

typedef struct nodoIngresos {///PRIMERA LISTA DE INGRESOS QUE SE DESPRENDE DEL ARBOL DE PACIENTES
    ingresos dato;
    struct pracXingreso *listaPracticasXingreso; // Puntero a la lista de pr�cticas asociadas a este ingreso
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

void altaOrden(int perfil);

/// FUNCIONES PARA ARCHIVO EMPLEADOS
empleados_laboratorio ingresoEmpleado();
bool empleadoExiste(int dni);
void altaEmpleado();
void mostrarEmpleadosEnArchivo();
void borrarEmpleadoPorDNI();
void modificarEmpleadoPorDNI();

/// FUNCIONES PARA ARCHIVO PACIENTES
paciente IngresoPaciente(int dni);
bool pacienteExiste(int dni);
void altaPaciente();
void muestroUnPaciente(paciente paciente);
void mostrarPacientes();
void modificarPacientePorDNI();
void bajaPaciente();
int verIngresosAsoc(int dni);

///FUNCIONES PARA ARCHIVO DE PRACTICAS
practicas ingresoPracticas();
void altaDePracticas();
void mostrarPracticas();
void modificarPracticaPorNumero();
void darPracticaDeBaja();
int verVincDePractica(int nroDePractica);

///FUNCIONES PARA ARCHIVO DE PRACTICAS X INGRESO
pracXingreso nuevaPracticaXingreso(int nroPractica, int nroIngreso,int perfil);
bool practicaExiste(int nroPractica);
bool ingresoExiste(int nroIngreso);
void altaPracticasXingreso(int perfil);
void modificarPracXingreso(int perfil);
void mostrarPracticasXingreso();

///FUNCIONES PARA ARCHIVO DE INGRESOS
ingresos nuevoIngreso(int dni);
void altaIngreso(int dni);
void modificarIngresoPorNro();
void mostrarIngresos();
void bajaDeIngreso();
int nuevoNumeroDeIngreso();
void buscarIngresoPorDni();
void muestroNumerosDeIngreso();
#endif // FUNCARCHIVOS_H_INCLUDED
