#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "atm.h"

int isEmptyTuple(Tuple **history)
{
	return (*history) == NULL;
}

int isEmptyCard(Card **c)
{
	return (*c) == NULL;
}

int isEmptyLSC(LSC **lsc)
{
	return (*lsc) == NULL;
}

int InsertCard(Card **c, char *nr, char *pin, char *month, char *year, char *cvv)
{
	Card *aux = (Card*)malloc(sizeof(Card));
	Card *start = (*c);
	if(aux) {

		aux->number = (char *)malloc(20*sizeof(char));
		if(!aux->number)
			return 12;

		aux->pin = (char*)malloc(4*sizeof(char));
		if(!aux->pin)
			return 12;

		aux->status = (char*)malloc(20*sizeof(char));
		if(!aux->status)
			return 12;

		aux->month = (char*)malloc(4*sizeof(char));
		if(!aux->month)
			return 12;

		aux->year = (char*)malloc(4*sizeof(char));
		if(!aux->year)
			return 12;

		aux->cvv = (char*)malloc(4*sizeof(char));
		if(!aux->cvv)
			return 12;

		aux->inserted = false;
		aux->nr_tries = 0;
		strcpy(aux->number, nr);
		strcpy(aux->pin, pin);
		aux->pin_changed = false;
		strcpy(aux->month, month);
		strcpy(aux->year, year);
		strcpy(aux->cvv, cvv);
		aux->balance = 0;
		aux->history = NULL;
		strcpy(aux->status, "NEW");
		aux->next = NULL;

	} else if(!aux) {
		return 1;
	}

	if(!start) {
		(*c) = aux;
		return 0;

	} else {

		start = *c;
		while(start != NULL) {
			if(!strcmp(start->number, nr)) {
				return 5;
			}
			start = start->next;
		}
		start = *c;

		aux->next = (*c);
		(*c) = aux;
	
	}
	return 0;
}

int VerificareExistentaCard(LSC *n, char *nr, int nr_sub)
{
	int sum = sumOfString(nr);
	int subset = sum % nr_sub;


	while(n) {
		if(n->pos == subset)
		{
			Card *start = n->cardList;
			while(start != NULL) {
				if(!strcmp(start->number, nr)) {
					return 5;
				}
				start = start->next;
			}
		}
		n = n->next;
	}
	return 0;
}


int InsertHistory(Tuple **t, bool succ, char *op)
{

	Tuple *aux = (Tuple*)malloc(20*sizeof(Tuple));
	if(aux) {
		aux->operation = (char*)malloc(200*sizeof(char));
		
		if(!aux->operation)
			return 1;

		aux->success = succ;
		strcpy(aux->operation, op);
		aux->next = NULL;
	
	} else if(!aux) {
		return 1;
	}

	if(isEmptyTuple(t)) {
		(*t) = aux;
		return 0;
	
	} else {
		aux->next = (*t);
		(*t) = aux;
		return 0;
	}

	return 0;

}

int InsertLSC(LSC **head, int nr_sub, int nr)
{
	LSC *temp = *head;
	LSC *sub = (LSC*)malloc(sizeof(LSC));
	if(sub) {
		sub->cardList = NULL;
		sub->pos = nr;
		sub->next = NULL;
		sub->hadElem = false;
	}
	else if(!sub) {
		return 1;
	}

	if(isEmptyLSC(head)) {
		(*head) = sub;
	} else {

		while(temp->next != NULL)
			temp = temp->next;

		temp->next = sub;
	}
	return 1;

}

int deleteCard(Card **n, char *card_id)
{
	Card *c;
	Card *temp = *n;

	if(!strcmp(temp->number, card_id)) { //daca este in head-ul listei

		*n = temp->next;

		while(temp->history != NULL) {

			Tuple *aux = temp->history;
			temp->history = aux->next;
			free(aux->operation);
			free(aux);
		}

		free(temp->number);
		free(temp->pin);
		free(temp->status);
		free(temp);
		return 0;
	}

	while(temp != NULL && strcmp(temp->number, card_id)) {
		c = temp;
		temp = temp->next;
	}

	if(temp == NULL)
		return 12;

	c->next = temp->next;

	while(temp->history != NULL) {

			Tuple *aux1 = temp->history;
			temp->history = aux1->next;
			free(aux1->operation);
			free(aux1);
	}

	free(temp->number);
	free(temp->pin);
	free(temp->status);
	free(temp);

	return 0;
}

