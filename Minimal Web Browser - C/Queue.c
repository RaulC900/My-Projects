#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"

int isEmptyQueue(void *q)
{
    return (((Queue*)q)->front == NULL && ((Queue*)q)->rear == NULL);
}

void *InitQueue(size_t d)
{
    Queue *q;
    q = (Queue*)malloc(d);
    if(!q) {
        return NULL;
    }

    q->dim = d;
    q->front = NULL;
    q->rear = NULL;

    return (void*)q;
}

int Insert(void *info, void *q)
{
    qCell *aux = (qCell*)malloc(sizeof(qCell));
    if(!aux) {
        return 1;
    }
    aux->data = malloc(((Queue*)q)->dim);
	if(!aux->data) {
		return 1;
	}

    if(isEmptyQueue(q)) {

        strcpy(aux->data, info);
    	aux->next = NULL;
        ((Queue*)q)->front = aux;
        ((Queue*)q)->rear = aux;
        return 0;
    }

    memcpy(aux->data, info, ((Queue*)q)->dim);
    aux->next = NULL;
    ((qCell*)((Queue*)q)->rear)->next = aux;
    ((Queue*)q)->rear = aux;
    return 0;
}

int Extract(void *temp, void *q)
{
    if(isEmptyQueue(q)) {
        return 1;
    }
    qCell *aux = malloc(sizeof(qCell));
    if(!aux) {
    	return 100;
    }

    aux->data = malloc(((Queue*)q)->dim);
    if(!aux->data) {
    	return 100;
    }

    if(((Queue*)q)->front == ((Queue*)q)->rear) {
        aux = ((Queue*)q)->front;
        ((Queue*)q)->front = aux->next;

        memcpy(temp, aux->data, ((Queue*)q)->dim);
        free(aux->data);
        free(aux);

        if(((Queue*)q)->front == NULL) {
            ((Queue*)q)->rear = NULL;
        }
        return 0;
    
    } else {
        aux = ((Queue*)q)->front;
        ((Queue*)q)->front = aux->next;

        memcpy(temp, aux->data, ((Queue*)q)->dim);
        free(aux->data);
		free(aux);
        return 0;
    }
    return 0;
}

int Peek(void *temp, void *q)
{
    if(isEmptyQueue(q)) {
        return 1;
    }
    qCell *aux = malloc(sizeof(qCell));

    if(((Queue*)q)->front == ((Queue*)q)->rear) {
        aux = ((Queue*)q)->front;
        ((Queue*)q)->front = aux;

        memcpy(temp, aux->data, ((Queue*)q)->dim);
        return 0;
    
    } else {
        aux = ((Queue*)q)->front;
        ((Queue*)q)->front = aux->next;

        memcpy(temp, aux->data, ((Queue*)q)->dim);
        return 0;
    }
    return 0;
}

int ResetQueue(void *q)
{
    qCell *prev, *list;

    prev = ((Queue*)q)->front;
    list = ((Queue*)q)->front;

    while(list != NULL) {
        prev = list;
        list = list->next;
        free(prev->data);
        free(prev);
        prev = NULL;
    }
    //free(((Queue*)q)->front);
    ((Queue*)q)->front = NULL;
    //free(((Queue*)q)->rear);
    ((Queue*)q)->rear = NULL;
    return 0;
}

int DestroyQueue(void *q)
{
    qCell *prev, *list;

    prev = ((Queue*)q)->front;
    list = ((Queue*)q)->front;

    while(list != NULL) {
        prev = list;
        list = list->next;
        free(prev->data);
        free(prev);
        prev = NULL;
    }
    //free(((Queue*)q)->front);
    ((Queue*)q)->front = NULL;
    //free(((Queue*)q)->rear);
    ((Queue*)q)->rear = NULL;
    free(q);
    q = NULL;
    return 0;
}
