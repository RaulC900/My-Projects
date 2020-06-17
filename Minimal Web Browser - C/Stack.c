#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Stack.h"

int isEmptyStack(void *s)
{
    return (((Stack*)s)->top == NULL);
}

void* InitStack(size_t d)
{
    Stack *s;
    s = (Stack*)malloc(sizeof(Stack));
    if(!s) {
        return NULL;
    }

    s->dim = d;
    s->top = NULL;

    return (void*)s;
}

int Push(void *info, void *s)
{
    sCell *aux = malloc(sizeof(sCell));
    if(!aux) {
        return 1;
    }
    aux->data = malloc(((Stack*)s)->dim);

    memcpy(aux->data, info, ((Stack*)s)->dim);

    aux->next = ((Stack*)s)->top;
    ((Stack*)s)->top = aux;
    return 0;
}

int Pop(void *temp, void *s)
{
    if(isEmptyStack(s)) {
        return 1;
    }
    sCell* aux = malloc(sizeof(sCell));
    if(!aux) {
    	return 100;
    }
    aux->data = malloc(((Stack*)s)->dim);
    if(!aux->data) {
    	return 100;
    }
    //temp = ((Stack*)s)->top->data;
    aux = ((Stack*)s)->top;
    ((Stack*)s)->top = aux->next;

    memcpy(temp, aux->data, ((Stack*)s)->dim);
    //free(aux->data);
    //free(aux);
    return 0;
}

int Top(void *temp, void *s)
{
    if(isEmptyStack(s)) {
        return 1;
    }
    memcpy(temp, ((Stack*)s)->top->data, ((Stack*)s)->dim);
    //temp = ((Stack*)s)->top->data;
    return 0;
}

int ResetStack(void *s)
{
    sCell *prev, *list;

    prev = ((Stack*)s)->top;
    list = ((Stack*)s)->top;

    while(list != NULL) {
        prev = list;
        list = list->next;
        free(prev->data);
        free(prev);
    }
    //free(((Stack*)s)->top);
    ((Stack*)s)->top = NULL;
    return 0;
}

int DestroyStack(void *s)
{
    sCell *prev, *list;

    prev = ((Stack*)s)->top;
    list = ((Stack*)s)->top;

    while(list != NULL) {
        prev = list;
        list = list->next;
        free(prev->data);
        free(prev);
        prev = NULL;
    }
    //free(((Stack*)s)->top->data);
    //free(((Stack*)s)->top); // aici era problema
    ((Stack*)s)->top = NULL;
    //free(s);
    return 0;
}
