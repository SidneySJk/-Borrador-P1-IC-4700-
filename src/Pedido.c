#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "../headers/Libro.h"
#include "../headers/Pedido.h"
#include "../headers/Cliente.h"

extern char* espacioDeMemoria();

// Función auxiliar para obtener información de un libro por código
static bool obtenerInfoLibro(int codigoLibro, char **nombre, float *precio, int *stockActual) {
    FILE *archivo = fopen(ARCHIVO_LIBROS, "r");
    if (!archivo) return false;

    char linea[256];
    bool encontrado = false;
    *nombre = NULL;
    *precio = 0;
    *stockActual = 0;

    while (fgets(linea, sizeof(linea), archivo)) {
        if (strncmp(linea, "Codigo: LIB", 11) == 0) {
            int codigo;
            sscanf(linea, "Codigo: LIB%d", &codigo);
            if (codigo == codigoLibro) {
                encontrado = true;
                
                // Leer nombre
                fgets(linea, sizeof(linea), archivo);
                char nombreTemp[100];
                sscanf(linea, "Nombre: %[^\n]", nombreTemp);
                *nombre = strdup(nombreTemp);
                
                // Leer precio
                fgets(linea, sizeof(linea), archivo);
                sscanf(linea, "Precio: %f", precio);
                
                // Leer cantidad
                fgets(linea, sizeof(linea), archivo);
                sscanf(linea, "Cantidad: %d", stockActual);
                break;
            }
        }
    }
    
    fclose(archivo);
    return encontrado;
}

Pedido CrearPedido() {
    Pedido ped;
    ped.numeroPedido = 0;
    ped.cedula = NULL;
    ped.fecha = NULL;
    ped.lineas = malloc(MAX_LINEAS_INICIAL * sizeof(LineaPedido));
    ped.cantidadLineas = 0;
    ped.capacidadLineas = MAX_LINEAS_INICIAL;
    ped.subtotal = 0;
    ped.impuesto = 0;
    ped.total = 0;
    return ped;
}

void LiberarMemoriaPedido(Pedido *ped) {
    for (int i = 0; i < ped->cantidadLineas; i++) {
        free(ped->lineas[i].nombreLibro);
    }
    free(ped->lineas);
    free(ped->cedula);
    free(ped->fecha);
    
    ped->lineas = NULL;
    ped->cedula = NULL;
    ped->fecha = NULL;
    ped->cantidadLineas = 0;
    ped->capacidadLineas = 0;
}

bool agregarLineaPedido(Pedido *ped, int codigoLibro, int cantidad) {
    char *nombreLibro;
    float precio;
    int stockActual;
    
    if (!obtenerInfoLibro(codigoLibro, &nombreLibro, &precio, &stockActual)) {
        printf("Error: Libro no encontrado.\n");
        return false;
    }
    
    if (stockActual < cantidad) {
        printf("Error: Stock insuficiente. Stock actual: %d\n", stockActual);
        free(nombreLibro);
        return false;
    }
    
    // Verificar si el libro ya existe en el pedido
    for (int i = 0; i < ped->cantidadLineas; i++) {
        if (ped->lineas[i].codigoLibro == codigoLibro) {
            if (stockActual >= (ped->lineas[i].cantidad + cantidad)) {
                ped->lineas[i].cantidad += cantidad;
                ped->lineas[i].subtotal = ped->lineas[i].cantidad * ped->lineas[i].precioUnitario;
                free(nombreLibro);
                calcularTotales(ped);
                return true;
            } else {
                printf("Error: Stock insuficiente para aumentar cantidad. Stock actual: %d\n", stockActual);
                free(nombreLibro);
                return false;
            }
        }
    }
    
    // Expandir el arreglo si es necesario
    if (ped->cantidadLineas >= ped->capacidadLineas) {
        int nuevaCapacidad = ped->capacidadLineas * 2;
        LineaPedido *temp = realloc(ped->lineas, nuevaCapacidad * sizeof(LineaPedido));
        if (!temp) {
            printf("Error: No se pudo expandir el pedido.\n");
            free(nombreLibro);
            return false;
        }
        ped->lineas = temp;
        ped->capacidadLineas = nuevaCapacidad;
    }
    
    // Agregar nueva línea
    LineaPedido nuevaLinea = {
        .numeroLinea = ped->cantidadLineas + 1,
        .nombreLibro = nombreLibro,
        .codigoLibro = codigoLibro,
        .cantidad = cantidad,
        .precioUnitario = precio,
        .subtotal = precio * cantidad
    };
    
    ped->lineas[ped->cantidadLineas] = nuevaLinea;
    ped->cantidadLineas++;
    
    calcularTotales(ped);
    return true;
}

