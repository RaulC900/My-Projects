/* CREMENESCU RAUL-VALENTIN - 341C5 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include "List.h"
#include "data.h"

void DeleteIntOccurence(t_intCell *cells)
{
	t_intCell *aux;

	while(cells){
		aux = cells;
		cells = cells->next;
		free(aux);
	}
}

void DeleteFloatOccurence(t_floatCell *cells)
{
	t_floatCell *aux;

	while(cells){
		aux = cells;
		cells = cells->next;
		free(aux);
	}
}

void DeleteStringOccurence(t_stringCell *cells)
{
	t_stringCell *aux;

	while(cells){
		aux = cells;
		cells = cells->next;
		free(aux);
	}
}

void RemoveChar(char *str, char character)
{

    char *src, *dst;
    for (src = dst = str; *src != '\0'; src++) {
        *dst = *src;
        if (*dst != character) dst++;
    }
    *dst = '\0';
}

int isEmptyTable(t_table **tables)
{
	return (*tables) == NULL;
}

int isEmptyColumns(t_column **columns)
{
	return (*columns) == NULL;
}

int isEmptyIntLines(t_intLine **line)
{
	return (*line) == NULL;
}

int isEmptyFloatLines(t_floatLine **line)
{
	return (*line) == NULL;
}

int isEmptyStringLines(t_stringLine **line)
{
	return (*line) == NULL;
}

int isEmptyIntCell(t_intCell **cell)
{
	return (*cell) == NULL;
}

int isEmptyFloatCell(t_floatCell **cell)
{
	return (*cell) == NULL;
}

int isEmptyStringCell(t_stringCell **cell)
{
	return (*cell) == NULL;
}

int InitDB(char *name, t_db **db)
{
    strncpy((*db)->name, name, MAX_DB_NAME_LEN);
    return 0;
}

int IntrodTable(char *tableName, char *cellType, t_db ** db)
{
    t_table *aux = malloc(sizeof(t_table));
	memset(aux, 0, sizeof(t_table));
    t_table *tables = (*db)->tables;

    if(aux) {

        aux->columns = NULL;
        aux->next = NULL;

        strncpy(aux->name, tableName, MAX_TABLE_NAME_LEN);

        if(strcmp(cellType, "INT") == 0) {
            aux->type = INT;
        
        } else if(strcmp(cellType, "FLOAT") == 0) {
            aux->type = FLOAT;
        
        } else if(strcmp(cellType, "STRING") == 0) {
            aux->type = STRING;
        
        } else {
            printf("Unknown data type: %s.\n", cellType);
            return 1;
        }

    } else if(!aux) {
		return 100;
	}
    
    if(isEmptyTable(&tables)) {
        (*db)->tables = aux;
        return 0;

    } else {
        tables = (*db)->tables;

        while(tables->next != NULL) {
            tables = tables->next;
        }

        if(strcmp(tables->name, tableName) == 0) {
			printf("Table %s already exists.\n", tableName);
			return 5;
		}
        
        tables->next = aux;    
    }

    return 0;
}

int PrintTable(char *name, t_db ** db)
{
    t_table *tables = (*db)->tables;

	while(tables != NULL && (strcmp(tables->name, name) != 0)) {
		tables = tables->next;
	}

    if(tables == NULL) {
    	printf("Table \"%s\" not found in database.\n", name);
		return 1;
    }

    t_column *columns = tables->columns;

    if(strcmp(columns->name, "") == 0) {
		return 1;
    }

	printf("TABLE: %s\n", tables->name);

	if(isEmptyColumns(&(tables->columns))){
		return 1;
	}

	columns = tables->columns;

	char out[MAX_COLUMN_NAME_LEN];

	// printez coloanele
	while(columns != NULL) {
		memset(out, ' ', MAX_COLUMN_NAME_LEN - strlen(columns->name));
		out[MAX_COLUMN_NAME_LEN - strlen(columns->name)] = 0;

		char *auxName;
		auxName = (char *)malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
		strncpy(auxName, columns->name, MAX_COLUMN_NAME_LEN);

		RemoveChar(auxName, '\n');
		strncpy(columns->name, auxName, MAX_COLUMN_NAME_LEN);

		printf("%s", columns->name);
		printf("%s", out);
		printf(" ");

		columns = columns->next;

		free(auxName);
	}

	printf("\n");

	// out este aici linia cu ----- pentru fiecare coloana
	memset(out, '-', MAX_COLUMN_NAME_LEN);
	out[MAX_COLUMN_NAME_LEN] = ' ';
	out[MAX_COLUMN_NAME_LEN + 1] = 0;

	columns = tables->columns;

	while(columns != NULL) {
		printf("%s", out);
		columns =	columns->next;
	}

	printf("\n");

	columns = tables->columns;

	// printez liniile
	if(tables->type == INT) { //in functie de ce tip este tabelul
		t_intLine *lines = tables->lines;
		t_intCell *cells;

		while(lines != NULL) {
			cells = lines->cells;

			char out[MAX_COLUMN_NAME_LEN];

			while(cells != NULL) {
				char *str = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
				sprintf(str, "%d", cells->value);

				// out este aici restul de ' ' pana la urm coloana
				memset(out, ' ', MAX_COLUMN_NAME_LEN - strlen(str) + 1);
				out[MAX_COLUMN_NAME_LEN - strlen(str) + 1] = 0;

				printf("%d", cells->value);
				printf("%s", out);

				cells = cells->next;
				columns = columns->next;

				free(str);
			}

			columns = tables->columns;
			printf("\n");

			lines = lines->next;
		}

		lines = tables->lines;

	}

	if(tables->type == FLOAT) {
		t_floatLine *lines = tables->lines;
		t_floatCell *cells;

		while(lines != NULL) {
			cells = lines->cells;

			char out[MAX_COLUMN_NAME_LEN];

			while(cells != NULL) {
				char *str = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
				sprintf(str, "%f", cells->value);

				memset(out, ' ', MAX_COLUMN_NAME_LEN - strlen(str) + 1);
				out[MAX_COLUMN_NAME_LEN - strlen(str) + 1] = 0;

				printf("%f", cells->value);
				printf("%s", out);

				cells = cells->next;
				columns = columns->next;
				
				free(str);
			}

			columns = tables->columns;
			printf("\n");

			lines = lines->next;
		}

		lines = tables->lines;

	}

	if(tables->type == STRING) {
		t_stringLine *lines = tables->lines;
		t_stringCell *cells;

		while(lines != NULL) {
			cells = lines->cells;

			char out[MAX_COLUMN_NAME_LEN];

			while(cells != NULL) {
				char *str = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
				sprintf(str, "%s", cells->value);

				memset(out, ' ', MAX_COLUMN_NAME_LEN - strlen(str) + 1);
				out[MAX_COLUMN_NAME_LEN - strlen(str) + 1] = 0;

				printf("%s", cells->value);
				printf("%s", out);

				cells = cells->next;
				columns = columns->next;

				free(str);
			}

			columns = tables->columns;
			printf("\n");

			lines = lines->next;
		}

		lines = tables->lines;

	}
	printf("\n");
    return 0;
}

int IntrodColumns(char *colName, char *tableName, t_db ** db)
{
    t_table *tables = (*db)->tables;

    while(tables != NULL && (strcmp(tables->name, tableName) != 0)) {
		tables = tables->next;
	}

	if(tables == NULL) {
		printf("Table \"%s\" not found in database.\n", tableName);
		return 1;
	}

	t_column *aux = malloc(sizeof(t_column));
	t_column *columns = tables->columns;

	if(aux) {
		aux->next = NULL;
		strncpy(aux->name, colName, MAX_COLUMN_NAME_LEN);

	} else if(!aux) {
		return 1;
	}

	if(isEmptyColumns(&columns)) { // daca este prima coloana introd
		tables->columns = aux;
		return 0;

	} else { // daca nu, punem la sfarsitul listei
		columns = tables->columns;

		while(columns->next != NULL) {
			if(strcmp(columns->name, colName) == 0) {
				return 5;
			}
			columns = columns->next;
		}

		columns->next = aux;
		return 0;
	}
    return 0;

}

int IntrodIntCells(char *value, t_intLine **line)
{
    t_intCell *aux = malloc(sizeof(t_intCell)); //introducere celule in linie
    t_intCell *cells = (*line)->cells;

    if(aux) {
        aux->next = NULL;
        int x;
        x = atoi(value);
        aux->value = x;

    } else if(!aux) {
		return 1;
	}

    if(isEmptyIntCell(&cells)) { // daca e prima celula introd
        (*line)->cells = aux;
        return 0;

    } else {
        cells = (*line)->cells;

        while(cells->next != NULL) {
            cells = cells->next;
        }

        cells->next = aux;
        return 0;
    }
    return 0;
}

int IntrodFloatCells(char *value, t_floatLine **line)
{

    t_floatCell *aux = malloc(sizeof(t_floatCell));
    t_floatCell *cells = (*line)->cells;

    if(aux) {
        aux->next = NULL;
        float x;
        x = atof(value);
        aux->value = x;

    } else if(!aux) {
		return 1;
	}

    if(isEmptyFloatCell(&cells)) {
        (*line)->cells = aux;
        return 0;

    } else {
        cells = (*line)->cells;

        while(cells->next != NULL) {
            cells = cells->next;
        }

        cells->next = aux;
        return 0;

    }

    return 0;

}

int IntrodStringCells(char *value, t_stringLine **line)
{
    t_stringCell *aux = malloc(sizeof(t_stringCell));
    t_stringCell *cells = (*line)->cells;

    if(aux) {
        aux->next = NULL;
        aux->value = value;

    } else if(!aux) {
		return 1;
	}

    if(isEmptyStringCell(&cells)) {
        (*line)->cells = aux;
        return 0;

    } else {
        cells = (*line)->cells;

        while(cells->next != NULL) {
            cells = cells->next;
        }

        cells->next = aux;
        return 0;
    }
    return 0;

}



int IntrodLines(char *value, char *tableName, t_db **db)
{
    t_table *tables = (*db)->tables;

	while(tables != NULL && (strcmp(tables->name, tableName) != 0)) {
		tables = tables->next;
	}

	if(tables == NULL) {
		printf("Table \"%s\" not found in database.\n", tableName);
		return 10;

	}

	t_column *aux = tables->columns;

	if(strcmp(aux->name, "") == 0) {
		printf("Table \"%s\" not found in database.\n", tableName);
		return 1;
	}

	if(tables->type == INT){ // in functie de tipul tabelului
		t_intLine *lines = tables->lines;
		t_intLine *aux = malloc(sizeof(t_intLine));
		memset(aux, 0, sizeof(t_intLine));

		if(aux) {
			aux->next = NULL;

			char *cellValue = strtok(value, " ");

			while(cellValue != NULL) {
				IntrodIntCells(cellValue, &aux); //introducem celulele pe rand
				cellValue = strtok(NULL, " ");
			}

		} else {
			return 1;
		}

		if(isEmptyIntLines(&lines)) {
			tables->lines = aux;
			return 0;

		} else {
			lines = tables->lines;

			while(lines->next != NULL) {
				lines = lines->next;
			}

			lines->next = aux;
			lines = tables->lines;

			while(lines != NULL) {
				t_intCell *head = lines->cells;
				
				while(head != NULL) {
					head = head->next;
				}
				lines = lines->next;
				free(head);
			}
			return 0;
		}

	} else if(tables->type == FLOAT) {
		t_floatLine *lines = tables->lines;
		t_floatLine *aux = malloc(sizeof(t_floatLine));

		if(aux) {
			aux->next = NULL;

			char *cellValue = strtok(value, " ");

			while(cellValue != NULL) {
				IntrodFloatCells(cellValue, &aux);
				cellValue = strtok(NULL, " ");
			}

		} else {
			return 1;
		}

		if(isEmptyFloatLines(&lines)) {
			tables->lines = aux;
			return 0;

		} else {
			lines = tables->lines;

			while(lines->next != NULL) {
				lines = lines->next;
			}

			lines->next = aux;
			lines = tables->lines;

			while(lines != NULL) {
				t_floatCell *head = lines->cells;

				while(head != NULL) {
					head = head->next;
				}
				lines = lines->next;
				free(head);
			}
			return 0;
		}


	} else if(tables->type == STRING) {
		t_stringLine *lines = tables->lines;
		t_stringLine *aux = malloc(sizeof(t_stringLine));

		if(aux) {
			aux->next = NULL;

			char *cellValue = strtok(value, " ");

			while(cellValue != NULL) {
				IntrodStringCells(cellValue, &aux);
				cellValue = strtok(NULL, " ");
			}

		} else {
			return 1;
		}

		if(isEmptyStringLines(&lines)) {
			tables->lines = aux;
			return 0;

		} else {
			lines = tables->lines;

			while(lines->next != NULL) {
				lines = lines->next;
			}

			lines->next = aux;
			lines = tables->lines;

			while(lines != NULL) {
				t_stringCell *head = lines->cells;

				while(head != NULL) {
					head = head->next;
				}
				lines = lines->next;
				free(head);
			}
			return 0;
		}
	}
    return 0;
}

int SearchTable(char *tName, char *cName, char *op, char *opVal, t_db **db)
{
	t_table *tables = (*db)->tables;

	while(tables != NULL && (strcmp(tables->name, tName) != 0)) {
		tables = tables->next;
	}

	if(tables == NULL) {
		printf("Table \"%s\" not found in database.\n", tName);
		return 10;
	}

	t_column *columns = tables->columns;

	while(columns != NULL && (strcmp(columns->name, cName) != 0)) {
		columns = columns->next;
	}

	if(columns == NULL) {
		printf("Table \"%s\" does not contain column \"%s\".\n", tName, cName);
		return 10;
	}

	columns = tables->columns;

	printf("TABLE: %s\n", tables->name);

	if(isEmptyColumns(&(tables->columns))){
		return 1;
	}

	columns = tables->columns;

	char out[MAX_COLUMN_NAME_LEN];

	while(columns != NULL) {
		memset(out, ' ', MAX_COLUMN_NAME_LEN - strlen(columns->name));
		out[MAX_COLUMN_NAME_LEN - strlen(columns->name)] = 0;

		char *auxName;
		auxName = (char *)malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
		strncpy(auxName, columns->name, MAX_COLUMN_NAME_LEN);

		RemoveChar(auxName, '\n');
		strncpy(columns->name, auxName, MAX_COLUMN_NAME_LEN);

		printf("%s", columns->name);
		printf("%s", out);
		printf(" ");

		columns = columns->next;
		free(auxName);
	}

	printf("\n");

	memset(out, '-', MAX_COLUMN_NAME_LEN);
	out[MAX_COLUMN_NAME_LEN] = ' ';
	out[MAX_COLUMN_NAME_LEN + 1] = 0;

	columns = tables->columns;

	while(columns != NULL) {
		printf("%s", out);
		columns = columns->next;
	}

	printf("\n");

	columns = tables->columns;

	if(tables->type == INT) {
		int x = atoi(opVal);
		int opCode;
		t_intLine *lines = tables->lines;
		t_intCell *cells;

		while(lines != NULL) {
			cells = lines->cells;
			columns = tables->columns;

			while(cells != NULL) {
				if(strcmp(op, "!=") == 0) {
					opCode = 0;

				} else if (strcmp(op, "==") == 0) {
					opCode = 1;
				
				} else if (strcmp(op, "<") == 0) {
					opCode = 2;

				} else if (strcmp(op, "<=") == 0) {
					opCode = 3;

				} else if (strcmp(op, ">") == 0) {
					opCode = 4;
				
				} else if (strcmp(op, ">=") == 0) {
					opCode = 5;
				}

				int length = 0;

				//daca celula coresp coloanei din linie respecta cond
				if (cells->value != x
					&& (strcmp(columns->name, cName) == 0) && opCode == 0) {

					columns = tables->columns;
					cells = lines->cells;

					while(columns != NULL) {
						char *str = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
						sprintf(str, "%d", cells->value);
						length = strlen(str);

						memset(out, ' ', MAX_COLUMN_NAME_LEN - length + 1);
						out[MAX_COLUMN_NAME_LEN - length + 1] = 0;

						printf("%d", cells->value);
						printf("%s", out);

						cells = cells->next;
						columns = columns->next;

						free(str);
					}
					printf("\n");
					break;

				} else if (cells->value == x 
					&& (strcmp(columns->name, cName) == 0) && opCode == 1) {

					columns = tables->columns;
					cells = lines->cells;

					while(columns != NULL) {
						char *str = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
						sprintf(str, "%d", cells->value);
						length = strlen(str);

						memset(out, ' ', MAX_COLUMN_NAME_LEN - length + 1);
						out[MAX_COLUMN_NAME_LEN - length + 1] = 0;

						printf("%d", cells->value);
						printf("%s", out);

						cells = cells->next;
						columns = columns->next;

						free(str);
					}
					printf("\n");
					break;

				} else if (cells->value < x 
					&& (strcmp(columns->name, cName) == 0) && opCode == 2) {

					columns = tables->columns;
					cells = lines->cells;

					while(columns != NULL) {
						char *str = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
						sprintf(str, "%d", cells->value);
						length = strlen(str);

						memset(out, ' ', MAX_COLUMN_NAME_LEN - length + 1);
						out[MAX_COLUMN_NAME_LEN - length + 1] = 0;

						printf("%d", cells->value);
						printf("%s", out);

						cells = cells->next;
						columns = columns->next;

						free(str);
					}
					printf("\n");
					break;

				} else if (cells->value <= x 
					&& (strcmp(columns->name, cName) == 0) && opCode == 3) {

					columns = tables->columns;
					cells = lines->cells;

					while(columns != NULL) {
						char *str = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
						sprintf(str, "%d", cells->value);
						length = strlen(str);

						memset(out, ' ', MAX_COLUMN_NAME_LEN - length + 1);
						out[MAX_COLUMN_NAME_LEN - length + 1] = 0;

						printf("%d", cells->value);
						printf("%s", out);

						cells = cells->next;
						columns = columns->next;

						free(str);
					}
					printf("\n");
					break;

				} else if (cells->value > x 
					&& (strcmp(columns->name, cName) == 0) && opCode == 4) {

					columns = tables->columns;
					cells = lines->cells;

					while(columns != NULL) {
						char *str = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
						sprintf(str, "%d", cells->value);
						length = strlen(str);

						memset(out, ' ', MAX_COLUMN_NAME_LEN - length + 1);
						out[MAX_COLUMN_NAME_LEN - length + 1] = 0;

						printf("%d", cells->value);
						printf("%s", out);

						cells = cells->next;
						columns = columns->next;

						free(str);
					}
					printf("\n");
					break;

				} else if (cells->value >= x 
					&& (strcmp(columns->name, cName) == 0) && opCode == 5) {

					columns = tables->columns;
					cells = lines->cells;

					while(columns != NULL) {
						char *str = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
						sprintf(str, "%d", cells->value);
						length = strlen(str);

						memset(out, ' ', MAX_COLUMN_NAME_LEN - length + 1);
						out[MAX_COLUMN_NAME_LEN - length + 1] = 0;

						printf("%d", cells->value);
						printf("%s", out);

						cells = cells->next;
						columns = columns->next;

						free(str);
					}
					printf("\n");
					break;

				}
				cells = cells->next;
				columns = columns->next;
			}
			lines = lines->next;
		}
		printf("\n");
	}

	if(tables->type == FLOAT) {
		float x = atof(opVal);
		int opCode;
		t_floatLine *lines = tables->lines;
		t_floatCell *cells;

		while(lines != NULL) {
			cells = lines->cells;
			columns = tables->columns;

			while(cells != NULL) {
				if(strcmp(op, "!=") == 0) {
					opCode = 0;

				} else if (strcmp(op, "==") == 0) {
					opCode = 1;
				
				} else if (strcmp(op, "<") == 0) {
					opCode = 2;

				} else if (strcmp(op, "<=") == 0) {
					opCode = 3;

				} else if (strcmp(op, ">") == 0) {
					opCode = 4;
				
				} else if (strcmp(op, ">=") == 0) {
					opCode = 5;
				}

				int length = 0;

				if (cells->value != x 
					&& (strcmp(columns->name, cName) == 0) && opCode == 0) {

					columns = tables->columns;
					cells = lines->cells;

					while(columns != NULL) {
						char *str = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
						sprintf(str, "%f", cells->value);
						length = strlen(str);

						memset(out, ' ', MAX_COLUMN_NAME_LEN - length + 1);
						out[MAX_COLUMN_NAME_LEN - length + 1] = 0;

						printf("%f", cells->value);
						printf("%s", out);

						cells = cells->next;
						columns = columns->next;

						free(str);
					}
					printf("\n");
					break;

				} else if (cells->value == x 
					&& (strcmp(columns->name, cName) == 0) && opCode == 1) {

					columns = tables->columns;
					cells = lines->cells;

					while(columns != NULL) {
						char *str = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
						sprintf(str, "%f", cells->value);
						length = strlen(str);

						memset(out, ' ', MAX_COLUMN_NAME_LEN - length + 1);
						out[MAX_COLUMN_NAME_LEN - length + 1] = 0;

						printf("%f", cells->value);
						printf("%s", out);

						cells = cells->next;
						columns = columns->next;

						free(str);
					}
					printf("\n");
					break;

				} else if (cells->value < x 
						&& (strcmp(columns->name, cName) == 0) && opCode == 2) {

					columns = tables->columns;
					cells = lines->cells;

					while(columns != NULL) {
						char *str = malloc(MAX_COLUMN_NAME_LEN * sizeof(char));
						sprintf(str, "%f", cells->value);
						length = strlen(str);

						memset(out, ' ', MAX_COLUMN_NAME_LEN - length + 1);
						out[MAX_COLUMN_NAME_LEN - length + 1] = 0;

						printf("%f", cells->value);
						printf("%s", out);

						cells = cells->next;
						columns = columns->next;

						free(str);
					}
					printf("\n");
					break;

				} else if (cells->value <= x 
					&& (strcmp(columns->name, cName) == 0) && opCode == 3) {

					columns = tables->columns;
					cells = lines->cells;

					while(columns != NULL) {
						char *str = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
						sprintf(str, "%f", cells->value);
						length = strlen(str);

						memset(out, ' ', MAX_COLUMN_NAME_LEN - length + 1);
						out[MAX_COLUMN_NAME_LEN - length + 1] = 0;

						printf("%f", cells->value);
						printf("%s", out);

						cells = cells->next;
						columns = columns->next;

						free(str);
					}
					printf("\n");
					break;

				} else if (cells->value > x 
					&& (strcmp(columns->name, cName) == 0) && opCode == 4) {

					columns = tables->columns;
					cells = lines->cells;

					while(columns != NULL) {
						char *str = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
						sprintf(str, "%f", cells->value);
						length = strlen(str);

						memset(out, ' ', MAX_COLUMN_NAME_LEN - length + 1);
						out[MAX_COLUMN_NAME_LEN - length + 1] = 0;

						printf("%f", cells->value);
						printf("%s", out);

						cells = cells->next;
						columns = columns->next;

						free(str);
					}
					printf("\n");
					break;

				} else if (cells->value >= x 
					&& (strcmp(columns->name, cName) == 0) && opCode == 5) {

					columns = tables->columns;
					cells = lines->cells;

					while(columns != NULL) {
						char *str = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
						sprintf(str, "%f", cells->value);
						length = strlen(str);

						memset(out, ' ', MAX_COLUMN_NAME_LEN - length + 1);
						out[MAX_COLUMN_NAME_LEN - length + 1] = 0;

						printf("%f", cells->value);
						printf("%s", out);

						cells = cells->next;
						columns = columns->next;

						free(str);
					}
					printf("\n");
					break;
				}
				cells = cells->next;
				columns = columns->next;
			}
			lines = lines->next;
		}
		printf("\n");
	}

	if(tables->type == STRING) {

		t_stringLine *lines = tables->lines;
		t_stringCell *cells;
		int opCode;

		while(lines != NULL) {
			cells = lines->cells;
			columns = tables->columns;

			while(cells != NULL) {
				char char1, char2;
				char *string1 = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
				strncpy(string1, cells->value, MAX_COLUMN_NAME_LEN);

				char1 = string1[0];

				char2 = opVal[0];

				if(strcmp(op, "!=") == 0) {
					opCode = 0;

				} else if (strcmp(op, "==") == 0) {
					opCode = 1;
				
				} else if (strcmp(op, "<") == 0) {
					opCode = 2;

				} else if (strcmp(op, "<=") == 0) {
					opCode = 3;

				} else if (strcmp(op, ">") == 0) {
					opCode = 4;
				
				} else if (strcmp(op, ">=") == 0) {
					opCode = 5;
				}

				int length = 0;

				if((strcmp(cells->value, opVal) != 0) 
					&& (strcmp(columns->name, cName) == 0) && opCode == 0) {

					columns = tables->columns;
					cells = lines->cells;

					while(columns != NULL) {
						char *str = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
						sprintf(str, "%s", cells->value);
						length = strlen(str);

						memset(out, ' ', MAX_COLUMN_NAME_LEN - length + 1);
						out[MAX_COLUMN_NAME_LEN - length + 1] = 0;

						printf("%s", cells->value);
						printf("%s", out);

						cells = cells->next;
						columns = columns->next;

						free(str);
					}
					printf("\n");
					break;

				} else if ((strcmp(cells->value, opVal) == 0) 
					&& (strcmp(columns->name, cName) == 0) && opCode == 1) {

					columns = tables->columns;
					cells = lines->cells;

					while(columns != NULL) {
						char *str = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
						sprintf(str, "%s", cells->value);
						length = strlen(str);

						memset(out, ' ', MAX_COLUMN_NAME_LEN - length + 1);
						out[MAX_COLUMN_NAME_LEN - length + 1] = 0;

						printf("%s", cells->value);
						printf("%s", out);

						cells = cells->next;
						columns = columns->next;

						free(str);
					}
					printf("\n");
					break;

				} else if ((char1 < char2) 
					&& (strcmp(columns->name, cName) == 0) && opCode == 2) {

					columns = tables->columns;
					cells = lines->cells;

					while(columns != NULL) {
						char *str = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
						sprintf(str, "%s", cells->value);
						length = strlen(str);

						memset(out, ' ', MAX_COLUMN_NAME_LEN - length + 1);
						out[MAX_COLUMN_NAME_LEN - length + 1] = 0;

						printf("%s", cells->value);
						printf("%s", out);

						cells = cells->next;
						columns = columns->next;

						free(str);
					}
					printf("\n");
					break;

				} else if ((char1 <= char2) 
					&& (strcmp(columns->name, cName) == 0) && opCode == 3) {

					columns = tables->columns;
					cells = lines->cells;

					while(columns != NULL) {
						char *str = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
						sprintf(str, "%s", cells->value);
						length = strlen(str);

						memset(out, ' ', MAX_COLUMN_NAME_LEN - length + 1);
						out[MAX_COLUMN_NAME_LEN - length + 1] = 0;

						printf("%s", cells->value);
						printf("%s", out);

						cells = cells->next;
						columns = columns->next;

						free(str);
					}
					printf("\n");
					break;

				} else if ((char1 > char2) 
					&& (strcmp(columns->name, cName) == 0) && opCode == 4) {

					columns = tables->columns;
					cells = lines->cells;

					while(columns != NULL) {
						char *str = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
						sprintf(str, "%s", cells->value);
						length = strlen(str);

						memset(out, ' ', MAX_COLUMN_NAME_LEN - length + 1);
						out[MAX_COLUMN_NAME_LEN - length + 1] = 0;

						printf("%s", cells->value);
						printf("%s", out);

						cells = cells->next;
						columns = columns->next;

						free(str);
					}
					printf("\n");
					break;

				} else if ((char1 >= char2) 
					&& (strcmp(columns->name, cName) == 0) && opCode == 5) {

					columns = tables->columns;
					cells = lines->cells;

					while(columns != NULL) {
						char *str = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
						sprintf(str, "%s", cells->value);
						length = strlen(str);

						memset(out, ' ', MAX_COLUMN_NAME_LEN - length + 1);
						out[MAX_COLUMN_NAME_LEN - length + 1] = 0;

						printf("%s", cells->value);
						printf("%s", out);

						cells = cells->next;
						columns = columns->next;

						free(str);
					}
					printf("\n");
					break;
				}
				cells = cells->next;
				columns = columns->next;
			}
			lines = lines->next;
		}
		printf("\n");
	}
	return 5;
}

int DeleteLine(char *tName, char *cName, char *op, char *opVal, t_db **db)
{
	t_table *tables = (*db)->tables;
	bool foundLine = false;

	while(tables != NULL && (strcmp(tables->name, tName) != 0)) {
		tables = tables->next;
	}

	if(tables == NULL) {
		printf("Table \"%s\" not found in database.\n", tName);
		return 1;
	}

	t_column *columns = tables->columns;

	while(columns != NULL && (strcmp(columns->name, cName) != 0)) {
		columns = columns->next;
	}

	if(columns == NULL) {
		printf("Table \"%s\" does not contain column \"%s\".\n", tName, cName);
		return 10;
	}

	columns = tables->columns;

	if(tables->type == INT) {
		int x = atoi(opVal);
		t_intLine *lines = tables->lines;
		t_intLine *previous = tables->lines;

		while(lines != NULL) {
			t_intCell *cells = lines->cells;
			columns = tables->columns;
			foundLine = false;

			while(cells != NULL) {

				if(strcmp(columns->name, cName) == 0) {

					if(strcmp(op, "<") == 0) {

						if(cells->value < x) {
							foundLine = true;
						}
					}
					if(strcmp(op, "<=") == 0) {

						if(cells->value <= x) {
							foundLine = true;
						}
					}
					if(strcmp(op, ">") == 0) {

						if(cells->value > x) {
							foundLine = true;
						}
					}
					if(strcmp(op, ">=") == 0) {

						if(cells->value >= x) {
							foundLine = true;
						}
					}
					if(strcmp(op, "==") == 0) {

						if(cells->value == x) {
							foundLine = true;
						}
					}
					if(strcmp(op, "!=") == 0) {

						if(cells->value != x) {
							foundLine = true;
						}
					}
					break;
				}
				columns = columns->next;
				cells = cells->next;
			}

			if(foundLine == true) { // daca este in capul listei

				bool firstLine = false;
				if(previous == tables->lines && lines == tables->lines){
					tables->lines = lines->next;
					firstLine = true;

				} else { // daca nu este in cap
					previous->next = lines->next;
				}

				DeleteIntOccurence(lines->cells);
				free(lines);

				if(firstLine){ // pointam catre next
					lines = tables->lines;
					previous = tables->lines;

				} else { // refacem leg cu linia de dupa cea stearsa
					lines = previous->next;
				}

			} else { // iteram prin lista pana gasim linia
				previous = lines;
				lines = lines->next;
			}



		}


	}
	if(tables->type == FLOAT) { // acelasi lucru ca mai sus

		float x = atof(opVal);
		t_floatLine *lines = tables->lines;
		t_floatLine *previous = tables->lines;

		while(lines != NULL) {
			t_floatCell *cells = lines->cells;
			columns = tables->columns;
			foundLine = false;

			while(cells != NULL) {

				if(strcmp(columns->name, cName) == 0) {

					if(strcmp(op, "<") == 0) {

						if(cells->value < x) {
							foundLine = true;
						}
					}
					if(strcmp(op, "<=") == 0) {

						if(cells->value <= x) {
							foundLine = true;
						}
					}
					if(strcmp(op, ">") == 0) {

						if(cells->value > x) {
							foundLine = true;
						}
					}
					if(strcmp(op, ">=") == 0) {

						if(cells->value >= x) {
							foundLine = true;
						}
					}
					if(strcmp(op, "==") == 0) {

						if(cells->value == x) {
							foundLine = true;
						}
					}
					if(strcmp(op, "!=") == 0) {

						if(cells->value != x) {
							foundLine = true;
						}
					}
					break;
				}
				columns = columns->next;
				cells = cells->next;
			}

			if(foundLine == true) {

				bool firstLine = false;
				if(previous == tables->lines && lines == tables->lines){
					tables->lines = lines->next;
					firstLine = true;

				} else {
					previous->next = lines->next;
				}

				DeleteFloatOccurence(lines->cells);
				free(lines);

				if(firstLine){
					lines = tables->lines;
					previous = tables->lines;

				} else {
					lines = previous->next;
				}

			} else {
				previous = lines;
				lines = lines->next;
			}

		}


	}

	if(tables->type == STRING) { // acelasi lucru ca mai sus

		t_stringLine *lines = tables->lines;
		t_stringLine *previous = tables->lines;

		while(lines != NULL) {
			t_stringCell *cells = lines->cells;
			columns = tables->columns;
			foundLine = false;

			while(cells != NULL) {

				if(strcmp(columns->name, cName) == 0) {
					char character1, character2;
					char *string1 = malloc(MAX_COLUMN_NAME_LEN *sizeof(char));
					strncpy(string1, cells->value, MAX_COLUMN_NAME_LEN);

					character1 = string1[0];
					character2 = opVal[0];

					if(strcmp(op, "==") == 0) {

						if(strcmp(cells->value, opVal) == 0) {
							foundLine = true;
						}
					}
					if(strcmp(op, "!=") == 0) {

						if(strcmp(cells->value, opVal) != 0) {
							foundLine = true;
						}
					}
					if(strcmp(op, "<") == 0) {

						if(character1 < character2) {
							foundLine = true;
						}
					}
					if(strcmp(op, "<=") == 0) {

						if(character1 <= character2) {
							foundLine = true;
						}
					}
					if(strcmp(op, ">") == 0) {

						if(character1 > character2) {
							foundLine = true;
						}
					}
					if(strcmp(op, ">=") == 0) {

						if(character1 >= character2) {
							foundLine = true;
						}
					}
					free(string1);
					break;
				}

				columns = columns->next;
				cells = cells->next;
			}

			if(foundLine == true) {

				bool firstLine = false;
				if(previous == tables->lines && lines == tables->lines){
					tables->lines = lines->next;
					firstLine = true;

				} else {
					previous->next = lines->next;
				}

				DeleteStringOccurence(lines->cells);
				free(lines);

				if(firstLine){
					lines = tables->lines;
					previous = tables->lines;

				} else {
					lines = previous->next;
				}

			} else {
				previous = lines;
				lines = lines->next;
			}
		}
	}
	return 5;
}

int ClearLines(char *tableName, t_db **db)
{
	t_table *tables = (*db)->tables;

	while(tables != NULL && (strcmp(tables->name, tableName) != 0)) {
		tables = tables->next;
	}

	if(tables == NULL) {
		printf("Table \"%s\" not found in database.\n", tableName);
		return 1;
	}

	if(tables->type == INT) { //stergem toate liniile
		t_intLine *lines = tables->lines;
		t_intLine *previous = tables->lines;

		while(lines != NULL) {
			previous = lines;
			lines = lines->next;
			DeleteIntOccurence(previous->cells);
			free(previous);

		}
		tables->lines = NULL;
		return 0;

	} else if (tables->type == FLOAT) { //stergem toate liniile
		t_floatLine *lines = tables->lines;
		t_floatLine *previous = tables->lines;

		while(lines != NULL) {
			previous = lines;
			lines = lines->next;
			DeleteFloatOccurence(previous->cells);
			free(previous);

		}
		tables->lines = NULL;
		return 0;

	} else if (tables->type == STRING) { //stergem toate liniile
		t_stringLine *lines = tables->lines;
		t_stringLine *previous = tables->lines;

		while(lines != NULL) {
			previous = lines;
			lines = lines->next;
			DeleteStringOccurence(previous->cells);
			free(previous);

		}
		tables->lines = NULL;
		return 0;

	}

	return 1;

}

int DeleteTable(char *tableName, t_db **db)
{
	t_db * database = (*db);
	t_table *tables = database->tables;
	t_table *previousTable = database->tables;

	while(tables != NULL && (strcmp(tables->name, tableName) != 0)) {
		previousTable = tables;
		tables = tables->next;
	}

	if(tables == NULL) {
		printf("Table \"%s\" not found in database.\n", tableName);
		return 1;
	}

	if(tables->type == INT) { //stergem toate liniile
		ClearLines(tables->name, &database);

	} else if (tables->type == FLOAT) {
		ClearLines(tables->name, &database);

	} else if (tables->type == STRING) {
		ClearLines(tables->name, &database);

	}

	t_column *columns = tables->columns;
	t_column *previousColumn = tables->columns;

	while(columns != NULL) { // stergem coloanele
		previousColumn = columns;
		columns = columns->next;
		free(previousColumn);

	}

	bool firstTable = false;
	if(previousTable == tables){ // daca este in capul listei
		(*db)->tables = tables->next;
		firstTable = true;

	} else {
		previousTable->next = tables->next;
	}

	free(tables); // stergem tabelul cautat
	tables = NULL;

	if(firstTable){
		tables = (*db)->tables;
		previousTable = (*db)->tables;

	} else {
		tables = previousTable->next;
	}

	return 1;

}

int DeleteDB(t_db **db)
{

	t_db *database = (*db);
	t_table *tables = database->tables;

	while(tables != NULL) { // stergem toate tabelele
		DeleteTable(tables->name, &(database));
		tables = tables->next;

	}
	database->tables = NULL;
	free(database);
	database = NULL;

    return 0;
}