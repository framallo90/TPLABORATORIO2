#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ARBOLES.h"
#include "FuncArchivos.h"

#define TECLA_ENTER 13
#define TECLA_BACKSPACE 8
#define LONGITUD 10
#define MAX_INTENTOS 3
/// TERMINAR USUARIOS DE EMPLEADOS, HACER MENU, REPENSAR LOG IN.



int main() {
    int opcion;
    char repetir = 1;
    int perfil;

    do {
        system("cls");

        printf("\n\nHOSPITAL\n");
        printf("1. ABRIR MENU DE ADMINISTRADOR\n");
        printf("2. ABRIR MENU DE ADMINITRATIVO\n");
        printf("3. ABRIR MENU DE TECNICO DE LABORATORIO\n");
        printf("0. SALIR\n");

        printf("\nINGRESE UNA OPCION: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                perfil = login();
                if(perfil == 1){
                     printf("\n\tACA VA EL MENU DE ADMIN");
                }else{
                    printf("\n\tESTE PERFIL NO ES ADMIN.\n");
                }

                system("pause>nul"); // Pausa
                break;

            case 2:
                perfil = login();
                if(perfil == 2){
                     printf("\n\tACA VA EL MENU DE ADMINISTRATIVO");
                }else{
                    printf("\n\tESTE PERFIL NO ES ADMINISTRATIVO.\n");
                }

                system("pause>nul"); // Pausa
                break;

            case 3:
                perfil = login();
                if(perfil == 3){
                     printf("\n\tACA VA EL MENU DE TEC. DE LABORATORIO");
                }else{
                    printf("\n\tESTE PERFIL NO ES TECNICO DE LABORATORIO.\n");
                }
                system("pause>nul"); // Pausa
                break;

            case 0:
            	repetir = 0;
            	break;
        }
    } while (repetir);


    return 0;
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

