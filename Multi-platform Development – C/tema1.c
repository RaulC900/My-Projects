#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "compare.h"
#define BUFSIZE 20000

typedef struct node {
	char *word;
	int priority;
	struct node *next;
} Node;

int isEmpty(Node **n)
{
	return (*n) == NULL;
}

void freeQueue(Node **n)
{
	while ((*n) != NULL) {
		Node *aux = (*n);
		*n = (*n)->next;
		free(aux->word);
		free(aux);
	}
}

int Insert(Node **n, char *w, int p)
{
	Node *start = (*n);
	Node *aux = (Node *)malloc(sizeof(Node));

	if (aux) {

		aux->word = (char *)malloc((strlen(w)+1) * sizeof(char));

		if (!aux->word)
			return 12;
		strcpy(aux->word, w);
		aux->priority = p;
		aux->next = NULL;

	} else if (!aux)
		return 12;

	if (isEmpty(n)) {
		*n = aux;
	} else {

		if (compare((*n)->priority, p) < 0) {
					//vede daca primul elem are
					//prioritatea mai mica decat p
			aux->next = *n; //daca da, il pun pe aux primul
			*n = aux;

		} else {

			while (start->next != NULL	//iterez prin lista
				 && (compare(start->next->priority, p) > 0))
				start = start->next; // pana cand gasesc la
				//start->next prioritate mai mica decat p
			aux->next = start->next; //
			start->next = aux; //il pun pe aux in poz
		}
	}

	return 0;
}



char *top(Node **n)
{
	if (isEmpty(n))
		return "\n";
	else
		return (*n)->word;
}

void pop(Node **n)
{
	if (!isEmpty(n)) {
		Node *aux = *n;
		(*n) = (*n)->next;
		free(aux->word);
		free(aux);
	}
}



int ReadFiles(Node **n, char *file)
{
	int j = 0;
	int code = 0;
	FILE *pFile;
	char *buffer;
	char *text;
	char *text1;

	pFile = fopen(file, "r");

	if (pFile != NULL) {
		buffer = (char *)malloc((BUFSIZE + 1) * sizeof(char));

		if (!buffer)
			return 12;

		while (fgets(buffer, 20000, pFile) != NULL) {
			text = strtok(buffer, " "); //verific daca
						//buffer este insert/top/pop

			if (!strcmp(text, "insert")) {
				text = strtok(NULL, " ");
				text1 = strtok(NULL, " ");

				if (text == NULL)
					break; //nu avem cuvant

				if (text1 != NULL) {
					j = atoi(text1);

					if (strtok(NULL, " ") != NULL)
						break;
						//alt string dupa priority
					code = Insert(n, text, j);

					if (code == 12)
						return 12;
				}
			} else if (!strcmp(text, "top\n")) {

				if (strtok(NULL, " ") == NULL)
					printf("%s\n", top(n));

			} else if (!strcmp(text, "pop\n"))

				if (strtok(NULL, " ") == NULL)
					pop(n);
		}

		free(buffer);
		fclose(pFile);
	}

	return 1;
}

int ReadStdin(Node **n)
{
	int j;
	int code = 0;
	char *buffer;
	char *text;
	char *text1;

	buffer = (char *)malloc((BUFSIZE + 1) * sizeof(char));

	if (!buffer)
		return 12;

	while (fgets(buffer, 20000, stdin) != NULL) {
		text = strtok(buffer, " ");

		if (!strcmp(text, "insert")) {
			text = strtok(NULL, " ");
			text1 = strtok(NULL, " ");

			if (text == NULL)
				break;

			if (text1 != NULL) {
				j = atoi(text1);

				if (strtok(NULL, " ") != NULL)
					break;
				code = Insert(n, text, j);

				if (code == 12)
					return 12;
			}
		} else if (!strcmp(text, "top\n")) {
			if (strtok(NULL, " ") == NULL)
				printf("%s\n", top(n));

		} else if (!strcmp(text, "pop\n")) {
			if (strtok(NULL, " ") == NULL)
				pop(n);
		}
	}
	free(buffer);
	return 0;
}

int main(int argc, char *argv[])
{
	Node *n = NULL;
	int i;
	int j, k;

	if (argc > 1) { //citire din fisiere (1 sau mai multe)
		for (i = 1; i < argc; i++) {
			j = ReadFiles(&n, argv[i]);
			if (j == 12)
				exit(12);
		}
	} else { //citire de la stdin
		k = ReadStdin(&n);
			if (k == 12)
				exit(12);
	}
	freeQueue(&n);
	return 0;
}
