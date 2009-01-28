
/*

Read Polish File Format

Based on: cGPSmapper-UsrMan-v02.4.3.pdf
Source: http://cgpsmapper.com/manual.htm

*/

#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include "stringhandling.h"
#include "datastructure.h"
#include "polishfm.h"

void processSection (char *sSection) {
	int iTmp, bodyObject=0;
printf("///processing section\n");
	/* Body */
	if (stricmp("POI", sSection) == 0 || stricmp("RGN10", sSection) == 0 || stricmp("RGN20", sSection) == 0) {
		bodyObject=1;
	} else if (stricmp("POLYGON", sSection) == 0 || stricmp("RGN80", sSection) == 0) {
		/* Body */
		bodyObject=1;
	} else if (stricmp("POLYLINE", sSection) == 0 || stricmp("RGN40", sSection) == 0) {
		/* Body */
		bodyObject=1;
	} else if (stricmp("WPT", sSection) == 0) {
		/* Body */
		bodyObject=1;
	} else if (stricmp("PLT", sSection) == 0) {
		/* Body */
		bodyObject=1;
	} else if (stricmp("SHP", sSection) == 0) {
		/* Body */
		bodyObject=1;
	} else if (stricmp("DBX", sSection) == 0) {
		/* Body */
		bodyObject=1;
		//undocumented
		printf("--- Undocumented section found: %s\n", sSection);
		return;
	} else if (stricmp("FILE", sSection) == 0) {
		/* Body */
		bodyObject=1;
	} else {
		printf("--- Not body object: %s\n", sSection);
		return;
	}
	//filtering done, valid sections were found
	if (bodyObject == 1) {
		if (activeObjectList == NULL || stricmp(activeObjectList->sType, sSection) != 0) {
			activeObjectList=getObjectList(sSection);
		}
printf("^^^^^adding object to objectlist");
		activeObject=addObjectToObjectList(activeObjectList);
	}
}

