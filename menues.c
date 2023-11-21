#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ARBOLES.h"
#include "LISTAS.h"
#include "FuncArchivos.h"
#include "menues.h"

void menu(){
    int opcion;
    int repetir = 1;
    int perfil;

    do {
        system("cls");

        printf("\n\n\t HOSPITAL \n");
        printf("\n\nDESEA INICIAR SESION COMO:\n");
        printf("1. ADMINISTRADOR\n");
        printf("2. ADMINISTRATIVO\n");
        printf("3. PROFESIONAL DE LABORATORIO\n");
        printf("0. SALIR\n");

        printf("\nINGRESE UNA OPCION: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                perfil = login();
                if (perfil == 1) {
                    menuAdministrador();
                } else {
                    printf("\n\tESTE PERFIL NO ES ADMIN.\n");
                }

                system("pause>nul"); // Pausa
                break;

            case 2:
                perfil = login();
                if (perfil == 2) {
                    menuAdministrativo();
                } else {
                    printf("\n\tESTE PERFIL NO ES ADMINISTRATIVO.\n");
                }

                system("pause>nul"); // Pausa
                break;

            case 3:
                perfil = login();
                if (perfil == 3) {
                    menuProfesionalLaboratorio();
                } else {
                    printf("\n\tESTE PERFIL NO ES TECNICO DE LABORATORIO.\n");
                }
                system("pause>nul"); // Pausa
                break;

            case 0:
                repetir = 0;
                break;
        }
    } while (repetir);
}

int login(){
   	char usuario[LONGITUD + 1];
	char clave[LONGITUD + 1];
	int intento = 0;
	int ingresa = 0;
	int perfil;
	char caracter;
	int i = 0;
    int j = 0;


	do {
        i = 0;
		system("cls");
		printf("\n\t\t\tINICIO DE SESION\n");
		printf("\t\t\t---------------\n");
		printf("\n\tUSUARIO: ");
		fflush(stdin);
		gets(usuario);
		printf("\tCLAVE: ");
		while (caracter = getch()) {
			if (caracter == TECLA_ENTER) {
				clave[i] = '\0';
				break;
            }else if (caracter == TECLA_BACKSPACE) {
				if (i > 0) {
					i--;
					printf("\b \b");
				}
			}else{
                if (i < LONGITUD) {
					printf("*");
					clave[i] = caracter;
					i++;
				}
			}
		}

        FILE*archi = fopen("empleados.bin","rb");
        empleados_laboratorio logueo;
        if(archi != NULL){
            while(fread(&logueo,sizeof(empleados_laboratorio),1,archi)>0){
                if (strcmp(usuario, logueo.Usuario) == 0 && strcmp(clave, logueo.constrasena) == 0) {
                ingresa = 1;
                break;
            }
        }
        if(strcmp(logueo.perfil,"ADMIN")==0){
            perfil = 1;
        }else if(strcmp(logueo.perfil,"ADMINISTRATIVO")==0){
            perfil = 2;
        }else{
            perfil = 3;
        }
        fclose(archi);

        }


        if (ingresa == 0) {
            printf("\n\tUsuario y/o clave son incorrectos\n");
            intento++;
            getchar();
        }


	} while (intento < MAX_INTENTOS && ingresa == 0);

	if (ingresa == 1) {
		printf("\n\n\tBienvenido al Sistema\n");

        /* Aquí va el código del programa cuando el usuario ingresa sus credenciales correctas */

	} else {
		printf("\n\n\tHa sobrepasado el numero maximo de intentos permitidos\n");
	}

	return perfil;
}

void menuArchivoEmpleados(){
    int opcion;
    int repetir = 1;

        do {
        system("cls");

        printf("\n\nMENU ARCHIVO EMPLEADOS\n");
        printf("1. ALTA EMPLEADO.\n");
        printf("2. BORRAR EMPLEADO.\n");
        printf("3. MODIFICAR EMPLEADO.\n");
        printf("4. MOSTRAR ARCHIVO.\n");
        printf("0. SALIR\n");

        printf("\nINGRESE UNA OPCION: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                altaEmpleado();
                printf("\nEMPLEADO DADO DE ALTA EXITOSAMENTE.\n");
                system("pause>nul"); // Pausa
                break;

            case 2:
                borrarEmpleadoPorDNI();
                printf("\nIngreso modificado exitosamente.\n");
                system("pause>nul"); // Pausa
                break;

            case 3:
                modificarEmpleadoPorDNI();
                printf("\nSe modifico el empleado de manera exitosamente.\n");
                system("pause>nul"); // Pausa
                break;

            case 4:
                mostrarEmpleadosEnArchivo();

                system("pause>nul"); // Pausa
                break;

            case 0:
            	repetir = 0;
            	break;
            }
        }while (repetir);
}

