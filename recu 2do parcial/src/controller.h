/*
 * controller.h
 *
 *  Created on: 29 nov. 2022
 *      Author: PC
 */

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

int controller_loadFile(char* path,LinkedList* movieList);
int controller_saveFile(char* path,LinkedList* movieList);
int controller_printList(LinkedList* movieList);
int controller_setMap(LinkedList* movieList,LinkedList** movieListRating);
int controller_filterLikes(LinkedList* movieList);
int controller_filterDislikes(LinkedList* movieList);
int controller_sortRedes(LinkedList* movieList);
int controller_mostrarMasPopular(LinkedList* redList);

#endif /* CONTROLLER_H_ */
