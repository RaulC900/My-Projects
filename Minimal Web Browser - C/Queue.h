#ifndef QUEUE_H_
#define QUEUE_H_
#include <stdio.h>
#include <stdlib.h>

typedef struct queueCell
{
    void *data;
    struct queueCell *next;
} qCell;

typedef struct Queue
{
    size_t dim;
    qCell *front;
    qCell *rear;
} Queue;

int isEmptyQueue(void *q);
void *InitQueue(size_t d);
int Insert(void *info, void *q);
int Extract(void *temp, void *q);
int Peek(void *temp, void *q);
int ResetQueue(void *q);
int DestroyQueue(void *q);

#endif /* QUEUE_H_ */
