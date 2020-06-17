#ifndef PRIORITYQUEUE_H_
#define PRIORITYQUEUE_H_
#include <stdio.h>
#include <stdlib.h>
#include "Queue.h"
#include "utils.h"

typedef struct pQueueCell
{
	void *id;
    unsigned long downloaded;
    unsigned long size;
    struct pQueueCell *next;
} pqCell;

typedef struct PQ
{
    size_t dim;
    pqCell *front;
    pqCell *rear;
} PQ;

int isEmptyPQ(void *q);
void *InitPQ(size_t d);
int InsertPQ(void *temp, void *q);
int ExtractPQ(void *temp, void *q);
int PeekPQ(void *res, void *q);
int ResetPQ(void *q);
int DestroyPQ(void *q);

#endif /* PRIORITYQUEUE_H_ */
