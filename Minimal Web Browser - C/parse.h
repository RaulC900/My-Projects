#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include "BrowserFunctions.h"
#include "List.h"
#include "PriorityQueue.h"

#define MAX_CMD_LEN 257

Tab *ParseCmd(char *command, int size, Tab *tabs, Tab *currentTab, Queue *history, PQ *downloads, PQ *finished, int *bandwidth, FILE *out);
void RemoveChar(char *str, char character);