void eliminarLineaPedido(Pedido *ped, int numeroLinea) {
    if (numeroLinea < 1 || numeroLinea > ped->cantidadLineas) {
        printf("Error: Numero de linea invalido.\n");
        return;
    }
    
    int indice = numeroLinea - 1;
    free(ped->lineas[indice].nombreLibro);
    
    // Mover las líneas restantes
    for (int i = indice; i < ped->cantidadLineas - 1; i++) {
        ped->lineas[i] = ped->lineas[i + 1];
        ped->lineas[i].numeroLinea = i + 1;
    }
    
    ped->cantidadLineas--;
    calcularTotales(ped);
}

void mostrarPedidoActual(const Pedido *ped) {
    printf("\n--- PEDIDO ACTUAL ---\n");
    printf("Linea | Codigo | Libro                  | Cantidad | Precio Unit. | Subtotal\n");
    printf("-------------------------------------------------------------------------\n");
    
    for (int i = 0; i < ped->cantidadLineas; i++) {
        printf("%-5d | LIB%-3d | %-20s | %-8d | ₡%-10.2f | ₡%.2f\n",
            ped->lineas[i].numeroLinea,
            ped->lineas[i].codigoLibro,
            ped->lineas[i].nombreLibro,
            ped->lineas[i].cantidad,
            ped->lineas[i].precioUnitario,
            ped->lineas[i].subtotal);
    }
    
    printf("-------------------------------------------------------------------------\n");
    printf("Subtotal: %.2f\n", ped->subtotal);
    printf("IVA (13%%): %.2f\n", ped->impuesto);
    printf("Total: %.2f\n", ped->total);
}

bool validarStockDisponible(int codigoLibro, int cantidad) {
    char *nombre;
    float precio;
    int stockActual;
    
    if (!obtenerInfoLibro(codigoLibro, &nombre, &precio, &stockActual)) {
        return false;
    }
    
    free(nombre);
    return stockActual >= cantidad;
}

void calcularTotales(Pedido *ped) {
    ped->subtotal = 0;
    for (int i = 0; i < ped->cantidadLineas; i++) {
        ped->subtotal += ped->lineas[i].subtotal;
    }
    
    ped->impuesto = ped->subtotal * IVA;
    ped->total = ped->subtotal + ped->impuesto;
}

int obtenerSiguienteNumeroPedido() {
    FILE *archivo = fopen(ARCHIVO_PEDIDOS, "r");
    if (!archivo) return 1;
    
    int maxNumero = 0;
    char linea[256];
    
    while (fgets(linea, sizeof(linea), archivo)) {
        if (strncmp(linea, "Numero de Pedido:", 16) == 0) {
            int numero;
            sscanf(linea, "Numero de Pedido: %d", &numero);
            if (numero > maxNumero) maxNumero = numero;
        }
    }
    
    fclose(archivo);
    return maxNumero + 1;
}

