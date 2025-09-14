#include "Menu.h"//../headers/Menu.h"//Menu.h
#include "Libro.h//"//../headers/Libro.h"
#include "Cliente.h"//"../headers/Cliente.h"
#include "Inventario.h"//"../headers/Inventario.h"
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
            printf("Pronta implementacion");
            break;
        case 2: // Consulta de Cliente
            printf("Pronta implementacion");
            break;
        case 3: // Salir
            menuInicial();
            return 0;
        default:
            printf("Opción inválida.\n");
    }
}

int menuAdministrativo() {
    int opcion;

    while (1) {
        printf("\n------------------------------\n");
        printf("   OPCIONES ADMINISTRATIVAS\n");
        printf("------------------------------\n");
        printf("1. Registrar libro\n"); 
        printf("2. Registrar cliente\n");
        printf("3. Gestion de inventario\n");
        printf("4. Crear pedido\n");
        printf("5. Estadisticas\n");
        printf("6. Volver al Menu Principal\n");
        printf("Seleccione una Opcion: ");
        scanf("%d", &opcion);
        getchar();

        switch (opcion) {
            case 1:
                registrarLibro();
                system("pause");
                break;
            case 2:
                registrarCliente();
                system("pause");
                break;
            case 3:
                printf("Pronta implementacion");
                Inventario inve = CrearInventario();
                leerTxt(&inve);
                system("pause");
                //LiberarMemoriaInventario(inve);
                break;
            case 4:
                printf("En desarrollo");
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
