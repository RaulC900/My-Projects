/* CREMENESCU RAUL-VALENTIN - 341C5 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include "List.h"
#include "data.h"

int ParseCmd(char *command, t_db **db)
{
    t_db * database = * db;
    char * cmd;
    char * text;
    char * completeCmd;
    char * tableName;
    char * cellType;
    char * columnName;
    char * operator;
    char * operatorValue;
    cmd = (char *)malloc(MAX_CMD_LEN * sizeof(char));
    text = (char *)malloc(MAX_CMD_LEN * sizeof(char*));
    completeCmd = (char *)malloc(MAX_CMD_LEN * sizeof(char));
    tableName = (char *)malloc(MAX_TABLE_NAME_LEN * sizeof(char));
    cellType = (char *)malloc(7 * sizeof(char));
    columnName = (char *)malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
    operator = (char *)malloc(3 * sizeof(char));
    operatorValue = (char *)malloc(MAX_COLUMN_NAME_LEN * sizeof(char));

    strncpy(cmd, command, MAX_CMD_LEN);
    strncpy(completeCmd, command, MAX_CMD_LEN);
    
    text = strtok(cmd, " ");
    
    if(strcmp(text, "INIT_DB") == 0) {

        text = strtok(NULL, " ");
        InitDB(text, db);
        return 0;

    } else if (strcmp(text, "DELETE_DB\n") == 0) {

    	database = (* db);
        
        DeleteDB(&database);
        return 200;

    } else if (strcmp(text, "CREATE") == 0) {

        database = * db;
        
        text = strtok(NULL, " ");
        strncpy(tableName, text, MAX_TABLE_NAME_LEN);
        
        text = strtok(NULL, " ");
        strcpy(cellType, text);

        IntrodTable(tableName, cellType, &(database));
    
        char * rest = malloc(MAX_TABLE_NAME_LEN * sizeof(char));
        rest = strtok(NULL, " ");

        database = * db;

        while(rest != NULL) {
        	RemoveChar(rest, '\n');
            IntrodColumns(rest, tableName, &(database));
            rest = strtok(NULL, " ");
        }
        return 0;
        
    } else if (strcmp(text, "PRINT_DB\n") == 0) {

        database = *db;
        t_table *tables = database->tables;

        printf("DATABASE: %s", database->name);
        printf("\n");

        while (tables != NULL) {
        	PrintTable(tables->name, &(database));
            tables = tables->next;

        }
        return 0;

    } else if (strcmp(text, "PRINT") == 0) {

        database = * db;

        text = strtok(NULL, "\n");
        strncpy(tableName, text, MAX_TABLE_NAME_LEN);

        PrintTable(tableName, &(database));
        return 0;

    } else if (strcmp(text, "SEARCH") == 0) {

    	database = *db;

        text = strtok(NULL, " ");
        strncpy(tableName, text, MAX_TABLE_NAME_LEN);

        text = strtok(NULL, " ");
        strncpy(columnName, text, MAX_COLUMN_NAME_LEN);

        text = strtok(NULL, " ");
        strncpy(operator, text, 3);

        text = strtok(NULL, " ");
        strncpy(operatorValue, text, MAX_COLUMN_NAME_LEN);
        RemoveChar(operatorValue, '\n');

        SearchTable(tableName, columnName, operator, operatorValue, &(database));
        return 0;

    } else if (strcmp(text, "ADD") == 0) {

        database = * db;

        text = strtok(NULL, " ");
        strncpy(tableName, text, MAX_TABLE_NAME_LEN);

        char * line = strtok(NULL, "\n");

        IntrodLines(line, tableName, &(database));
        return 0;

    } else if (strcmp(text, "DELETE") == 0) {

    	database = *db;

		text = strtok(NULL, " ");
		strncpy(tableName, text, MAX_TABLE_NAME_LEN);
		RemoveChar(tableName, '\n');

		text = strtok(NULL, " ");
		if(text == NULL) {
			DeleteTable(tableName, &database);
			return 0;
		}
		strncpy(columnName, text, MAX_COLUMN_NAME_LEN);

		text = strtok(NULL, " ");
		strncpy(operator, text, 3);

		text = strtok(NULL, " ");
		strncpy(operatorValue, text, MAX_COLUMN_NAME_LEN);
		RemoveChar(operatorValue, '\n');

		DeleteLine(tableName, columnName, operator, operatorValue, &(database));
		return 0;

    }  else if (strcmp(text, "CLEAR") == 0) {

    	database = *db;

        text = strtok(NULL, " ");
        strncpy(tableName, text, MAX_TABLE_NAME_LEN);
        RemoveChar(tableName, '\n');
        
        ClearLines(tableName, &database);
        return 0;

    } else {

    	RemoveChar(completeCmd, '\n');
    	printf("Unknown command: \"%s\".\n", completeCmd);
        return 1;
    }
    return 0;

}
