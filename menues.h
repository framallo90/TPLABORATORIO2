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
#define MAX_INTENTOS 99


void menu();
int login();
void menuArchivoEmpleados();
void menuArchivoIngresos(int perfil);
void menuArchivoPacientes();
void menuArchivoPracticas();
void menuArchivoPractXingreso(int perfil);
void menuAdministrador(int perfil);
void menuAdministrativo(int perfil);
void menuProfesionalLaboratorio(int perfil);

#endif // MENUES_H_INCLUDED
