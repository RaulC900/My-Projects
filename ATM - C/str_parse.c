#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include "atm.h"


int ReadFile(LSC **lsc)
{
	LSC *n = *lsc;
	LSC *start;
	LSC *startAux;
	LSC *rezerva = NULL;

	char *text, *text1, *nr_card, *temp, *aux, *pin;
	char *buffer, *month, *year, *cvv;
	char *bufAux;
	char *bufRez;

	int nr_sub;
	int subset, subset1;
	int sum = 0, money = 0;
	int noCards = 0;
	int ret_value;
	int i;
	int prnt = 0;

	bool atLeastOnce;

	FILE *fd, *fd2;

	fd = fopen("input.in", "r");
	fd2 = fopen("output.out", "wb");

	if(fd != NULL) {

		buffer = (char*)malloc(2000*sizeof(char));
		bufRez = (char*)malloc(70*sizeof(char));
		
		if(!buffer) {
			return 1;
		}

		nr_sub = atoi(fgets(buffer, 2000, fd));
		for(i = 0; i < nr_sub; i++) {
			InsertLSC(&n, nr_sub, i);
		}

		bufAux = (char *)malloc(200*sizeof(char));

		while(fgets(buffer, 2000, fd) != NULL) {

			strcpy(bufAux, buffer);
			for(i = 0; i < strlen(bufAux); i++) {
				if(bufAux[i] == '\n'){
					bufAux[i] = 0;
				}
			}

			text = (char*)malloc(70*sizeof(char));
			text = strtok(buffer, " ");

			if((!strcmp(text, "show")) || (!strcmp(text, "show\n"))) {

				strcpy(bufRez, bufAux);
				if(!strcmp(text, "show\n")) {
					strcpy(text, "show");
				}
			}

			if(!strcmp(text, "add_card")) {

				nr_card = (char*)malloc(20*sizeof(char));
				temp = (char*)malloc(20*sizeof(char));
				pin = (char*)malloc(4*sizeof(char));
				start = n;


				sum = 0;
				text = strtok(NULL, " ");
				strcpy(nr_card, text);
				strcpy(temp, nr_card);

				text = strtok(NULL, " ");
				strcpy(pin, text);

				month = strtok(NULL, "/");
				year = strtok(NULL, " ");

				cvv = strtok(NULL, "\n");
				

				start = n;


				if(noCards == nr_sub && VerificareExistentaCard(n, temp, nr_sub) == 0) {

					nr_sub = nr_sub * 2;
					rezerva = NULL;
				 	for(i = 0; i < nr_sub; i++) {
				 		InsertLSC(&rezerva, nr_sub, i);

				 	}

					start = n;
					startAux = rezerva;

					while(start) {
						while(start->cardList) {

							sum = sumOfString(start->cardList->number);
							Card * ctemp = start->cardList;
							start->cardList = start->cardList->next;
							subset = sum % nr_sub;
							startAux = rezerva;

							while(startAux) {
								if(startAux->pos == subset) {
									ctemp->next = startAux->cardList;
									startAux->cardList = ctemp;
									startAux->hadElem = true;
									break;
								}
								startAux = startAux->next;
							}

						}
						start = start->next;
					}

					deleteAllLSC(&n);
					n = rezerva;
				}
				start = n;

				sum = sumOfString(temp);
				subset = sum % nr_sub;

				while(start != NULL) {

					if(start->pos == subset) {

						ret_value = InsertCard(&(start->cardList), temp, 
							pin, month, year, cvv);

						prnt++;
						if(ret_value == 5) {
							printf("The card already exists\n");
							fprintf(fd2, "The card already exists\n");
						}
						else if(ret_value == 0) {
							noCards = noCards + 1;
							start->hadElem = true;
							atLeastOnce = true;
						}

					}
					start = start->next;
				}

				start = n;

				free(nr_card);
				free(temp);
				free(pin);

			}

			if(!strcmp(text, "delete_card")) {

				sum = 0;
				aux = (char*)malloc(20*sizeof(char));
				text = strtok(NULL, "\n");

				strcpy(aux, text);

				sum = sumOfString(aux);

				subset = sum % nr_sub;

				start = n;
				while(start != NULL) {
					if(start->pos == subset) {
						ret_value = deleteCard(&(start->cardList), aux);
						if(ret_value == 0) {
							noCards = noCards - 1;
						}
					}
					start = start->next;
				}
				free(aux);

			}

			if(!strcmp(text, "reverse_transaction")) {

				nr_card = (char*)malloc(20*sizeof(char));
				temp = (char*)malloc(20*sizeof(char));
				sum = 0;

				text = strtok(NULL, " ");
				text1 = strtok(NULL, " ");
				strcpy(nr_card, text);
				strcpy(temp, text1);
				text = strtok(NULL, " ");
				money = atoi(text);
				bool enoughMoney = false; //daca card_destinatie are destui bani
				bool transactionExists = false; //daca se efectueaza minusTransaction
				
				sum = sumOfString(nr_card);
				subset = sum % nr_sub;
				sum = 0;

				sum = sumOfString(temp);
				subset1 = sum % nr_sub;

				start = n;
				while(start != NULL) {

					if(start->pos == subset1) {
						Card *cautat = start->cardList;
						while(cautat != NULL && (strcmp(cautat->number, temp))){
							cautat = cautat->next;
						}
						if(cautat != NULL) {
							ret_value = minusTransaction(&(cautat), money);

							if(ret_value == 0) {

								deleteEntry(&(cautat->history), temp, money);
								enoughMoney = true;
								transactionExists = true;

							} else if(ret_value == 11) {
								printf("The transaction cannot be reversed\n");
								fprintf(fd2, "The transaction cannot be reversed\n");
							} else if(ret_value == 12) {
								printf("The transaction cannot be reversed\n");
								fprintf(fd2, "The transaction cannot be reversed\n");
							}
						}
						


					}
					start = start->next;

				}

				start = n;
				while(start != NULL) {
					if(enoughMoney == true && transactionExists == true) {
						if(start->pos == subset) {
							Card *cautat = start->cardList;
							while(cautat != NULL && (strcmp(cautat->number, nr_card))){
								cautat = cautat->next;
							}
							if(cautat != NULL) {
								plusTransaction(&(cautat), money);
								InsertHistory(&(cautat->history), true, bufAux);
								enoughMoney = false;
								transactionExists = false;
							}

						} 
					}
					start = start->next;
				}
				free(nr_card);
				free(temp);


			}

			if(!strcmp(text, "unblock_card")) {

				nr_card = (char*)malloc(20*sizeof(char));
				sum = 0;

				text = strtok(NULL, "\n");
				strcpy(nr_card, text);

				sum = sumOfString(nr_card);

				subset = sum % nr_sub;
				sum = 0;

				start = n;
				while(start != NULL) {
					if(start->pos == subset) {
						unblockCard(&(start->cardList), nr_card);

					}
					start = start->next;
				}
				free(nr_card);


			}

			if((!strcmp(text, "show")) && (!strcmp(bufRez, "show"))) {

				int i = 0;
				int border = 0;
				int empty = 0;

				start = n;
				while(start) {
					if(start->hadElem == true) {
						border = start->pos; // ultima submultime care a avut 
					}						// cel putin un card
					start = start->next;
				}
				start = n;
				if(noCards == 0 && atLeastOnce == true) {
					while(start) {
						if((start->cardList == NULL && start->pos <= border) 
							|| (start->hadElem == true)) {
							printf("pos%d: []\n", start->pos);
							fprintf(fd2, "pos%d: []\n", start->pos);
						}
						start = start->next;
					}
					start = n;

				} else {

					while((start && start->pos <= border && prnt != 0) 
						|| (start && start->hadElem == true)) {
						
						if(i != 0){
							printf("\n");
							fprintf(fd2, "\n");
						}

						i++;
						printf("pos%d: [", start->pos);
						fprintf(fd2, "pos%d: [", start->pos);

						empty = 0;
						Card *inceput = start->cardList;
						while(inceput != NULL) {

							printf("\n");
							fprintf(fd2, "\n");
							printf("(");
							fprintf(fd2, "(");
							printf("card number: %s, PIN: %s, expiry date: %s/%s, CVV: %s, balance: %d, status: %s, history: [", inceput->number
								, inceput->pin, inceput->month, inceput->year, inceput->cvv, inceput->balance
								, inceput->status);
							fprintf(fd2, "card number: %s, PIN: %s, expiry date: %s/%s, CVV: %s, balance: %d, status: %s, history: [", inceput->number
								, inceput->pin, inceput->month, inceput->year, inceput->cvv, inceput->balance
								, inceput->status);

							if(isEmptyTuple(&(inceput->history))) {
								printf("]");
								fprintf(fd2, "]");
							}
							Tuple *tp = inceput->history;
							while(tp) {

								if(tp->success == 1) {
									printf("(SUCCESS, %s)", tp->operation);
									fprintf(fd2, "(SUCCESS, %s)", tp->operation);
								}
								else if(tp->success == 0) {
									printf("(FAIL, %s)", tp->operation);
									fprintf(fd2, "(FAIL, %s)", tp->operation);
								}
								if(tp->next != NULL) {
									printf(", ");
									fprintf(fd2, ", ");
								} else {
									printf("]");
									fprintf(fd2, "]");
								}
								tp = tp->next;

							}
							printf(")");
							fprintf(fd2, ")");
							
							inceput = inceput->next;
							empty++; // daca != 0 inseamna ca start->cardList != NULL

						}
						if(empty > 0){ // start->cardList != NULL
							if(start->pos != border) {
								printf("\n]");
								fprintf(fd2, "\n]");
							} else {
								printf("\n]\n");
								fprintf(fd2, "\n]\n");
							}
						} else {
							if(start->pos != border) { // ] se pune pe aceeasi linie
								printf("]");
								fprintf(fd2, "]");
							}else{
								printf("]\n");
								fprintf(fd2, "]\n");
							}
						}
						start = start->next;

					}
				}
				start = n;
			}

			if((!strcmp(text, "show")) && (strcmp(bufRez, "show"))) {

				temp = (char*)malloc(20*sizeof(char));
				sum = 0;
				text1 = strtok(NULL, "\n");
				strcpy(temp, text1);

				sum = sumOfString(temp);

				subset = sum % nr_sub;
				sum = 0;
				int i = 0;

				start = n;
				while(start != NULL) {

					if(start->pos == subset) {

						Card *cautat = start->cardList;
						while(cautat != NULL && (strcmp(cautat->number, temp))){
							cautat = cautat->next;
						}
						if(cautat != NULL) {
							if(i != 0) {
								printf("\n");
								fprintf(fd2, "\n");
							}
							i++;
							printf("(");
							fprintf(fd2, "(");
							printf("card number: %s, PIN: %s, expiry date: %s/%s, CVV: %s, balance: %d, status: %s, history: [", cautat->number
								, cautat->pin, cautat->month, cautat->year, cautat->cvv, cautat->balance
								, cautat->status);
							fprintf(fd2, "card number: %s, PIN: %s, expiry date: %s/%s, CVV: %s, balance: %d, status: %s, history: [", cautat->number
								, cautat->pin, cautat->month, cautat->year, cautat->cvv, cautat->balance
								, cautat->status);
							if(isEmptyTuple(&(cautat->history))) {
								printf("]");
								fprintf(fd2, "]");
							}
							Tuple *tp = cautat->history;
							while(tp) {

								if(tp->success == 1) {
									printf("(SUCCESS, %s)", tp->operation);
									fprintf(fd2, "(SUCCESS, %s)", tp->operation);
								}
								else if(tp->success == 0) {
									printf("(FAIL, %s)", tp->operation);
									fprintf(fd2, "(FAIL, %s)", tp->operation);
								}
								if(tp->next != NULL) {
									printf(", ");
									fprintf(fd2, ", ");
								} else {
									printf("]");
									fprintf(fd2, "]");
								}
								tp = tp->next;
							}
							printf(")");
							fprintf(fd2, ")");
						}
					}
					start = start->next;

				}
				printf("\n");
				fprintf(fd2, "\n");
				free(temp);
				start = n;
			}

			
			if(!strcmp(text, "insert_card")) {

				nr_card = (char*)malloc(20*sizeof(char));
				pin = (char*)malloc(4*sizeof(char));
				sum = 0;

				text = strtok(NULL, " ");
				strcpy(nr_card, text);
				text = strtok(NULL, "\n");
				strcpy(pin, text);

				sum = sumOfString(nr_card);

				subset = sum % nr_sub;
				sum = 0;

				start = n;
				while(start != NULL) {
					if(start->pos == subset) {
						Card *cautat = start->cardList;
						while(cautat != NULL && (strcmp(cautat->number, nr_card))){
							cautat = cautat->next;
						}

						ret_value = verifyPin(&(cautat), pin);
						if(ret_value == 0) {

							InsertHistory(&(cautat->history), true, bufAux);
							cautat->inserted = true;
						}
						if(ret_value == 1) {

							InsertHistory(&(cautat->history), true, bufAux);
							cautat->inserted = true;
							fprintf(fd2, "You must change your PIN.\n");
						}
						if(ret_value == 10) {

							InsertHistory(&(cautat->history), false, bufAux);
							cautat->inserted = false;
							fprintf(fd2, "Invalid PIN\n");
						}
						if(ret_value == 12) {

							InsertHistory(&(cautat->history), false, bufAux);
							printf("The card is blocked. Please contact the administrator.\n");
							fprintf(fd2, "The card is blocked. Please contact the administrator.\n");
						}
						if(ret_value == 14) {

							InsertHistory(&(cautat->history), false, bufAux);
							printf("Invalid PIN\n");
							printf("The card is blocked. Please contact the administrator.\n");
							fprintf(fd2, "Invalid PIN\n");
							fprintf(fd2, "The card is blocked. Please contact the administrator.\n");
						}
					}
					start = start->next;
				}
				free(nr_card);
				free(pin);

			}

			if(!strcmp(text, "recharge")) {

				nr_card = (char*)malloc(20*sizeof(char));
				sum = 0;
				money = 0;

				text = strtok(NULL, " ");
				strcpy(nr_card, text);
				text = strtok(NULL, "\n");
				money = atoi(text);

				sum = sumOfString(nr_card);

				subset = sum % nr_sub;
				sum = 0;

				start = n;
				while(start != NULL) {
					if(start->pos == subset) {
						Card *cautat = start->cardList;
						while(cautat != NULL && (strcmp(cautat->number, nr_card))){
							cautat = cautat->next;
						}

						if(cautat!= NULL && cautat->inserted == true) {

							if(money % 10 == 0) {

								plusTransaction(&(cautat), money);
								InsertHistory(&(cautat->history), true, bufAux);

								printf("%d\n", cautat->balance);
								fprintf(fd2, "%d\n", cautat->balance);
								cancel(&(cautat));

							} else {

								InsertHistory(&(cautat->history), false, bufAux);
								printf("​The added amount must be multiple of 10\n");
								fprintf(fd2, "The added amount must be multiple of 10\n");
								cancel(&(cautat));
							}
						}
					}
					start = start->next;
					}

				free(nr_card);
			}

			if(!strcmp(text, "cash_withdrawal")) {

				nr_card = (char*)malloc(20*sizeof(char));
				sum = 0;
				money = 0;

				text = strtok(NULL, " ");
				strcpy(nr_card, text);
				text = strtok(NULL, "\n");
				money = atoi(text);
				sum = sumOfString(nr_card);

				subset = sum % nr_sub;
				sum = 0;

				start = n;
				while(start != NULL) {
					if(start->pos == subset) {
						Card *cautat = start->cardList;
						while(cautat != NULL && (strcmp(cautat->number, nr_card))){
							cautat = cautat->next;
						}

						if(cautat != NULL && cautat->inserted == true) {
							ret_value = minusTransaction(&(cautat), money);
							printf("%d\n", cautat->balance);
							cancel(&(cautat));

							if(ret_value == 0) {
								InsertHistory(&(cautat->history), true, bufAux);
								fprintf(fd2, "%d\n", cautat->balance);
							}
							if(ret_value == 11) {
								InsertHistory(&(cautat->history), false, bufAux);
								printf("​The requested amount must be multiple of 10​\n");
								fprintf(fd2, "The requested amount must be multiple of 10\n");
							}
							if(ret_value == 12) {
								InsertHistory(&(cautat->history), false, bufAux);
								fprintf(fd2, "Insufficient funds\n");
							}

						}

					}
					start = start->next;
					}
				free(nr_card);

			}

			if(!strcmp(text, "balance_inquiry")) {

				temp = (char*)malloc(20*sizeof(char));
				sum = 0;

				text = strtok(NULL, "\n");
				strcpy(temp, text);

				sum = sumOfString(temp);

				subset = sum % nr_sub;
				sum = 0;

				start = n;
				while(start != NULL) {
					if(start->pos == subset) {
						Card *cautat = start->cardList;
						while(cautat != NULL && (strcmp(cautat->number, temp))){
							cautat = cautat->next;
						}
						if(cautat != NULL && cautat->inserted == true) {
							printf("%d\n", cautat->balance);
							InsertHistory(&(cautat->history), true, bufAux);
							fprintf(fd2, "%d\n", cautat->balance);
							cancel(&(cautat));
						}

					}
					start = start->next;
				}
				free(temp);

			}

			if(!strcmp(text, "transfer_funds")) {

				nr_card = (char*)malloc(20*sizeof(char));
				temp = (char*)malloc(20*sizeof(char));
				sum = 0;

				text = strtok(NULL, " ");
				strcpy(nr_card, text);
				text = strtok(NULL, " ");
				strcpy(temp, text);
				text = strtok(NULL, "\n");
				money = atoi(text);

				bool ins = false; //true daca card_sursa are destui bani 
									// si suma e multiplu de 10

				sum = sumOfString(nr_card);

				subset = sum % nr_sub;
				sum = 0;

				sum = sumOfString(temp);

				subset1 = sum % nr_sub;

				start = n;
				while(start != NULL) {

					if(start->pos == subset) {
						Card *cautat = start->cardList;
						while(cautat != NULL && (strcmp(cautat->number, nr_card))){
							cautat = cautat->next;
						}

						if(cautat != NULL && cautat->inserted == true) {

								ret_value = minusTransaction(&(cautat), money);

								if(ret_value == 0) {

									InsertHistory(&(cautat->history), true, bufAux);
									printf("%d\n", cautat->balance);
									fprintf(fd2, "%d\n", cautat->balance);
									ins = true;
									cancel(&(cautat));
								}
								if(ret_value == 11) {

									InsertHistory(&(cautat->history), false, bufAux);
									fprintf(fd2, "The transferred amount must be multiple of 10\n");
									printf("The transferred amount must be multiple of 10\n");
									ins = false;
									cancel(&(cautat));

								}
								if(ret_value == 12) {

									InsertHistory(&(cautat->history), false, bufAux);
									fprintf(fd2, "Insufficient funds\n");
									ins = false;
									cancel(&(cautat));
								}

						}

					}
					start = start->next;
				}

				start = n;
				while(start != NULL) {

					if(ins == true) {

						if(start->pos == subset1) {
							Card *cautat = start->cardList;
							while(cautat != NULL && (strcmp(cautat->number, temp))){
								cautat = cautat->next;
							}
							if(cautat != NULL) {
								ret_value = plusTransaction(&(cautat), money);
								if(ret_value == 0) {
									InsertHistory(&(cautat->history), true, bufAux);
								}
							}


						}
					}
					start = start->next;
				}
				ins = false;
				free(nr_card);
				free(temp);

			}

			if(!strcmp(text, "pin_change")) {

				nr_card = (char*)malloc(20*sizeof(char));
				pin = (char*)malloc(5*sizeof(char));
				sum = 0;

				text = strtok(NULL, " ");
				strcpy(nr_card, text);
				text = strtok(NULL, "\n");
				strcpy(pin, text);

				sum = sumOfString(nr_card);

				subset = sum % nr_sub;
				sum = 0;

					start = n;
					while(start != NULL) {
						if(start->pos == subset) {
							Card *cautat = start->cardList;

							while(cautat != NULL && (strcmp(cautat->number, nr_card))){
								cautat = cautat->next;
							}
							
							if(cautat != NULL) {
								if(cautat->inserted) {

									ret_value = pinChange(&(cautat), pin);

									cancel(&(cautat));

									if(ret_value == 0) {

										InsertHistory(&(cautat->history), true, bufAux);
									}
									if(ret_value == 12) {

										InsertHistory(&(cautat->history), false, bufAux);
										fprintf(fd2, "Invalid PIN\n");
									}
								}
							}
						}
						start = start->next;
					}

				free(nr_card);
				free(pin);

			}

			if(!strcmp(text, "cancel")) {

				temp = (char*)malloc(20*sizeof(char));
				sum = 0;

				text = strtok(NULL, "\n");
				strcpy(temp, text);

				sum = sumOfString(temp);

				subset = sum % nr_sub;
				sum = 0;

				start = n;
				while(start != NULL) {
					if(start->pos == subset) {

						Card *cautat = start->cardList;

						while(cautat != NULL && (strcmp(cautat->number, temp))){
							cautat = cautat->next;
						}
						if(cautat!=NULL && cautat->inserted == true) {

							InsertHistory(&(cautat->history), true, bufAux);

							cautat->inserted = false;

						}

					}
					start = start->next;
				}

			}
			
		}

	}

	free(buffer);
	free(bufRez);
	free(bufAux);
	fclose(fd);
	fclose(fd2);
	return 0;

}
