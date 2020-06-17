/* CREMENESCU RAUL-VALENTIN - 341C5 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include "List.h"
#include "parse.h"

int main()
{
    char *str;
    t_db *db = NULL;
    int returnCode;

    str = (char*)malloc(MAX_CMD_LEN * sizeof(char));
    db = (t_db *)malloc(sizeof(t_db));
    memset(db, 0, sizeof(t_db));

    t_db *start = db;

    while(fgets(str, MAX_CMD_LEN, stdin)) {
        returnCode = ParseCmd(str, &start);
        if(returnCode == 200) {
        	break;
        }
    }
    return 0;

}
