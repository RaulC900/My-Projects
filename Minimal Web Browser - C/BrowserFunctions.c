#include <stdio.h>
#include <stdlib.h>
#include "BrowserFunctions.h"
#include "utils.h"
#include "math.h"

int Goto(char *url, Tab *tab)
{
    char *temp;

    if(tab->back_stack == NULL) {
        tab->back_stack = InitStack(MAX_WEBSITE_NAME_LEN * sizeof(char));
    }

    if(tab->url != NULL) {
    	temp = tab->url;
    	Push((void*)temp, (void*)tab->back_stack);
        memcpy(tab->url, url, MAX_WEBSITE_NAME_LEN * sizeof(char));
        return 0;
    }
    tab->url = malloc((strlen(url) + 1) * sizeof(char));
    strcpy(tab->url, url);
    return 0;
}

int PrintOpenTabs(Tab *t, FILE *out)
{
	Tab *start = t;
	while(start != NULL) {
		if(start->url == NULL) {
			fprintf(out, "(%d: empty)\n", start->index);

		} else if (start->url != NULL) {
			fprintf(out, "(%d: %s)\n", start->index, start->url);

		}
		start = start->next;
	}
	return 0;
}

Tab *ChangeTab(int i, Tab *currentTab, Tab *tabs)
{
	Tab *start = tabs;
	while(start != NULL && (start->index != i)) {
		start = start->next;
	}
	if(start == NULL) {
		return currentTab;
	}
	return start;
}

int PrintHistory(Queue *history, FILE *out)
{
	void *q = (void*)history;
	void *aux = InitQueue(((Queue*)history)->dim);

	while(((Queue*)q)->front != NULL) {
		void *temp = malloc(MAX_WEBSITE_NAME_LEN * sizeof(char));
		Extract(temp, q);
		fprintf(out, "%s\n", (char*)temp);
		Insert(temp, aux);
	}

	while(((Queue*)aux)->front != NULL) {
		void *temp = malloc(MAX_WEBSITE_NAME_LEN * sizeof(char));
		Extract(temp, aux);
		Insert(temp, q);
	}
	return 0;
}

int GoBack(Tab *tab)
{
	Tab *aux = tab;
	if(aux->url == NULL) {
		return 1;
	}
	void *temp = malloc(aux->back_stack->dim);
	if(!temp) {
		return 100;
	}
	if(aux->back_stack->top == NULL) {
		return 5;
	}
	Pop(temp, (void*)aux->back_stack);
	if(aux->front_stack == NULL) {
		aux->front_stack = InitStack(MAX_WEBSITE_NAME_LEN * sizeof(char));
	}
	Push(aux->url, (void*)aux->front_stack);
	memcpy(aux->url, temp, MAX_WEBSITE_NAME_LEN * sizeof(char));
	return 0;
}

int GoForward(Tab *tab)
{
	Tab *aux = tab;
	if(aux->url == NULL) {
		return 1;
	}
	void *temp = malloc(aux->back_stack->dim);
	if(!temp) {
		return 100;
	}
	if(aux->front_stack->top == NULL) {
		return 5;
	}
	Pop(temp, (void*)aux->front_stack);
	if(aux->front_stack == NULL) {
		return 1;
	}
	Push(aux->url, (void*)aux->back_stack);
	memcpy(aux->url, temp, MAX_WEBSITE_NAME_LEN * sizeof(char));
	return 0;
}

Tab *DeleteTab(Tab *tabs, Tab *currentTab)
{
	Tab *start = tabs;
	Tab *previous = tabs;

	while(start->next != NULL) {
		previous = start;
		start = start->next;
	}

	if(previous == (tabs) && start == (tabs)) {
		(tabs) = start->next;
		if(start->back_stack) {
			DestroyStack((void*)(start->back_stack));
			start->back_stack = NULL;
		}
		if(start->front_stack) {
			DestroyStack((void*)(start->front_stack));
			start->front_stack = NULL;
		}
		free(start->url);
		free(start);
		start = NULL;
		return (tabs);
	}

	if(start == currentTab) {
		previous->next = start->next;
		if(start->back_stack) {
			DestroyStack((void*)(start->back_stack));
			start->back_stack = NULL;
		}
		if(start->front_stack) {
			DestroyStack((void*)(start->front_stack));
			start->front_stack = NULL;
		}
		free(start->url);
		free(start);
		start = NULL;
		return previous;
	}

	previous->next = start->next;
	if(start->back_stack) {
		DestroyStack((void*)(start->back_stack));
	}
	if(start->front_stack) {
		DestroyStack((void*)(start->front_stack));
	}
	free(start->url);
	free(start);
	start = NULL;
	return currentTab;

}