void menuArchivoIngresos(){
    int opcion;
    int repetir = 1;
        do {
        system("cls");

        printf("\n\nMENU ARCHIVO INGRESOS\n");
        printf("1. ALTA INGRESOS (SOLO INGRESO).\n");
        printf("2. MODIFICAR INGRESO.\n");
        printf("3. MOSTRAR ARCHIVO.\n");
        printf("4. DAR DE BAJA INGRESO. \n");
        printf("0. SALIR\n");

        printf("\nINGRESE UNA OPCION: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                altaIngreso();

                system("pause>nul"); // Pausa
                break;

            case 2:
                modificarIngresoPorNro();

                system("pause>nul"); // Pausa
                break;

            case 3:
                mostrarIngresos();

                system("pause>nul"); // Pausa
                break;

            case 4:
                bajaDeIngreso();

                system("pause>nul"); //Pausa
                break;
            case 0:
                repetir = 0;
                break;
            }
        }while (repetir);
}

void menuArchivoPacientes(){
    int opcion;
    int repetir = 1;
        do {
        system("cls");

        printf("\n\nMENU ARCHIVO PACIENTES\n");
        printf("1. ALTA PACIENTE.\n");
        printf("2. MODIFICAR PACIENTE POR DNI.\n");
        printf("3. MOSTRAR ARCHIVO.\n");
        printf("0. SALIR\n");

        printf("\nINGRESE UNA OPCION: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                altaPaciente();

                system("pause>nul"); // Pausa
                break;

            case 2:
                modificarPacientePorDNI();

                system("pause>nul"); // Pausa
                break;

            case 3:
                mostrarPacientes();

                system("pause>nul"); // Pausa
                break;

            case 0:
            	repetir = 0;
            	break;
            }
        }while (repetir);
}

void menuArchivoPracticas(){
    int opcion;
    int repetir = 1;
        do {
        system("cls");

        printf("\n\nMENU ARCHIVO PRACTICAS\n");
        printf("1. ALTA PRACTICAS.\n");
        printf("2. MODIFICAR PRACTICA.\n");
        printf("3. MOSTRAR ARCHIVO.\n");
        printf("0. SALIR\n");

        printf("\nINGRESE UNA OPCION: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                altaDePracticas();

                system("pause>nul"); // Pausa
                break;

            case 2:
                modificarPracticaPorNumero();

                system("pause>nul"); // Pausa
                break;

            case 3:
                mostrarPracticas();

                system("pause>nul"); // Pausa
                break;

            case 0:
            	repetir = 0;
            	break;
            }
        }while (repetir);

}

void menuArchivoPractXingreso(){
    int opcion;
    int repetir = 1;
        do {
        system("cls");

        printf("\n\nMENU ARCHIVO PRACTICAS POR INGRESO\n");
        printf("1. ALTA PRACTICAS POR INGRESO.\n");
        printf("2. MODIFICAR PRACTICA POR INGRESO.\n");
        printf("3. MOSTRAR ARCHIVO.\n");
        printf("0. SALIR\n");

        printf("\nINGRESE UNA OPCION: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:

                altaPracticasXingreso();

                system("pause>nul"); // Pausa
                break;

            case 2:
                modificarPracXingreso();

                system("pause>nul"); // Pausa
                break;

            case 3:
                mostrarPracticasXingreso();

                system("pause>nul"); // Pausa
                break;

            case 0:
            	repetir = 0;
            	break;
            }
        }while (repetir);
}

