


#include"tipo.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hardCodearTipos(eTipo listadoDeTipos[], int tamanioTipos)
{
    int error = -1;
    int id [4] = {5000,5001,5002,5003};
    char colores [4][20]= {
        "Gamer",
        "Disenio",
        "Ultrabook",
        "Normalita",
    };

    for(int i = 0; i<tamanioTipos;i++)
    {
        strcpy(listadoDeTipos[i].descripcion,colores[i]);
        listadoDeTipos[i].idTipo = id[i];
    }


    return error;
}

void mostrarTipo(eTipo unTipo)
{
    printf(" %d         %s \n",unTipo.idTipo,unTipo.descripcion);
}

int listarTipos(eTipo listaDetipos[], int tamanioTipos)
{
    int error = -1;

    if(listaDetipos !=NULL && tamanioTipos>0)
    {
        system("cls");
        printf(" ****  LISTADO DE TIPOS  ****\n");
        printf("Id        Descripcion\n");
        printf("----------------------------------\n");

        for(int i = 0 ; i<tamanioTipos; i++)
        {
            mostrarTipo(listaDetipos[i]);
        }
        error = 0;
    }
    return error;
}
