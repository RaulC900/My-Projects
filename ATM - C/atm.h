#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct tuple
{
	bool success;
	char* operation;
	struct tuple *next;

} Tuple;

//Tuple *history; // (SUCCESS/FAIL, *comanda*)

typedef struct card
{
	bool inserted;
	int nr_tries;
	char *number;
	char *pin;
	bool pin_changed;
	char *month;
	char *year;
	char *cvv;
	int balance;
	Tuple *history;
	char *status; //poate fi NEW, ACTIVE sau LOCKED
	struct card *next;

} Card;

typedef struct lsc
{
	Card *cardList;
	int pos;
	bool hadElem;
	struct lsc *next;

} LSC;

int isEmptyTuple(Tuple **history);
int isEmptyCard(Card **c);
int isEmptyLSC(LSC **lsc);
int InsertLSC(LSC **lsc, int nr_sub, int nr);
int InsertCard(Card **c, char *nr, char *pin, char *month, char *year, char *cvv);
int VerificareExistentaCard(LSC *n, char *nr, int nr_sub);
int InsertHistory(Tuple **t, bool result, char *op);
int deleteEntry(Tuple **t, char *nr_card, int money);
int deleteCard(Card **c, char *card_id);
void display(LSC **n);
int minusTransaction(Card **n, int sum);
int plusTransaction(Card **n, int sum);
int unblockCard(Card **n, char *nr_card);
int verifyPin(Card **n, char *pin);
int balanceInquiry(Card **n);
int pinChange(Card **n, char *pin);
void deleteallCards(Card **n);
void deleteAllLSC(LSC **c);
void cancel(Card **c);
int sumOfString(char *str);
