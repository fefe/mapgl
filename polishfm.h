
#ifndef __polishfm_h_ 
#define __polishfm_h_

#define SECTIONWIDTH 10

void processSection (char *sSection);
void processTag (char *sSection, char *sKey, char *sValue);
void processData(char *sData);
int  readPolishFile(char *sFileName);
void displayNet(void);
void displayPolishMap(void);
void displayPOI(object *curO, point *curP);

void CALLBACK tessBeginCallback(GLenum which);
void CALLBACK tessErrorCallback(GLenum errorCode);
void CALLBACK tessEndCallback(void);
void CALLBACK tessVertexCallback(GLvoid *vertex);

void displayPolygon(object *curO, point *curP);
void displayPolyline(object *curO, point *curP);
void computeCoordinates(void);

#endif /*__polishfm_h_*/ 

