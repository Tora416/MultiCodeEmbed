

#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "utn.h"

int menu (int *opcionMenu)
{
    int error = -1;
    int opcion;
    if(opcionMenu != NULL)
    {
        

        printf("*** ABM Service de Notebooks ***\n\n");
        printf("1  Alta Notebook\n");
        printf("2  Modificar Notebook\n");
        printf("3  Baja Notebook\n");
        printf("4  Listar Notebook\n");
        printf("5  Listar Marcas\n");
        printf("6  Listar Tipos\n");
        printf("7  Listar Servicios\n");
        printf("8  Alta Trabajo\n");
        printf("9  Listar Trabajos\n");
        printf("10 Listar x Tipo\n");
        printf("11 Listar x Marca\n");
        printf("12 Contar x Marca y Tipo\n");
        printf("13 Listar Notebooks separadas x cada Marca\n");
        printf("14 Mostrar Marcas mas elegidas \n");
        printf("15 Mostrar Notebooks mas baratas \n");
        printf("16 Listar trabajos por ID notebook\n");
        printf("17 Listar total a pagar por ID notebook\n");
        printf("18 Mostrar Notebooks por Servicio\n");
        printf("19 Mostrar servicio por fecha\n");
        printf("20 Salir\n");

        if(!utn_getNumeroInt(&opcion,"\nIngrese la opcion deseada\n","Error, opcion invalida\n",1,20, 4))
        {

            *opcionMenu = opcion;
        }
        error = 0;

    }
    return error;
}
