#include "../headers/Menu.h"
#include "../headers/Libro.h"
#include "../headers/Cliente.h"
#include "../headers/Pedido.h"
<<<<<<< HEAD
#include "../headers/Inventario.h"
=======
#include "../headers/Estadisticas.h"
>>>>>>> 4c1aebc6957dca4159b71c56e191eeb8e96963ef
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
                printf("Opcion invalida.\n");
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
            break;
        case 2: // Consulta de Cliente
            consultarClientePorCedula();
            break;
        case 3: // Salir
            menuInicial();
            //break;
            return 0;
        default:
            printf("Opcion invalida.\n");
    }
    return 0;
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
                menuEstadisticas();
                break;
            case 6:
                return 0;
            default:
                printf("Opcion invalida.\n");
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
                system("pause");
                printf("En desarrollo");
                break;
            case 4:
                return 0;
            default:
                printf("Opcion invalida.\n");
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
                gestionarPedido();
                break;
            case 2: {
                printf("Ingrese el numero de pedido a eliminar: ");
                int numeroPedido;
                scanf("%d", &numeroPedido);
                getchar(); // Limpiar buffer
                eliminarPedido(numeroPedido);
                system("pause");
                break;
            }
            case 3:
                iniciarActualizacionDeStock();
                system("pause");
                printf("En desarrollo");
                //return 0;
                break;
            case 4:
                consultarPedidos();
                system("pause");
                break;
            case 5:
                return 0;
            default:
                printf("Opcion invalida.\n");
        }
    }
<<<<<<< HEAD
    return 0;
=======
}

int menuEstadisticas() {
    int opcion;

    while(1) {
        printf("\n------------------------------\n");
        printf("   MENU DE ESTADISTICAS\n");
        printf("------------------------------\n");
        printf("1. Total de ventas realizadas\n"); 
        printf("2. Clientes con mas pedidos\n");
        printf("3. Libros mas vendidos\n");
        printf("4. Volver al menu administrativo\n");
        printf("Seleccione una Opcion: ");
        scanf("%d", &opcion);
        getchar();
        
        switch (opcion) {
            case 1:
                calcularTotalVentas();
                break;
            case 2:
                clientesConMasPedidos();
                break;
            case 3:
                librosMasVendidos();
                break;
            case 4:
                return 0;
            default:
                printf("Opcion invalida");
        }     
    }
>>>>>>> 4c1aebc6957dca4159b71c56e191eeb8e96963ef
}