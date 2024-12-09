#include "csvfile.h"

CSVFile openCSV(char *path){
	
	CSVFile csv;
	
	char *buff;
	FILE *f = fopen(path, "r");
	
	if(!f){
		printf("Erreur : Chargement du fichier %s impossible", path);
		fclose(f);
		exit(1);
	}
	
	//Extract column
	readLine(&buff, f);
	CSVFile_createColumns(buff, &csv);
	
	free(buff);
	buff = NULL;
	
	CSVFile_extractContent(f, &csv);
	fclose(f);
	
	return csv;
}
void CSVFile_createColumns(char *buff, CSVFile *csv) {
    int last_index = 0;
    int columnIndex = 0;

    csv->column = NULL;
    csv->columnCount = 0;

    for (int i = 0;; i++) {
        
        if (buff[i] == ';' || buff[i] == '\0') {
            int segmentLength = i - last_index;

            csv->column = (char **)realloc(csv->column, (csv->columnCount + 1) * sizeof(char *));

            csv->column[csv->columnCount] = (char *)malloc((segmentLength + 1) * sizeof(char));

            strncpy(csv->column[csv->columnCount], &buff[last_index], segmentLength);
            csv->column[csv->columnCount][segmentLength] = '\0';

            csv->columnCount++; 

            if (buff[i] == '\0') {
                break; 
            }

            last_index = i + 1;
        }
    }
}
void CSVFile_extractContent(FILE *f, CSVFile *csv) {
	
	char *buff;
	
    csv->content = NULL;
	csv->content = (char ***)malloc(sizeof(char**));
	csv->lineCount = 0;
	
	while(readLine(&buff, f)){
		CSVFile_addLine(buff, csv);
		free(buff);
		buff = NULL;
	}
}
void CSVFile_addLine(char *buff, CSVFile *csv) {
    int last_index = 0;
    int columnIndex = 0;

    csv->lineCount += 1;

    csv->content = (char ***)realloc(csv->content, csv->lineCount * sizeof(char **));

    csv->content[csv->lineCount - 1] = NULL;

    for (int i = 0;; i++) {

        if (buff[i] == ';' || buff[i] == '\0') {
            int segmentLength = i - last_index;

            csv->content[csv->lineCount - 1] = (char **)realloc(
                csv->content[csv->lineCount - 1],
                (columnIndex + 1) * sizeof(char *)
            );

            csv->content[csv->lineCount - 1][columnIndex] = (char *)malloc((segmentLength + 1) * sizeof(char));

            strncpy(csv->content[csv->lineCount - 1][columnIndex], &buff[last_index], segmentLength);
            csv->content[csv->lineCount - 1][columnIndex][segmentLength] = '\0'; 
			
            columnIndex++; 

            if (buff[i] == '\0') {
                break; 
            }

            last_index = i + 1;
        }
    }

    if (csv->columnCount == 0) {
        csv->columnCount = columnIndex;
    }
}
int readLine(char **buff, FILE *f){
	
	char c;
	int size = sizeof(char);
	
	*buff = (char *)malloc(size);
	
	while((c = fgetc(f)) != '\n' && c != EOF){
		
		(*buff)[size-1] = c;
		
		size+=sizeof(char);
		*buff = (char *)realloc(*buff, size + 1);
	}
	
	if(c == EOF){
		return 0;
	}
	
	(*buff)[size-1] = '\0';
	
	return 1;
}
