

#include"cliente.h"
#include "notebook.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int hardCodearClientes(eCliente listadoClientes[], int tamanioClientes)
{
    int error = -1;
    int id[10] ={1,2,3,4,5,6,7,8,9,10};
    char nombres [10][20] = {"Juan","Carlos","Martin","Lucas","Daniel","Ana","Julia","Daniela","Maria","Pedro"};
    char sexos [10] = {'m','m','m','m','m','f','f','f','f','m'};

    if(listadoClientes != NULL && tamanioClientes>0)
    {
        for(int i = 0; i<tamanioClientes; i++)
        {
            listadoClientes[i].idCliente = id[i];
            strcpy(listadoClientes[i].nombre,nombres[i]);
            listadoClientes[i].sexo = sexos[i];

        }
        error = 0;
    }
    return error;
}

void mostrarCliente(eCliente unCliente)
{
    printf("%d        %10s         %c\n",unCliente.idCliente,unCliente.nombre,unCliente.sexo);
}

int listarClientes(eCliente listadoDeClientes[], int tamanio)
{
    int error = -1;

    if(listadoDeClientes !=NULL && tamanio>0)
    {
        system("cls");
        printf("\n****  LISTADO DE CLIENTES  ****\n");
        printf(" Id             Nombre           Sexo\n");
        printf("----------------------------------\n");

        for(int i = 0 ; i<tamanio; i++)
        {
            listadoDeClientes[0].idCliente = 1;
            mostrarCliente(listadoDeClientes[i]);
        }
        error = 0;
    }
    return error;
}

int obtenerCliente(eCliente listaDeClientes[], int idCliente, int tamClientes, char nombreCliente [], char* sexoCliente)
{
    int error = -1;

    if(listaDeClientes != NULL && idCliente >0 && tamClientes >0 && nombreCliente != NULL)
    {
        for(int i = 0; i<tamClientes; i++)
        {
            if(idCliente == listaDeClientes[i].idCliente)
            {
                listaDeClientes[i].idCliente = idCliente;
                strcpy(nombreCliente,listaDeClientes[i].nombre);
                *sexoCliente = listaDeClientes[i].sexo;
                error = 0;
            }
        }
    }

    return error;
}

