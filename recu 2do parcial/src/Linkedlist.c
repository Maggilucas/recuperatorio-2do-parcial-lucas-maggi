#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "LinkedList.h"


static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
	LinkedList* this = NULL;

	this = (LinkedList*) malloc(sizeof(LinkedList));

	if(this != NULL)
	{
		this->size = 0;//inicio el tama�o en cero
		this->pFirstNode = NULL;//apunto al final de la lista NULL
	}

	    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
	int returnAux = -1;

	if(this != NULL)
	{
		returnAux = this->size;//devuelvo el tama�o
	}

	return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pNode) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
	Node* pNode = NULL;
	int i;

	if(this != NULL && nodeIndex >= 0 && nodeIndex < ll_len(this))//verifico que no sea NULL la lista y que el index no sea menor a cero
	{
		pNode = this->pFirstNode;//le asigno el primer nodo para recorrer en busca del que pide

		for(i=0; i<nodeIndex ;i++)//recorro hasta la cantidad que ingreso
		{
			pNode = pNode->pNextNode;//va igualando hasta llegar al ultimo
		}
	}

	return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{
   int returnAux = -1;
   Node* pNodeNew = NULL;
   Node* pNodePrev = NULL;

   if(this != NULL && nodeIndex >= 0 && nodeIndex <= ll_len(this))
   {
	pNodeNew = (Node*) malloc(sizeof(Node));

	if(pNodeNew != NULL)
	{
		pNodeNew->pElement = pElement;
		pNodeNew->pNextNode = NULL; //por ser mi ultimo nodo agregado a la lista

		if(nodeIndex == 0)//si es mi primer elemento en la lista
		{
			pNodeNew->pNextNode = this->pFirstNode;//el primer nodo va a asignarse al nuevo nodo creado
			this->pFirstNode = pNodeNew;//el primer nodo va a ser el nuevo
		}
		else
		{
			pNodePrev = getNode(this,nodeIndex-1);//busco el nodo anterior a donde lo quiero agregar

			if(pNodePrev != NULL)
			{
				pNodeNew->pNextNode = pNodePrev->pNextNode;//a donde apunta el anterior nodo va a pasar a apuntar mi nuevo nodo
				pNodePrev->pNextNode = pNodeNew;//el anterior nodo empieza a apuntar al nuevo nodo
			}
		}
		this->size++;
		returnAux = 0;
	}
   }
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    if(this != NULL)
	{
    	returnAux = addNode(this,ll_len(this),pElement);//len va a ser el ultimo lugar que puedo agregar mi nuevo elemento
	}
    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* pNode = NULL;

	if(this != NULL && index >= 0)
	{
		if(index < ll_len(this))
		{
			pNode = getNode(this, index);

			if(pNode != NULL)
			{
				returnAux = pNode->pElement;
			}
		}
	}

    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* pNode = NULL;

	if(this != NULL && index >= 0)
	{
		if(index < ll_len(this))
		{
			pNode = getNode(this,index);

			if(pNode != NULL)
			{
				pNode->pElement = pElement;
				returnAux = 0;
			}
		}
	}

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    int len;
	Node* pNodeAux = NULL;
	Node* pNodePrev = NULL;


	if(this != NULL && index >= 0)
	{
		len = ll_len(this);

		if(index < len)
		{
			pNodeAux = getNode(this,index);//busco el nodo de la posicion que quiero eliminar

			if(pNodeAux != NULL)//si existe el nodo
			{
				if(index == 0)//si mi posicion es la primera
				{
					this->pFirstNode = pNodeAux->pNextNode; //le paso el proximo nodo al primer nodo y libero el nodo pedido
					free(pNodeAux);
					this->size--;//achico la lista
					returnAux = 0;
				}
				else
				{
					pNodePrev = getNode(this,index-1);//busco el anterior nodo al que quiero eliminar

					if(pNodePrev != NULL)
					{
						pNodePrev->pNextNode = pNodeAux->pNextNode;//al anterior nodo le paso la direccion del siguiente nodo que apuntaba el nodo que quiero eliminar
						free(pNodeAux);//libero el nodo pedido
						this->size--;//achico la lista
						returnAux = 0;
					}
				}
			}
		}
	}

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    int i;

	if(this != NULL)
	{
		if(!ll_isEmpty(this))//si existen elementos en la lista
		{
			for(i=0; i<ll_len(this) ;i++)
			{
				ll_remove(this,i);//borro en todas las posiciones hasta el final del len
				returnAux = 0;
			}
		}
		else//si no, dejo el nodo apuntando a NULL
		{
			this->pFirstNode = NULL;
			this->size = 0;
			returnAux = 0;
		}
	}

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;
    if(this != NULL)
   {
	if(!ll_clear(this))
	{
		free(this);
		returnAux = 0;
	}
   }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;
	Node* pNode = NULL;

	if(this != NULL)
	{
		if(!ll_isEmpty(this))//si no esta vacia la lista
		{
			for(i=0; i<ll_len(this) ;i++)
			{
				pNode = getNode(this,i);//obtengo el nodo en esa posicion
				if(pNode != NULL && pNode->pElement == pElement)
				{
					returnAux = i;
					break;
				}
			}
		}
	}

    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;
    int len;

	if(this != NULL)
	{
		len = ll_len(this);

		if(len>0)
		{
			returnAux = 0;//si no esta vacia
		}
		else
		{
			returnAux = 1;//si esta vacia
		}
	}


    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;

	if(this != NULL && index >= 0 && index <= ll_len(this))
	{
		returnAux = addNode(this,index,pElement);//le paso el indice y el elemento a guardar
	}


    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    void* pAux = NULL;

	if(this != NULL && index >= 0 && index <= ll_len(this))
	{
		 pAux = ll_get(this,index);//guardo el elemento en un auxiliar

		if(!ll_remove(this,index))//si pude removerlo lo devuelvo sino, NULL
		{
			returnAux = pAux;
		}
	}

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    int i;

	if(this != NULL)
	{
		returnAux = 0;//no esta en la lista

		if(!ll_isEmpty(this))//si la lista no esta vacia
		{
			for(i=0; i<ll_len(this) ;i++)
			{
				if(ll_indexOf(this,pElement)==i)//verifico si la posicion de ese elemento es la misma que mi iteracion
				{
					returnAux = 1;//esta en la lista
				}
			}
		}
	}


    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;
    int i;
	void* pElement = NULL;

	if(this != NULL && this2 != NULL)
	{
		returnAux = 1;

		if(!ll_isEmpty(this2) && !ll_isEmpty(this))//si las listas no estan vacias
		{
			for(i=0; i<ll_len(this2) ;i++)//recorro mi this2
			{
				pElement = ll_get(this2,i);//tomo el elemento de thi2 en esa posicion

				if(pElement != NULL)
				{
					if(!ll_contains(this,pElement))//comparo si ese elemento esta contenido en mi this, si no encuentra el elemento, no estan contenidos todos
					{
						returnAux = 0;//no contiene a los elementos
						break;//al primer elemento no encontrado, termina
					}
				}
			}
		}
	}

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;
    void* pElement = NULL;
   int i;

   if(this != NULL && from >= 0 && to >= 0 && from <= ll_len(this) && to <= ll_len(this))
   {
	cloneArray = ll_newLinkedList();//genero el espacio

	if(cloneArray != NULL)
	{
		for(i=from; i<to ;i++)//itera desde el valor from hasta el valor to
		{
			pElement = ll_get(this,i);//guardo el elemento de mi lista principal de esa posicion en un auxiliar
			ll_add(cloneArray,pElement);//añado mi elemento en la nueva lista creada(aunque sea NULL)
		}
	}
   }


    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

   if(this != NULL)
   {
	cloneArray = ll_subList(this,0,ll_len(this));//desde mi primer posicion hasta el tamaño de la lista original
   }


    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void* ,void*), int order)
{
    int returnAux =-1;
    int i;
   int j;
   int len;
   void* pElementI = NULL;
   void* pElementJ = NULL;
   //void* pAux = NULL;

   if(this != NULL && (order==1 || order==0) && pFunc!=NULL)
   {
	len = ll_len(this);

	for(i=0; i<len-1 ;i++)
	{
		for(j=i+1; j<len ;j++)
		{
			pElementI = ll_get(this,i);//obtengo el primer elemento de mi primer iteracion
			pElementJ = ll_get(this,j);//obtengo el segundo elemento de mi segunda iteracion

			if(pFunc(pElementI,pElementJ)>0 && order==1)//si es p1 es mayor a p2, ascendente
			{
				 //pAux = pElement1;
				 ll_set(this,i,pElementJ);//pongo al menor
				 ll_set(this,j,pElementI);
				 returnAux = 0;
			}
			else
			{
				if(pFunc(pElementI,pElementJ)<=0 && order==0)//si p1 es menor a p2, descendente
				{
					//pAux = pElement1;
					ll_set(this,i,pElementJ);//pongo al mayor
					ll_set(this,j,pElementI);
					returnAux = 0;
				}
			}
		}
	}
   }
    return returnAux;

}

LinkedList* ll_map (LinkedList* this, void*(*pFunc) (void* element))
{
    LinkedList* auxLista = NULL;
    int len;
    void* pElementAux;
    if(this != NULL && pFunc != NULL)
    {
        auxLista = ll_newLinkedList();
        if (auxLista != NULL)
        {
            len = ll_len(this);
            for (int i = 0; i < len; i++)
            {
                pElementAux = pFunc(ll_get(this,i));
                ll_add(auxLista,pElementAux);

            }
        }
    }
    return auxLista;
}

LinkedList* ll_filter(LinkedList* this,int (*pFunc)(void*))
{
    LinkedList* filterList = NULL;
    int len;
    void* pElementAux = NULL;
    if (this != NULL && pFunc != NULL)
    {
        filterList = ll_newLinkedList();
        if (filterList != NULL)
        {
            len = ll_len(this);
            for (int i = 0; i < len; i ++)
            {
                pElementAux = ll_get(this,i);
                if (pFunc(pElementAux))
                {
                    ll_add(filterList,pElementAux);
                }
            }
        }
    }
    return filterList;
}