void menuAdministrador(){
    int opcion;
    int repetir = 1;
    nodoPaciente* arbol=cargarArbolConListas(arbol);

        do {
        system("cls");

        printf("\n\nMENU ADMINISTRADOR\n");
        printf("1. MENU ARCHIVO EMPLEADOS.\n");
        printf("2. MENU ARCHIVO PACIENTES.\n");
        printf("3. MENU ARCHIVO PRACTICAS.\n");
        printf("4. MENU ARCHIVO INGRESOS.\n");
        printf("5. MENU ARCHIVO PRACTICAS POR INGRESO.\n");
        printf("6. MOSTRAR ARBOL DE PACIENTES. \n");
        printf("7. MOSTRAR INGRESOS Y PRACTICAS DE LOS PACIENTES. \n");
        printf("8. ALTA ORDEN (INGRESO + PRACTICAS).\n");
        printf("0. SALIR\n");

        printf("\nINGRESE UNA OPCION: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                menuArchivoEmpleados();

                system("pause>nul"); // Pausa
                break;

            case 2:
                menuArchivoPacientes();

                system("pause>nul"); // Pausa
                break;

            case 3:
                menuArchivoPracticas();

                system("pause>nul"); // Pausa
                break;

            case 4:
                menuArchivoIngresos();
                system("pause>nul"); //Pausa
                break;
            case 5:
                menuArchivoPractXingreso();
                system("pause>nul"); //Pausa
                break;

            case 6:
                inorder(arbol);
                system("pause>nul"); //Pausa
                break;

            case 7:
                mostrarListaDeIngreso(arbol);
                system("pause>nul");
                break;
             case 8:
                altaOrden();
                system("pause>nul"); //Pausa
                break;

            case 0:
            	repetir = 0;
            	break;
            }
        }while (repetir);
}

void menuAdministrativo(){
    int opcion;
    int repetir = 1;
    nodoPaciente* arbol= cargarPacientesDesdeArchivo();

    do {
        system("cls");

        printf("\n\nMENU ADMINISTRATIVO\n");
        printf("1. ALTA INGRESO.\n");
        printf("2. MODIFICAR INGRESO.\n");
        printf("3. MOSTRAR INGRESOS.\n");
        printf("4. DAR DE BAJA INGRESO. \n");
        printf("5. MENU PACIENTES.\n");
        printf("6. MOSTRAR ARBOL DE PACIENTES. \n");
        printf("7. MOSTRAR LISTAS DE INGRESOS. \n");
        printf("0. SALIR\n");

        printf("\nINGRESE UNA OPCION: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                altaOrden();
                system("pause>nul"); // Pausa
                break;

            case 2:
                modificarIngresoPorNro();
                system("pause>nul"); // Pausa
                break;

            case 3:
                mostrarIngresos();
                system("pause>nul"); // Pausa
                break;

            case 4:
                bajaDeIngreso();

                system("pause>nul"); //Pausa
                break;

            case 5:
                menuArchivoPacientes();
                break;

            case 6:
                inorder(arbol);
                system("pause>nul");
                break;

            case 7:
                arbol = cargarListaDeIngresosDesdeArbol(arbol);
                mostrarListaDeIngreso(arbol);
                system("pause>nul");
                break;

            case 0:
                repetir = 0;
                break;
        }
    } while (repetir);
}

void menuProfesionalLaboratorio(){
    int opcion;
    int repetir = 1;
    nodoPaciente* arbol=cargarArbolConListas(arbol);

    do {
        system("cls");

        printf("\n\nMENU PROFESIONAL DE LABORATORIO\n");
        printf("1. ALTA PRACTICAS POR INGRESO.\n");
        printf("2. MODIFICAR PRACTICAS POR INGRESO.\n");
        printf("3. MOSTRAR PRACTICAS POR INGRESO.\n");
        printf("4. MOSTRAR ARBOL DE PACIENTES. \n");
        printf("5. MOSTRAR INGRESOS Y PRACTICAS DE LOS PACIENTES. \n");
        printf("0. SALIR\n");

        printf("\nINGRESE UNA OPCION: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                altaPracticasXingreso();
                printf("\nPráctica por ingreso dada de alta exitosamente.\n");
                system("pause>nul"); // Pausa
                break;

            case 2:
                modificarPracXingreso();
                printf("\nPráctica por ingreso modificada exitosamente.\n");
                system("pause>nul"); // Pausa
                break;

            case 3:
                mostrarPracticasXingreso();
                system("pause>nul"); // Pausa
                break;

            case 4:
                inorder(arbol);
                system("pause>nul");
                break;

            case 5:
                mostrarListaDeIngreso(arbol);
                system("pause>nul");
                break;

            case 0:
                repetir = 0;
                break;
        }
    } while (repetir);
}
