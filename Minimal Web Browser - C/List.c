#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

int isEmptyTabList(Tab *t)
{
    return (t == NULL);
}

Tab* InitTabList()
{
	Tab *t = malloc(sizeof(Tab));
	if(!t) {
		return NULL;
	}
	t->url = NULL;
	t->index = 0;
	t->back_stack = NULL;
	t->front_stack = NULL;
	t->next = NULL;
	return t;
}

Tab *InsertTab(Tab *t)
{
	Tab *temp = t;
    int count = 1;
    Tab *aux = malloc(sizeof(Tab));
 
    if(!aux) {
        return 0;
    
    } else if (aux) {
        aux->url = NULL;
        aux->back_stack = NULL; // be sure to allocate it when putting smth in it / not now tho, now it's NULL
        aux->front_stack = NULL;
        aux->next = NULL;
    }

    while(temp->next != NULL) {
        temp = temp->next;
        count += 1;
    }
    aux->index = count;
    temp->next = aux;
    return temp->next;
}

int isEmptydwList(dwL *d)
{
	return (d->id == NULL);
}

dwL* InitdwList()
{

	dwL *d = malloc(sizeof(dwL));
	if(!d) {
		return NULL;
	}
	d->id = NULL;
	d->downloaded = 0;
	d->size = 0;
	d->next = NULL;
	return d;

}

int InsertdwList(void *res, dwL **dw)
{
	dwL *l = (*dw);

	dwL *aux = malloc(sizeof(dwL));
	if(!aux) {
		return 100;
	}
	aux->id = malloc(MAX_WEBSITE_NAME_LEN * sizeof(char));
	if(!aux->id) {
		return 100;
	}
	memcpy(aux->id, ((pqCell*)res)->id, MAX_WEBSITE_NAME_LEN * sizeof(char));
	aux->size = ((pqCell*)res)->size;
	aux->downloaded = ((pqCell*)res)->downloaded;
	aux->next = NULL;

	if(isEmptydwList((*dw))) {
		(*dw) = aux;
		return 0;
	}

	if((aux->size - aux->downloaded) <= ((*dw)->size - (*dw)->downloaded)) { //caz special head
		aux->next = (*dw);
		(*dw) = aux;
		return 0;
	}

	while(l->next != NULL && ((aux->size - aux->downloaded) >= (l->next->size - l->next->downloaded))) {
		if((aux->size - aux->downloaded) == (l->next->size - l->next->downloaded)) {
			break;
		}
		l = l->next;
	}

	aux->next = l->next;
	l->next = aux;
	return 0;
}

int InsertdwList_WithoutInversing(void *res, dwL **dw)
{
	dwL *l = (*dw);

	dwL *aux = malloc(sizeof(dwL));
	if(!aux) {
		return 100;
	}
	aux->id = malloc(MAX_WEBSITE_NAME_LEN * sizeof(char));
	if(!aux->id) {
		return 100;
	}
	memcpy(aux->id, ((pqCell*)res)->id, MAX_WEBSITE_NAME_LEN * sizeof(char));
	aux->size = ((pqCell*)res)->size;
	aux->downloaded = ((pqCell*)res)->downloaded;
	aux->next = NULL;

	if(isEmptydwList((*dw))) {
		(*dw) = aux;
		return 0;
	}

	if((aux->size - aux->downloaded) < ((*dw)->size - (*dw)->downloaded)) { //caz special head
		aux->next = (*dw);
		(*dw) = aux;
		return 0;
	}

	while(l->next != NULL && ((aux->size - aux->downloaded) >= (l->next->size - l->next->downloaded))) {
		l = l->next;
	}

	aux->next = l->next;
	l->next = aux;
	return 0;
}

int InsertNoPriority(void *res, dwL **dw)
{
	dwL *l = (*dw);

	dwL *aux = malloc(sizeof(dwL));
	if(!aux) {
		return 100;
	}
	aux->id = malloc(MAX_WEBSITE_NAME_LEN * sizeof(char));
	if(!aux->id) {
		return 100;
	}
	memcpy(aux->id, ((pqCell*)res)->id, MAX_WEBSITE_NAME_LEN * sizeof(char));
	aux->size = ((pqCell*)res)->size;
	aux->downloaded = ((pqCell*)res)->downloaded;
	aux->next = NULL;

	if(isEmptydwList((*dw))) {
		(*dw) = aux;
		return 0;
	}

	while(l->next != NULL) {
		l = l->next;
	}

	l->next = aux;
	return 0;
}

int ExtractdwList(void *res, dwL **dw)
{
	dwL *prev = (*dw);

	prev = (*dw);
	(*dw) = (*dw)->next;
	memcpy(((pqCell*)res)->id, prev->id, MAX_WEBSITE_NAME_LEN * sizeof(char));
	((pqCell*)res)->downloaded = prev->downloaded;
	((pqCell*)res)->size = prev->size;
	free(prev->id);
	free(prev);
	prev = NULL;

	return 0;
}










