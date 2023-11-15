#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ARBOLES.h"
#include "FuncArchivos.h"


/// FUNCIONES PARA ARCHIVO EMPLEADOS
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

void altaEmpleado() {/// PIDE DNI, COMPRUEBA QUE NO EXISTA Y COMIENZA EL ALTA. UTILIZA INGRESO EMPLEADO Y EMPLEADO EXISTE //REVISAR GUARDADO
    int dni;
    printf("\nINGRESE EL DNI DEL EMPLEADO: ");
    scanf("%d", &dni);

    if (empleadoExiste(dni)) {
        printf("\nEL EMPLEADO YA EXISTE EN EL ARCHIVO.");
        return;
    }else{
        printf("\nNUEVA ALTA DE EMPLEADO: \n");
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

void mostrarEmpleadosEnArchivo() {/// MUESTRA EMPLEADOS CARGADOS EN EL ARCHIVO EMPLEADOS.BIN
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
        printf("\nNOMBRE Y APELLIDO: %s", empleado.NyA);
        printf("\nDNI: %d", empleado.DNI);
        printf("\nUSUARIO: %s", empleado.Usuario);
        printf("\nPERFIL: %s", empleado.perfil);
        printf("\nCONTASENA: %s", empleado.constrasena);
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
        printf("EMPLEADO CON DNI %d ELIMINADO EXITOSAMENTE.\n", dni);
    } else {
        remove("temp.bin"); // Si no se encontró al empleado, eliminamos el archivo temporal
        printf("EL EMPLEADO CON DNI %d, NO EXISTE EN EL ARCHIVO.\n", dni);
    }
}

void modificarEmpleadoPorDNI() {///PIDE DNI, BUSCA EN EL ARCHIVO EMPLEADOS.BIN Y MODIFICA LOS DATOS DEL EMPLEADO ENCONTRADO //REVISAR WHILE
    int dni;
    char comprobacion[20]; // Comprobación para la contraseña
    int contra = 1; // Contraseña
    int perf = 1; // Perfil
    int rta = 0; // Respuesta, perfil
    printf("\nINGRESE EL DNI DEL EMPLEADO: ");
    scanf("%d", &dni);

    FILE *archi = fopen("empleados.bin", "rb+");//rb+ permite la modificacion de los registros existentes.
    if (archi == NULL) {
        printf("\nERROR AL ABRIR EL ARCHIVO DE EMPLEADOS.");
        return;
    }

    empleados_laboratorio empleado;
    int encontrado = 0; // flag

    while (fread(&empleado, sizeof(empleados_laboratorio), 1, archi) == 1) {
        if (empleado.DNI == dni) {
            encontrado = 1;
            printf("Empleado encontrado:\n");
            printf("Nombre y Apellido: %s\n", empleado.NyA);
            printf("DNI: %d\n", empleado.DNI);
            printf("Perfil: %s\n", empleado.perfil);
            printf("Nombre de usuario: %s\n", empleado.Usuario);
            printf("Contraseña: %s\n", empleado.constrasena);

            // Realizar modificaciones
            printf("\nINGRESE LA NUEVA INFORMACION");
            printf("\nNOMBRE Y APELLIDO: ");
            fflush(stdin);
            gets(empleado.NyA);

            while (perf == 1) {
                    printf("\nPERFIL: \n1) ADMIN \n2) ADMINISTRATIVO \n3) PROFESIONAL DE LABORATORIO \n INGRESE NRO DE PERFIL: ");
                    scanf(" %d", &rta);
                    switch (rta) {
                        case 1:
                            strcpy(empleado.perfil, "ADMIN");
                            perf = 0;
                            break;
                        case 2:
                            strcpy(empleado.perfil, "ADMINISTRATIVO");
                            perf = 0;
                            break;
                        case 3:
                            while (perf == 1) {
                                printf("\n1) BIOQUIMICO \n2) TECNICO \n INGRESE NRO DE PERFIL: ");
                                scanf(" %d", &rta);
                                switch (rta) {
                                    case 1:
                                        strcpy(empleado.perfil, "BIOQUIMICO");
                                        perf = 0;
                                        break;
                                    case 2:
                                        strcpy(empleado.perfil, "TECNICO");
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

            gets(empleado.perfil);
            printf("\nNOMBRE DE USUARIO: ");
            fflush(stdin);
            gets(empleado.Usuario);

            while (contra == 1) {
                    printf("\nINGRESE LA CONTRASEÑA: ");
                    fflush(stdin);
                    scanf(" %s", empleado.constrasena);
                    printf("\nVUELVA A INGRESAR LA CONTRASEÑA: ");
                    fflush(stdin);
                    scanf(" %s", comprobacion);
                    if (strcmp(comprobacion, empleado.constrasena) == 0) {
                        contra = 0;
                        printf("\nCONTRASEÑA ESTABLECIDA.");
                    } else {
                        printf("\nLAS CONTRASEÑAS NO COINCIDEN, VUELVA A INTENTARLO.");
                    }
                }

            rewind(archi);

            if (fwrite(&empleado, sizeof(empleados_laboratorio), 1, archi) != 1) {
                printf("\nERROR AL ESCRIBIR EN EL ARCHIVO.");
            } else {
                printf("\nEMPLEADO MODIFICADO CON EXITO.");
            }
        }
    }

    fclose(archi);

    if (!encontrado) {
        printf("EMPLEADO DNI %d NO ENCONTRADO.\n", dni);
    }
}


/// FUNCIONES PARA ARCHIVO PACIENTES
paciente IngresoPaciente() {///INGRESA DATOS DE PACIENTES E INICIALIZA LOS PUNTEROS EN NULL.
    paciente nuevo;
    printf("\nAPELLIDO Y NOMBRE DEL PACIENTE: ");
    fflush(stdin);
    gets(&nuevo.NyA);
    printf("\nEDAD DEL PACIENTE: ");
    scanf(" %d", &nuevo.Edad);
    printf("\nDNI DEL PACIENTE: ");
    scanf(" %d", &nuevo.DNI);
    printf("\nDIRECCION DEL PACIENTE: ");
    fflush(stdin);
    gets(&nuevo.Direccion);
    printf("\nTELEFONO DEL PACIENTE: ");
    fflush(stdin);
    gets(&nuevo.telefono);
    nuevo.Eliminado = 0; // Por defecto, el paciente no esta dado de baja

    return nuevo;
}

bool pacienteExiste(int dni) {/// TRUE OR FALSE, SI EL PACIENTE EXISTE O NO EN EL ARCHIVO PACIENTES.BIN, SE USA EN ALTA PACIENTE.
    FILE *archi = fopen("pacientes.bin", "rb");
    if (archi == NULL) {
        return false; // Si no se puede abrir el archivo, asumimos que el paciente no existe
    }

    paciente paciente;
    while (fread(&paciente, sizeof(paciente), 1, archi) == 1) {
        if (paciente.DNI == dni) {
            fclose(archi);
            return true; // El paciente ya existe en el archivo
        }
    }

    fclose(archi);
    return false; // El paciente no existe en el archivo
}

void altaPaciente() {/// PIDE DNI, COMPRUEBA QUE NO EXISTA Y COMIENZA EL ALTA. UTILIZA INGRESO PACIENTE Y PACIENTE EXISTE
    paciente nuevo;
    int dni;

    printf("\nDNI DEL PACIENTE: ");
    scanf("%d", &dni);

    if (pacienteExiste(dni)) {//quiere decir si paciente dni es "TRUE"...
        printf("\nEL PACIENTE CON DNI %d YA EXISTE EN EL ARCHIVO.", dni);
        return;
    }

    // en cambio si devuelve "FALSE", saltea el if.
    nuevo = IngresoPaciente();

    FILE *archi = fopen("pacientes.bin", "ab");
    if (archi == NULL) {
        printf("\nERROR AL ABRIR EL ARCHIVO.");
        return;
    }

    if (fwrite(&nuevo, sizeof(paciente), 1, archi) != 1) {
        printf("\nERROR AL ESCRIBIR EN EL ARCHIVO.");
    } else {
        printf("\nPACIENTE AGREGADO CON EXITO.");
    }

    fclose(archi);
}

void muestroUnPaciente(paciente paciente){

        printf("\nNOMBRE Y APELLIDO: %s", paciente.NyA);
        printf("\nEDAD: %d", paciente.Edad);
        printf("\nDNI: %d", paciente.DNI);
        printf("\nDIRECCION: %s", paciente.Direccion);
        printf("\nTELEFONOS: %s", paciente.telefono);
        if(paciente.Eliminado == 0 ){
            printf("\nEL PACIENTE ESTA DADO DE ALTA.");
        }else{
            printf("\nEL PACIENTE ESTA DADO DE BAJA.");
        }
}

void mostrarPacientes() {///MUESTRA PACIENTES POR DNI EN EL ARCHIVO DE PACIENTES.BIN
    FILE *archi = fopen("pacientes.bin", "rb");
    if (archi == NULL) {
        printf("\nERROR AL ABRIR EL ARCHIVO DE PACIENTES");
        return;
    }

    paciente paciente;
    int contador = 0;

    while (fread(&paciente, sizeof(paciente), 1, archi) == 1) {
        contador++;
        printf("\nPACIENTE #%d)", contador);
        muestroUnPaciente(paciente);
        printf("\n");
    }

    if (contador == 0) {
        printf("NO HAY PACIENTES REGISTRADOS EN EL ARCHIVO.\n");
    }

    fclose(archi);
}

void modificarPacientePorDNI() {///PIDE DNI, BUSCA EN EL ARCHIVO DE PACIENTES.BIN Y MODIFICA LOS DATOS DEL PACIENTE ENCONTRADO
    int dni;
    printf("\nINGRESE EL DNI DEL PACIENTE A MODIFICAR: ");
    scanf("%d", &dni);

    FILE *archi = fopen("pacientes.bin", "rb+");
    if (archi == NULL) {
        printf("\nERROR AL ABRIR EL ARCHIVO DE PACIENTES.");
        return;
    }

    paciente nuevo;
    int encontrado = 0; // Flag

    while (fread(&nuevo, sizeof(paciente), 1, archi) == 1) {
        if (nuevo.DNI == dni) {
            encontrado = 1;
            printf("\nPACIENTE ENCONTRADO:\n");
            muestroUnPaciente(nuevo);

            // Realizar modificaciones
            printf("\nINGRESE LA NUEVA INFORMACION:\n");
            printf("\nNUEVO NOMBRE Y APELLIDO: ");
            fflush(stdin);
            gets(nuevo.NyA);
            printf("\nNUEVO DNI: ");
            scanf("%d", &nuevo.DNI);
            printf("\nNUEVA EDAD: ");
            scanf("%d", &nuevo.Edad);
            printf("\nNUEVO TELEFONO: ");
            fflush(stdin);
            gets(nuevo.telefono);
            printf("\nNUEVA DIRECCION: ");
            fflush(stdin);
            gets(nuevo.Direccion);

            fseek(archi, -sizeof(paciente), SEEK_CUR); // Retrocede al inicio del registro como el rewind(archi)
            fwrite(&nuevo, sizeof(paciente), 1, archi); // Sobrescribe el registro modificado
            printf("\nPACIENTE MODIFICADO CON EXITO.\n");
            break; /// Sal del bucle una vez que se haya modificado el paciente... PREGUNTARLE A ADRIAN SI PUEDO USARLO
        }
    }

    fclose(archi);

    if (!encontrado) {
        printf("PACIENTE DNI %d NO ENCONTRADO.\n", dni);
    }
}

void bajaPaciente(){///PIDE DNI, BUSCA EN EL ARCHIVO DE PACIENTES.BIN Y MODIFICA LOS DATOS DEL PACIENTE ENCONTRADO
    int dni;
    printf("\nINGRESE EL DNI DEL PACIENTE A MODIFICAR: ");
    scanf("%d", &dni);

    FILE *archi = fopen("pacientes.bin", "rb+");
    if (archi == NULL) {
        printf("\nERROR AL ABRIR EL ARCHIVO DE PACIENTES.");
        return;
    }

    paciente nuevo;
    int encontrado = 0; // Flag

    while (fread(&nuevo, sizeof(paciente), 1, archi) == 1) {
        if (nuevo.DNI == dni) {
            encontrado = 1;
            printf("\nPACIENTE ENCONTRADO:\n");
            muestroUnPaciente(nuevo);
            int ver = verIngresosAsoc(dni);
            if(ver == 1){
                printf("\nEL PACIENTE TIENE INGRESOS ASOCIADOS NO PUEDE DARSE DE BAJA.");
                }

            printf("\nDANDO DE BAJA....");
            nuevo.Eliminado = 1;

            fseek(archi, -sizeof(paciente), SEEK_CUR); // Retrocede al inicio del registro como el rewind(archi)
            fwrite(&nuevo, sizeof(paciente), 1, archi); // Sobrescribe el registro modificado
            printf("\nPACIENTE DADO DE BAJA CON EXITO.\n");
            break;
        }
    }

    fclose(archi);

    if (!encontrado) {
        printf("PACIENTE DNI %d NO ENCONTRADO.\n", dni);
    }
}

int verIngresosAsoc(int dni){
    int flag= 0;
    ingresos nuevo;
    FILE* archi = fopen("ingresos.bin","rb");
    if(archi != NULL){
        while(fread(&nuevo, sizeof(ingresos),1,archi)>0){
            if(dni == nuevo.DniPaciente){
                if(nuevo.Eliminado == 0){
                    flag = 1;
                }
            }
        }
    }
    fclose(archi);
    return flag;
}


///FUNCIONES PARA ARCHIVO DE PRACTICAS
practicas ingresoPracticas() {///INGRESA LAS PRACTICAS, ELIMINADO (PARA DAR DE BAJA) ES 0 POR DEFECTO
    practicas practica;

    printf("\nNOMBRE D.E PRACTICA: ");
    fflush(stdin);
    gets(practica.NombreDePractica);
    printf("\nNro DE PRACTICA: ");
    scanf(" %d", &practica.NroDePractica);
    practica.Eliminado = 0;

    return practica;
}

void altaDePracticas() {///ALTA DE PRACTICAS, USA INGRESO PRACTICAS, ********FALTA COMPROBACION POR NUMERO********
    FILE *archi = fopen("practicas.bin", "ab");
    if (archi == NULL) {
        printf("\nERROR AL ABRIR EL ARCHIVO DE PRACTICAS.");
        return;
    }

    int numPracticas;
    printf("\nINGRESE LA CANTIDAD DE PRACTICAS QUE DESEA INGRESAR: ");
    scanf(" %d", &numPracticas);

    for (int i = 0; i < numPracticas; i++) {
        practicas practica = ingresoPracticas();

        if (fwrite(&practica, sizeof(practicas), 1, archi) != 1) {
            printf("\nERROR AL ESCRIBIR LA PRACTICA EN EL ARCHIVO.");
        }
    }

    fclose(archi);
    printf("\nSE GUARDARON %d PRACTICAS ",numPracticas);
}

void mostrarPracticas() {
    FILE *archi = fopen("practicas.bin", "rb");
    if (archi == NULL) {
        printf("\n ERROR AL ABRIR EL ARCHIVO DE PRACTICAS.\n");
        return;
    }else{

        practicas practica;
        int contador = 0;

        printf("\nPRACTICAS REGISTRADAS:\n");

        while (fread(&practica, sizeof(practicas), 1, archi) == 1) {

            printf("\nNro DE PRACTICA: %d", practica.NroDePractica);
            printf("\n   NOMBRE DE PRACTICA: %s", practica.NombreDePractica);
            if(practica.Eliminado == 0){
                printf("\nLA PRACTICA ESTA ACTIVA.");
            }else{
                printf("\nESTA PRACTICA NO SE ENCUENTRA ACTIVA.");
            }
        }

    }
    fclose(archi);
}

void modificarPracticaPorNumero() {///PIDE NUMERO DE PRACT. SI LO ENCUENTRA DEJA MODIFICAR EL NOMBRE.
    int numero;
    printf("\nINGRESE EL NUMERO DE LA PRACTICA QUE DESEA ELIMINAR: ");
    scanf(" %d", &numero);
    FILE *archi = fopen("practicas.bin", "rb+");
    if (archi == NULL) {
        printf("\n ERROR AL ABRIR EL ARCHIVO DE PRACTICAS.\n");
        return;
    }

    practicas practica;
    int encontrado = 0;

    while (fread(&practica, sizeof(practicas), 1, archi) == 1) {
        if (practica.NroDePractica == numero) {
            encontrado = 1;
            printf("\nPRACTICA ENCONTRADA:\n");
            printf("Nro DE PRACTICA: %d\n", practica.NroDePractica);
            printf("NOMBRE DE PRACTICA: %s\n", practica.NombreDePractica);

            // Realizar la modificación
            printf("\nINGRESE EL NUEVO NOMBRE PARA LA PRACTICA: ");
            fflush(stdin);
            gets(practica.NombreDePractica);

            // Regresar al inicio del registro para sobrescribirlo
            rewind(archi);
            fwrite(&practica, sizeof(practicas), 1, archi);
            printf("\nPRACTICA MODIFICADA CON EXITO.\n");
            break;
        }
    }

    fclose(archi);

    if (!encontrado) {
        printf("\n PRACTICA CON Nro %d, NO ENCONTRADA.", numero);
    }
}
//FALTA DAR DE BAJA


///FUNCIONES PARA ARCHIVO DE PRACTICAS X INGRESO
pracXingreso nuevaPracticaXingreso(){
    pracXingreso nueva;
    printf("\nNRO DE INGRESO: ");
    scanf(" %d",&nueva.NroDeIngreso);
    printf("\nNRO DE PRACTICA: ");
    scanf(" %d",&nueva.NroDePractica);
    printf("\nRESULTADO:\n");
    scanf("    %s",&nueva.Resultado);

    return nueva;
}

bool practicaExiste(int nroPractica) {/// TRUE OR FALSE, SI EL NRO DE PRACTICA EXISTE O NO EN EL ARCHIVO PRACTICAS.BIN, SE USA EN ALTA PRACTICA
    FILE *archi = fopen("practicas.bin", "rb");
    if (archi == NULL) {
        return false; // Si no se puede abrir el archivo, asumimos que la practica no existe
    }

    practicas practica;
    while (fread(&practica, sizeof(practicas), 1, archi) == 1) {
        if (practica.NroDePractica == nroPractica) {
            fclose(archi);
            return true; // La practica ya existe en el archivo
        }
    }

    fclose(archi);
    return false; // La practica no existe en el archivo
}

bool ingresoExiste(int nroIngreso) {/// TRUE OR FALSE, SI EL NRO DE PRACTICA EXISTE O NO EN EL ARCHIVO PRACTICAS.BIN, SE USA EN ALTA PRACTICA
    FILE *archi = fopen("ingresos.bin", "rb");
    if (archi == NULL) {
        return false; // Si no se puede abrir el archivo, asumimos que el ingreso no existe
    }

    ingresos ingreso;
    while (fread(&ingreso, sizeof(ingresos), 1, archi) == 1) {
        if (ingreso.NroDeIngreso == nroIngreso) {
            fclose(archi);
            return true; // El ingreso existe en el archivo
        }
    }

    fclose(archi);
    return false; // El ingreso no existe en el archivo
}

void altaPracticasXingreso() {/// PIDE NRO INGRESO NRO PRACTICA, COMPRUEBA QUE EXISTAN Y COMIENZA EL ALTA. UTILIZA NUEVA PRACTICAXING Y VERIF PRACT E ING
    pracXingreso nuevo;
    int nroPractica;
    int nroIngreso;

    printf("\nINGRESE EL NUMERO DE PRACTICA: ");
    scanf("%d", &nroPractica);
    printf("\nINGRESE EL NUMERO DE INGRESO: ");
    scanf("%d", &nroIngreso);

       if (ingresoExiste(nroIngreso)!=true || practicaExiste(nroPractica)!=true) {
        printf("\nEL INGRESO %d O LA PRACTICA %d INGRESADAS NO EXISTEN.", nroIngreso,nroPractica);
        return;
    }

    // en cambio si devuelve "true", saltea el if.
    nuevo = nuevaPracticaXingreso();

    FILE *archi = fopen("pracXingresos.bin", "ab");
    if (archi == NULL) {
        printf("\nERROR AL ABRIR EL ARCHIVO.");
        return;
    }

    if (fwrite(&nuevo, sizeof(pracXingreso), 1, archi) != 1) {
        printf("\nERROR AL ESCRIBIR EN EL ARCHIVO.");
    } else {
        printf("\nPRACTICA POR INGRESO AGREGADA CON EXITO.");
    }

    fclose(archi);
}

void modificarPracXingreso() {///PIDE DNI, BUSCA EN EL ARCHIVO DE PACIENTES.BIN Y MODIFICA LOS DATOS DEL PACIENTE ENCONTRADO
    int nroIngreso;
    printf("\nINGRESE EL NRO. DE INGRESO ASOCIADO A LA PRACTICA QUE QUIERE MODIFICAR: ");
    scanf("%d", &nroIngreso);

    FILE *archi = fopen("pracXingresos.bin", "rb+");
    if (archi == NULL) {
        printf("\nERROR AL ABRIR EL ARCHIVO DE PRACT. POR INGRESOS.");
        return;
    }

    pracXingreso nuevo;
    int encontrado = 0; // Flag

    while (fread(&nuevo, sizeof(pracXingreso), 1, archi) == 1) {
        if (nuevo.NroDeIngreso == nroIngreso) {
            encontrado = 1;
            printf("\nPRACTICA POR INGRESO ENCONTRADA:\n");
            printf("\nNUMERO DE PRACTICA: %d", nuevo.NroDePractica);
            printf("\nRESULTADO: %s", nuevo.Resultado);

            // Realizar modificaciones
            printf("\nINGRESE LA NUEVA INFORMACION:\n");
            printf("\nNUMERO DE PRACTICA: ");
            scanf("%d", &nuevo.NroDePractica);
            printf("\nRESULTADO: ");
            scanf("%s", &nuevo.Resultado);

            fseek(archi, -sizeof(pracXingreso), SEEK_CUR); // Retrocede al inicio del registro como el rewind(archi)
            fwrite(&nuevo, sizeof(pracXingreso), 1, archi); // Sobrescribe el registro modificado
            printf("\nPRACTICA POR INGRESO MODIFICADA CON EXITO.\n");
            break;
        }
    }

    fclose(archi);

    if (!encontrado) {
        printf("INGRESO NRO %d NO ENCONTRADO.\n", nroIngreso);
    }
}

void mostrarPracticasXingreso() {
    FILE *archi = fopen("pracXingresos.bin", "rb");
    if (archi == NULL) {
        printf("\n ERROR AL ABRIR EL ARCHIVO DE PRACTICAS POR INGRESOS.\n");
        return;
    }else{

        pracXingreso practica;

        printf("\nPRACTICAS X INGRESOS REGISTRADAS:\n");

        while (fread(&practica, sizeof(pracXingreso), 1, archi) == 1) {

            printf("\n=====================================================");
            printf("\nNUMERO DE INGRESO: %d",practica.NroDeIngreso);
            printf("\nNUMERO DE PRACTICA: %d", practica.NroDePractica);
            printf("\nRESULTADO: %s", practica.Resultado);
        }

    }
    fclose(archi);
}


///FUNCIONES PARA ARCHIVO DE INGRESOS
ingresos nuevoIngreso(){
    ingresos nuevo;
    printf("\nNRO DE INGRESO: ");
    scanf(" %d",&nuevo.NroDeIngreso);
    printf("\nFECHA DE INGRESO d/m/aaaa : ");
    scanf(" %s",&nuevo.FechaDeIngreso);
    printf("\nFECHA DE RETIRO d/m/aaaa : ");
    scanf(" %s",&nuevo.FechaDeRetiro);
    printf("\nDNI PACIENTE: ");
    scanf(" %d",&nuevo.DniPaciente);
    printf("\nMATRICULA DEL PROFESIONAL SOLICITANTE: ");
    scanf(" %d",&nuevo.MatriculaDelProfesionalSolicitante);
    nuevo.Eliminado = 0;

    return nuevo;
}

void altaIngreso() {/// PIDE DNI, COMPRUEBA QUE EXISTA Y COMIENZA EL ALTA. UTILIZA NUEVO INGRESO Y PACIENTE EXISTE
    ingresos nuevo;
    int dni;

    printf("\nDNI DEL PACIENTE: ");
    scanf("%d", &dni);

    if (pacienteExiste(dni)!=true) {//quiere decir si paciente dni no es "TRUE"...
        printf("\nEL PACIENTE CON DNI %d NO SE ENCUENTRA EN EL ARCHIVO.", dni);
        return;
    }


    nuevo = nuevoIngreso();

    FILE *archi = fopen("ingresos.bin", "ab");
    if (archi == NULL) {
        printf("\nERROR AL ABRIR EL ARCHIVO.");
        return;
    }

    if (fwrite(&nuevo, sizeof(ingresos), 1, archi) != 1) {
        printf("\nERROR AL ESCRIBIR EN EL ARCHIVO.");
    } else {
        printf("\nPACIENTE AGREGADO CON EXITO.");
    }

    fclose(archi);
}

void modificarIngresoPorNro() {///PIDE DNI, BUSCA EN EL ARCHIVO DE PACIENTES.BIN Y MODIFICA LOS DATOS DEL PACIENTE ENCONTRADO
    int nroIngreso;
    printf("\nINGRESE EL INGRESO A MODIFICAR: ");
    scanf("%d", &nroIngreso);

    FILE *archi = fopen("ingresos.bin", "rb+");
    if (archi == NULL) {
        printf("\nERROR AL ABRIR EL ARCHIVO DE INGRESOS.");
        return;
    }

    ingresos nuevo;
    int encontrado = 0; // Flag

    while (fread(&nuevo, sizeof(ingresos), 1, archi) == 1) {
        if (nuevo.NroDeIngreso == nroIngreso) {
            encontrado = 1;
            printf("\nPACIENTE ENCONTRADO:\n");
            printf("\nFECHA DE INGRESO: %s", nuevo.FechaDeIngreso);
            printf("\nFECHA DE RETIRO: %s", nuevo.FechaDeRetiro);
            printf("\nMATRICULA DEL PROFESIONAL SOLICITANTE: %d", nuevo.MatriculaDelProfesionalSolicitante);
            printf("\nDNI DEL PACIENTE: %d", nuevo.DniPaciente);
            if(nuevo.Eliminado == 0){
                    printf("\n EL INGRESO SE ENCUENTRA ACTIVO.");
            }
            else{
                   printf("\n EL INGRESO ESTA DADO DE BAJA.");
            }


            // Realizar modificaciones
            printf("\nINGRESE LA NUEVA INFORMACION:\n");
            printf("\nFECHA DE INGRESO: ");
            fflush(stdin);
            scanf("%s", &nuevo.FechaDeIngreso);
            printf("\nFECHA DE RETIRO: ");
            fflush(stdin);
            scanf("%s", &nuevo.FechaDeRetiro);
            printf("\nMATRICULA DEL PROFESIONAL SOLICITANTE: ");
            scanf("%d", &nuevo.MatriculaDelProfesionalSolicitante);

            fseek(archi, -sizeof(ingresos), SEEK_CUR); // Retrocede al inicio del registro como el rewind(archi)
            fwrite(&nuevo, sizeof(ingresos), 1, archi); // Sobrescribe el registro modificado
            printf("\nPACIENTE MODIFICADO CON EXITO.\n");
            break;
        }
    }

    fclose(archi);

    if (!encontrado) {
        printf("INGRESO NRO %d NO ENCONTRADO.\n", nroIngreso);
    }
}

void mostrarIngresos() {
    FILE *archi = fopen("ingresos.bin", "rb");
    if (archi == NULL) {
        printf("\n ERROR AL ABRIR EL ARCHIVO DE INGRESOS.\n");
        return;
    }else{

        ingresos nuevo;
        int contador = 0;

        printf("\nPRACTICAS X INGRESOS REGISTRADAS:\n");

        while (fread(&nuevo, sizeof(ingresos), 1, archi) == 1) {

            printf("\n=====================================================");
            printf("\nNUMERO DE INGRESO: %d",nuevo.NroDeIngreso);
            printf("\nFECHA DE INGRESO: %s", nuevo.FechaDeIngreso);
            printf("\nFECHA DE RETIRO: %s", nuevo.FechaDeRetiro);
            printf("\nDNI DEL PACIENTE: %d",nuevo.DniPaciente);
            printf("\nMATRICULA DEL PROFESIONAL: %d",nuevo.MatriculaDelProfesionalSolicitante);
            if(nuevo.Eliminado == 0 ){
                printf("\nEL INGRESO SE ENCUENTRA ACTIVO.");
            }else{
                printf("\nEL INGRESO ESTA DADO DE BAJA.");
            }
        }

    }
    fclose(archi);
}
//FALTA BAJA DE INGRESO, DEBE DAR DE BAJA LAS PRACTICAS ASOCIADAS AL INGRESO

