#include <stdio.h>
#include <stdlib.h>

typedef struct stackCell
{
    void *data;
    struct stackCell *next;
} sCell;

typedef struct Stack
{
    size_t dim;
    sCell *top;
} Stack;

int isEmptyStack(void *s);
void* InitStack(size_t d);
int Push(void *info, void *s);
int Pop(void *temp, void *s);
int Top(void *temp, void *s);
int ResetStack(void *s);
int DestroyStack(void *s);
