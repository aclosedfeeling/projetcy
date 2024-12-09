#include "station.h"

ElectricalElement *ElectricalElement_Init(char **data){
	
	ElectricalElement *ee = (ElectricalElement *)malloc(sizeof(ElectricalElement));
	
	int i, j, k;
	for(i=COMPANY; i < INDIVIDUAL && !strcmp(data[i], "-");i++);
	for(j=LV_STATION_ID; !strcmp(data[j], "-");j--);
	for(k=j; !strcmp(data[j], "-");k--);
	
	
	if(strcmp(data[i], "-")){ //Si c'est un consomateur
		ee->type = i;
		ee->id = atoi(data[i]);
		ee->capacity = atoi(data[CAPACITY]);
		ee->parentid = atoi(data[k]);
		ee->consumption = atoi(data[LOAD]);
		ee->parenttype = k;
	}else{ //Si c'est une station
		ee->type = j;
		ee->id = atoi(data[j]);
		ee->parentid = atoi(data[(k) ? k-1 : 0]);
		ee->capacity = atoi(data[CAPACITY]);
		ee->consumption = 0;
		ee->parenttype = k-1;
	}
	
	ee->centralid = atoi(data[POWER_PLANT]);
	ee->parentkey = ee->parentid;
	if(ee->type != POWER_PLANT)ee->parentkey = ElectricalElement_getKeyFromChild(ee);
	
	return ee;
}
int ElectricalElement_getKeyFromChild(void *ee){
	ElectricalElement *e = (ElectricalElement *)ee;
	return e->parenttype*__MAX_CATEGORY__ + e->parentid;
}
int ElectricalElement_getKey(void *ee){
	ElectricalElement *e = (ElectricalElement *)ee;
	return e->type*__MAX_CATEGORY__ + e->id;
}
void searchDirectConsumer(AVLNode *node, int parentkey, int *consumption){
	
	if(node == NULL) return;
	ElectricalElement *t = (ElectricalElement *)node->element;
	if(node->left != NULL){
		ElectricalElement *el = (ElectricalElement *)node->left->element;
		if(el->parentkey == parentkey && el->consumption != 0){
			*consumption += el->consumption;
		}
		searchDirectConsumer(node->left, parentkey, consumption);
	}
	
	if(node->right != NULL){
		ElectricalElement *er = (ElectricalElement *)node->right->element;
		if(er->parentkey == parentkey && er->consumption != 0){
			*consumption += er->consumption;
		}	
		searchDirectConsumer(node->right, parentkey, consumption);
	}
	
}
void calculConsommationDirecte(AVLNode *arbre, long int *consommation, long int parentkey, int filter){
	
	ElectricalElement *ee = (ElectricalElement *)(arbre->element);
	
	if(ee->parentkey == parentkey && ee->consumption != 0 && (ee->type == (filter+4) || filter == ALL))*consommation += ee->consumption;

	if(arbre->left !=NULL )calculConsommationDirecte(arbre->left, consommation, parentkey, filter);
	if(arbre->right !=NULL )calculConsommationDirecte(arbre->right, consommation, parentkey, filter);
}
void rechercheSousStation(AVLNode *arbre, long int parentkey, long int **stations, long int *nstations){
	
	if(*stations == NULL) *stations = (long int *)malloc(sizeof(long int));
	ElectricalElement *ee = (ElectricalElement *)(arbre->element);
	
	if(ee->parentkey == parentkey && ee->consumption == 0 && arbre->key != parentkey){
		*nstations+=1;
		*stations = (long int *)realloc(*stations, sizeof(long int) * (*nstations));
		(*stations)[(*nstations)-1] = arbre->key;
	}
	
	if(arbre->left !=NULL )rechercheSousStation(arbre->left, parentkey, stations, nstations);
	if(arbre->right !=NULL )rechercheSousStation(arbre->right, parentkey, stations, nstations);
}
long int calculConsommation(AVLNode *node, int key, int filter){
	
	long int consumption=0, *stationskey=NULL, nstations=0;
	
	calculConsommationDirecte(node, &consumption, key, filter);
	rechercheSousStation(node, key, &stationskey, &nstations);
	
	for(int i = 0 ; i < nstations ; i++){
		consumption += calculConsommation(node, stationskey[i], filter);
	}
	
	free(stationskey);
	
	return consumption;
}