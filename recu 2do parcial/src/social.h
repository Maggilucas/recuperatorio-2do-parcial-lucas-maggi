/*
 * social.h
 *
 *  Created on: 7 dic. 2022
 *      Author: PC
 */

#ifndef SOCIAL_H_
#define SOCIAL_H_

#include "LinkedList.h"

typedef struct
{
	int id;
	char usuario[50];
	int likes;
	int dislikes;
	int seguidores;

}eRed;

eRed* red_new();

eRed* red_newParam(char* idStr, char* usuario, char* likes, char* dislikes , char* seguidores);
void red_delete(eRed* this);
////////////// SETTERS///////////////////////
int red_setId(eRed* this,int id);
int red_setUsuario(eRed* this,char* usuario);
int red_setLikes(eRed* this,int likes);
int red_setDislikes(eRed* this,int dislikes);
int red_setSeguidores(eRed* this,int seguidores);
/////////// GETTERS/////////////////////////
int red_getId(eRed* this,int* id);
int red_getUsuario(eRed* this,char* usuario);
int red_getLikes(eRed* this,int* likes);
int red_getDislikes(eRed* this,int* dislikes);
int red_getSeguidores(eRed* this,int* seguidores);

int mostrarRed(eRed* red);
int mostrarRedes(LinkedList* redes);

void* red_map (void* element);
int red_filterLikes(void* element);
int red_filterDislikes(void* element);
int red_filterSeguidores(void* element);
int red_sortSeguidores(void* a, void* b);


#endif /* SOCIAL_H_ */
