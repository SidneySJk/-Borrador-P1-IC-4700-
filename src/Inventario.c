#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Inventario.h"//"../headers/Inventario.h"
//#include "Operadores.c"
//#include "Operadores.h"
//#include "Consola.c"
//#include "Consola.h"
#include "Menu.h"


//extern char* espacioDeMemoria();

Inventario CrearInventario() {
    Inventario inve;
    inve.codigoBuscado = malloc(236*sizeof(char));
    inve.modificar = (int*)malloc(sizeof(int));
    return inve;
}


void leerTxt(Inventario *inve)
{
    FILE *archi = fopen("Modificaciones.txt","r+");
    char *buffer = malloc(236*sizeof(char));//espacioDeMemoria();
    //char *codigoBuscado =  malloc(236*sizeof(char));
    char *cantidadModificar = malloc(236*sizeof(char));;
    char *puntero;
    
    while (fgets(buffer, sizeof(buffer), archi)) { //(archi != NULL) {
        fscanf(archi,"%s",buffer);
        
        
        while ( *buffer != 0) {
            int indice = 0;
            while ((*buffer != ',') && (*buffer != '\0')){
                inve->codigoBuscado[indice] = *buffer;
                indice++;
                buffer++;
            }
            //char* cantidadModificar = strchr(linea,',');
            //str(codigoBuscado, linea, archi - linea);
            inve->codigoBuscado[indice] = '\0';
            if(*buffer ==',') buffer++;
            indice = 0;
            while ((*buffer != ',') && (*buffer != '\0')){
                cantidadModificar[indice] = *buffer;
                indice++;
                buffer++;
            }
            inve->codigoBuscado[indice] = '\0';
            *(inve->modificar) = (int) strtol(cantidadModificar, &puntero, 10);
            actualizarCarga(inve);//->codigoBuscado, &inve->modificar);
            
        }
    }
    free(buffer);
    free(cantidadModificar );
    //LiberarMemoriaInventario(inve);

}

//Retorna el nuevo stack o devuelve al menu
int modifcarStock(int stock, Inventario *inve){
    printf("Desea sumar/restar del stock actual?\n1) Sumar\n2) Restar\n");
    int entrada;
    scanf("%d", &entrada);

    switch(entrada){
        case 1:{
            return stock + *inve->modificar;
            break;
        }   
        case 2:{
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
                //return (stock - (*inve->modificar - ((stock - *inve->modificar) * -1)));
            }
            return stock - *inve->modificar;
            break;
        } default:{
            printf("Entrada invalida, debe seguir el formato");
            menuAdministrativo();
        }
    }
}

//Tomar info de txt y actualizar el stock actual "Libros.txt"
void actualizarCarga(Inventario *inve){//(char *codigoBuscado, int *cantidadModificar){
    //int codigoBuscado;
    FILE *archi = fopen("Modificaciones.txt", "r");
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
    // Guardar linea
    char *buffer = malloc(236*sizeof(char));//espacioDeMemoria();
    char *numModificado = malloc(236*sizeof(char));
    char *nuevaLinea;
    
    //linea con el codigo que se busca
    char strChar[3] = {*inve->codigoBuscado, '\0'};
    char *lineaCodigo = strcat("Codigo: ", strChar);
    
    //Boleanos
    bool encontrado = false; 
    bool copiar = true;
    //char *NuevaLinea;
    //int modificar;
    
    while (fgets(buffer, sizeof(buffer), archi)) {
        
        if (strncmp(buffer, "Codigo:", 7) == 0) {
            
            if (strcmp(lineaCodigo,buffer) == 0){
                encontrado = true;
            }
        }

        if ((strncmp(buffer, "Cantidad:", 9) == 0) && encontrado){
            copiar = false;
            char *token = strtok(NULL, ": ");
            if (token != NULL){
                    int nuevoNum = modifcarStock(atoi(token), inve);
                    sprintf(numModificado, "%d", nuevoNum);
                    nuevaLinea = strcat("Cantidad: ", numModificado);//nuevoNum);//, token);
                    fputs(nuevaLinea, temp);
                    fputs("\n",temp);
                    copiar = true;
                    encontrado = false;
                } else { 
                    printf("No pudo acceder a la cantidad\n");
                }

            }
            //fprintf(temp,"Codigo: ");
            //char cedulaArchivo[20]; 
            //sscanf(buffer, "Codigo: %19s", cantidadModificar);}}}
        
        if (copiar) {
                fputs(buffer, temp);
        }
    }

    fclose(archi);
    fclose(temp);


    if (remove("Modificaciones.txt") != 0 || rename("Temp.txt", "Modificaciones.txt") != 0) {
        perror("Error al actualizar archivo");
        return;
    }

    LiberarMemoriaInventario(inve);
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
    free(inve->modificar);
    inve->codigoBuscado = NULL;
    inve->modificar = NULL;
}


