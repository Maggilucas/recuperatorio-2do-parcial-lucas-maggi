#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "menus.h"
#include "LinkedList.h"
#include "parser.h"
#include "social.h"
#include "controller.h"

int controller_loadFile(char* path,LinkedList* movieList)
{
	int todoOk = -1;
	FILE* pArchivo;

	if(path!=NULL && movieList!=NULL)
	{
		pArchivo = fopen(path,"r");

		if(pArchivo!= NULL && path != NULL)
		{
			if(parser_loadFile(pArchivo, movieList)== 1)
			{
				printf("Se cargo con exito\n");
				todoOk=1;
			}
		}
		else
		{
			printf("Error al abrir el archivo\n");
		}
		fclose(pArchivo);
	}
	return todoOk;
}

int controller_saveFile(char* path,LinkedList* movieList)
{
    int retorno = 0;
    int saveOk = 0;
    FILE* f = NULL;
    if(path != NULL && movieList != NULL)
    {
        f = fopen(path,"w");
        if (f != NULL)
        {
            saveOk = parser_saveFile(f,movieList);
            if (saveOk >0)
            {
                printf("Se guardaron correctamente %d redes\n",saveOk);
            }
        }
        fclose(f);
    }
    return retorno;
}
int controller_printList(LinkedList* movieList)
{
    int retorno = 0;
    int showOk = 0;
    if (movieList != NULL)
    {
        showOk = mostrarRedes(movieList);
        if(showOk > 0)
        {
            printf("\n\nSe mostraron un total de %d redes.\n",showOk);
            retorno = 1;
        }
    }
    return retorno;
}
int controller_setMap(LinkedList* movieList,LinkedList** movieListRating)
{
    int retorno = 0;
    LinkedList* aux;
    if (movieList != NULL && movieListRating != NULL)
    {
        *movieListRating = ll_map(movieList,red_map);
        mostrarRedes(*movieListRating);
    	aux= ll_clone(*movieListRating);
    	movieList=aux;
    	ll_deleteLinkedList(aux);
        retorno = 1;
    }
    return retorno;
}
int controller_filterLikes(LinkedList* movieList)
{
    int retorno = 0;
    LinkedList* aux;


    if (movieList != NULL)
    {
		aux= ll_clone(movieList);
		aux= ll_filter(aux,red_filterLikes);
		controller_saveFile("mejores post.csv",aux);
		mostrarRedes(aux);
    }
    return retorno;
}
int controller_filterDislikes(LinkedList* movieList)
{
    int retorno = 0;
    LinkedList* aux;


    if (movieList != NULL)
    {
		aux= ll_clone(movieList);
		aux= ll_filter(aux,red_filterDislikes);
		controller_saveFile("malos post.csv",aux);
		mostrarRedes(aux);
    }
    return retorno;
}

int controller_sortRedes(LinkedList* movieList)
{
    int retorno = 0;
    if (movieList != NULL)
    {
        if(ll_sort(movieList,red_sortSeguidores,1) == 0)
        {
        	mostrarRedes(movieList);
            retorno = 1;
        }
    }
    return retorno;
}

int controller_mostrarMasPopular(LinkedList* redList)
{
	eRed* auxRed = NULL;
	int retorno = 0;
	int len;
	LinkedList* aux;

	aux= ll_clone(redList);
	aux= ll_filter(aux,red_filterLikes);
	len = ll_len(aux);
	for(int i = 0; i < len; i++)
	{
		auxRed = (eRed*)ll_get(aux,i);
		if(mostrarRed(auxRed)== 1)
		{
			retorno++;
		}
	}

	return retorno;
}
