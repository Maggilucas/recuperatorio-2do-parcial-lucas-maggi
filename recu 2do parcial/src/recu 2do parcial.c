/*
 ============================================================================
 Name        : practica.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "LinkedList.h"
#include "parser.h"
#include "social.h"
#include "controller.h"
#include "menus.h"
#include "time.h"


int main()
{
	setbuf(stdout,NULL);
	setbuf(stdin,NULL);
    //flags
    int flagLoad = 0;
    int flagCarga = 0;
    //rand
    srand(time(NULL));
  //  char path[50];
    //linkedList y punteros a linkedList
    LinkedList* redList = ll_newLinkedList();
    if (redList == NULL)
    {
        printf("No se consiguio memoria.\n");
        exit(1);
    }
    LinkedList* redListCompleta = NULL;

    int seguir = 1;
    do
    {
        switch(menu())
        {
        case 1:

            if(controller_loadFile("posts.csv",redList) == 1 && flagLoad == 0)
            {
                printf("archivo posts.csv cargado con exito \n");
                flagLoad = 1;
            }
            else
            {
                printf("Ya se realiazo la carga.\n");
            }
            break;
        case 2:
            if (flagLoad)
            {
                controller_printList(redList);
            }
            else
            {
                printf("Primero se debe realizar la carga (opcion 1)\n");
            }
            break;
        case 3:
            if (flagLoad && !flagCarga)
            {
            	controller_setMap(redList,&redListCompleta);
            	flagCarga = 1;
            }
            else
            {
                printf("Primero se debe realizar la carga (opcion 1) o bien la duracion ya fue asignada.\n");
            }

            break;
        case 4:
            if(flagLoad == 1 &&  flagCarga==1)
            {
               controller_filterLikes(redListCompleta);
               printf("filtrado realizado con exito \n");
            }
            else
            {
                printf("error en la filtracion \n");
            }
            break;
        case 5:
            if (flagLoad == 1 &&  flagCarga==1)
            {
            	controller_filterDislikes(redListCompleta);
            	printf("filtrado realizado con exito \n");
            }
            else
            {
            	printf("error en la filtracion \n");
            }
            break;
        case 6:
        	if(flagLoad == 1 &&  flagCarga==1)
        	{
        		controller_sortRedes(redListCompleta);
        	}
        	else
        	{
        		printf("error en el sort");
        	}
        	break;
        case 7:
            if (flagLoad == 1 &&  flagCarga==1)
            {
            	controller_mostrarMasPopular(redListCompleta);
            }
            else
            {
                printf("error al buscar el mas popular\n");
            }

            break;
        case 8:
            seguir = 0;
            ll_deleteLinkedList(redList);
            ll_deleteLinkedList(redListCompleta);
            break;
        default:
            printf("Opcion invalida.\n");
            break;
        }
        system("pause");
    }
    while(seguir == 1);

    return 0;
}