void guardarPedidoEnTXT(const Pedido *ped) {
    FILE *archivo = fopen(ARCHIVO_PEDIDOS, "a");
    if (!archivo) {
        printf("Error: No se pudo abrir el archivo de pedidos.\n");
        return;
    }
    
    fprintf(archivo, "\n=== %s ===\n", NOMBRE_COMERCIO);
    fprintf(archivo, "Direccion: %s\n", DIRECCION_COMERCIO);
    fprintf(archivo, "Telefono: %s\n", TELEFONO_COMERCIO);
    fprintf(archivo, "Fecha: %s\n", ped->fecha);
    fprintf(archivo, "Numero de Pedido: %d\n", ped->numeroPedido);
    fprintf(archivo, "Cedula del Cliente: %s\n\n", ped->cedula);
    
    fprintf(archivo, "DETALLE DEL PEDIDO\n");
    fprintf(archivo, "-------------------------------------------------------------------------\n");
    for (int i = 0; i < ped->cantidadLineas; i++) {
        fprintf(archivo, "%-5d | LIB%-3d | %-20s | %-8d | ₡%-10.2f | ₡%.2f\n",
            ped->lineas[i].numeroLinea,
            ped->lineas[i].codigoLibro,
            ped->lineas[i].nombreLibro,
            ped->lineas[i].cantidad,
            ped->lineas[i].precioUnitario,
            ped->lineas[i].subtotal);
    }
    
    fprintf(archivo, "-------------------------------------------------------------------------\n");
    fprintf(archivo, "Subtotal: %.2f\n", ped->subtotal);
    fprintf(archivo, "IVA (13%%): %.2f\n", ped->impuesto);
    fprintf(archivo, "Total: %.2f\n", ped->total);
    fprintf(archivo, ";\n");
    
    fclose(archivo);
}

void actualizarStock(const Pedido *ped) {
    FILE *original = fopen(ARCHIVO_LIBROS, "r");
    FILE *temp = fopen("Temp.txt", "w");
    
    if (!original || !temp) {
        printf("Error al actualizar el stock.\n");
        if (original) fclose(original);
        if (temp) fclose(temp);
        return;
    }
    
    char linea[256];
    bool actualizando = false;
    int codigoActual = 0;
    
    while (fgets(linea, sizeof(linea), original)) {
        if (strncmp(linea, "Codigo: LIB", 11) == 0) {
            sscanf(linea, "Codigo: LIB%d", &codigoActual);
            actualizando = false;
            
            // Verificar si este libro está en el pedido
            for (int i = 0; i < ped->cantidadLineas; i++) {
                if (ped->lineas[i].codigoLibro == codigoActual) {
                    actualizando = true;
                    break;
                }
            }
        }
        
        if (actualizando && strncmp(linea, "Cantidad:", 9) == 0) {
            int cantidadActual;
            sscanf(linea, "Cantidad: %d", &cantidadActual);
            
            // Encontrar la cantidad a descontar
            for (int i = 0; i < ped->cantidadLineas; i++) {
                if (ped->lineas[i].codigoLibro == codigoActual) {
                    cantidadActual -= ped->lineas[i].cantidad;
                    fprintf(temp, "Cantidad: %d\n", cantidadActual);
                    break;
                }
            }
        } else {
            fputs(linea, temp);
        }
    }
    
    fclose(original);
    fclose(temp);
    
    remove(ARCHIVO_LIBROS);
    rename("Temp.txt", ARCHIVO_LIBROS);
}

void generarPedido(Pedido *ped) {
    // Solicitar cédula del cliente
    printf("Ingrese la cédula del cliente: ");
    ped->cedula = espacioDeMemoria();
    
    // Generar fecha actual
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char fechaStr[20];
    strftime(fechaStr, sizeof(fechaStr), "%d/%m/%Y", tm);
    ped->fecha = strdup(fechaStr);
    
    // Asignar número de pedido
    ped->numeroPedido = obtenerSiguienteNumeroPedido();
    
    // Guardar el pedido y actualizar stock
    guardarPedidoEnTXT(ped);
    actualizarStock(ped);
    
    printf("\nPedido #%d generado exitos}amente!\n", ped->numeroPedido);
}

