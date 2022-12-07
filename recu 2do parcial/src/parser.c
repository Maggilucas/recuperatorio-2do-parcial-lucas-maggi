#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "LinkedList.h"
#include "parser.h"
#include "social.h"

/** \brief Parsea los datos de los jugadores desde el archivo jugadores.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListJugador LinkedList*
 * \return int
 */
int parser_loadFile(FILE* pFile, LinkedList* movieList)
{
	int todoOk = 0;
	eRed* redes;
	char id[30];
	char usuario[100];
	char likes[30];
	char dislikes[30];
	char seguidores[30];

	if(movieList != NULL)
	{
		fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n", id, usuario, likes, dislikes,seguidores);
		do
		{
			if(fscanf(pFile,"%[^,],%[^,],%[^,],%[^,],%[^\n]\n", id, usuario, likes, dislikes,seguidores)== 5)
			{
				redes = red_newParam(id, usuario, likes, dislikes, seguidores);

				if(redes != NULL)
				{
					ll_add(movieList, redes);
					todoOk = 1;
				}
			}

		}while(!feof(pFile));
	}

	return todoOk;
}
int parser_saveFile(FILE* pFile, LinkedList* movieList)
{
    int retorno = 0;
    char encabezado [50]="id,usuario,likes,dislikes,seguidores\n";
    int len;
    eRed* auxRed = NULL;
    int id;
    char usuario[50];
    int likes;
    int dislikes;
    int seguidores;
    if (pFile != NULL && movieList != NULL)
    {
        fprintf(pFile,encabezado);
        len = ll_len(movieList);
        for (int i = 0; i < len; i++)
        {
        	auxRed = (eRed*)ll_get(movieList,i);
            if((red_getId(auxRed,&id) && red_getUsuario(auxRed,usuario) && red_getLikes(auxRed,&likes) && red_getDislikes(auxRed,&dislikes) && red_getSeguidores(auxRed,&seguidores)))
            {
                fprintf(pFile,"%d,%s,%d,%d,%d\n",id,usuario,likes,dislikes,seguidores);
                retorno ++;
            }
            else
            {
                printf("Hubo algun error en la carga de informacion");
                break;
            }
        }
    }
    return retorno;
}
