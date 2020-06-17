#ifndef __STRUCTURES__
#define __STRUCTURES__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"
#include "Stack.h"
#include "PriorityQueue.h"
#include "utils.h"

#define MAX_WEBSITE_NAME_LEN 257

typedef struct tab
{
    char *url;
    int index;
    Stack *back_stack;
    Stack *front_stack;
    struct tab *next;
} Tab;

typedef struct dwL
{
	char *id;
	long unsigned int downloaded;
	long unsigned int size;
	struct dwL *next;
} dwL;

int isEmptyTabList(Tab *t);
Tab* InitTabList();
Tab *InsertTab(Tab *t);

int isEmptydwList(dwL *t);
dwL *InitdwList();
int InsertdwList(void *res, dwL **dw);
int InsertdwList_WithoutInversing(void *res, dwL **dw);
int InsertNoPriority(void *res, dwL **dw);
int ExtractdwList(void *res, dwL **dw);

#endif
