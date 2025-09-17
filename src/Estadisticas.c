#include "../headers/Estadisticas.h"
#include "../headers/Cliente.h"
#include "../headers/Pedido.h"
#include "../headers/Libro.h"
#include <string.h>
#include <time.h>

void calcularTotalVentas() {
    FILE *archi = fopen(ARCHIVO_PEDIDOS, "r");
    if (!archi) {
        printf("No hay pedidos registrados.\n");
        return;
    }

    char linea[256];
    int totalPedido = 0;
    float montoTotal = 0;
    float monto2023 = 0, monto2024 = 0, monto2025 = 0;

    while (fgets(linea, sizeof(linea), archi)) {
        if (strstr(linea, "Total:")) {
            float totalPedido;
            sscanf(linea, "Total: %f", &totalPedido);
            totalPedido++;
            montoTotal += totalPedido;
        }
        else if (strstr(linea, "Fecha:")) {
            int dia, mes, anio;
            sscanf(linea, "Fecha: %d/%d/%d", &dia, &mes, &anio);
            
            if (anio == 2023) monto2023 += totalPedido;
            else if (anio == 2024) monto2024 += totalPedido;
            else if (anio == 2025) monto2025 += totalPedido;
        }
    }

    fclose(archi);
    
    printf("\n=== TOTAL DE VENTAS ===\n");
    printf("Pedidos totales: %d\n", totalPedido);
    printf("Monto total: ₡%.2f\n", montoTotal);
    
    if (monto2023 > 0) printf("Monto 2023: ₡%.2f\n", monto2023);
    if (monto2024 > 0) printf("Monto 2024: ₡%.2f\n", monto2024);
    if (monto2025 > 0) printf("Monto 2025: ₡%.2f\n", monto2025);
}

// Función auxiliar para ordenar clientes por pedidos (Bubble Sort)
void ordenarClientes(ClienteEstadistica *clientes, int cantidad) {
    for (int i = 0; i < cantidad - 1; i++) {
        for (int j = 0; j < cantidad - i - 1; j++) {
            if (clientes[j].pedidos < clientes[j + 1].pedidos) {
                // Intercambiar clientes
                ClienteEstadistica temp = clientes[j];
                clientes[j] = clientes[j + 1];
                clientes[j + 1] = temp;
            }
        }
    }
}

void clientesConMasPedidos() {
    // Primero contar clientes
    FILE *archiClientes = fopen(ARCHIVO_CLIENTES, "r");
    if (!archiClientes) {
        printf("No hay clientes registrados.\n");
        return;
    }

    int totalClientes = 0;
    char linea[256];
    while (fgets(linea, sizeof(linea), archiClientes)) {
        if (strstr(linea, "Cedula:")) totalClientes++;
    }
    fclose(archiClientes);

    if (totalClientes == 0) {
        printf("No hay clientes registrados.\n");
        return;
    }

    // Crear arreglo de clientes
    ClienteEstadistica *clientes = malloc(totalClientes * sizeof(ClienteEstadistica));
    if (!clientes) {
        printf("Error de memoria.\n");
        return;
    }

    // Leer clientes
    archiClientes = fopen(ARCHIVO_CLIENTES, "r");
    int i = 0;
    while (fgets(linea, sizeof(linea), archiClientes)) {
        if (strstr(linea, "Cedula:")) {
            sscanf(linea, "Cedula: %19s", clientes[i].cedula);
            
            fgets(linea, sizeof(linea), archiClientes);
            sscanf(linea, "Nombre: %99[^\n]", clientes[i].nombre);
            
            clientes[i].pedidos = 0;
            i++;
            
            // Saltar línea de teléfono y separador
            fgets(linea, sizeof(linea), archiClientes); // Teléfono
            fgets(linea, sizeof(linea), archiClientes); // ;
        }
    }
    fclose(archiClientes);

    // Contar pedidos por cliente
    FILE *archiPedidos = fopen(ARCHIVO_PEDIDOS, "r");
    if (archiPedidos) {
        while (fgets(linea, sizeof(linea), archiPedidos)) {
            if (strstr(linea, "Cedula del Cliente:")) {
                char cedula[20];
                sscanf(linea, "Cedula del Cliente: %19s", cedula);
                
                for (int j = 0; j < totalClientes; j++) {
                    if (strcmp(clientes[j].cedula, cedula) == 0) {
                        clientes[j].pedidos++;
                        break;
                    }
                }
            }
        }
        fclose(archiPedidos);
    }

    // Ordenar clientes usando la función separada
    ordenarClientes(clientes, totalClientes);

    // Mostrar resultados
    printf("\n=== CLIENTES CON MAS PEDIDOS ===\n");
    printf("TOP 5 Clientes:\n");
    printf("Pos | Cedula       | Nombre                 | Pedidos\n");
    printf("----------------------------------------------------\n");
    
    int mostrar = totalClientes > 5 ? 5 : totalClientes;
    for (int i = 0; i < mostrar; i++) {
        printf("%-3d | %-12s | %-20s | %-7d\n", 
               i + 1, clientes[i].cedula, clientes[i].nombre, clientes[i].pedidos);
    }
    
    free(clientes);
}