// Función auxiliar para leer pedido del archivo
static Pedido* leerPedido(FILE* archivo) {
    Pedido* ped = malloc(sizeof(Pedido));
    if (!ped) return NULL;
    
    *ped = CrearPedido();
    char linea[256];
    bool leyendoDetalle = false;
    
    while (fgets(linea, sizeof(linea), archivo)) {
        if (linea[0] == ';') break;
        
        if (strstr(linea, "Numero de Pedido:")) {
            sscanf(linea, "Numero de Pedido: %d", &ped->numeroPedido);
        }
        else if (strstr(linea, "Cedula del Cliente:")) {
            char cedula[50];
            sscanf(linea, "Cedula del Cliente: %[^\n]", cedula);
            ped->cedula = strdup(cedula);
        }
        else if (strstr(linea, "Fecha:")) {
            char fecha[20];
            sscanf(linea, "Fecha: %[^\n]", fecha);
            ped->fecha = strdup(fecha);
        }
        else if (strstr(linea, "DETALLE DEL PEDIDO")) {
            leyendoDetalle = true;
            fgets(linea, sizeof(linea), archivo); // Saltar línea de separación
            continue;
        }
        
        if (leyendoDetalle && strstr(linea, "|")) {
            int numeroLinea, codigoLibro, cantidad;
            char nombreLibro[100];
            float precioUnitario, subtotal;
            
            sscanf(linea, "%d | LIB%d | %[^|] | %d | ₡%f | ₡%f",
                   &numeroLinea, &codigoLibro, nombreLibro, &cantidad,
                   &precioUnitario, &subtotal);
            
            // Eliminar espacios al final del nombre del libro
            char* end = nombreLibro + strlen(nombreLibro) - 1;
            while (end > nombreLibro && (*end == ' ' || *end == '\t')) end--;
            *(end + 1) = '\0';
            
            agregarLineaPedido(ped, codigoLibro, cantidad);
        }
    }
    
    return ped;
}

// Función para restaurar el stock de un pedido
static void restaurarStock(const Pedido *ped) {
    FILE *original = fopen(ARCHIVO_LIBROS, "r");
    FILE *temp = fopen("Temp.txt", "w");
    
    if (!original || !temp) {
        if (original) fclose(original);
        if (temp) fclose(temp);
        return;
    }
    
    char linea[256];
    bool actualizando = false;
    int codigoActual = 0;
    
    while (fgets(linea, sizeof(linea), original)) {
        if (strncmp(linea, "Codigo: LIB", 11) == 0) {
            sscanf(linea, "Codigo: LIB%d", &codigoActual);
            actualizando = false;
            
            for (int i = 0; i < ped->cantidadLineas; i++) {
                if (ped->lineas[i].codigoLibro == codigoActual) {
                    actualizando = true;
                    break;
                }
            }
        }
        
        if (actualizando && strncmp(linea, "Cantidad:", 9) == 0) {
            int cantidadActual;
            sscanf(linea, "Cantidad: %d", &cantidadActual);
            
            for (int i = 0; i < ped->cantidadLineas; i++) {
                if (ped->lineas[i].codigoLibro == codigoActual) {
                    cantidadActual += ped->lineas[i].cantidad;
                    fprintf(temp, "Cantidad: %d\n", cantidadActual);
                    break;
                }
            }
        } else {
            fputs(linea, temp);
        }
    }
    
    fclose(original);
    fclose(temp);
    
    remove(ARCHIVO_LIBROS);
    rename("Temp.txt", ARCHIVO_LIBROS);
}

