#ifndef MENUES_H_INCLUDED
#define MENUES_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ARBOLES.h"
#include "LISTAS.h"
#include "FuncArchivos.h"
#include "menues.h"

#define TECLA_ENTER 13
#define TECLA_BACKSPACE 8
#define LONGITUD 20
#define MAX_INTENTOS 3


void menu();
int login();
void menuArchivoEmpleados();
void menuArchivoIngresos();
void menuArchivoPacientes();
void menuArchivoPracticas();
void menuArchivoPractXingreso();
void menuAdministrador();
void menuAdministrativo();
void menuProfesionalLaboratorio();

#endif // MENUES_H_INCLUDED
