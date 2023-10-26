#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define clear system("cls")
#define pausa system("pause")

typedef struct empleados_laboratorio {
    int DNI;
    char NyA[40];
    char Usuario[20];
    char constrasena[20];
    char perfil[20];
} empleados_laboratorio;

typedef struct paciente {
    char NyA[40];
    int Edad;
    int DNI;
    char Direccion[30];
    char telefono[15];
    int Eliminado;
    struct ingresos *listaIngresos; // Puntero a la lista de ingresos asociados a este paciente
    struct paciente *izq; // Puntero al hijo izquierdo en el árbol (menor DNI)
    struct paciente *der; // Puntero al hijo derecho en el árbol (mayor DNI)
} paciente;

typedef struct ingresos {
    int NroDeIngreso;
    char FechaDeIngreso[10];
    char FechaDeRetiro[10];
    int DniPaciente;
    int MatriculaDelProfesionalSolicitante;
    int Eliminado;
    struct practicas *listaPracticas; // Puntero a la lista de prácticas asociadas a este ingreso
    struct ingresos *siguiente; // Puntero al siguiente ingreso en la lista de ingresos
} ingresos;

typedef struct practicas {
    int NroDePractica;
    char NombreDePractica[30];
    int Eliminado;
} practicas;

typedef struct pracXingreso {
    int NroDeIngreso;
    int NroDePractica;
    char Resultado[40];
    struct pracXingreso *siguiente; // Puntero al siguiente elemento en la lista de prácticas por ingreso
} pracXingreso;

int main() {

    altaEmpleado();
    mostrarEmpleados();
    borrarEmpleadoPorDNI();
    mostrarEmpleados();
    return 0;
}


/// ARCHIVO EMPLEADOS
empleados_laboratorio ingresoEmpleado() { /// INGRESO EMPLEADO POR CONSOLA
    empleados_laboratorio nuevo;
    char comprobacion[20]; // Comprobación para la contraseña
    int contra = 1; // Contraseña
    int perf = 1; // Perfil
    int rta = 0; // Respuesta, perfil

    printf("\nAPELLIDO Y NOMBRE: ");
    fflush(stdin);
    gets(nuevo.NyA);
    printf("\nDNI: ");
    scanf(" %d", &nuevo.DNI);

    while (perf == 1) {
        printf("\nPERFIL: \n1) ADMIN \n2) ADMINISTRATIVO \n3) PROFESIONAL DE LABORATORIO \n INGRESE NRO DE PERFIL: ");
        scanf(" %d", &rta);
        switch (rta) {
            case 1:
                strcpy(nuevo.perfil, "ADMIN");
                perf = 0;
                break;
            case 2:
                strcpy(nuevo.perfil, "ADMINISTRATIVO");
                perf = 0;
                break;
            case 3:
                while (perf == 1) {
                    printf("\n1) BIOQUIMICO \n2) TECNICO \n INGRESE NRO DE PERFIL: ");
                    scanf(" %d", &rta);
                    switch (rta) {
                        case 1:
                            strcpy(nuevo.perfil, "BIOQUIMICO");
                            perf = 0;
                            break;
                        case 2:
                            strcpy(nuevo.perfil, "TECNICO");
                            perf = 0;
                            break;
                        default:
                            printf("\nOPCIÓN DE PERFIL NO VÁLIDA, INTENTE DE NUEVO");
                    }
                }
                break;
            default:
                printf("\nEL PERFIL SELECCIONADO NO EXISTE, INTENTELO DE NUEVO;");
        }
    }

    printf("\nNOMBRE DE USUARIO: ");
    fflush(stdin);
    gets(nuevo.Usuario);

    while (contra == 1) {
        printf("\nINGRESE LA CONTRASEÑA: ");
        fflush(stdin);
        scanf(" %s", nuevo.constrasena);
        printf("\nVUELVA A INGRESAR LA CONTRASEÑA: ");
        fflush(stdin);
        scanf(" %s", comprobacion);
        if (strcmp(comprobacion, nuevo.constrasena) == 0) {
            contra = 0;
            printf("\nCONTRASEÑA ESTABLECIDA.");
        } else {
            printf("\nLAS CONTRASEÑAS NO COINCIDEN, VUELVA A INTENTARLO.");
        }
    }

    return nuevo;
}

