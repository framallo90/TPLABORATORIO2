#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ARBOLES.h"
#include "FuncArchivos.h"

#define TECLA_ENTER 13
#define TECLA_BACKSPACE 8
#define LONGITUD 20
#define MAX_INTENTOS 3
/// TERMINAR USUARIOS DE EMPLEADOS, HACER MENU, REPENSAR LOG IN.



int main() {


    /*** altaEmpleado();
    mostrarEmpleadosEnArchivo();
    borrarEmpleadoPorDNI();
    modificarEmpleadoPorDNI();***/
    mostrarEmpleadosEnArchivo();
    login();

   /***
    altaPaciente();
    mostrarPacientes();
     /***modificarPacientePorDNI();***/


     /***altaDePracticas();
    mostrarPracticas();
    nodoPaciente* arbol = cargarPacientesDesdeArchivo();
    inorder(arbol);***/



    return 0;
}


int login(){///HACER QUE DEVUELVA 1 2 o 3 SEGUN ADMINISTRADOR TEC DE LAB O ADMINISTRATIVO.
   	char usuario[LONGITUD + 1];
	char clave[LONGITUD + 1];
	int intento = 0;
	int ingresa = 0;
	char caracter;
	int i = 0;
    int j = 0;


	do {
		i = 0;
		system("cls");
		printf("\n\t\t\tINICIO DE SESION\n");
		printf("\t\t\t---------------\n");
		printf("\n\tUSUARIO: ");
		gets(usuario);
		printf("\tCLAVE: ");
		while (caracter = getch()) {
			if (caracter == TECLA_ENTER) {
                clave[i] = '\0';
				break;

			} else if (caracter == TECLA_BACKSPACE) {
				if (i > 0) {
					i--;
					printf("\b \b");
				}

			} else {
				if (i < LONGITUD) {
					printf("*");
					clave[i] = caracter;
					i++;
				}
			}
		}

        /* El usuario y clave debe coincidir con alguno de los que se encuentran en el array */
        FILE*archi = fopen("empleados.bin","rb");
        empleados_laboratorio logueo;
        if(archi != NULL){
            while(fread(&logueo,sizeof(empleados_laboratorio),1,archi)>0){
                if (strcmp(usuario, logueo.Usuario) == 0 && strcmp(clave, logueo.constrasena) == 0) {
                ingresa = 1;
                break;
            }
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

	return ingresa;
}