int DeleteHistory(int nr, Queue *history)
{
	Queue *q = history;
	char *temp = malloc(q->dim);
	if(nr == 0) {
		while(q->front != NULL) {
			Extract(temp, q);
		}
		free(temp);
		return 0;
	}
	while(nr > 0) {
		if(q->front == NULL) {
			break;
		}
		Extract(temp, q);
		nr -= 1;
	}
	free(temp);
	return 0;
}
int ListDownloads(Tab *currentTab, FILE *out)
{
	int nr = 0;
	int i = 0;
	if(currentTab->url == NULL) {
		return 1;
	}
	Resource *res = get_page_resources(currentTab->url, &nr);
	while(i < nr) {
		fprintf(out, "[%d - \"%s\" : %ld]\n", i, res[i].name, res[i].dimension);
		i += 1;
	}
	return 0;
}

int DownloadResource(int n, int nr_resurse, PQ *downloads, Tab *currentTab)
{
	if(currentTab->url == NULL) {
		return 1;
	}
	Resource *res = get_page_resources(currentTab->url, &nr_resurse);

	pqCell *temp = malloc(sizeof(pqCell));
	if(!temp) {
		return 0;
	}
	temp->id = malloc(MAX_WEBSITE_NAME_LEN * sizeof(char));
	if(!temp->id) {
		return 0;
	}

	if(downloads->front == NULL) {
		memcpy(temp->id, res[n].name, MAX_WEBSITE_NAME_LEN * sizeof(char));
		temp->size = res[n].dimension;
		temp->downloaded = res[n].currently_downloaded;
		InsertPQ(temp, downloads);
		return 0;
	}

	dwL *dwList = InitdwList();
	while(downloads->front != NULL) {
		ExtractPQ((void*)temp, downloads);
		InsertdwList_WithoutInversing(temp, &dwList);
		// aici cand pun in dwList ce era deja in downloads, 
		// daca au aceeasi val pt remaining
		// si fac InsertdwList normal, o sa le inverseze
	}

	memcpy(temp->id, res[n].name, MAX_WEBSITE_NAME_LEN * sizeof(char));
	temp->size = res[n].dimension;
	temp->downloaded = res[n].currently_downloaded;
	InsertdwList(temp, &dwList);

	while(dwList != NULL) {
		memcpy(temp->id, dwList->id, MAX_WEBSITE_NAME_LEN * sizeof(char));
		temp->size = dwList->size;
		temp->downloaded = dwList->downloaded;
		InsertPQ(dwList, downloads);
		dwList = dwList->next;
	}
	return 0;
}

int PrintDownloadQueue(PQ *downloads, PQ *finished, FILE *out)
{
	if(downloads->front == NULL) {
		return 1;
	}
	PQ *start = downloads;
	pqCell *temp = malloc(sizeof(pqCell));
	if(!temp) {
		return 100;
	}
	temp->id = malloc(MAX_WEBSITE_NAME_LEN * sizeof(char));
	if(!temp->id) {
		return 100;
	}
	dwL *dwList = InitdwList();
	while(start->front) {
		ExtractPQ((void*)temp, start);
		unsigned long remaining = temp->size - temp->downloaded;
		fprintf(out, "[\"%s\" : %ld/%ld]\n", (char*)temp->id, remaining, temp->size);
		InsertdwList_WithoutInversing(temp, &dwList);
	}

	while(dwList != NULL) {
		ExtractdwList(temp, &dwList);
		InsertPQ(temp, downloads);
	}

	if(finished->front == NULL) {
		return 1;
	}

	PQ *aux = finished;
	dwL *dwList1 = InitdwList();
	while(aux->front) {
		ExtractPQ((void*)temp, aux);
		fprintf(out, "[\"%s\" : completed]\n", (char*)temp->id);
		InsertNoPriority(temp, &dwList1); //aicea
	}

	while(dwList1 != NULL) {
		ExtractdwList(temp, &dwList1);
		InsertPQ(temp, finished);
	}
	return 0;
}

int Wait(int sec, int bandwidth, PQ *downloads, PQ *finished)
{
	double seconds = (float)sec;
	if(downloads->front == NULL) {
		return 1;
	}
	PQ *start = downloads;
	pqCell *temp = malloc(sizeof(pqCell));
	if(!temp) {
		return 100;
	}
	temp->id = malloc(MAX_WEBSITE_NAME_LEN * sizeof(char));
	if(!temp->id) {
		return 100;
	}
	while(seconds > 0) {
		unsigned long res = start->front->size - start->front->downloaded;
		if(seconds * bandwidth >= res) {
			double a = (double)((((double)res)/(double)bandwidth));
			double b = floor(a * 10000000000) / 10000000000; // 9 zecimale
			seconds -= b;
			start->front->downloaded += a * bandwidth;
			ExtractPQ(temp, downloads);
			InsertPQ(temp, finished);

		} else {
			double c = seconds * bandwidth;
			double d = floor(c * 10000000000) / 10000000000;
			start->front->downloaded += d;
			seconds = 0;
		}
	}
	return 0;
}