bool empleadoExiste(int dni) {/// TRUE OR FALSE, SI EL EMPLEADO EXISTE O NO EN EL ARCHIVO EMPLEADOS.BIN, SE USA EN ALTA EMPLEADO
    FILE *archi = fopen("empleados.bin", "rb");
    if (archi == NULL) {
        return false; // Si no se puede abrir el archivo, asumimos que el empleado no existe
    }

    empleados_laboratorio empleado;
    while (fread(&empleado, sizeof(empleados_laboratorio), 1, archi) == 1) {
        if (empleado.DNI == dni) {
            fclose(archi);
            return true; // El empleado ya existe en el archivo
        }
    }

    fclose(archi);
    return false; // El empleado no existe en el archivo
}

void altaEmpleado() {/// PIDE DNI, COMPRUEBA QUE NO EXISTA Y COMIENZA EL ALTA. UTILIZA INGRESO EMPLEADO Y EMPLEADO EXISTE
    int dni;
    printf("\nINGRESE EL DNI DEL EMPLEADO: ");
    scanf("%d", &dni);

    if (empleadoExiste(dni)) {
        printf("\nEL EMPLEADO YA EXISTE EN EL ARCHIVO.");
        return;
    }else{
        printf("\nNUEVA ALTA DE EMPLEADO: ");
    }

    FILE *archi = fopen("empleados.bin", "ab");
    if (archi == NULL) {
        printf("\n ERROR AL ABRIR EL ARCHIVO.");
        return;
    }

    empleados_laboratorio nuevo = ingresoEmpleado();
    if (fwrite(&nuevo, sizeof(empleados_laboratorio), 1, archi) != 1) {
        printf("\n ERROR AL ESCRIBIR EN EL ARCHIVO.");
    } else {
        printf("\n EMPLEADO AGREGADO EXITOSAMENTE.\n");
    }

    fclose(archi);
}

void mostrarEmpleados() {/// MUESTRA EMPLEADOS CARGADOS EN EL ARCHIVO EMPLEADOS.BIN
    FILE *archi = fopen("empleados.bin", "rb");
    if (archi == NULL) {
        printf("\n ERROR AL ABRIR EL ARCHIVO.");
        return;
    }
    empleados_laboratorio empleado;
    int contador = 0;
    printf("\nEMPLEADOS: ");
    while (fread(&empleado, sizeof(empleados_laboratorio), 1, archi) == 1) {
        contador++;
        printf("\n%d)", contador);
        printf("NOMBRE Y APELLIDO: %s, ", empleado.NyA);
        printf("DNI: %d, ", empleado.DNI);
        printf("USUARIO: %s, ", empleado.Usuario);
        printf("PERFIL: %s\n", empleado.perfil);
        printf("\n");
    }
    if (contador == 0) {
        printf("NO HAY EMPLEADOS REGISTRADOS EN EL ARCHIVO.\n");
    }
    fclose(archi);
}

void borrarEmpleadoPorDNI() {///BORRA EMPLEADOS POR DNI EN EL ARCHIVOS EMPLEADOS.BIN
    int dni = 0;
    printf("\nINGRESE EL DNI DEL EMPLEADO A ELIMINAR: ");
    scanf(" %d",&dni);
    FILE *archi = fopen("empleados.bin", "rb");
    if (archi == NULL) {
        printf("ERROR AL ABRIR EL ARCHIVO DE EMPLEADOS.\n");
        return;
    }

    FILE *temp = fopen("temp.bin", "wb"); // Archivo temporal para escribir empleados válidos
    if (temp == NULL) {
        fclose(archi);
        printf("ERROR AL ABRIR EL ARCHIVO TEMPORAL.\n");
        return;
    }

    empleados_laboratorio empleado;
    int encontrado = 0;

    while (fread(&empleado, sizeof(empleados_laboratorio), 1, archi) == 1) {
        if (empleado.DNI == dni) {
            encontrado = 1;
            // No copiamos este empleado al archivo temporal (lo estamos eliminando)
        } else {
            // Copiamos los otros empleados al archivo temporal
            fwrite(&empleado, sizeof(empleados_laboratorio), 1, temp);
        }
    }

    fclose(archi);
    fclose(temp);

    if (encontrado) {
        // Reemplazamos el archivo original con el archivo temporal
        remove("empleados.bin");
        rename("temp.bin", "empleados.bin");
        printf("Empleado con DNI %d eliminado con éxito.\n", dni);
    } else {
        remove("temp.bin"); // Si no se encontró al empleado, eliminamos el archivo temporal
        printf("Empleado con DNI %d no encontrado.\n", dni);
    }
}
