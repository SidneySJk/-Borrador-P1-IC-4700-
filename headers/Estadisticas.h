#ifndef ESTADISTICAS_H
#define ESTADISTICAS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Pedido.h"
#include "Libro.h"

typedef struct {
    char cedula[20];
    char nombre[100];
    int pedidos;
} ClienteEstadistica;

typedef struct {
    int codigo;
    char nombre[100];
    int vendidos;
} LibroEstadistica;

// Prototipos de funciones
void calcularTotalVentas();
void clientesConMasPedidos();
void librosMasVendidos();

#endif