#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include "atm.h"
#include "str_parse.h"


int main(void)
{
	LSC *lsc = NULL;
	LSC *start = lsc;
	ReadFile(&start);
	//printf("%d\n", lsc->pos);
	//display(&lsc);
	deleteAllLSC(&lsc);
	return 0;
}
