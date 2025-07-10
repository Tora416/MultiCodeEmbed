

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "notebook.h"
#include "marca.h"
#include "tipo.h"
#include "servicio.h"
#include "trabajo.h"
#include "utn.h"
#include "menu.h"

#define TAM_NOTEBOOKS 10
#define TAM_MARCAS 4
#define TAM_TIPOS 4
#define TAM_SERVICIOS 4
#define TAM_TRABAJOS 20
#define TAM_CLIENTES 10


int main()
{


    eNotebook listaDeNotebooks[TAM_NOTEBOOKS];
    eMarca listadoDeMarcas[TAM_MARCAS];
    eTrabajo listadoDeTrabajos[TAM_TRABAJOS];
    eTipo listadoDeTipos[TAM_TIPOS];
    eServicio listadoDeServicios [TAM_SERVICIOS];
    eCliente listadoDeClientes [TAM_CLIENTES];

    int proximoIdTrabajo = 100;
    int proximoIdNotebook = 1;
    int auxModificacion;
    int auxBaja;
    int opcionMenu;

    if(!inicializarNotebook(listaDeNotebooks,TAM_NOTEBOOKS) && !inicializarTrabajo(listadoDeTrabajos,TAM_TRABAJOS))
    {
        printf("Sistema inicializado con exito!\n\n");
    }else
    {
        printf("Problema para inicializar el sistema\n");
    }


    hardCodearTipos(listadoDeTipos,TAM_TIPOS);
    hardcodearMarcas(listadoDeMarcas,TAM_MARCAS);
    hardCodearServicios(listadoDeServicios,TAM_SERVICIOS);
    hardCodearClientes(listadoDeClientes,TAM_NOTEBOOKS);
    hardCodearTrabajos(listadoDeTrabajos,TAM_NOTEBOOKS);




    do
    {
        menu(&opcionMenu);

        switch(opcionMenu)
        {
            case 1:

                if(!altaNotebook(listaDeNotebooks,listadoDeClientes,listadoDeMarcas,listadoDeTipos,TAM_NOTEBOOKS,TAM_CLIENTES,proximoIdNotebook,TAM_TIPOS,TAM_MARCAS))
                {
                    proximoIdNotebook++;
                    printf("ALTA EXITOSA!\n");
                }
                else
                {
                    printf("Problema para realizar el alta\n");
                }

            break;
            case 2:
                if(verificarExistenciaNotebook(listaDeNotebooks,TAM_NOTEBOOKS)==0)
                {
                    auxModificacion = modificarNotebook(listaDeNotebooks,listadoDeMarcas,listadoDeTipos,listadoDeClientes,TAM_CLIENTES,TAM_NOTEBOOKS,TAM_MARCAS,TAM_TIPOS);

                    if( auxModificacion == 0)
                    {
                        printf("Modificacion exitosa\n");
                    }
                    else if(auxModificacion == 2)
                    {
                        printf("La modificacion ha sido cancelada por usuario\n");
                    }
                    else
                    {
                        printf("Se ha producido un error en la modificacion\n");
                    }

                }else
                {
                    printf("No hay notebooks en el listado\n");
                }
            break;

            case 3 :
                if(verificarExistenciaNotebook(listaDeNotebooks,TAM_NOTEBOOKS)==0)
                {
                    auxBaja = bajaNotebook(listaDeNotebooks,listadoDeMarcas,listadoDeTipos,listadoDeClientes,TAM_CLIENTES,TAM_NOTEBOOKS,TAM_TIPOS,TAM_MARCAS);

                    if( auxBaja == 0)
                    {
                        printf("Modificacion exitosa\n");
                    }
                    else if(auxBaja == 2)
                    {
                        printf("La baja ha sido cancelada por usuario\n");
                    }
                    else
                    {
                        printf("Se ha producido un error en la baja\n");
                    }

                }else
                {
                    printf("No hay notebooks en la lista\n");
                }

            break;

            case 4:
                if(!verificarExistenciaNotebook(listaDeNotebooks,TAM_NOTEBOOKS))
                {
                    ordenarNotebooks(listaDeNotebooks,TAM_NOTEBOOKS);
                    listarNotebook(listaDeNotebooks, listadoDeMarcas,listadoDeClientes,listadoDeTipos,TAM_CLIENTES,TAM_NOTEBOOKS,TAM_MARCAS,TAM_TIPOS);


                }else
                {
                    printf("No hay notebooks en la lista\n");
                }

            break;

            case 5:
                system("cls");
                listarMarcas(listadoDeMarcas,TAM_MARCAS);
            break;

            case 6:
                system("cls");
                listarTipos(listadoDeTipos,TAM_TIPOS);

            break;

            case 7:
                system("cls");
                listarServicios(listadoDeServicios,TAM_SERVICIOS);
            break;

            case 8:
                if(!verificarExistenciaNotebook(listaDeNotebooks,TAM_NOTEBOOKS))
                {
                    if(altaTrabajo(listaDeNotebooks,listadoDeTrabajos,listadoDeServicios,listadoDeMarcas,listadoDeTipos,listadoDeClientes,TAM_CLIENTES,
                            TAM_NOTEBOOKS,TAM_TRABAJOS,TAM_SERVICIOS,TAM_TIPOS,TAM_MARCAS,proximoIdTrabajo)==0)
                    {
                        proximoIdTrabajo++;
                        printf("ALTA TRABAJO EXITOSA!\n");
                    }else
                    {
                        printf("Se produjo un error al ingresa el trabajo\n");
                    }

                }else
                {
                    printf("No hay notebooks en la lista, no se puede ingresar trabajo\n");
                }

            break;

            case 9:
                if(!verificarExistenciaNotebook(listaDeNotebooks,TAM_NOTEBOOKS) &&
                    !verificarExistenciaTrabajo(listadoDeTrabajos,TAM_TRABAJOS))
                {
                    system("cls");
                    listarTrabajos(listadoDeTrabajos,listaDeNotebooks,listadoDeServicios,TAM_NOTEBOOKS,TAM_TRABAJOS,TAM_SERVICIOS);

                }else
                {
                    printf("No se ingresaron trabajos o notebooks\n");
                }

            break;

            case 10:
                system("cls");
                if(verificarExistenciaNotebook(listaDeNotebooks,TAM_NOTEBOOKS)==0)
                {

                    listarPorTipo(listaDeNotebooks,TAM_NOTEBOOKS,listadoDeMarcas,listadoDeClientes,TAM_CLIENTES,TAM_MARCAS,listadoDeTipos,TAM_TIPOS);

                }else
                {
                    printf("No hay notebooks en la lista\n");
                }
            break;

            case 11:
                system("cls");
                if(verificarExistenciaNotebook(listaDeNotebooks,TAM_NOTEBOOKS)==0)
                {

                    listarPorMarca(listaDeNotebooks,listadoDeClientes,TAM_CLIENTES,TAM_NOTEBOOKS,listadoDeMarcas,listadoDeTipos,TAM_MARCAS,TAM_TIPOS);

                }else
                {
                    printf("No hay notebooks en la lista\n");
                }
            break;

            case 12:
                if(!verificarExistenciaNotebook(listaDeNotebooks,TAM_NOTEBOOKS))
                {
                    contarNotebooksMarcaYTipo(listaDeNotebooks, TAM_NOTEBOOKS,listadoDeMarcas,TAM_MARCAS,listadoDeClientes, TAM_CLIENTES, listadoDeTipos, TAM_TIPOS);
                }
            break;

            case 13:
                if(verificarExistenciaNotebook(listaDeNotebooks,TAM_NOTEBOOKS)==0)
                {
                    system("cls");
                    listarNotebookXCadaMarca(listaDeNotebooks,listadoDeClientes,TAM_CLIENTES,TAM_NOTEBOOKS,listadoDeMarcas,listadoDeTipos,TAM_TIPOS,TAM_MARCAS);

                }else
                {
                    printf("No hay notebooks en la lista\n");
                }

            break;

            case 14:
                if(verificarExistenciaNotebook(listaDeNotebooks,TAM_NOTEBOOKS)==0)
                {
                    system("cls");
                    marcaFavorita(listaDeNotebooks,TAM_NOTEBOOKS,listadoDeMarcas,listadoDeTipos,TAM_MARCAS);
                }else
                {
                    printf("No hay notebooks en la lista\n");
                }

            break;

            case 15:
                if(verificarExistenciaNotebook(listaDeNotebooks,TAM_NOTEBOOKS)==0)
                {
                    system("cls");
                    notebookMasBarata(listaDeNotebooks,TAM_NOTEBOOKS,listadoDeMarcas,listadoDeTipos,listadoDeClientes,TAM_CLIENTES,TAM_TIPOS,TAM_MARCAS);

                }else
                {
                    printf("No hay notebooks en la lista\n");
                }

            break;

            case 16:
                if(!verificarExistenciaNotebook(listaDeNotebooks,TAM_NOTEBOOKS) && !verificarExistenciaTrabajo(listadoDeTrabajos, TAM_TRABAJOS))
                {
                    listarTrabajosXNotebook(listadoDeTrabajos,listaDeNotebooks,listadoDeClientes,listadoDeMarcas,listadoDeTipos,listadoDeServicios,TAM_CLIENTES,TAM_NOTEBOOKS,TAM_TRABAJOS,TAM_SERVICIOS,TAM_MARCAS,TAM_TIPOS);

                }
            break;
            case 17:
                if(!verificarExistenciaNotebook(listaDeNotebooks,TAM_NOTEBOOKS) && !verificarExistenciaTrabajo(listadoDeTrabajos, TAM_TRABAJOS))
                {
                    mostrarSumaDeImportesXNotebook(listadoDeServicios, TAM_SERVICIOS, listadoDeTrabajos, listaDeNotebooks, TAM_NOTEBOOKS, listadoDeMarcas, listadoDeTipos, listadoDeClientes, TAM_CLIENTES, TAM_TIPOS, TAM_MARCAS, TAM_TRABAJOS);
                }else
                {
                    printf("No hay notebooks o trabajos cargados\n");
                }
            break;

            case 18:

                 if(!verificarExistenciaNotebook(listaDeNotebooks,TAM_NOTEBOOKS) && !verificarExistenciaTrabajo(listadoDeTrabajos, TAM_TRABAJOS))
                {
                    mostrarFechaYNotebookXServicio(listadoDeClientes,listadoDeTrabajos,TAM_TRABAJOS,listadoDeServicios,TAM_SERVICIOS,listaDeNotebooks,TAM_NOTEBOOKS,listadoDeMarcas,TAM_MARCAS,listadoDeTipos,TAM_TIPOS,TAM_CLIENTES);

                }else
                {
                    printf("No hay notebooks o trabajos cargados\n");
                }

            break;

            case 19:

                if(!verificarExistenciaNotebook(listaDeNotebooks,TAM_NOTEBOOKS) && !verificarExistenciaTrabajo(listadoDeTrabajos, TAM_TRABAJOS))
                {
                    mostrarServiciosXFecha(listadoDeTrabajos,TAM_TRABAJOS,listadoDeServicios,TAM_SERVICIOS);
                }else
                {
                    printf("No hay notebooks o trabajos cargados\n");
                }

            break;

        }

    }while(opcionMenu != 20);

    return 0;
}


