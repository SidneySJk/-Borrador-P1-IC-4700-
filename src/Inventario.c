#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../headers/Inventario.h"
#include "../headers/Menu.h"


extern char* espacioDeMemoria();

Inventario CrearInventario() {
    Inventario inve;
    inve.codigoBuscado = malloc(MAX_CARACTERES*sizeof(char));
    inve.modificar = (int*)malloc(sizeof(int));
    return inve;
}


void leerTxt(Inventario *inve)
{
    printf("Leyendo modificaciones...\n");
    FILE *archi = fopen("../data/Modificaciones.txt","r+");
    if (!archi) {
        printf("No se pudo abrir %s\n", "Modificaciones.txt");
        return;
    }
   
    char *buffer = malloc(MAX_CARACTERES*sizeof(char));
    char *codigo =  malloc(MAX_CARACTERES*sizeof(char));
    char *cantidadModificar = malloc(MAX_CARACTERES*sizeof(char)); 
    char *copiaBuffer = buffer;
    char *puntero;
    int lineaLeida = 0;

    
    while (fgets(buffer, MAX_CARACTERES , archi)) { 
    
        
        //printf("-------------------\n");
        copiaBuffer = buffer;
        //printf("Buffer axtual: %s\n", copiaBuffer);
        //printf("-------------------\n");
        lineaLeida++;
        while ( *copiaBuffer != 0) {
            int indice = 0;
            //printf("%s\n", copiaBuffer);
            while ((*copiaBuffer != ',') && (*copiaBuffer != '\0')){

                codigo[indice] = *copiaBuffer;
                //printf("Caracter leido: %c\n", *copiaBuffer);
                
                indice++;
                copiaBuffer++;
                //printf("Se entro en el bucle de lectura del codigo\n");

            }
            codigo[indice] = '\0';
            strcpy(inve->codigoBuscado, codigo);

            printf("Codigo leido: %s\n", inve->codigoBuscado);
            if(*copiaBuffer ==',') copiaBuffer++;
            indice = 0;
            while ((*copiaBuffer != ',') && (*copiaBuffer != '\0')){
                cantidadModificar[indice] = *copiaBuffer;
                
                indice++;
                copiaBuffer++;
                //printf("Se entro en el otro bucle de lectura del codigo\n");
            }
            cantidadModificar[indice] = '\0';
            printf("Cantidad a modificar: %s\n", cantidadModificar);
            *(inve->modificar) = (int) strtol(cantidadModificar, &puntero, 10);
            actualizarCarga(inve);
        }
        
    }
    printf("Liberando memoria...\n");
        
    free(cantidadModificar);
    free(codigo);
    free(buffer);
    //free(copiaBuffer);
    
    
    fclose(archi);

    //LiberarMemoriaInventario(inve);
    menuAdministrativo();

}

//Retorna el nuevo stack o devuelve al menu
int modificarStock(int stock, Inventario *inve){
    printf("Desea sumar/restar del stock actual?\n1) Sumar\n2) Restar\n");
    int entrada;
    scanf("%d", &entrada);

    switch(entrada){
        
        case 1:{
            printf("Se sumara al stock actual\n");
            return stock + *inve->modificar;
            break;
        }   
        case 2:{
            printf("Se restara del stock actual\n");
            if ((stock - *inve->modificar) < 0) {
                printf("La cantidad a retirar es mayor al stock actual, desea retirar todo el stock?\n1) Si\n2) No\n");
                scanf("%d", &entrada);
                switch(entrada) {
                    case 1:{
                        return (stock - (*inve->modificar - ((stock - *inve->modificar) * -1)));
                    }
                    case 2:{
                        menuAdministrativo();
                    }
                }

            }
            return stock - *inve->modificar;
            break;
        } default:{
            printf("Entrada invalida, debe seguir el formato");
            menuAdministrativo();
        }
    }
    LiberarMemoriaInventario(inve);
    return 0;
}

//Tomar info de txt y actualizar el stock actual "Libros.txt"
void actualizarCarga(Inventario *inve){//(char *codigoBuscado, int *cantidadModificar){

    printf("Se actualizara el inventario\n");
    FILE *archi = fopen("../data/Libros.txt", "r");
    if (!archi) {
        printf("No se pudo abrir %s\n", "Libros.txt");
        fclose(archi);
        return;
    }

    FILE *temp = fopen("../data/Temp.txt", "w");
    if (!temp) {
        printf("No se pudo crear archivo temporal\n");
        fclose(temp);
        return;
    }

    char *_buffer = malloc(MAX_CARACTERES*sizeof(char));
    char *numModificado = malloc(MAX_CARACTERES*sizeof(char));
    char *nuevaLinea = malloc(MAX_CARACTERES*sizeof(char));
    char lineaCodigo[MAX_CARACTERES];
    sprintf(lineaCodigo, "Codigo: %s", inve->codigoBuscado);
    //printf("Linea: %s\n", lineaCodigo);
    
    //Boleanos
    bool encontrado = false; 
    bool copiar = true;

    while (fgets(_buffer, MAX_CARACTERES, archi)) {
       
        //printf("Ciclo while\n");
        //printf("Linea con codigo: %s\n", lineaCodigo);
        //printf("Buffer leido: %s\n", _buffer);
        //printf("--------------\n");
        if (strncmp(lineaCodigo,_buffer, strlen(lineaCodigo)) == 0){

            //printf("Comparar\n");
            //printf("Linea Codigo: %s\n", lineaCodigo);
            //printf("Buffer: %s\n", _buffer);

            encontrado = true;

            //printf("%d\n", encontrado);
        }
        
        //Si se encontro el codigo, buscar la linea de cantidad y modificarla
        if ((strncmp(_buffer, "Cantidad:", 9) == 0) && encontrado){
            //printf("Se esta reescribiendo la linea\n");
            copiar = false;
            char *token = strtok(_buffer, ": ");
            token = strtok(NULL, ": ");
            if (token != NULL){
         
                    int nuevoNum = modificarStock(atoi(token), inve);
                    //printf("Nuevo numero: %d\n", nuevoNum);
                    sprintf(numModificado, "%d", nuevoNum);
                    sprintf(nuevaLinea, "Cantidad: %s", numModificado);
                    //printf("Nueva linea: %s\n", nuevaLinea);
                    fputs(nuevaLinea, temp);
                    fputs("\n",temp);
                    encontrado = false;
                } else { 
                    printf("No pudo acceder a la cantidad\n");
                }

        } 

        if (copiar) {
                fputs(_buffer, temp);
        }
       
        copiar = true;
        
        
    }

    free(_buffer);
    free(numModificado);
    free(nuevaLinea);
    printf("Archivo actualizado correctamente.\n");
    fclose(archi);
    fclose(temp);
    
    if (remove("../data/Libros.txt") != 0 || rename("../data/Temp.txt", "../data/Libros.txt") != 0) {
        perror("Error al actualizar archivo");
        return;
    }
    
    LiberarMemoriaInventario(inve);
}


void iniciarActualizacionDeStock(){
   Inventario inve = CrearInventario();
   leerTxt(&inve);
}


void LiberarMemoriaInventario(Inventario *inve) {
    free(inve->codigoBuscado);
    free(inve->modificar);
    inve->codigoBuscado = NULL;
    inve->modificar = NULL;
}

