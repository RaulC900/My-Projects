#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include "parse.h"

void RemoveChar(char *str, char character)
{

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != character) dst++;
    }
    *dst = '\0';
}

Tab *ParseCmd(char *command, int size, Tab *tabs, Tab *currentTab, Queue *history, PQ *downloads, PQ *finished, int *bandwidth, FILE *out)
{
    char *cmd;
    char *text;
    char *completeCmd;
    cmd = (char *)malloc(size * sizeof(char));
    text = (char *)malloc(size * sizeof(char));
    completeCmd = (char *)malloc(size * sizeof(char));

    strncpy(cmd, command, size);
    strncpy(completeCmd, command, size);
    
    text = strtok(cmd, " ");
    
    Tab *t = tabs;

    if(strcmp(text, "newtab\n") == 0) {
    	currentTab = InsertTab(t);
    	return currentTab;

    } else if(strcmp(text, "goto") == 0) { //incarcarea unei pagini dureaza 1 sec, deci wait 1
		text = strtok(NULL, " ");
        RemoveChar(text, '\n');
        Insert(text, history);
        Goto(text, currentTab);
        Wait(1, *bandwidth, downloads, finished);
		return currentTab;

    } else if(strcmp(text, "print_open_tabs\n") == 0) {
    	PrintOpenTabs(t, out);
    	return currentTab;

    } else if(strcmp(text, "change_tab") == 0) {
    	text = strtok(NULL, " ");
    	RemoveChar(text, '\n');
    	int nr = atoi(text);
    	currentTab = ChangeTab(nr, currentTab, t);
    	return currentTab;

    } else if(strcmp(text, "history\n") == 0) {
    	PrintHistory(history, out);
    	return currentTab;

    } else if (strcmp(text, "back\n") == 0) {
    	GoBack(currentTab);
    	return currentTab;

    } else if (strcmp(text, "forward\n") == 0) {
    	GoForward(currentTab);
    	return currentTab;

    } else if (strcmp(text, "deltab\n") == 0) {
    	currentTab = DeleteTab(t, currentTab);
    	return currentTab;

    } else if (strcmp(text, "del_history") == 0) {
    	text = strtok(NULL, " ");
    	int nr = atoi(text);
    	DeleteHistory(nr, history);
    	return currentTab;

    } else if (strcmp(text, "list_dl\n") == 0) {
    	ListDownloads(currentTab, out);
    	return currentTab;

    } else if (strcmp(text, "download") == 0) {
    	int nr_resurse = 0;
    	text = strtok(NULL, " ");
    	int n = atoi(text);
    	DownloadResource(n, nr_resurse, downloads, currentTab);

    	return currentTab;

    } else if (strcmp(text, "set_band") == 0) {
    	text = strtok(NULL, " ");
    	int bandw = atoi(text);
    	*bandwidth = bandw;
    	return currentTab;

    } else if (strcmp(text, "downloads\n") == 0) {
    	PrintDownloadQueue(downloads, finished, out);
    	return currentTab;

    } else if (strcmp(text, "wait") == 0) {
    	text = strtok(NULL, " ");
    	int sec = atoi(text);
    	Wait(sec, *bandwidth, downloads, finished);

    	return currentTab;

    } else {

    	return currentTab;
    }

    return 0;

}
