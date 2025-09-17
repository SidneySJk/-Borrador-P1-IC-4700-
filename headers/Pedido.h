#ifndef PEDIDO_H
#define PEDIDO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../headers/Cliente.h"
#include "../headers/Libro.h"

// Macros para configuración
#define ARCHIVO_PEDIDOS "data/Pedidos.txt"
#define IVA 0.13 // 13% impuesto de venta
#define MAX_LINEAS_INICIAL 5
#define NOMBRE_COMERCIO "Librería TEC"
#define DIRECCION_COMERCIO "Limón, Costa Rica"
#define TELEFONO_COMERCIO "2550-2500"

// Estructura para cada línea del pedido
typedef struct {
    int numeroLinea;
    char *nombreLibro;
    int codigoLibro;
    int cantidad;
    float precioUnitario;
    float subtotal;
} LineaPedido;

// Estructura principal del pedido
typedef struct {
    int numeroPedido;
    char *cedula;
    char *fecha;
    LineaPedido *lineas;
    int cantidadLineas;
    int capacidadLineas;
    float subtotal;
    float impuesto;
    float total;
} Pedido;

// Funciones de creación y gestión
Pedido CrearPedido();
void LiberarMemoriaPedido(Pedido *ped);
bool agregarLineaPedido(Pedido *ped, int codigoLibro, int cantidad);
void eliminarLineaPedido(Pedido *ped, int numeroLinea);
void mostrarPedidoActual(const Pedido *ped);

// Funciones de validación y cálculo
bool validarStockDisponible(int codigoLibro, int cantidad);
void calcularTotales(Pedido *ped);
int obtenerSiguienteNumeroPedido();

// Funciones de persistencia
void guardarPedidoEnTXT(const Pedido *ped);
void actualizarStock(const Pedido *ped);
void generarPedido(Pedido *ped);

// Función principal de gestión de pedidos
void gestionarPedido();

// Función para eliminar pedido
bool eliminarPedido(int numeroPedido);

// Función para consultar pedidos
void consultarPedidos();

// Funcion prara mostrar pedidos por cedula
void mostrarPedidosPorCedula(const char* cedulaBuscada);

#endif