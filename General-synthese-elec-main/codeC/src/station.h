#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"

#ifndef __STATION_H__
#define __STATION_H__

#define __MAX_CATEGORY__ 100000000
enum COLUMN_TO_ID
{
	POWER_PLANT = 0,
	HVB_STATION_ID = 1,
	HVA_STATION_ID = 2,
	LV_STATION_ID = 3,
	COMPANY = 4,
	INDIVIDUAL = 5,
	CAPACITY = 6,
	LOAD = 7,
	
};
enum FILTER_ID
{
	COMPANY_ONLY = 0,
	INDIVIDUAL_ONLY = 1,
	ALL = 2,
};
typedef struct ElectricalElement
{
	int id, parentid, parentkey, parenttype;
	int centralid;
	int type;
	int capacity;
	int charge;
	int consumption;
	
}ElectricalElement;

ElectricalElement *ElectricalElement_Init(char **data);
int ElectricalElement_getKey(void *ee);
int ElectricalElement_getKeyFromChild(void *ee);

long int calculConsommation(AVLNode *node, int id, int filter);
#endif