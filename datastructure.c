
/*

Data structure for Polish File Format

Based on: cGPSmapper-UsrMan-v02.4.3.pdf
Source: http://cgpsmapper.com/manual.htm

*/

/*
struct pointCoord {
	int x;
	int y;
	int z;
	struct pointCoord *next;
};
typedef struct pointCoord point;
*/

#include <stdio.h>
#include <string.h>
#include "stringhandling.h" 
#include "datastructure.h" 

/*
	workptr = (psngr_rec*)malloc(sizeof(point));
	if (workptr == NULL) { printf("Error building the dynamic list\n");
		return 1;
	}
	actptr->nextrec = workptr; // Build the chain
	//structptr->structfield // or the next are the same
    //(*structptr).structfield
*/

/*
when reading the polish format file
	- type found - opening object tag [type] - getObjectList(type), set activeObjectList
	- first line of object - addObjectToObjectList(activeObjectList), set activeObject
	- reading first attribute - addAttributeToObject(activeObject, sKey, sValue)
	- reading first point - addPointToObject(activeObject, x, y, p)
*/

void initDataStructure(void) {
	rootObjectList=NULL;
	activeObjectList=NULL;
	activeObject=NULL;
	//todo - check to make sure default values are correct
	minx=40000.0; //out of range for sure [36000km]
	maxx=-40000.0;
	//miny=-11.0; //depth in km
	//maxy=11.0; //height in km
	miny=0.0; //depth in km
	maxy=0.0; //height in km
	minz=40000.0;
	maxz=-40000.0;
	centerx=0.0;
	centery=0.0;
	centerz=0.0;

	minlat=400.0; //out of range for sure [-180;180]
	maxlat=-400.0;
	minlon=400.0;
	maxlon=-400.0;
	centerlat=0.0;
	centerlon=0.0;

	poi=0;
}

/*

Attribute

*/

attribute *addAttribute(attribute *curA, char *sKey, char *sValue) {
	//Adds a new attribute after attribute curA
	attribute *newA;
	newA=(attribute*)malloc(sizeof(attribute));
	if (newA == NULL) {
		printf("Can not allocate memory for next attribute!\n");
		return NULL;
	}
	if (curA != NULL) {
		curA->next=newA;
	}
	char *sTmp;
	newA->sKey=(char*)malloc(sizeof(char) * (strlen(sKey)+1)); //todo - error handling for malloc
	strcpy(newA->sKey, sKey);
	sTmp=newA->sKey;
	//todo erre szukseg van?, string vege...
	sTmp[strlen(sKey)]='\0';
	newA->sValue=(char*)malloc(sizeof(char) * (strlen(sValue)+1)); //todo - error handling for malloc
	strcpy(newA->sValue, sValue);
	sTmp=newA->sValue;
	//todo erre szukseg van?, string vege...
	sTmp[strlen(sValue)]='\0';
	newA->prev=curA;
	newA->next=NULL;
	return newA;
}

attribute *addAttributeToObject(object *curO, char *sKey, char *sValue) {
	//Adds a new attribute to the object curO
	if (curO == NULL) {
		printf("Can not add new attribute to object NULL!\n");
		return NULL;
	}
	attribute *newA;
	if (curO->firstAttribute == NULL) {
		newA=addAttribute(NULL, sKey, sValue);
		curO->firstAttribute=newA;
	} else {
		newA=addAttribute(curO->lastAttribute, sKey, sValue);
	}
	curO->lastAttribute=newA;
	return newA;
}

int numberOfAttributes(attribute *curA) {
	//Returns number of attributes starting from attribute curA inclusive 
	int i=0;
	while (curA != NULL) {
		i++;
		curA=curA->next;
	}
	return i;
}