void deleteallCards(Card **n)
{
	while((*n) != NULL) {
		
		Card *aux = *n;
		*n = (*n)->next;

		while(aux->history != NULL) {

				Tuple *temp = aux->history;
				aux->history = temp->next;
				free(temp->operation);
				free(temp);
		}

		free(aux->number);
		free(aux->pin);
		free(aux->status);
		free(aux);
	}
}

void deleteAllLSC(LSC **c)
{
	while(*c != NULL) {

		LSC *aux = *c;
		*c = (*c)->next;

		while(aux->cardList != NULL) {

			Card *card = aux->cardList;
			aux->cardList = card->next;
			deleteallCards(&card);
			
		}
		free(aux);
	}
	*c=NULL;
}

int plusTransaction(Card **n, int sum)
{
	Card *start = *n;

	start->balance += sum;
	return 0;

}

int minusTransaction(Card **n, int sum)
{
	Card *start = *n;
	
	if(sum % 10 != 0) {	
		return 11;
	}
	if(start->balance >= sum) {

		start->balance -= sum;	
		return 0;

	} else {
		printf("Insufficient funds\n");
		return 12;
	}

}

int unblockCard(Card **n, char *nr_card)
{
	Card *start = *n;

	while(start && strcmp(start->number, nr_card)) {
		start = start->next;
	}
	if(start) {
		strcpy(start->status, "ACTIVE");
		start->pin_changed = true;
		start->nr_tries = 0;
		return 0;
	}
	return 12;
}

int verifyPin(Card **n, char *pin)
{
	Card *start = *n;

	if(*n == NULL) {
		return 20;
	}

	if(!strcmp(start->status, "LOCKED")) {
		return 12;
	}

	if(strcmp(start->pin, pin)) {
		start->nr_tries++;

		if(start->nr_tries == 3) {
			strcpy(start->status, "LOCKED");
			return 14;
		}
		return 10;
	}

	if(!strcmp(start->pin, pin)) {
		start->nr_tries = 0;
		if(!start->pin_changed) {
			printf("You must change your PIN.\n");
			return 1;
		} else {
			return 0;
		}

		return 0;	
	}
	
	return 10;
	
}

int balanceInquiry(Card **n)
{
	Card *start = *n;
	printf("%d\n", start->balance);
	return 0;
}

int pinChange(Card **n, char *pin)
{
	int i;
	if(strlen(pin) == 4) {
		for(i = 0; i < 4; i++) {
			if(pin[i] > '9' || pin[i] < '0') {
				return 12;
			}
		}
		Card *start = *n;
		if(strcmp(start->status, "BLOCKED")) {

			strcpy(start->pin, pin);
			start->pin_changed = true;
			strcpy(start->status, "ACTIVE");
			start->nr_tries = 0;
			return 0;

		} else {
			return 11;
		}

	} else {

		printf("Invalid PIN\n");
		return 12;
	}

}

void cancel(Card **c)
{
	(*c)->inserted = false;
}

int sumOfString(char *str)
{
	int count;
	int sum = 0;

	for(count = 0; str[count] != '\0'; count++) {
		sum += (str[count] - '0');
	}
	return sum;
}

int deleteEntry(Tuple **t, char *nr_card, int money)
{
	Tuple *start = *t;
	Tuple *c;
	char oper[30], card1[20], card2[20];
	int suma = 0;

	sscanf(start->operation, "%s %s %s %d", oper, card1, card2, &suma);

	if(!strcmp(oper, "transfer_funds") && !strcmp(card2, nr_card) && (suma == money)) {

		*t = start->next;

		free(start->operation);
		free(start);

		return 0;

	}
	while(start != NULL) {
		c = start;
		start = start->next;
		sscanf(start->operation, "%s %s %s %d", oper, card1, card2, &suma);

		if( strcmp(card2, nr_card)==0 && (suma == money) && !strcmp(oper, "transfer_funds")) {
			break;
		}

	}
	if(start == NULL) {
		return 12;
	}

	c->next = start->next;
	free(start->operation);
	free(start);

	return 0;
}
