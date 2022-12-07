#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "LinkedList.h"
#include "parser.h"
#include "social.h"
#include "controller.h"
#include "menus.h"

int menu()
{
    int opcion;
    system("cls");
    printf("1.Cargar archivo.\n");
    printf("2.Imprimir Lista\n");
    printf("3.Asignar likes dislikes y seguidores.\n");
    printf("4.Filtrar por likes.\n");
    printf("5.filtrar por haters.\n");
    printf("6.ordenar por seguidores\n");
    printf("7.mostrar mas popular\n");
    printf("8.Salir\n");
    printf("Ingrese opcion: ");
    fflush(stdin);
    scanf("%d",&opcion);
    return opcion;
}
