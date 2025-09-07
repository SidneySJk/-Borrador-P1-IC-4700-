#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"

typedef struct {
    char* nombreLibro;
    //char* caracteres;
    float* precioLibro;
    int codigoLibro;
    int* cantidad;
} Libro;

Libro CrearLibro() {

    Libro lib;
    //lib.caracteres = (char *)malloc(100 * sizeof(char));
    lib.nombreLibro = NULL;
    lib.precioLibro = (float*)malloc(sizeof(float));
    lib.cantidad = (int*)malloc(sizeof(int));
    lib.codigoLibro = 0;
    return lib;
}

void registrarLibro(Libro *lib) { //struct Libro* libro

    printf("Nombre del libro:");
    
    //scanf("%s", lib->nombreLibro);
    lib->nombreLibro = espacioDeMemoria();

    printf("Precio del libro: ");
    scanf("%f", lib->precioLibro);

    printf("Cantidad: ");
    scanf("%d", lib->cantidad);

    lib->codigoLibro += 1;
    printf("Libro registrado exitosamente, el codigo del libro es el siguiente: %d\n", lib->codigoLibro);
    int c;

    while ((c= getchar()) != '\n' && c != EOF) {

    }
}

void LiberarMemoria(Libro *lib) {
    free(lib->nombreLibro);
    free(lib->precioLibro);
    //free(lib->caracteres);
    //free(lib->codigoLibro);
    free(lib->cantidad);
    lib->nombreLibro = NULL;
    lib->precioLibro = NULL;
    //lib->caracteres = NULL;
    lib->cantidad = NULL;
}

int main() {
    
    Libro lib = CrearLibro();
    registrarLibro(&lib);
    LiberarMemoria(&lib);

    return 0;
}

