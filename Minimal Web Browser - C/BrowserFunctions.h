#include <stdio.h>
#include <stdlib.h>
#include "List.h"
#include "PriorityQueue.h"

int Goto(char *url, Tab *tab);
int PrintOpenTabs(Tab *t, FILE *out);
Tab *ChangeTab(int i, Tab *currentTab, Tab *tabs);
int PrintHistory(Queue *history, FILE *out);
int GoBack(Tab *tab);
int GoForward(Tab *tab);
Tab *DeleteTab(Tab *tabs, Tab *currentTab);
int DeleteHistory(int nr, Queue *history);
int ListDownloads(Tab *tab, FILE *out);
int DownloadResource(int n, int nr_resurse, PQ *downloads, Tab *currentTab);
int PrintDownloadQueue(PQ *downloads, PQ *finished, FILE *out);
int Wait(int seconds, int bandwidth, PQ *downloads, PQ *finished);