void processTag (char *sSection, char *sKey, char *sValue) {
	/*
	 * Header:
	 *	IMG ID
	 *
	 * Declarations:
	 *	COUNTRIES
	 *	REGIONS
	 *	CITIES
	 *	CHART INFO
	 *
	 * Advanced declarations:
	 *	DICTIONARY
	 *	BACKGROUND
	 *	HIGHWAYS
	 *	ZIPCODES
	 *	DEFINITIONS
	 *
	 * Body (objects):
	 *	POI
	 *	POLYLINE
	 *	POLYGON
	 *	PLT
	 *	WPT
	 *	DBX
	 *	SHP
	 *	FILE
	 *	RGN10, RGN20, RGN40, RGN80
	 *
	 */

	int iTmp, bodyObject=0;
	if (stricmp("IMG_ID", sSection) == 0) {
		/* Header */
		//mandatory
		if (stricmp("ID", sKey) == 0) {
			//mandatory
			sscanf(sValue, "%d", &iImgId);
		} else if (stricmp("Name", sKey) == 0) {
			//mandatory
			sImgName=(char*)malloc(sizeof(char)*(strlen(sValue)+1));
			strcpy(sImgName, sValue);
		} else if (stricmp("LBLcoding", sKey) == 0) {
		} else if (stricmp("Codepage", sKey) == 0) {
		} else if (stricmp("Datum", sKey) == 0) {
		} else if (stricmp("Transparent", sKey) == 0) {
		} else if (stricmp("MG", sKey) == 0) {
		} else if (stricmp("Numbering", sKey) == 0) {
		} else if (stricmp("Routing", sKey) == 0) {
		} else if (stricmp("Lock", sKey) == 0) {
		} else if (stricmp("ProductCode", sKey) == 0) {
		} else if (stricmp("CopyRight", sKey) == 0) {
		} else if (stricmp("Elevation", sKey) == 0) {
		} else if (stricmp("POIOnly", sKey) == 0) {
		} else if (stricmp("POIIndex", sKey) == 0) {
		} else if (stricmp("POINumberFirst", sKey) == 0) {
		} else if (stricmp("POIZipFirst", sKey) == 0) {
		} else if (stricmp("DefaultCityCountry", sKey) == 0) {
		} else if (stricmp("DefaultRegionCount", sKey) == 0) {
		} else if (stricmp("TreSize", sKey) == 0) {
			//mandatory
		} else if (stricmp("RgnLimit", sKey) == 0) {
			//mandatory
		} else if (stricmp("SimplifyLevel", sKey) == 0) {
		} else if (stricmp("PreProcess", sKey) == 0) {
		} else if (stricmp("Levels", sKey) == 0) {
			//mandatory
		} else if (stricmp("Level#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else if (stricmp("Zoom#", sKey) == 0) {
			//todo - # has to be replaced in matching patter to a real digit
		} else if (stricmp("Preview", sKey) == 0) {
		} else if (stricmp("AlighMethod", sKey) == 0) {
		} else if (stricmp("BlockSize", sKey) == 0) {
		} else if (stricmp("LevelFill", sKey) == 0) {
		} else if (stricmp("LevelLimit", sKey) == 0) {
		} else if (stricmp("WorldMap", sKey) == 0) {
		} else if (stricmp("DrawPriority", sKey) == 0) {
		} else if (stricmp("Marine", sKey) == 0) {
		} else if (stricmp("", sKey) == 0) {
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (stricmp("COUNTRIES", sSection) == 0) {
		/*  Declarations */
		if (stricmp("Country#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (stricmp("REGIONS", sSection) == 0) {
		/*  Declarations */
		if (stricmp("Region#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else if (stricmp("CountryIdx#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (stricmp("CITIES", sSection) == 0) {
		/*  Declarations */
		if (stricmp("City#", sKey) == 0) {
		} else if (stricmp("RegionIdx#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (stricmp("CHART_INFO", sSection) == 0) {
		/*  Declarations */
		if (stricmp("Name", sKey) == 0) {
		} else if (stricmp("Number", sKey) == 0) {
		} else if (stricmp("Projection", sKey) == 0) {
		} else if (stricmp("Published", sKey) == 0) {
		} else if (stricmp("Scale", sKey) == 0) {
		} else if (stricmp("DeltaSN", sKey) == 0) {
		} else if (stricmp("DeltaWE", sKey) == 0) {
		} else if (stricmp("IALA", sKey) == 0) {
		} else if (stricmp("Print", sKey) == 0) {
		} else if (stricmp("Edition", sKey) == 0) {
		} else if (stricmp("Correction", sKey) == 0) {
		} else if (stricmp("Text", sKey) == 0) {
		} else if (stricmp("TextFile", sKey) == 0) {
		} else if (stricmp("ReferenceEllipsoid", sKey) == 0) {
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (stricmp("BACKGROUND", sSection) == 0) {
		/* Advanced declarations */
		if (stricmp("Name", sKey) == 0) {
			//mandatory
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (stricmp("DICTIONARY", sSection) == 0) {
		/* Advanced declarations */
		if (stricmp("Level#RGNnn", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
			//todo - nn has to be replaced in matching patter to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (stricmp("HIGHWAYS", sSection) == 0) {
		/* Advanced declarations */
		//undocumented
		printf("--- Undocumented section found: %s\n", sSection);
		return;
	} else if (stricmp("ZIPCODES", sSection) == 0) {
		/* Advanced declarations */
		//undocumented
		printf("--- Undocumented section found: %s\n", sSection);
		return;
	} else if (stricmp("DEFINITIONS", sSection) == 0) {
		/* Advanced declarations */
		//undocumented
		printf("--- Undocumented section found: %s\n", sSection);
		return;
	} else if (stricmp("POI", sSection) == 0 || stricmp("RGN10", sSection) == 0 || stricmp("RGN20", sSection) == 0) {
		/* Body */
		bodyObject=1;
		if (stricmp("Type", sKey) == 0) {
			//mandatory
		} else if (stricmp("SubType", sKey) == 0) {
		} else if (stricmp("Marine", sKey) == 0) {
		} else if (stricmp("City", sKey) == 0) {
		} else if (stricmp("Label", sKey) == 0) {
		} else if (stricmp("EndLevel", sKey) == 0) {
		} else if (stricmp("Data1", sKey) == 0) {
			//mandatory
		} else if (stricmp("Data#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else if (stricmp("StreetDesc", sKey) == 0) {
		} else if (stricmp("OvernightParking", sKey) == 0) {
		} else if (stricmp("Highway", sKey) == 0) {
		} else if (stricmp("CityName", sKey) == 0) {
		} else if (stricmp("RegionName", sKey) == 0) {
		} else if (stricmp("CountryName", sKey) == 0) {
		} else if (stricmp("Zip", sKey) == 0) {
		} else if (stricmp("Exit#", sKey) == 0) {
			//todo - # has to be replaced in matching patter to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (stricmp("POLYGON", sSection) == 0 || stricmp("RGN80", sSection) == 0) {
		/* Body */
		bodyObject=1;
		if (stricmp("Type", sKey) == 0) {
			//mandatory
		} else if (stricmp("SubType", sKey) == 0) {
		} else if (stricmp("Marine", sKey) == 0) {
		} else if (stricmp("Label", sKey) == 0) {
		} else if (stricmp("EndLevel", sKey) == 0) {
		} else if (stricmp("Background", sKey) == 0) {
		} else if (stricmp("Data1", sKey) == 0) {
			//mandatory
		} else if (stricmp("Data#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (stricmp("POLYLINE", sSection) == 0 || stricmp("RGN40", sSection) == 0) {
		/* Body */
		bodyObject=1;
		if (stricmp("Type", sKey) == 0) {
		} else if (stricmp("SubType", sKey) == 0) {
		} else if (stricmp("Marine", sKey) == 0) {
		} else if (stricmp("Label", sKey) == 0) {
		} else if (stricmp("Label2", sKey) == 0) {
		} else if (stricmp("EndLevel", sKey) == 0) {
		} else if (stricmp("Data1", sKey) == 0) {
			//mandatory
		} else if (stricmp("Data#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else if (stricmp("StreetDesc", sKey) == 0) {
		} else if (stricmp("DirIndicator", sKey) == 0) {
		} else if (stricmp("CityName", sKey) == 0) {
		} else if (stricmp("RegionName", sKey) == 0) {
		} else if (stricmp("CountryName", sKey) == 0) {
		} else if (stricmp("Zip", sKey) == 0) {
		} else if (stricmp("RoadID", sKey) == 0) {
		} else if (stricmp("Numbers#", sKey) == 0) {
			//todo - # has to be replaced in matching patter to a real digit
		} else if (stricmp("Routeparam", sKey) == 0) {
		} else if (stricmp("NodID", sKey) == 0) {
			//todo - # has to be replaced in matching patter to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (stricmp("WPT", sSection) == 0) {
		/* Body */
		bodyObject=1;
		if (stricmp("", sKey) == 0) {
		} else if (stricmp("RgnType", sKey) == 0) {
			//mandatory
		} else if (stricmp("Type", sKey) == 0) {
			//mandatory
		} else if (stricmp("EndLevel", sKey) == 0) {
		} else if (stricmp("File#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (stricmp("PLT", sSection) == 0) {
		/* Body */
		bodyObject=1;
		if (stricmp("RgnType", sKey) == 0) {
			//mandatory
		} else if (stricmp("Type", sKey) == 0) {
			//mandatory
		} else if (stricmp("Label", sKey) == 0) {
		} else if (stricmp("DirIndicator", sKey) == 0) {
		} else if (stricmp("EndLevel", sKey) == 0) {
		} else if (stricmp("File#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (stricmp("SHP", sSection) == 0) {
		/* Body */
		bodyObject=1;
		if (stricmp("name", sKey) == 0) {
			//mandatory
		} else if (stricmp("Type", sKey) == 0) {
			//mandatory
		} else if (stricmp("LabelField", sKey) == 0) {
		} else if (stricmp("Label2Field", sKey) == 0) {
			//mandatory
		} else if (stricmp("TypeField", sKey) == 0) {
		} else if (stricmp("SubTypeField", sKey) == 0) {
		} else if (stricmp("DirField", sKey) == 0) {
		} else if (stricmp("Level", sKey) == 0) {
			//mandatory
		} else if (stricmp("EndLevel", sKey) == 0) {
			//mandatory
		} else if (stricmp("DefaultType", sKey) == 0) {
		} else if (stricmp("CityName", sKey) == 0) {
		} else if (stricmp("RegionName", sKey) == 0) {
		} else if (stricmp("CountryName", sKey) == 0) {
		} else if (stricmp("HouseNumber", sKey) == 0) {
		} else if (stricmp("StreetDesc", sKey) == 0) {
		} else if (stricmp("PhoneNumber", sKey) == 0) {
		} else if (stricmp("Zip", sKey) == 0) {
		} else if (stricmp("RoatID", sKey) == 0) {
		} else if (stricmp("SpeedType", sKey) == 0) {
		} else if (stricmp("RoadClass", sKey) == 0) {
		} else if (stricmp("OneWay", sKey) == 0) {
		} else if (stricmp("Toll", sKey) == 0) {
		} else if (stricmp("VehicleD", sKey) == 0) {
		} else if (stricmp("VehicleC", sKey) == 0) {
		} else if (stricmp("VehicleB", sKey) == 0) {
		} else if (stricmp("VehicleT", sKey) == 0) {
		} else if (stricmp("VehicleP", sKey) == 0) {
		} else if (stricmp("VehicleI", sKey) == 0) {
		} else if (stricmp("VehicleR", sKey) == 0) {
		} else if (stricmp("TextFileLines", sKey) == 0) {
		} else if (stricmp("TextStart", sKey) == 0) {
		} else if (stricmp("TextEnd", sKey) == 0) {
		} else if (stricmp("TextFile", sKey) == 0) {
		} else if (stricmp("Color", sKey) == 0) {
		} else if (stricmp("Style", sKey) == 0) {
		} else if (stricmp("Height", sKey) == 0) {
		} else if (stricmp("Depth", sKey) == 0) {
		} else if (stricmp("DepthUnit", sKey) == 0) {
		} else if (stricmp("HeightUnit", sKey) == 0) {
		} else if (stricmp("Position", sKey) == 0) {
		} else if (stricmp("DepthFlag", sKey) == 0) {
		} else if (stricmp("FoundationColor", sKey) == 0) {
		} else if (stricmp("Light", sKey) == 0) {
		} else if (stricmp("LightType", sKey) == 0) {
		} else if (stricmp("Note", sKey) == 0) {
		} else if (stricmp("LocalDesignator", sKey) == 0) {
		} else if (stricmp("IngernationalDesignator", sKey) == 0) {
		} else if (stricmp("Period", sKey) == 0) {
		} else if (stricmp("HeightAboveFoundation", sKey) == 0) {
		} else if (stricmp("HeightAboveDatum", sKey) == 0) {
		} else if (stricmp("HeightAboveFoundationUnit", sKey) == 0) {
		} else if (stricmp("HeightAboveDatumUnit", sKey) == 0) {
		} else if (stricmp("LeadingAngle", sKey) == 0) {
		} else if (stricmp("Racon", sKey) == 0) {
		} else if (stricmp("DoubleLights", sKey) == 0) {
		} else if (stricmp("DoubleLightsHorizontal", sKey) == 0) {
		} else if (stricmp("FacilityPoint", sKey) == 0) {
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (stricmp("DBX", sSection) == 0) {
		/* Body */
		bodyObject=1;
		//undocumented
		printf("--- Undocumented section found: %s\n", sSection);
		return;
	} else if (stricmp("FILE", sSection) == 0) {
		/* Body */
		bodyObject=1;
		if (stricmp("name", sKey) == 0) {
			//mandatory
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else {
		printf("--- Unknown section found: %s\n", sSection);
		return;
	}
	//filtering done, valid sections and keys were found
	char sTmp[5];
	strncpy(sTmp, sKey, 4);
	sTmp[4]='\0';
	if (bodyObject == 1) {
		if (stricmp(sTmp, "Data") != 0) {
printf("xxxx---process tag %s\n", sTmp);
			addAttributeToObject(activeObject, sKey, sValue);
printObject(activeObject, 999);
printf("xxxx---process tag ... done\n");
		} else {
			processData(sValue);
printObject(activeObject, 999);
printf("xxxx---process tag ... data ... done\n");
		}
	}
}

void processData(char *sData) {
printf("xxxx---process data start .................................\n");
	int iTmp;
	char *sToken;
	float x, z;
	sToken=strtok( sData, "()");
	while (sToken != NULL) {
//todo / tokenizalas ketszer olvassa be az elso darabot, megnezni miert
printf("sdata=%s\n", sData);
		iTmp=sscanf(sData, "(%f,%f", &x, &z);
printf("itmp=%d\n", iTmp);
		if (iTmp == 2) {
printf("xxxx---process data %f %f\n", x, z);
			addPointToObject(activeObject, x, 0.0, z); //todo - height information is is zero 
		}
		sToken=strtok( NULL, "()");
	}
}

//read polish format map file
void readPolishFile(char *sFileName) {
	initDataStructure();
	//Open file
	FILE *pFile;
	pFile = fopen(sFileName,"r");
	if (pFile == NULL) {
		printf("error opening file: %s\n", sFileName);
		//todo graphical error handling
		fclose(pFile);
		return;
	}
	char sSection[SECTIONWIDTH+1]; //todo check all section id for length
	sSection[0]='\0';
	char sTag[10]; //todo check all tag for length
	sTag[0]='\0';
	int iLineNo=0;
	while (!feof(pFile)) {
		char *sLine=NULL;
		sLine = sGetLine(pFile);
		strReplace(sLine, ' ', '_');
		iLineNo++;
		if (iLineNo > 100) {
			//read only the first few lines of the file
			break; //debug
		}
		if (sLine == NULL) {
			printf("sLine==NULL\n"); //todo graphical error handling
		} else {
			printf("%d >> %s\n", iLineNo, sLine); //debug
			//printf("stricmp:%d char:%d\n", stricmp("", sLine), sLine[0]); //debug
			
			switch (sLine[0]) {
				case '\r':
				case '\n':
				case '\0':
				case ';':
					//debug
					//printf(">>>noop:%d\n", sLine[0]);
					//noop, empty line or comment
					break;
				case '[':
					//sectoin start or end
					if (sSection[0] == '\0') {
						//we are not in a section, this is the start
						int iTmp=strlen(sLine);
						char sTmp[iTmp+1];
						iTmp=sscanf(sLine, "[%s]", sTmp);
						strReplace(sTmp, ']', '\0'); //sscanf reads the ] sign as well, remove it
						//debug
						if (iTmp>0) {
							strncpy(sSection, sTmp, SECTIONWIDTH);
							//sSection[SECTIONWIDTH]='\0'; //strncpy puts terminating null
							//printf("%d: [%s]\n", iLineNo, sTmp); //debug
							printf("%d: section found:[%s] found=%d\n", iLineNo, sSection, iTmp);
							processSection(sSection);
						} else {
							printf("%d: section not found: length=%d\n", iLineNo, iTmp);
						}
					} else {
						//we are in a section, this is the close tag
						int iTmp=strlen(sLine);
						char sTmp[iTmp+1];
						sscanf(sLine, "[%3s", sTmp);
						sTmp[3]='\0';
						if (stricmp(sTmp, "END") != 0) {
							printf("%d: [%s] End of section expected, but not found\n", iLineNo, sSection);
						} else {
							//closing section
							printf("%d: [%s] End of section\n", iLineNo, sSection);
							sSection[0]='\0';
						}
					}
					break;
				default:
				{
					char *sKey;
					char *sValue;
					sKey=strtok( sLine, "=");
					sValue=strtok( NULL, "=");
					//todo sorvegrol leszedni a nem lathato szemetet, igy jo?
					strReplace(sValue, '\n', '\0');
					strReplace(sValue, '\r', '\0');
					printf("%d: sec:%s key:%s value:%s\n", iLineNo, sSection, sKey, sValue);
					processTag(sSection, sKey, sValue);
				}
			}
		}
		free(sLine);
	}
} 

void displayPolishMap(void) {
	//display the objects stored in the data structure
	if (rootObjectList == NULL) {
		printf("Root object list is NULL, nothing to display!\n");
		return;
	}

	objectList *curOL;
	curOL=rootObjectList;
	do {
		if (stricmp("POI", curOL->sType) == 0) {
			//todo - optimize with separate display lists
			object *curO;
			curO=curOL->firstObject;
			if (curO != NULL) {
				//if we have an object, create a display list for that type
				poi=1;
				dlPoi=glGenLists(1);
				glNewList(dlPoi, GL_COMPILE);
					glBegin(GL_POINT);
						do {
printf("vertex %f, %f, %f\n", curO->firstPoint->x, curO->firstPoint->y, curO->firstPoint->z);
							glVertex3f(curO->firstPoint->x, curO->firstPoint->y, curO->firstPoint->z);
							curO=curO->next;
						} while (curO != NULL);
					glEnd();
				glEndList();
			}
		} else if (stricmp("todo", curOL->sType) == 0) {
			//todo the other object types
		}
		curOL=curOL->next;
	} while (curOL != NULL);
	
	
}