void deleteAttributeChain(attribute *curA) {
	//Deletes point curP and all following points
	//freeing a NULL pointer does not do anything, no error is generated, no need to check
	if (curA->next != NULL) {
		deleteAttributeChain(curA->next);
	}
	if (curA->prev != NULL) {
		(curA->prev)->next=NULL;
	}
	free(curA->sKey);
	free(curA->sValue);
	free(curA);
}

/*

Point

*/

point *addPoint(point *curP, float lat, float lon) {
	//Adds a new point after point curP
	point *newP;
	newP=(point*)malloc(sizeof(point));
	if (newP == NULL) {
		printf("Can not allocate memory for next point!\n");
		return NULL;
	}
	if (curP != NULL) {
		curP->next=newP;
	}
	newP->lat=lat;
	newP->lon=lon;
	newP->prev=curP;
	newP->next=NULL;

	//set border values
	if (lat<minlat) minlat=lat;
	if (lon<minlon) minlon=lon;
	if (lat>maxlat) maxlat=lat;
	if (lon>maxlon) maxlon=lon;
	return newP;
}

point *addPointToObject(object *curO, float lat, float lon) {
	//Adds a new point to the object curO
	if (curO == NULL) {
		printf("Can not add new point to object NULL!\n");
		return NULL;
	}
	point *newP;
	if (curO->firstPoint == NULL) {
		newP=addPoint(NULL, lat, lon);
		curO->firstPoint=newP;
	} else {
		newP=addPoint(curO->lastPoint, lat, lon);
	}
	curO->lastPoint=newP;
	return newP;
}

int numberOfPoints(point *curP) {
	//Returns number of points starting from point curP inclusive 
	int i=0;
	while (curP != NULL) {
		i++;
		curP=curP->next;
	}
	return i;
}

void deletePointChain(point *curP) {
	//Deletes point curP and all following points
	if (curP->next != NULL) {
		deletePointChain(curP->next);
	}
	if (curP->prev != NULL) {
		(curP->prev)->next=NULL;
	}
	free(curP);
}

/*

Object

*/

object *addObject(object *curO) {
	//Adds a new object after object curO
	object *newO;
	newO=(object*)malloc(sizeof(object));
	if (newO == NULL) {
		printf("Can not allocate memory for new object!\n");
		return NULL;
	}
	if (curO != NULL) {
		curO->next=newO;
	}
	newO->firstAttribute=NULL;
	newO->lastAttribute=NULL;
	newO->firstPoint=NULL;
	newO->lastPoint=NULL;
	newO->prev=curO;
	newO->next=NULL;
	return newO;
}

object *addObjectToObjectList(objectList *curOL) {
	//Adds a new object to the object list curOL
	if (curOL == NULL) {
		printf("Can not add new object to object list NULL!\n");
		return NULL;
	}
	object *newO;
	if (curOL->firstObject == NULL) {
		newO=addObject(NULL);
		curOL->firstObject=newO;
	} else {
		newO=addObject(curOL->lastObject);
	}
	curOL->lastObject=newO;
	return newO;
}


int numberOfObjects(object *curO) {
	//Returns number of objects starting from object curO inclusive
	int i=0;
	while (curO != NULL) {
		i++;
		curO=curO->next;
	}
	return i;
}

void deleteObjectChain(object *curO) {
	//Deletes object curO and all following objects	 
	if (curO->next != NULL) {
		deleteObjectChain(curO->next);
	}
	if (curO->prev != NULL) {
		(curO->prev)->next=NULL;
	}
	deleteAttributeChain(curO->firstAttribute);
	deletePointChain(curO->firstPoint);
	free(curO);
}

/*

Object list

*/

objectList *addObjectList(objectList *curOL, char *sType) {
	//Adds an new object list of type after object list curOL
	// 

printf("------------adding objectlist %s\n", sType);
	objectList *newOL;
	newOL=(objectList*)malloc(sizeof(objectList));
	if (newOL == NULL) {
		printf("Can not allocate memory for new object list!\n");
		return NULL;
	}
	if (curOL != NULL) {
		curOL->next=newOL;
	}
	newOL->sType=(char*)malloc(sizeof(char)*(strlen(sType)+1));
	strcpy(newOL->sType, sType);
	newOL->firstObject=NULL;
	newOL->lastObject=NULL;
	newOL->prev=curOL;
	newOL->next=NULL;
	return newOL;
}

