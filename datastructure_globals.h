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
extern int dlNet;
extern int poi, dlPoi;
extern int polygon, dlPolygon;
extern int polyline, dlPolyline;

extern int iImgId; //used in polishfm.c
extern char *sImgName;


#endif /* __datastrucure_globals_h_*/