bool eliminarPedido(int numeroPedido) {
    FILE *original = fopen(ARCHIVO_PEDIDOS, "r");
    if (!original) {
        printf("Error: No se pudo abrir el archivo de pedidos.\n");
        return false;
    }
    
    FILE *temp = fopen("TempPedidos.txt", "w");
    if (!temp) {
        printf("Error: No se pudo crear archivo temporal.\n");
        fclose(original);
        return false;
    }
    
    char linea[256];
    bool encontrado = false;
    Pedido* pedidoAEliminar = NULL;
    long posicionInicioPedido = 0;
    bool copiandoPedido = true;
    
    while (fgets(linea, sizeof(linea), original)) {
        if (strstr(linea, "=== ")) {
            posicionInicioPedido = ftell(original) - strlen(linea);
        }
        
        if (strstr(linea, "Numero de Pedido:")) {
            int numPedido;
            sscanf(linea, "Numero de Pedido: %d", &numPedido);
            
            if (numPedido == numeroPedido) {
                encontrado = true;
                copiandoPedido = false;
                
                // Volver al inicio del pedido para leerlo completo
                fseek(original, posicionInicioPedido, SEEK_SET);
                pedidoAEliminar = leerPedido(original);
                continue;
            } else {
                copiandoPedido = true;
            }
        }
        
        if (copiandoPedido) {
            fputs(linea, temp);
        }
    }
    
    fclose(original);
    fclose(temp);
    
    if (!encontrado) {
        printf("Error: No se encontro el pedido numero %d.\n", numeroPedido);
        remove("TempPedidos.txt");
        return false;
    }
    
    // Restaurar el stock antes de eliminar el archivo
    if (pedidoAEliminar) {
        restaurarStock(pedidoAEliminar);
        LiberarMemoriaPedido(pedidoAEliminar);
        free(pedidoAEliminar);
    }
    
    // Reemplazar el archivo original con el temporal
    if (remove(ARCHIVO_PEDIDOS) != 0 || rename("TempPedidos.txt", ARCHIVO_PEDIDOS) != 0) {
        printf("Error: No se pudo actualizar el archivo de pedidos.\n");
        return false;
    }
    
    printf("Pedido #%d eliminado exitosamente.\n", numeroPedido);
    return true;
}

void consultarPedidos() {
    FILE *archi = fopen(ARCHIVO_PEDIDOS, "r");
    if (!archi) {
        printf("No hay pedidos registrados.\n");
        return;
    }
    
    char linea[256];
    int numeroPedido;
    char cedula[50];
    char fecha[20];
    bool mostrandoEncabezado = true;
    float subtotal = 0, impuesto = 0, total = 0;
    
    printf("\n=== CONSULTA DE PEDIDOS ===\n\n");
    
    while (fgets(linea, sizeof(linea), archi)) {
        if (strstr(linea, "=== ")) {
            if (!mostrandoEncabezado) {
                // Imprimir totales del pedido anterior
                printf("-----------------------------------------------------------\n");
                printf("Subtotal: %.2f\n", subtotal);
                printf("IVA (13%%): %.2f\n", impuesto);
                printf("Total: %.2f\n\n", total);
                printf("===========================================================\n\n");
            }
            mostrandoEncabezado = true;
            subtotal = 0;
            impuesto = 0;
            total = 0;
            continue;
        }
        
        if (strstr(linea, "Numero de Pedido:")) {
            sscanf(linea, "Numero de Pedido: %d", &numeroPedido);
            printf("PEDIDO #%d\n", numeroPedido);
        }
        else if (strstr(linea, "Fecha:")) {
            sscanf(linea, "Fecha: %[^\n]", fecha);
            printf("Fecha: %s\n", fecha);
        }
        else if (strstr(linea, "Cedula del Cliente:")) {
            sscanf(linea, "Cedula del Cliente: %[^\n]", cedula);
            printf("Cliente: %s\n", cedula);
        }
        else if (strstr(linea, "DETALLE DEL PEDIDO")) {
            printf("\nDETALLE:\n");
            printf("Linea | Codigo | Libro                  | Cantidad | Precio Unit. | Subtotal\n");
            printf("-----------------------------------------------------------\n");
            mostrandoEncabezado = false;
        }
        else if (!mostrandoEncabezado && strstr(linea, "|")) {
            // Imprimir línea de detalle tal como está
            printf("%s", linea);
        }
        else if (strstr(linea, "Subtotal: ")) {
            sscanf(linea, "Subtotal: %f", &subtotal);
        }
        else if (strstr(linea, "IVA")) {
            sscanf(linea, "IVA (13%%): %f", &impuesto);
        }
        else if (strstr(linea, "Total:")) {
            sscanf(linea, "Total: %f", &total);
        }
    }
    
    // Imprimir totales del último pedido si existe
    if (!mostrandoEncabezado) {
        printf("-----------------------------------------------------------\n");
        printf("Subtotal: %.2f\n", subtotal);
        printf("IVA (13%%): %.2f\n", impuesto);
        printf("Total: %.2f\n\n", total);
    }
    
    fclose(archi);
}

