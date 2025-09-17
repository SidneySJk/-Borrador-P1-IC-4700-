#ifndef LIBRO_H
#define LIBRO_H

#include <stdio.h>
#include <stdlib.h>

// Macros para configuración
#define ARCHIVO_LIBROS "data/Libros.txt"
#define MAX_NOMBRE 100

// Definición del struct
typedef struct {
    char *nombreLibro;
    float *precioLibro;
    int codigoLibro;
    int *cantidad;
} Libro;

// Prototipos de funciones
Libro CrearLibro();
int obtenerSiguienteCodigo();
void registrarLibro();
void guardarLibroEnTXT(Libro *lib);
void LiberarMemoriaLibro(Libro *lib);
void eliminarLibro(const char* codigoBuscado);
char* solicitarCodigo();
void consultarCatalogo();
void inventarioDePrograma();

#endif