objectList *getLastObjectList(void) {
	if (rootObjectList == NULL) {
		return NULL;
	}
	objectList *curOL;
	curOL=rootObjectList;
	while (curOL->next != NULL) {
		curOL=curOL->next;
	}
	return curOL;
}

objectList *getObjectList(char *sType) {
	//Returns the object list for type, finds if exists or creates if does not exist
	objectList *curOL;
	curOL=findObjectList(sType);
	if (curOL != NULL) {
		//already exists, returning it
		return curOL;
	}
	curOL=addObjectList(getLastObjectList(), sType);
	if (rootObjectList == NULL) {
		//we had no root object list, this will be it
		rootObjectList=curOL;
	}
	return curOL;
}

objectList *findObjectList(char *sType) {
	//Search for an object list of type, starting from the root object list
	if (rootObjectList == NULL) {
		printf("There is no root object list yet, cannot search!\n");
		return NULL;
	}
	objectList *curOL;
	curOL=rootObjectList;
	if (stricmp(curOL->sType, sType) == 0) {
		return curOL;
	}
	while (curOL->next != NULL) {
		curOL=curOL->next;
		if (stricmp(curOL->sType, sType) == 0) {
			return curOL;
		}
	}
	//type was not found
	return NULL;
}

int numberOfObjectsLists(objectList *curOL) {
	//Returns number of objects lists starting from object list curOL inclusive
	int i=0;
	while (curOL != NULL) {
		i++;
		curOL=curOL->next;
	}
	return i;
}

void deleteObjectListChain(objectList *curOL) {
	//Deletes object list curOL and all following object lists	 
	if (curOL->next != NULL) {
		deleteObjectListChain(curOL->next);
	}
	if (curOL->prev != NULL) {
		(curOL->prev)->next=NULL;
	}
	deleteObjectChain(curOL->firstObject);
	free(curOL->sType);
	free(curOL);
}

void printAll(void) {
	if (rootObjectList == NULL) {
		printf("Root object list is NULL, nothing to print!\n");
	} else {
		printf("----------\n");
		printObjectList(rootObjectList, 1);
		printf("----------\n");
	}
}

void printPoint(point *curP, int counter) {
	if (curP == NULL) {
		//printf("NULL(point)");
		printf("\n");
		return;
	} else {
		printf("%d:([%f, %f] %f, %f, %f) ", counter, curP->lat, curP->lon, curP->x, curP->y, curP->z);
	}
	printPoint(curP->next, ++counter);
}

void printAttribute(attribute *curA, int counter) {
	if (curA == NULL) {
		//printf("NULL(attribute)");
		printf("\n");
		return;
	} else {
		printf("%d:(%s=%s) ", counter, curA->sKey, curA->sValue);
	}
	printAttribute(curA->next, ++counter);
}

void printObject(object *curO, int counter) {
	if (curO == NULL) {
		//printf("NULL(object)");
		//printf("\n");
		return;
	} else {
		printf("\tObject: %d\n", counter);
		printf("\t\tAttributes: ");
		printAttribute(curO->firstAttribute, 1);
		printf("\t\tPoints: ");
		printPoint(curO->firstPoint, 1);
	}
	printObject(curO->next, ++counter);
}

void printObjectList(objectList *curOL, int counter) {
	if (curOL == NULL) {
		//printf("NULL(objectList)");
		//printf("\n");
		return;
	} else {
		printf("ObjectList: %d [%s]\n", counter, curOL->sType);
		printObject(curOL->firstObject, 1);
	}
	printObjectList(curOL->next, ++counter);
}

