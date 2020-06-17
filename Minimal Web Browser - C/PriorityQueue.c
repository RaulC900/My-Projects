#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PriorityQueue.h"

int isEmptyPQ(void *q)
{
    return (((PQ*)q)->front == NULL && ((PQ*)q)->rear == NULL);
}

void *InitPQ(size_t d)
{
    PQ *q;
    q = (PQ*)malloc(d);
    if(!q) {
        return NULL;
    }

    q->dim = d;
    q->front = NULL;
    q->rear = NULL;

    return (void*)q;
}

int InsertPQ(void *temp, void *q)
{
    pqCell *aux = malloc(sizeof(pqCell));
    if(!aux) {
        return 1;
    }
    aux->id = malloc(((PQ*)q)->dim);
	if(!aux->id) {
		return 1;
	}

    if(isEmptyPQ(q)) {

        memcpy(aux->id, ((pqCell*)temp)->id, ((PQ*)q)->dim);
        aux->size = ((pqCell*)temp)->size;
        aux->downloaded = ((pqCell*)temp)->downloaded;
    	aux->next = NULL;
        ((PQ*)q)->front = aux;
        ((PQ*)q)->rear = aux;
        return 0;
    }

    memcpy(aux->id, ((pqCell*)temp)->id, ((PQ*)q)->dim);
    aux->next = NULL;
    aux->size = ((pqCell*)temp)->size;
	aux->downloaded = ((pqCell*)temp)->downloaded;
    ((pqCell*)((PQ*)q)->rear)->next = aux;
    ((PQ*)q)->rear = aux;
    return 0;
}

int ExtractPQ(void *temp, void *q)
{
    if(isEmptyPQ(q)) {
        return 1;
    }
    pqCell *aux = malloc(sizeof(pqCell));
    if(!aux) {
    	return 100;
    }

    aux->id = malloc(((PQ*)q)->dim);
    if(!aux->id) {
    	return 100;
    }

    if(((PQ*)q)->front == ((PQ*)q)->rear) {
        aux = ((PQ*)q)->front;
        ((PQ*)q)->front = aux->next;

        memcpy(((pqCell*)temp)->id, aux->id, ((Queue*)q)->dim);
        ((pqCell*)temp)->size = aux->size;
        ((pqCell*)temp)->downloaded = aux->downloaded;
        free(aux);

        if(((PQ*)q)->front == NULL) {
            ((PQ*)q)->rear = NULL;
        }
        return 0;

    } else {
        aux = ((PQ*)q)->front;
        ((PQ*)q)->front = aux->next;

        memcpy(((pqCell*)temp)->id, aux->id, ((PQ*)q)->dim);
        ((pqCell*)temp)->size = aux->size;
        ((pqCell*)temp)->downloaded = aux->downloaded;
        free(aux->id);
        free(aux);
        return 0;
    }
    return 0;
}

int PeekPQ(void *temp, void *q)
{
    if(isEmptyPQ(q)) {
        return 1;
    }
    pqCell *aux = malloc(sizeof(pqCell));

    if(((PQ*)q)->front == ((PQ*)q)->rear) {
        aux = ((PQ*)q)->front;
        ((PQ*)q)->front = aux;

        memcpy(((pqCell*)temp)->id, aux->id, ((PQ*)q)->dim);
        ((pqCell*)temp)->size = aux->size;
        ((pqCell*)temp)->downloaded = aux->downloaded;
        return 0;

    } else {
        aux = ((PQ*)q)->front;
        ((PQ*)q)->front = aux->next;

        memcpy(((pqCell*)temp)->id, aux->id, ((PQ*)q)->dim);
        ((pqCell*)temp)->size = aux->size;
        ((pqCell*)temp)->downloaded = aux->downloaded;
        return 0;
    }
    return 0;
}

int ResetPQ(void *q)
{
    pqCell *prev, *list;

    prev = ((PQ*)q)->front;
    list = ((PQ*)q)->front;

    while(list != NULL) {
        prev = list;
        list = list->next;
        free(prev->id);
        free(prev);
    }
    free(((PQ*)q)->front);
    ((PQ*)q)->front = NULL;
    free(((PQ*)q)->rear);
    ((PQ*)q)->rear = NULL;
    return 0;
}

int DestroyPQ(void *q)
{
    pqCell *prev, *list;

    prev = ((PQ*)q)->front;
    list = ((PQ*)q)->front;

    while(list != NULL) {
        prev = list;
        list = list->next;
        free(prev->id);
        free(prev);
    }
    free(((PQ*)q)->front);
    ((PQ*)q)->front = NULL;
    free(((PQ*)q)->rear);
    ((PQ*)q)->rear = NULL;
    free(q);
    q = NULL;
    return 0;
}














