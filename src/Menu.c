#include "Menu.h"
#include "Libro.h"
#include "Cliente.h"
#include "Inventario.h"
#include <stdio.h>
#include <stdlib.h>

int menuInicial() {
    int opcion;

    while (1) {
        printf("\n------------------------------\n");
        printf("      SISTEMA LIBRERIA\n");
        printf("------------------------------\n");
        printf("1. Opciones Generales\n");
        printf("2. Opciones Administrativas\n");
        printf("3. Salir\n");
        printf("Seleccione una Opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1: // Opciones Generales
                menuGeneral();
                break;
            case 2: // Opciones Administrativas
                menuAdministrativo();
                break;
            case 3: // Salir
                printf("Saliendo...\n");
                return 0;
            default:
                printf("Opción inválida.\n");
        }
    }
}

int menuGeneral() {
    int opcion;
    printf("\n------------------------------\n");
    printf("     OPCIONES GENERALES\n");
    printf("------------------------------\n");
    printf("1. Consulta de Catalogo\n");
    printf("2. Consulta de Cliente\n");
    printf("3. Volver al Menu Principal\n");
    printf("Seleccione una Opcion: ");
    scanf("%d", &opcion);
    getchar();

    switch (opcion) {
        case 1: // Consulta Catalogo
            consultarCatalogo();
            return 0;
            //break;
        case 2: // Consulta de Cliente
            printf("Pronta implementacion");
            return 0;
            //break;
        case 3: // Salir
            menuInicial();
            return 0;
        default:
            printf("Opción inválida.\n");
            return 0;
    }
}

int menuAdministrativo() {
    int opcion;

    while (1) {
        printf("\n------------------------------\n");
        printf("   OPCIONES ADMINISTRATIVAS\n");
        printf("------------------------------\n");
        printf("1. Registrar cliente\n"); 
        printf("2. Eliminar cliente\n");
        printf("3. Gestion de inventario\n");
        printf("4. Gestion de pedidos\n");
        printf("5. Estadisticas\n");
        printf("6. Volver al Menu Principal\n");
        printf("Seleccione una Opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                registrarCliente();
                system("pause");
                break;
            case 2: {
                char* cedula = solicitarCedula();
                eliminarCliente(cedula);
                free(cedula);
                system("pause");
                break;
            }
            case 3:
                menuInventario();
                break;
            case 4:
                menuPedidos();
                break;
            case 5:
                printf("En desarrollo");
                break;
            case 6:
                return 0;
            default:
                printf("Opción inválida.\n");
        }
    }
}

int menuInventario() {
    int opcion;

    while(1) {
        printf("\n------------------------------\n");
        printf("   GESTION DE INVENTARIO\n");
        printf("------------------------------\n");
        printf("1. Registrar libro\n"); 
        printf("2. Eliminar libro\n");
        printf("3. Carga de Inventario\n");
        printf("4. Volver al Menu Administrativo\n");
        printf("Seleccione una Opcion: ");
        scanf("%d", &opcion);
        getchar();
        
        switch (opcion) {
            case 1:
                registrarLibro();
                system("pause");
                break;
            case 2: {
                char* codigo = solicitarCodigo();
                eliminarCliente(codigo);
                free(codigo);
                system("pause");
                break;
            }
            case 3:
                iniciarActualizacionDeStock();
                //actualizarCargaInventario();
                system("pause");
                printf("En desarrollo");
                break;
            case 4:
                return 0;
            default:
                printf("Opción inválida.\n");
        }
    }
}

int menuPedidos() {
    int opcion;

    while(1) {
        printf("\n------------------------------\n");
        printf("   GESTION DE PEDIDOS\n");
        printf("------------------------------\n");
        printf("1. Crear pedido\n"); 
        printf("2. Eliminar pedido\n");
        printf("3. Modificar pedido\n");
        printf("4. Consulta de pedidos\n");
        printf("5. Volver al Menu Administrativo\n");
        printf("Seleccione una Opcion: ");
        scanf("%d", &opcion);
        getchar();
        
        switch (opcion) {
            case 1:
                printf("En desarrollo");
                break;
            case 2:
                printf("En desarrollo");
                break;
            case 3:
                printf("En desarrollo");
                break;
            case 4:
                printf("En desarrollo");
                break;
            case 5:
                return 0;
            default:
                printf("Opción inválida.\n");
        }
    }
}