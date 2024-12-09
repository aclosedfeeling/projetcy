#include <stdio.h>
#include <stdlib.h>
#include "csvfile.h"
#include "station.h"
#include "avl.h"

int main(int argc, char *argv[]){
	
	printf("%s", argv[2]);
	printf("Chargement des données %s...\n", argv[1]);
	
	//Création de l'arbre
	AVLNode *arbre;
	
	//Chargement des données
	CSVFile data = openCSV(argv[1]);
	
	//Insertion des noeuds dans l'arbre
	for(int i = 0; i < data.lineCount; i++){	
		ElectricalElement *ee = ElectricalElement_Init(data.content[i]);
		arbre = (!i) ?  AVLNode_init(ee, ElectricalElement_getKey) : AVLNode_insertion(arbre, ee, ElectricalElement_getKey);
	}
	
	//Calcul de la consommation selon le type données
	for(int i = 0; i < data.lineCount; i++){
		ElectricalElement *ee = ElectricalElement_Init(data.content[i]);
		if(atoi(argv[2]) == ee->type){
		printf("Consumption : %ld, %d\n", calculConsommation(arbre, ElectricalElement_getKey(ee), atoi(argv[3])), ElectricalElement_getKey(ee));
		}
	}
	

	return 0;
}