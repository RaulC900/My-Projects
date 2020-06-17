/* CREMENESCU RAUL-VALENTIN - 341C5 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <fcntl.h>
#include "List.h"

int isEmptyTable(t_table **tables);
int isEmptyColumns(t_column **columns);
int isEmptyIntLines(t_intLine **line);
int isEmptyFloatLines(t_floatLine **line);
int isEmptyStringLines(t_stringLine **line);
int isEmptyIntCell(t_intCell **cell);
int isEmptyFloatCell(t_floatCell **cell);
int isEmptyStringCell(t_stringCell **cell);

void DeleteIntOccurence(t_intCell *cells);
void DeleteFloatOccurence(t_floatCell *cells);
void DeleteStringOccurence(t_stringCell *cells);
int DeleteLine(char *tName, char *cName, char *op, char *opVal, t_db **db);
int ClearLines(char *tableName, t_db **db);
int DeleteTable(char *tableName, t_db **db);
int DeleteDB(t_db **db);

void RemoveChar(char *str, char newline);

int InitDB(char *name, t_db **db);
int IntrodTable(char *tableName, char *cellType, t_db **db);
int IntrodColumns(char *colName, char *tableName, t_db **db);
int IntrodLines(char *value, char *tableName, t_db **db);
int IntrodIntCells(char *value, t_intLine **line);
int IntrodFloatCells(char *value, t_floatLine **line);
int IntrodStringCells(char *value, t_stringLine **line);

int SearchTable(char *tName, char *cName, char *op, char *opVal, t_db **db);
int PrintTable(char *name, t_db **db);
