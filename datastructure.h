/*
struct pointCoord {
	int x;
	int y;
	int z;
	struct pointCoord *next;
};
typedef struct pointCoord point;
*/

#ifndef __datastructure_h_ 
#define __datastructure_h_

typedef struct point {
	float x;
	float y;
	float z;
	float lat;
	float lon;
	double v[3];
	struct point *prev;
	struct point *next;
} point;

typedef struct attribute {
	char *sKey;
	char *sValue;
	struct attribute *prev;
	struct attribute *next;
} attribute;

typedef struct object {
	attribute *firstAttribute;
	attribute *lastAttribute;
	point *firstPoint;
	point *lastPoint;
	struct object *prev;
	struct object *next;
} object;

typedef struct objectList {
	char *sType;
	object *firstObject;
	object *lastObject;
	struct objectList *prev;
	struct objectList *next;
} objectList;

//globals moved to datastructure.c and datastructure_globals.h separate header file

/*
objectList *rootObjectList;
objectList *activeObjectList;
object *activeObject;
point *activePoint;

float minx, maxx, miny, maxy, minz, maxz, centerx, centery, centerz;
float minlat, maxlat, minlon, maxlon, centerlat, centerlon;
float centerlatRad, centerlonRad, centerlatSin, centerlatCos, centerlonSin, centerlonCos;
float minlatRad, minlonRad, minlatSin, minlatCos, minlonSin, minlonCos;
int dlNet;
int poi, dlPoi;
int polygon, dlPolygon;
int polyline, dlPolyline;
*/

/*
	workptr = (psngr_rec*)malloc(sizeof(point));
	if (workptr == NULL) { printf("Error building the dynamic list\n");
		return 1;
	}
	actptr->nextrec = workptr; // Build the chain
	//structptr->structfield // or the next are the same
    //(*structptr).structfield
*/

void initDataStructure(void);

attribute *addAttribute(attribute *curA, char *sKey, char *sValue);
attribute *addAttributeToObject(object *curO, char *sKey, char *sValue);
int numberOfAttributes(attribute *curA);
void deleteAttributeChain(attribute *curA);

point *addPoint(point *curP, float lat, float lon);
point *addPointToObject(object *curO, float lat, float lon);
int numberOfPoints(point *curP);
void deletePointChain(point *curP);

object *addObject(object *curO);
object *addObjectToObjectList(objectList *curOL);
int numberOfObjects(object *curO);
void deleteObjectChain(object *curO);

objectList *addObjectList(objectList *curOL, char *sType);
objectList *getLastObjectList(void);
objectList *getObjectList(char *sType);
objectList *findObjectList(char *sType);
int numberOfObjectsLists(objectList *curOL);
void deleteObjectListChain(objectList *curOL);


void printAll(void);
void printPoint(point *curP, int counter);
void printAttribute(attribute *curA, int counter);
void printObject(object *curO, int counter);
void printObjectList(objectList *curOL, int counter);

char *getAttribute(object *curO, char *sKey);

#endif /* __datastrucure_h_*/
