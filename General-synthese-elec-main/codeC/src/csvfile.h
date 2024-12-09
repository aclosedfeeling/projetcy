#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#ifndef __CSV_H__
#define __CSV_H__

typedef struct CSVFile
{
	char *path;
	char **column;
	char ***content;
	
	int columnCount;
	int lineCount;
	
}CSVFile;

CSVFile openCSV(char *path);
int readLine(char **buff, FILE *f);
void CSVFile_createColumns(char *buff, CSVFile *csv);
void CSVFile_addLine(char *buff, CSVFile *csv);
void CSVFile_extractContent(FILE *f, CSVFile *csv);
#endif