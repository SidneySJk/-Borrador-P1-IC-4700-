#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../headers/Pedido.h"

#define ARCHIVO_CLIENTES "data/Clientes.txt"

typedef struct {
    char *cedula;
    char *nombre;
    char *telefono;
} Cliente;

Cliente CrearCliente();
void registrarCliente();
bool validarCedulaUnica(const char* cedula);
bool validarTelefono(const char* telefono);
void guardarClienteEnTXT(Cliente *cli);
void liberarMemoriaCliente(Cliente *cli);
void eliminarCliente(const char* cedulaBuscada);
void mostrarCliente(const char* cedulaBuscada);
void consultarClientePorCedula();
char* solicitarCedula();

#endif