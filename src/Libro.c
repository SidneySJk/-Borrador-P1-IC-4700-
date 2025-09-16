#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Libro.h"
#include "Cliente.h"

// -------------------------------------Guardar LIBRO------------------------------------------------------------------------------------

// Lee la cadena caracter por caracter para determinar su espacio de memoria
char* espacioDeMemoria() {
    
    char* cadena = NULL;
    int caracteres = 0;
    int c;

    while (( c = getchar()) != '\n' && c != EOF) { //Fuente: https://rabbit.eng.miami.edu/class/een218/getchar.html
        char* capacidad = realloc(cadena,( caracteres+2) * sizeof(char));//Se suma 2 para que quepa el caracter y '/0'
        if (capacidad == NULL) {
            printf("Error en la asignacion de memoria\n");
            free(capacidad);
            exit(1);
        }
        cadena = capacidad;
        cadena[caracteres] = (char)c;//'\0'
        caracteres+=1;
    }
   
    if (cadena != NULL) {
        cadena[caracteres] = '\0';
    }
    //capacidad[caracteres] = '\0';

    //return capacidad;
    return cadena;
}

Libro CrearLibro() {
    Libro lib;
    lib.nombreLibro = NULL;
    lib.precioLibro = (float*)malloc(sizeof(float));
    lib.cantidad = (int*)malloc(sizeof(int));
    lib.codigoLibro = 0;
    return lib;
}

int obtenerSiguienteCodigo() {
    FILE *archi = fopen(ARCHIVO_LIBROS, "r");
    if (!archi) {
        return 1; // Si no existe el archivo, empezamos en LIB1
    }

    int codigo = 0;
    while (fscanf(archi, "Codigo: LIB%d\n", &codigo) == 1) {
        // Guarda el último código leído
    }

    fclose(archi);
    return codigo + 1;
}

// ------------------------------------------------------------- Registrar Libro

void registrarLibro() {
    Libro lib = CrearLibro();
    
    // Solicitar nombre
    printf("Nombre del libro: ");
    lib.nombreLibro = espacioDeMemoria();

    // Solicitar precio
    printf("Precio del libro: ");
    scanf("%f", lib.precioLibro);

    // Solicitar cantidad
    printf("Cantidad: ");
    scanf("%d", lib.cantidad);

    // Asignar código
    lib.codigoLibro = obtenerSiguienteCodigo();

    // Limpiar buffer
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}

    // Guardar en archivo
    guardarLibroEnTXT(&lib);
    
    // Liberar memoria
    LiberarMemoriaLibro(&lib);
}

void guardarLibroEnTXT(Libro *lib) {
    FILE *archi = fopen(ARCHIVO_LIBROS, "a");
    if (!archi) {
        perror("No se pudo abrir el archivo");
        return;
    }

    fprintf(archi, "Codigo: LIB%d\n", lib->codigoLibro);
    fprintf(archi, "Nombre: %s\n", lib->nombreLibro ? lib->nombreLibro : "(sin nombre)");
    fprintf(archi, "Precio: %.2f\n", lib->precioLibro ? *lib->precioLibro : 0.0f);
    fprintf(archi, "Cantidad: %d\n", lib->cantidad ? *lib->cantidad : 0);
    fprintf(archi, ";\n");

    fclose(archi);
    printf("\nLibro LIB%d registrado exitosamente\n\n", lib->codigoLibro);
}

void LiberarMemoriaLibro(Libro *lib) {
    free(lib->nombreLibro);
    free(lib->precioLibro);
    free(lib->cantidad);
    lib->nombreLibro = NULL;
    lib->precioLibro = NULL;
    lib->cantidad = NULL;
}

// --------------------------------------------------Eliminar LIBRO----------------------------------------------------------------------

void eliminarLibro(const char* codigoBuscado){
    FILE *original = fopen("Libros.txt", "r");
    if (!original) {
        printf("No se pudo abrir Libros.txt\n");
        return;
    }

    FILE *temp = fopen("Temp.txt", "w"); // archivo temporal para almacenar los libros que no se van a borrar
    if (!temp) {
        printf("No se pudo crear archivo temporal\n");
        fclose(original);
        return;
    }

    char linea[256];
    bool encontrado = false;
    bool copiar = true;

    while (fgets(linea, sizeof(linea), original)) {
        if (strncmp(linea, "Codigo:", 7) == 0) {
            if (strstr(linea, codigoBuscado)) {
                encontrado = true;
                copiar = false;
            } else {
                copiar = true;
            }
        }

        if (copiar) {
            fputs(linea, temp);
        }

        if (linea[0] == ';') {
            copiar = true;
        }
    }

    fclose(original);
    fclose(temp);

    if (remove("Libros.txt") != 0 || rename("Temp.txt", "Libros.txt") != 0) {
        perror("Error al actualizar archivo");
        return;
    }

    if (encontrado) {
        printf("\nLibro %s eliminado correctamente.\n\n", codigoBuscado);
    } else {
        printf("\nNo se encontró el libro con código %s.\n\n", codigoBuscado);
    }
}

// --------------------------------------------------Consultar Catalogo----------------------------------------------------------------------

void consultarCatalogo() {
    FILE *archi = fopen("data/Libros.txt", "r");
    if (!archi) {
        printf("No hay libros registrados.\n");
        return;
    }
    
    printf("\n--- CATALOGO DE LIBROS ---\n");
    printf("CODIGO | NOMBRE                 | PRECIO    | CANTIDAD\n");
    printf("-----------------------------------------------------------\n");
    
    char linea[256];
    char nombre[100];
    float precio;
    int codigo, cantidad;
    
    while (fgets(linea, sizeof(linea), archi)) {
        if (sscanf(linea, "Codigo: LIB%d", &codigo) == 1) {
            // Leer las siguientes líneas del registro
            fgets(linea, sizeof(linea), archi);
            sscanf(linea, "Nombre: %[^\n]", nombre);
            
            fgets(linea, sizeof(linea), archi);
            sscanf(linea, "Precio: %f", &precio);
            
            fgets(linea, sizeof(linea), archi);
            sscanf(linea, "Cantidad: %d", &cantidad);
            
            // Saltar la línea de separación ";"
            fgets(linea, sizeof(linea), archi);
            
            // Mostrar el libro
            printf("LIB%-3d | %-22s | $%-6.2f | %-3d\n", 
                   codigo, nombre, precio, cantidad);
        }
    }
    
    fclose(archi);
}

// --------------------------------------------------Funcs Auxliares----------------------------------------------------------------------

char* solicitarCodigo(){
    char* codigo = malloc(20 * sizeof(char));;
    printf("Ingrese el codigo del libro EJEMPLO (LIB4)");
    scanf("%19s", codigo);
    return codigo;
}
