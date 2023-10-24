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

    return 0;
}

empleados_laboratorio ingresoEmpleado(){

    empleados_laboratorio nuevo;
    char comprobacion[20];
    int contra = 1;

    printf("\nAPELLIDO Y NOMBRE: ");
    fflush(stdin);
    scanf(" %s",&nuevo.NyA);
    printf("\nDNI: ");
    scanf(" %d",&nuevo.DNI);
    printf("\nPERFIL: ");
    scanf(" %s",&nuevo.perfil);
    printf("\nNOMBRE DE USUARIO: ");
    scanf(" %s",&nuevo.Usuario);

    while(contra == 1){
        printf("\nINGRESE LA CONSTRASENA: ");
    scanf(" %s",&nuevo.constrasena);
    printf("\nVUELVA A INGRESAR LA CONTRASENA: ");
    scanf(" %s",&comprobacion);
        if(strcmp(comprobacion,nuevo.constrasena)==0){
            contra = 0;
            printf("\nCONTRASENA ESTABLECIDA.");
        }else{
            printf("\nLAS CONTRASENAS NO COINCIDEN, VUELVA A INTENTARLO.");
        }
    }

    return nuevo;
}

bool empleadoExiste(int dni) {
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

void altaEmpleado() {
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

void mostrarEmpleados() {
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
