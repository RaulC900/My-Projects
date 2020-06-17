#include <stdio.h>
#include <stdlib.h>
#include "parse.h"

int main(int argc, char **argv)
{
    //int MAX_WEBSITE_NAME_LEN = 257;
    char *str = malloc(MAX_WEBSITE_NAME_LEN * sizeof(char));
    char *s = malloc(MAX_WEBSITE_NAME_LEN * sizeof(char));

    Queue *history = InitQueue(MAX_WEBSITE_NAME_LEN * sizeof(char));
    PQ *downloads = InitPQ(MAX_WEBSITE_NAME_LEN * sizeof(char));
    PQ *finished = InitPQ(MAX_WEBSITE_NAME_LEN * sizeof(char));
    int bandwidth = 1024;

    Tab *tabs = InitTabList();
    Tab *tabsPtr = tabs;
    Tab *currentTab = tabs;

    strcpy(s, argv[1]);

    FILE *in = fopen(argv[1], "r");
    FILE *out = fopen(argv[2], "w");

    if(in == NULL || out == NULL){
        perror("Error opening file\n");
        return 1; 
    }

    while(fgets(str, MAX_CMD_LEN, in)) {
    	currentTab = ParseCmd(str, MAX_WEBSITE_NAME_LEN, tabsPtr, currentTab, history, downloads, finished, &bandwidth, out);
    }

    fclose(in);
    fclose(out);
    return 0;
}
