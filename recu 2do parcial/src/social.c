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

eRed* red_new()
{
	return (eRed*) malloc(sizeof(eRed));
}

eRed* red_newParam(char* idStr, char* usuario, char* likes, char* dislikes , char* seguidores)
{

	eRed* red;
	int todoOk=0;
	red = red_new();

	if(red!=NULL)
	{
		if(red_setId(red, atoi(idStr)) == 1)
		{
			if(red_setUsuario(red, usuario) == 1)
			{
				if(red_setLikes(red,atoi(likes))== 1)
				{
					if(red_setDislikes(red,atoi(dislikes))== 1)
					{
						if(red_setSeguidores(red,atoi(seguidores))== 1)
						{
							todoOk=1;
						}
					}
				}
			}
		}
	}

	if(todoOk != 1)
	{
		red= NULL;
	}

		return red;
}


void red_delete(eRed* this)
{
	if(this != NULL)
	{
		free(this);
	}
}

////////////// SETTERS///////////////////////
int red_setId(eRed* this,int id)
{
	int retorno = -1;

		if(this != NULL && id > 0)
		{
			this->id = id;
			retorno = 1;
		}

		return retorno;
}
int red_setUsuario(eRed* this,char* usuario)
{
	int retorno = -1;

	if(this != NULL && usuario != NULL)
	{
		strcpy(this->usuario, usuario);
		retorno = 1;
	}

	return retorno;
}
int red_setLikes(eRed* this,int likes)
{
	int retorno = -1;

	if(this != NULL)
	{
		this->likes = likes;
		retorno = 1;
	}

	return retorno;
}
int red_setDislikes(eRed* this,int dislikes)
{
	int retorno = -1;

	if(this != NULL && dislikes >= 0)
	{
		this->dislikes = dislikes;
		retorno = 1;
	}

	return retorno;
}
int red_setSeguidores(eRed* this,int seguidores)
{
	int retorno = -1;

	if(this != NULL && seguidores >= 0)
	{
		this->seguidores = seguidores;
		retorno = 1;
	}

	return retorno;
}
/////////// GETTERS/////////////////////////
int red_getId(eRed* this,int* id)
{
	int retorno = -1;

	if(this != NULL && id != NULL)
	{
		*id = this->id;
		retorno = 1;
	}

	return retorno;
}
int red_getUsuario(eRed* this,char* usuario)
{
	int retorno = -1;

	if(this != NULL && usuario != NULL)
	{
		strcpy(usuario,this->usuario);
		retorno = 1;
	}

	return retorno;
}
int red_getLikes(eRed* this,int* likes)
{
	int retorno = -1;

	if(this != NULL && likes != NULL)
	{
		*likes = this->likes;
		retorno = 1;
	}

	return retorno;
}
int red_getDislikes(eRed* this,int* dislikes)
{
	int retorno = -1;

	if(this != NULL && dislikes != NULL)
	{
		*dislikes = this->dislikes;
		retorno = 1;
	}

	return retorno;
}
int red_getSeguidores(eRed* this,int* seguidores)
{
	int retorno = -1;

	if(this != NULL && seguidores != NULL)
	{
		*seguidores = this->seguidores;
		retorno = 1;
	}

	return retorno;
}


int mostrarRed(eRed* red)
{
    int retorno = 0;
    if (red != NULL)
    {
        printf("%4d %30s                 %d        %d                 %d\n",red->id,red->usuario,red->likes,red->dislikes,red->seguidores);
        retorno = 1;
    }
    return retorno;
}

int mostrarRedes(LinkedList* redes)
{
	eRed* auxRed = NULL;
    int retorno = 0;
    int len;
    if(redes != NULL)
    {
		len = ll_len(redes);
        printf("  ID                    NOMBRE                  LIKES       DISLIKES        SEGUIDORES\n");
        printf("--------------------------------------------------------------------------------------\n");
        for (int i = 0; i < len; i++)
        {
        	auxRed = (eRed*)ll_get(redes,i);
            if(mostrarRed(auxRed)== 1)
            {
                retorno++;
            }
        }
        auxRed = NULL;
    }
    return retorno;
}

void* red_map (void* element)//asigna elementos aleatorios
{
    void* retorno = element;
    eRed* auxElement = NULL;
    eRed* auxNewRed = NULL;
    int likesRandow;
    int dislikesRandow;
    int seguidoresRandow;
    auxNewRed = red_new();
    if (auxNewRed != NULL)
    {
        auxElement = (eRed*)element;
        *auxNewRed = *auxElement;
        do
        {
        	likesRandow = rand();
        }
        while(likesRandow < 600 || likesRandow >5000);
        do
		{
			dislikesRandow = rand();
		}
        while (dislikesRandow < 300 || dislikesRandow > 3500);
        do
		{
			seguidoresRandow = rand();
		}
		while (seguidoresRandow < 10000 || seguidoresRandow > 20000);

        red_setLikes(auxNewRed,likesRandow);
        red_setDislikes(auxNewRed,dislikesRandow);
        red_setSeguidores(auxNewRed,seguidoresRandow);
        retorno = auxNewRed;
    }

    return retorno;
}

//filter
int red_filterLikes(void* element)
{
    int retorno = 0;
    eRed* auxRed = NULL;
    if (element != NULL)
    {
    	auxRed = (eRed*) element;
        if(auxRed->likes >= 4000)
        {
            retorno = 1;
        }
    }
    return retorno;
}
int red_filterDislikes(void* element)
{
    int retorno = 0;
    eRed* auxRed = NULL;
    if (element != NULL)
    {
    	auxRed = (eRed*) element;
        if(auxRed->likes < auxRed->dislikes)
        {
            retorno = 1;
        }
    }
    return retorno;
}

int red_filterSeguidores(void* element)
{
    int retorno = 0;
    eRed* auxRed = NULL;
    eRed* auxRed2 = NULL;

    if (element != NULL)
    {
    	auxRed = (eRed*) element;
    	auxRed2 = (eRed*) element;
        if(auxRed->likes >= auxRed2->likes)
        {
            retorno = 1;
        }
    }
    return retorno;
}


//sort
int red_sortSeguidores(void* a, void* b)
{
    int retorno = 0;
    eRed* redA;
    eRed* redB;
    if (a != NULL && b != NULL)
    {
    	redA = (eRed*)a;
    	redB = (eRed*)b;
      if(redA->seguidores<redB->seguidores)
      {
          retorno = 1;
      }
    }
    return retorno;
}
