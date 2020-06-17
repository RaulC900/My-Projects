#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "atm.h"


Card* searchCard(LSC **l, char *id, int nr_sub)
{

	int count, subset;
	int sum = 0;
	LSC *c = *l;
	while(c) {
		for(count = 0; id[count] != '\0'; count++) { /////////se punea si \n in nr_card si ulterior in aux
			sum += (id[count] - '0');

		}
		subset = sum % nr_sub;
		
		if(c->pos == subset) {
			while(c->cardList != NULL && (strcmp(c->cardList->number, id)))
				c->cardList = c->cardList->next;

			return c->cardList;
		}
	}

	return 0;
}