

#include"servicio.h"
#include"utn.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int hardCodearServicios(eServicio listadoServicios[], int tamanioServicio)
{
    int error = -1;
    int idServicio [4]= {2000,2001,2002,2003};
    char servicio [4][25] = {"Bateria","Antivirus","Actualizacion","Fuente"};
    int precios[4] = {250,300,400,600};

    if(listadoServicios != NULL && tamanioServicio>0)
    {
        for(int i = 0; i<tamanioServicio; i++)
        {
            strcpy(listadoServicios[i].descripcion,servicio[i]);
            listadoServicios[i].precio = precios[i];
            listadoServicios[i].idServicio = idServicio[i];
        }
        error = 0;
    }
    return error;
}


void mostrarServicio(eServicio unServicio)
{
    printf("%4d     %10s         %3d\n",unServicio.idServicio,unServicio.descripcion,unServicio.precio);
}

int listarServicios(eServicio listaDeServicio[], int tamanioServicio)
{
    int error = -1;

    if(listaDeServicio !=NULL && tamanioServicio>0)
    {
        system("cls");
        printf("\n****  LISTADO DE SERVICIOS  ****\n");
        printf(" Id         Servicio        Precio\n");
        printf("----------------------------------\n");

        for(int i = 0 ; i<tamanioServicio; i++)
        {
            mostrarServicio(listaDeServicio[i]);
        }
        error = 0;
    }
    return error;
}

int getIdServicio(eServicio servicios[],int tam_s)
{
    int auxId;
    listarServicios(servicios,tam_s);

    utn_getNumeroInt(&auxId,"Ingrese id","Error, ingrese id valido",2000,2003,4);

    while(buscarServicios(servicios,tam_s,auxId) == -1)
    {
         utn_getNumeroInt(&auxId,"Ingrese un id valido","Error, ingrese id valido",2000,2003,4);
    }

    return auxId;
}
int buscarServicios(eServicio servicios[],int tam_s,int idServicio)
{
    int indice=-1;

    for(int i=0;i<tam_s;i++)
    {
        if(servicios[i].idServicio ==idServicio)
        {
            indice=i;
            break;
        }
    }
        return indice;
}
