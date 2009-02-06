
#ifndef __polishfm_h_ 
#define __polishfm_h_

#define SECTIONWIDTH 10

int iImgId;
char *sImgName;

void processSection (char *sSection);
void processTag (char *sSection, char *sKey, char *sValue);
void processData(char *sData);
void readPolishFile(char *sFileName);
void displayNet(void);
void displayPolishMap(void);

#endif /*__polishfm_h_*/ 