void gestionarPedido() {
    Pedido ped = CrearPedido();
    int opcion;
    bool salir = false;
    
    while (!salir) {
        mostrarPedidoActual(&ped);
        printf("\n1. Agregar linea\n");
        printf("2. Eliminar linea\n");
        printf("3. Generar pedido\n");
        printf("4. Salir sin guardar\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer
        
        switch (opcion) {
            case 1: {
                printf("Ingrese el codigo del libro (solo el numero, sin 'LIB'): ");
                int codigo;
                scanf("%d", &codigo);
                printf("Ingrese la cantidad: ");
                int cantidad;
                scanf("%d", &cantidad);
                getchar(); // Limpiar el buffer
                
                if (agregarLineaPedido(&ped, codigo, cantidad)) {
                    printf("Linea agregada exitosamente.\n");
                }
                break;
            }
            case 2: {
                printf("Ingrese el numero de linea a eliminar: ");
                int numeroLinea;
                scanf("%d", &numeroLinea);
                getchar(); // Limpiar el buffer
                eliminarLineaPedido(&ped, numeroLinea);
                break;
            }
            case 3:
                if (ped.cantidadLineas > 0) {
                    generarPedido(&ped);
                    salir = true;
                } else {
                    printf("Error: No se puede generar un pedido vacio.\n");
                }
                break;
            case 4:
                salir = true;
                break;
            default:
                printf("Opcion invalida.\n");
        }
    }
    
    LiberarMemoriaPedido(&ped);
}

void mostrarPedidosPorCedula(const char* cedulaBuscada) {
    FILE *archi = fopen(ARCHIVO_PEDIDOS, "r");
    if (!archi) {
        printf("No hay pedidos registrados.\n");
        return;
    }
    
    printf("=== PEDIDOS DEL CLIENTE ===\n");
    
    char linea[256];
    char cedula[50];
    int numeroPedido = 0;
    bool pedidoEncontrado = false;
    bool mostrandoPedido = false;
    
    bool mostrandoDetalle = false;
    
    while (fgets(linea, sizeof(linea), archi)) {
        if (strstr(linea, "=== ")) {
            mostrandoPedido = false;
            mostrandoDetalle = false;
            continue;
        }
        
        if (strstr(linea, "Numero de Pedido:")) {
            sscanf(linea, "Numero de Pedido: %d", &numeroPedido);
            continue;
        }
        
        if (strstr(linea, "Cedula del Cliente:")) {
            sscanf(linea, "Cedula del Cliente: %[^\n]", cedula);
            
            int i = 0;
            while (cedulaBuscada[i] != '\0' && cedula[i] != '\0') {
                if (cedulaBuscada[i] != cedula[i]) break;
                i++;
            }
            
            mostrandoPedido = (cedulaBuscada[i] == '\0' && cedula[i] == '\0');
            pedidoEncontrado = pedidoEncontrado || mostrandoPedido;
            
            if (mostrandoPedido) {
                printf("\nPEDIDO %d:", numeroPedido);  // ← \n aquí en lugar de arriba
                printf("\n====================");
                
            }
            continue;
        }
        
        if (mostrandoPedido) {
            if (strstr(linea, "DETALLE DEL PEDIDO")) {
                printf("\nLinea | Codigo | Libro               | Cantidad | Precio Unit. | Subtotal");
                printf("\n-----------------------------------------------------------------------");
                mostrandoDetalle = true;
                continue;
            }
            
            if (strstr(linea, "|") && mostrandoDetalle) {
                printf("\n%s", linea);
                continue;
            }
            
            if (strstr(linea, "Subtotal:") || strstr(linea, "IVA") || strstr(linea, "Total:")) {
                printf("%s", linea);
            }
        }
        
        if (mostrandoPedido && linea[0] == ';') {
            printf("====================\n");
            mostrandoPedido = false;
            mostrandoDetalle = false;
        }
    }
    
    if (!pedidoEncontrado) {
        printf("\nEl cliente no tiene pedidos registrados.\n");
    }
    
    fclose(archi);
}