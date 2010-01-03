#ifndef __datastructure_globals_h_ 
#define __datastructure_globasl_h_

//globals

extern objectList *rootObjectList;
extern objectList *activeObjectList;
extern object *activeObject;
extern point *activePoint;

extern float minx, maxx, miny, maxy, minz, maxz, centerx, centery, centerz;
extern float minlat, maxlat, minlon, maxlon;
extern float centerlatRad, centerlonRad, centerlatSin, centerlatCos, centerlonSin, centerlonCos;
extern float minlatRad, minlonRad, minlatSin, minlatCos, minlonSin, minlonCos;

extern int lod; //active level of details

//display list variables
extern int dlNet;
extern int poi, dlPoi[10];
extern int polygon, dlPolygon[10];
extern int polyline, dlPolyline[10];

extern int iImgId; //used in polishfm.c
extern char *sImgName;


#endif /* __datastrucure_globals_h_*/
