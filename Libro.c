#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"

typedef struct {
    char* nombreLibro;
    char* caracteres;
    float* precioLibro;
    int codigoLibro;
    int* anioPublicacion;
} Libro;

Libro CrearLibro() {

    Libro lib;
    lib.caracteres = (char *)malloc(100 * sizeof(char));
    lib.nombreLibro = NULL;
    lib.precioLibro = (float*)malloc(sizeof(float));
    lib.anioPublicacion  = (int*)malloc(sizeof(int));
    lib.codigoLibro = 0;
    return lib;
}

void registrarLibro(Libro *lib) { //struct Libro* libro

    printf("Nombre del libro:");
    
    scanf("%s", lib->caracteres);
    lib->nombreLibro = espacioDeMemoria(lib->caracteres);

    printf("Precio del libro: ");
    scanf("%f", lib->precioLibro);

    printf("Año de publicacion: ");
    scanf("%d", lib->anioPublicacion);

    lib->codigoLibro += 1;
    printf("Libro registrado exitosamente, el codigo del libro es el siguiente: %d\n", lib->codigoLibro);
}

void LiberarMemoria(Libro *lib) {
    free(lib->nombreLibro);
    free(lib->precioLibro);
    free(lib->caracteres);
    //free(lib->codigoLibro);
    free(lib->anioPublicacion);
    lib->nombreLibro = NULL;
    lib->precioLibro = NULL;
    lib->caracteres = NULL;
    lib->anioPublicacion = NULL;
}

int main() {


    // Crear libro vacío
    
    Libro lib = CrearLibro();

    // Registrar datos desde el usuario
    registrarLibro(&lib);

    // Liberar memoria
    LiberarMemoria(&lib);

    return 0;
}