void librosMasVendidos() {
    int anioFiltro;
    printf("Ingrese anio para filtrar (0 para todos): ");
    scanf("%d", &anioFiltro);
    getchar();

    // Contar libros
    FILE *archiLibros = fopen(ARCHIVO_LIBROS, "r");
    if (!archiLibros) {
        printf("No hay libros registrados.\n");
        return;
    }

    int totalLibros = 0;
    char linea[256];
    while (fgets(linea, sizeof(linea), archiLibros)) {
        if (strstr(linea, "Codigo:")) totalLibros++;
    }
    fclose(archiLibros);

    // Crear arreglo de libros
    LibroEstadistica *libros = malloc(totalLibros * sizeof(LibroEstadistica));
    
    // Leer libros
    archiLibros = fopen(ARCHIVO_LIBROS, "r");
    int i = 0;
    while (fgets(linea, sizeof(linea), archiLibros)) {
        if (strstr(linea, "Codigo:")) {
            sscanf(linea, "Codigo: LIB%d", &libros[i].codigo);
            
            fgets(linea, sizeof(linea), archiLibros);
            sscanf(linea, "Nombre: %99[^\n]", libros[i].nombre);
            
            libros[i].vendidos = 0;
            i++;
        }
    }
    fclose(archiLibros);

    // Contar ventas por libro
    FILE *archiPedidos = fopen(ARCHIVO_PEDIDOS, "r");
    if (archiPedidos) {
        int anioActual = 0;
        bool aplicarFiltro = (anioFiltro != 0);
        
        while (fgets(linea, sizeof(linea), archiPedidos)) {
            if (strstr(linea, "Fecha:")) {
                int dia, mes, anio;
                sscanf(linea, "Fecha: %d/%d/%d", &dia, &mes, &anio);
                anioActual = anio;
            }
            else if (strstr(linea, "|")) {
                if (!aplicarFiltro || anioActual == anioFiltro) {
                    int codigo, cantidad;
                    sscanf(linea, "%*d | LIB%d | %*[^|] | %d", &codigo, &cantidad);
                    
                    for (int j = 0; j < totalLibros; j++) {
                        if (libros[j].codigo == codigo) {
                            libros[j].vendidos += cantidad;
                            break;
                        }
                    }
                }
            }
        }
        fclose(archiPedidos);
    }

    // Ordenar libros por ventas
    for (int i = 0; i < totalLibros - 1; i++) {
        for (int j = 0; j < totalLibros - i - 1; j++) {
            if (libros[j].vendidos < libros[j + 1].vendidos) {
                LibroEstadistica temp = libros[j];
                libros[j] = libros[j + 1];
                libros[j + 1] = temp;
            }
        }
    }

    // Mostrar resultados
    printf("\n=== LIBROS MAS VENDIDOS ===\n");
    if (anioFiltro > 0) printf("Anio filtrado: %d\n", anioFiltro);
    printf("TOP 10 Libros:\n");
    printf("Pos | Codigo  | Libro                  | Vendidos\n");
    printf("-----------------------------------------------\n");
    
    int mostrar = totalLibros > 10 ? 10 : totalLibros;
    for (int i = 0; i < mostrar; i++) {
        printf("%-3d | LIB%-4d | %-20s | %-8d\n", 
               i + 1, libros[i].codigo, libros[i].nombre, libros[i].vendidos);
    }
    
    free(libros);
}