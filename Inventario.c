#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Inventario.h"
#include "Operadores.c"
#include "Operadores.h"


Inventario CrearInventario() {
    Inventario inve;
    inve.codigoBuscado = NULL;
    inve.cantidadModificar= (int*)malloc(sizeof(int));
    return inve;
}


void leerTxt()
{
    FILE *archi = fopen("Modificaciones.txt","r+");
    char *buffer = espacioDeMemoria();
    char *codigoBuscado = espacioDeMemoria();
    char *cantidadModificar = espacioDeMemoria();
    char *puntero;
    
    while (archi != NULL) {//(fgets(buffer, espacioDeMemoria, archi) == 0) {
        fscanf(archi,"%s",buffer);
        
        
        while ( *buffer != 0) {
            int indice = 0;
            while ((*buffer != ',') && (*buffer != '\0')){
                codigoBuscado[indice] = *buffer;
                indice++;
                buffer++;
            }
            //char* cantidadModificar = strchr(linea,',');
            //str(codigoBuscado, linea, archi - linea);
            codigoBuscado[indice] = '\0';
            if(*buffer ==',') buffer++;
            indice = 0;
            while ((*buffer != ',') && (*buffer != '\0')){
                cantidadModificar[indice] = *buffer;
                indice++;
                buffer++;
            }
            codigoBuscado[indice] = '\0';
            int modificar = (int) strtol(cantidadModificar, &puntero, 10);
            actualizarCarga(codigoBuscado, &modificar);
        }
    }
}
//Tomar info de txt y actualizar el stock actual "Libros.txt"
void actualizarCarga(char *codigoBuscado, int *cantidadModificar){
    //int codigoBuscado;
    FILE *archi = fopen("Libros.txt", "r");
    if (!archi) {
        printf("No se pudo abrir %s\n", "Clientes.txt");
        return;
    }

    FILE *temp = fopen("Temp.txt", "w");
    if (!temp) {
        printf("No se pudo crear archivo temporal\n");
        fclose(archi);
        return;
    }

    //scanf("%d", *codigoBuscado);
    char *buffer = espacioDeMemoria();
    int linea;
    //linea con el codigo que se busca
    char strChar[3] = {codigoBuscado, '\0'};
    char lineaCodigo = str("Codigo: ", strChar);
    
    bool encontrado = false; 
    bool copiar = true;
    //int linea;
    //int modificar;
    
    while (fgets(buffer, sizeof(buffer), archi)) {
        linea++;
        if (strncmp(buffer, "Codigo:", 7) == 0) {
            
            if (lineaCodigo == buffer){
                bool encontrado = true;
            }

            if ((strncmp(buffer, "Cantidad:", 9) == 0) && encontrado){
                char *token = strtok(NULL, ": ");
                if (token != NULL){
                    int num = atoi(token);
                } else { 
                    printf{"No pudo acceder a la cantidad\n"};
                }

            }
            //fprintf(temp,"Codigo: ");
            //char cedulaArchivo[20]; 
            //sscanf(buffer, "Codigo: %19s", cantidadModificar);}}}
        }
    }
}

/**
    do{
        char buffer[100];
        for(int indice = 0; indice < 100; indice++)
            buffer[indice];
            buffer[0] = '\0';
        fgets(buffer, 100, archi);
        printf(buffer);
        if (strncmp(buffer, "Codigo:", 7) == 0) {
            if (strstr(buffer, codigoBuscado)) {  
                printf("Libro encontrado:\n");
                scanf('%s\n',buffer);
                //printf('%s\n', buffer[1]);
                //printf('%s\n',buffer[2]);
                //printf('%s\n',buffer[3]);
                printf("Desea sumar/restar del stock actual?\n(Formato: +#/-#):\n");
                char* entrada;
                canf("%f", entrada);
                encontrado = buffer[3];
                char* cantidad = strchar(encontrado,':');
                archi = ("Libros.txt", "w");
                if (entrada == '+') {
                    result = (cantidad-'0');
                    modificar = result + cantidadModificar;
                    
                } if (entrada == '-') {
                    result = (cantidad-'0');
                    //modificar = result - cantidadModificar;
                } else { 
                    printf("Entrada invalida, debe seguir el formato");
                    inventarioDePrograma();
                }
            }
        }
    }while(archi != NULL);
}
    
    while (feof(archi) == 0) {
        linea++;
        if (strncmp(buffer, "Codigo:", 7) == 0) {
            if (strstr(buffer, codigoBuscado)) {  
                printf("Libro encontrado:\n");
                printf(buffer[0], '\n');
                printf(buffer[1], '\n');
                printf(buffer[2], '\n');
                printf(buffer[3], '\n');
                printf("Desea sumar/restar del stock actual?\n(Formato: +#/-#):\n");
                char* entrada;
                canf("%f", entrada);
                encontrado = buffer[3];
                char* cantidad = strchar(encontrado,':');
                archi = ("Libros.txt", "w");
                if (entrada == '+') {
                    result = (cantidad-'0');
                    modificar = result + cantidadModificar;
                    
                } if (entrada == '-') {
                    result = (cantidad-'0');
                    //modificar = result - cantidadModificar;
                } else { 
                    printf("Entrada invalida, debe seguir el formato");
                    inventarioDePrograma();
                }

            } 
        }
    }
    */


void LiberarMemoriaInventario(Inventario *inve) {
    free(inve->codigoBuscado);
    free(inve->cantidadModificar);
    inve->codigoBuscado = NULL;
    inve->cantidadModificar = NULL;
}


