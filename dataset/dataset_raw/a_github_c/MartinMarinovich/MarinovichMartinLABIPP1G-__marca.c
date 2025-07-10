


#include"marca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hardcodearMarcas(eMarca listaDeMarcas[], int tamanioMarcas)
{
    int error = -1;
    int id [4] = { 1000,1001,1002,1003};
    char marcas [4][20]= {
        "Compaq",
        "Asus",
        "Acer",
        "HP",
    };

    for(int i = 0; i<tamanioMarcas;i++)
    {
        strcpy(listaDeMarcas[i].descripcion,marcas[i]);
        listaDeMarcas[i].idMarca = id[i];
    }


    return error;
}

void mostrarMarca(eMarca unaMarca)
{
    printf("%4d  %10s \n",unaMarca.idMarca,unaMarca.descripcion);
}

int listarMarcas(eMarca listaDeMarcas[], int tamanio)
{
    int error = -1;

    if(listaDeMarcas !=NULL && tamanio>0)
    {
        system("cls");
        printf("\n****  LISTADO DE MARCAS  ****\n");
        printf(" Id       Descripcion\n");
        printf("----------------------------------\n");

        for(int i = 0 ; i<tamanio; i++)
        {
            mostrarMarca(listaDeMarcas[i]);
        }
        error = 0;
    }
    return error;
}
