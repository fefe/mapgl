
/*

Read Polish File Format

Based on: cGPSmapper-UsrMan-v02.4.3.pdf
Source: http://cgpsmapper.com/manual.htm

*/

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mapgl.h"
#include "stringhandling.h"
#include "datastructure.h"
#include "datastructure_globals.h"
#include "trigonometry.h"
#include "polishfm.h"

void processSection (char *sSection) {
	int iTmp;
	//int bodyObject=0; //remove warning - value never used
	int bodyObject;

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
		//bodyObject=1; //remove warning - value never used
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
			//creating object list or finding if it exists in the list
debug("creating objectList");
			activeObjectList=getObjectList(sSection);
		}
debug("adding object");
		activeObject=addObjectToObjectList(activeObjectList);
//printObject(activeObject, 9999);
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
			//todo - # has to be replaced in matching pattern to a real digit
		} else if (stricmp("Zoom#", sKey) == 0) {
			//todo - # has to be replaced in matching pattern to a real digit
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
			//todo - # has to be replaced in matching pattern to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (stricmp("REGIONS", sSection) == 0) {
		/*  Declarations */
		if (stricmp("Region#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching pattern to a real digit
		} else if (stricmp("CountryIdx#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching pattern to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (stricmp("CITIES", sSection) == 0) {
		/*  Declarations */
		if (stricmp("City#", sKey) == 0) {
		} else if (stricmp("RegionIdx#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching pattern to a real digit
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
			//todo - # has to be replaced in matching pattern to a real digit
			//todo - nn has to be replaced in matching pattern to a real digit
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
		} else if (stricmp("Data0", sKey) == 0) {
		} else if (stricmp("Data1", sKey) == 0) {
		} else if (stricmp("Data2", sKey) == 0) {
		} else if (stricmp("Data3", sKey) == 0) {
		} else if (stricmp("Data4", sKey) == 0) {
		} else if (stricmp("Data5", sKey) == 0) {
		} else if (stricmp("Data6", sKey) == 0) {
		} else if (stricmp("Data7", sKey) == 0) {
		} else if (stricmp("Data8", sKey) == 0) {
		} else if (stricmp("Data9", sKey) == 0) {
			//mandatory
		} else if (stricmp("Data#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching pattern to a real digit
		} else if (stricmp("StreetDesc", sKey) == 0) {
		} else if (stricmp("OvernightParking", sKey) == 0) {
		} else if (stricmp("Highway", sKey) == 0) {
		} else if (stricmp("CityName", sKey) == 0) {
		} else if (stricmp("RegionName", sKey) == 0) {
		} else if (stricmp("CountryName", sKey) == 0) {
		} else if (stricmp("Zip", sKey) == 0) {
		} else if (stricmp("Exit#", sKey) == 0) {
			//todo - # has to be replaced in matching pattern to a real digit
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
		} else if (stricmp("Data0", sKey) == 0) {
		} else if (stricmp("Data1", sKey) == 0) {
		} else if (stricmp("Data2", sKey) == 0) {
		} else if (stricmp("Data3", sKey) == 0) {
		} else if (stricmp("Data4", sKey) == 0) {
		} else if (stricmp("Data5", sKey) == 0) {
		} else if (stricmp("Data6", sKey) == 0) {
		} else if (stricmp("Data7", sKey) == 0) {
		} else if (stricmp("Data8", sKey) == 0) {
		} else if (stricmp("Data9", sKey) == 0) {
			//mandatory
		} else if (stricmp("Data#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching pattern to a real digit
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
		} else if (stricmp("Data0", sKey) == 0) {
		} else if (stricmp("Data1", sKey) == 0) {
		} else if (stricmp("Data2", sKey) == 0) {
		} else if (stricmp("Data3", sKey) == 0) {
		} else if (stricmp("Data4", sKey) == 0) {
		} else if (stricmp("Data5", sKey) == 0) {
		} else if (stricmp("Data6", sKey) == 0) {
		} else if (stricmp("Data7", sKey) == 0) {
		} else if (stricmp("Data8", sKey) == 0) {
		} else if (stricmp("Data9", sKey) == 0) {
			//mandatory
		} else if (stricmp("Data#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching pattern to a real digit
		} else if (stricmp("StreetDesc", sKey) == 0) {
		} else if (stricmp("DirIndicator", sKey) == 0) {
		} else if (stricmp("CityName", sKey) == 0) {
		} else if (stricmp("RegionName", sKey) == 0) {
		} else if (stricmp("CountryName", sKey) == 0) {
		} else if (stricmp("Zip", sKey) == 0) {
		} else if (stricmp("RoadID", sKey) == 0) {
		} else if (stricmp("Numbers#", sKey) == 0) {
			//todo - # has to be replaced in matching pattern to a real digit
		} else if (stricmp("Routeparam", sKey) == 0) {
		} else if (stricmp("NodID", sKey) == 0) {
			//todo - # has to be replaced in matching pattern to a real digit
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
			//todo - # has to be replaced in matching pattern to a real digit
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
			//todo - # has to be replaced in matching pattern to a real digit
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
		//bodyObject=1; //remove warning - value never used
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
	{//in a block, so bmp variable do not have to be moved to the beginning
		char sTmp[5];
		strncpy(sTmp, sKey, 4);
		sTmp[4]='\0';
		if (bodyObject == 1) {
			if (stricmp(sTmp, "Data") == 0) {
				//handle data attributes separate from the rest
				//CA-custom attribute, adding attribute prefix to avoid tag duplication
				addAttributeToObject(activeObject, "CALevel", sKey+4); //get level from Data tag, eg: Data3 -> CALevel=3, adding it as a custom attribute CA
				processData(sValue);
			} else {
				//every other attribute
				addAttributeToObject(activeObject, sKey, sValue);
			}
		}
	}
}


void processData(char *sData) {
	int iTmp;
	char *sToken;
	float lat, lon;
	sToken=strtok( sData, "()");
	while (sToken != NULL) {
		iTmp=sscanf(sToken, "%f,%f", &lat, &lon);
		if (iTmp == 2) {
			addPointToObject(activeObject, lat, lon); //todo - height information is zero 
		}
		sToken=strtok( NULL, "()");
	}
}

//read polish format map file
int readPolishFile(char *sFileName) {
	//todo - crash when first line contains invalid stuff (for example, created by is not commented with ; )
	FILE *pFile;
	char sSection[SECTIONWIDTH+1]; //todo check all section id for length
	char sTag[10]; //todo check all tag for length
	int iLineNo=0;
	char *sLine;
	//char *sLine=NULL; //remove warning - value never used

	initDataStructure();
	//Open file
	pFile = fopen(sFileName,"r");
	if (pFile == NULL) {
		printf("error opening file: %s\n", sFileName);
		//todo graphical error handling and opening file from gui
		fclose(pFile);
		return(1);
	}
	sSection[0]='\0';
	sTag[0]='\0';
	//while (!feof(pFile)) // crashed when reached eof, testing sLine instead
	sLine = sGetLine(pFile);
	while (sLine) {
//printf(">%s<", sLine);
		strReplace(sLine, ' ', '_');
		iLineNo++;
/*
		if (iLineNo > 80) {
			//read only the first few lines of the file
			break; //debug
		}
*/
		if (sLine == NULL) {
			printf("sLine==NULL\n"); //todo graphical error handling
		} else {
//printf("%d >> %s\n", iLineNo, sLine); //debug
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
						int iTmp;
						char* sTmp;
						sTmp=(char*)malloc((strlen(sLine)+1)*sizeof(char));
						iTmp=sscanf(sLine, "[%s]", sTmp);
						strReplace(sTmp, ']', '\0'); //sscanf reads the ] sign as well, remove it
						//debug
						if (iTmp>0) {
							strncpy(sSection, sTmp, SECTIONWIDTH);
							//sSection[SECTIONWIDTH]='\0'; //strncpy puts terminating null
							//printf("%d: [%s]\n", iLineNo, sTmp); //debug
//printf("%d: section found:[%s] found=%d\n", iLineNo, sSection, iTmp);
							processSection(sSection);
						} else {
							printf("%d: section not found: length=%d\n", iLineNo, iTmp);
						}
						free(sTmp);
					} else {
						//we are in a section, this is the close tag
						char* sTmp;
						sTmp=(char*)malloc((strlen(sLine)+1)*sizeof(char));
						sscanf(sLine, "[%3s", sTmp);
						sTmp[3]='\0';
						if (stricmp(sTmp, "END") == 0) {
							//closing section
//printObject(activeObject, 99999);
//printf("%d: [%s] End of section\n", iLineNo, sSection);
							sSection[0]='\0';
						} else {
							printf("%d: [%s] End of section expected, but not found\n", iLineNo, sSection);
						}
						free(sTmp);
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
					//printf("%d: sec:%s key:%s value:%s\n", iLineNo, sSection, sKey, sValue);
					processTag(sSection, sKey, sValue);
				}
			}
		}
		free(sLine);
		sLine = sGetLine(pFile);
	}
	free(sLine);
	fclose(pFile);
	return(0);
} 

/*
//sample loop
	objectList *curOL;
	curOL=rootObjectList;
	object *curO;
	curO=curOL->firstObject;
	point *curP;
	curP=curO->firstPoint;
	while (curOL != NULL) {
		while (curO != NULL) {
			while (curP != NULL) {
				//loop core

				curP=curP->next;
			}
			curO=curO->next;
			if (curO!=NULL) curP=curO->firstPoint;
		}
		curOL=curOL->next;
		if (curOL!=NULL) curO=curOL->firstObject;
		if (curO!=NULL) curP=curO->firstPoint;
	} 
*/

void displayNet(void) {
	int i,m;

	dlNet=glGenLists(1);
	glNewList(dlNet, GL_COMPILE);

	//axis
	glBegin(GL_LINES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(20.0, 0.0, 0.0);
		glVertex3f(-20.0, 0.0, 0.0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(0.0, 20.0, 0.0);
		glVertex3f(0.0, -20.0, 0.0);
		glColor3f(0.0, 0.0, 1.0);
		glVertex3f(0.0, 0.0, 20.0);
		glVertex3f(0.0, 0.0, -20.0);
	glEnd();

	//center
	glBegin(GL_LINES);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(centerx+1.0, centery, centerz);
		glVertex3f(centerx-1.0, centery, centerz);
		glVertex3f(centerx, centery+1.0, centerz);
		glVertex3f(centerx, centery-1.0, centerz);
		glVertex3f(centerx, 0.0, centerz+1.0);
		glVertex3f(centerx, 0.0, centerz-1.0);
	glEnd();

	//borders
	glBegin(GL_LINE_LOOP);
		glColor3f(1.0, 1.0, 1.0);
		glVertex3f(minx, miny, minz);
		glVertex3f(maxx, miny, minz);
		glVertex3f(maxx, miny, maxz);
		glVertex3f(minx, miny, maxz);
	glEnd();

	//net
	m=(maxx>maxz?maxx:maxz);
	glBegin(GL_LINES);
		for (i=0; i<m; i++) {
			if (i%5 == 0) {
				glColor3f(0.5, 0.0, 0.0);
			} else {
				glColor3f(0.5, 0.5, 0.5);
			}
			glVertex3f(0.0, 0.0, i);
			glVertex3f(m, 0.0, i);
			glVertex3f(i, 0.0, 0.0);
			glVertex3f(i, 0.0, m);
			
		}
	glEnd();

	glEndList();
}

void displayPolishMap(void) {
	//display the objects stored in the data structure
	objectList *curOL;
	object *curO;
	point *curP;
	float r,g,b,i;

	if (rootObjectList == NULL) {
		printf("Root object list is NULL, nothing to display!\n");
		return;
	}

	curOL=rootObjectList;
	curO=curOL->firstObject;
	curP=curO->firstPoint;

	while (curOL != NULL) {
		if (stricmp("POI", curOL->sType) == 0) {
			displayPOI(curO, curP);
		} else if (stricmp("POLYGON", curOL->sType) == 0) {
			displayPolygon(curO, curP);
		} else if (stricmp("POLYLINE", curOL->sType) == 0) {
			displayPolyline(curO, curP);
		} else if (stricmp("other objects", curOL->sType) == 0) {
debug("unknown object found\n");
		}
		curOL=curOL->next; //next objectlist
		if (curOL!=NULL) curO=curOL->firstObject; //next objectlist, first object
		if (curO!=NULL) curP=curO->firstPoint; //next objectlist, first object, first point
	} 
}

void churchDetails(int fill) {
	//todo -- move models to separate c source

	if (fill) {
		glColor3f(0.8, 0.8, 0.8);
	} else {
		glColor3f(0.6, 0.6, 0.6);
	}

	glPushMatrix();

	glScalef(0.1, 0.1, 0.1);

	glPushMatrix();
		glTranslatef(-2.0, 3.5, 1.0);
		glScalef(2.0, 7.0, 2.0);
		glutSolidCube(1.0);
	glPopMatrix();
	glPushMatrix();
		glTranslatef(1.0, 1.5, 2.5);
		glScalef(4.0, 3.0, 5.0);
		glutSolidCube(1.0);
	glPopMatrix();
	glBegin(GL_TRIANGLE_FAN);
		glVertex3f(-2, 8, 1);
		glVertex3f(-3, 7, 0);
		glVertex3f(-1, 7, 0);

		glVertex3f(-1, 7, 2);
		glVertex3f(-3, 7, 2);
		glVertex3f(-3, 7, 0);
	glEnd();
	glBegin(GL_TRIANGLES);
		glVertex3f(-1, 3, 0);
		glVertex3f(3, 3, 0);
		glVertex3f(1, 4, 0);

		glVertex3f(-1, 3, 5);
		glVertex3f(3, 3, 5);
		glVertex3f(1, 4, 5);
	glEnd();
	glBegin(GL_QUADS);
		glVertex3f(-1, 3, 0);
		glVertex3f(1, 4, 0);
		glVertex3f(1, 4, 5);
		glVertex3f(-1, 3, 5);

		glVertex3f(1, 4, 0);
		glVertex3f(3, 3, 0);
		glVertex3f(3, 3, 5);
		glVertex3f(1, 4, 5);
	glEnd();

	glPopMatrix();
}

void church(void) {
	glEnable(GL_POLYGON_OFFSET_FILL); //make sure lines are displayed well
	glPolygonOffset(1.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	churchDetails(1); //filled polygons
	glDisable(GL_POLYGON_OFFSET_FILL);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	churchDetails(0); //polygon border lines 
}


void displayPOI(object *curO, point *curP) {
	//display all POI
	int i;
	object *curOrig;
debug("begin list poi");
	poi=1;

	curOrig=curO;
	for (i=0;i<=9;i++) {
		//todo -- optimize, not efficient to go through the list this way 
		curO=curOrig;

		dlPoi[i]=glGenLists(1);
		glNewList(dlPoi[i], GL_COMPILE);
		glPointSize(6.0);
		while (curO != NULL) {
			if ( (char)getAttribute(curO, "CALevel")[0]-'0' == i) {
				//every zoom level has its own display list

				if ( 0 && ( stricmp(getAttribute(curO, "Type"), "0x0306") == 0 || stricmp(getAttribute(curO, "Type"), "0x6404") == 0 ) ) {
					//church
					while (curP != NULL) {
printf("church\n");
						glPushMatrix();
						glTranslatef(curP->x, curP->y, curP->z);
						church();
						glPopMatrix();
						curP=curP->next; //next point
					}
				} else {
					glBegin(GL_POINTS);
					glColor3f(1.0, 0.0, 1.0); //todo - color by POI type
			
					while (curP != NULL) {
						//loop core
						glVertex3f(curP->x, curP->y, curP->z);
debug("\t\tvertex");
						curP=curP->next; //next point
					}
debug("\tend");
					glEnd();
				}
			}
			curO=curO->next; //next object
			if (curO!=NULL) curP=curO->firstPoint; //next object, first point
		}
		glEndList();
	}
}

void CALLBACK tessBeginCallback(GLenum which) {
printf("<b>.");
	glBegin(which);
printf("</b>");
}

void CALLBACK tessErrorCallback(GLenum errorCode) {
	//todo - error handling
	const GLubyte *estring;
printf("<e>.");

	estring = gluErrorString(errorCode);
	fprintf(stderr, "Tessellation Error: %s\n", estring);
	exit(0);
}

void CALLBACK tessEndCallback(void) {
printf("<e>.");
	glEnd();
printf("</e>");
}

/* - original
void CALLBACK tessVertexCallback(GLvoid *vertex) {
	//todo - color per vertex not needed, make it simple
	const GLdouble *pointer;

printf("<v>.");

	pointer = (GLdouble *) vertex;
	glColor3dv(pointer+3);
	glVertex3dv(vertex);
printf("</v>");

}
*/

void CALLBACK tessVertexCallback(GLvoid *vertex) {
printf("<v>");
	glVertex3dv(vertex);
printf("</v>");
}

/* - original
void CALLBACK tessCombineCallback(GLdouble coords[3], 
							GLdouble *vertex_data[4],
							GLfloat weight[4], GLdouble **dataOut ) {
	//todo - color per vertex not needed, make it simple
	GLdouble *vertex;
	int i;
printf("<cb>.");

	vertex = (GLdouble *) malloc(6 * sizeof(GLdouble));

	vertex[0] = coords[0];
	vertex[1] = coords[1];
	vertex[2] = coords[2];
	for (i = 3; i < 6; i++)
		vertex[i] = weight[0] * vertex_data[0][i] 
						+ weight[1] * vertex_data[1][i]
						+ weight[2] * vertex_data[2][i] 
						+ weight[3] * vertex_data[3][i];
	*dataOut = vertex;
printf("</cb>");
}
*/

void CALLBACK tessCombineCallback(GLdouble coords[3], 
							GLdouble *vertex_data[4],
							GLfloat weight[4], GLdouble **dataOut ) {
	//todo - color per vertex not needed, make it simple
	GLdouble *vertex;
	int i;
printf("<cb>.");

	vertex = (GLdouble *) malloc(6 * sizeof(GLdouble));

	vertex[0] = coords[0];
	vertex[1] = coords[1];
	vertex[2] = coords[2];
/*
	for (i = 3; i < 6; i++)
		vertex[i] = weight[0] * vertex_data[0][i] 
						+ weight[1] * vertex_data[1][i]
						+ weight[2] * vertex_data[2][i] 
						+ weight[3] * vertex_data[3][i];
*/
	*dataOut = vertex;
printf("</cb>");
}

void displayPolygon(object *curO, point *curP) {
	//display all Polygon
	int i, tesselation;
	object *curOrig;
	GLUtesselator *tobj;

	tesselation=1; //activate tesselation

	//creating the tesselator object and binding callback functions
	if (tesselation==1) {
		//tesselation active
		tobj = gluNewTess();
		gluTessCallback(tobj, GLU_TESS_BEGIN, tessBeginCallback);
		gluTessCallback(tobj, GLU_TESS_ERROR, tessErrorCallback);
		gluTessCallback(tobj, GLU_TESS_END, tessEndCallback);
		gluTessCallback(tobj, GLU_TESS_VERTEX, tessVertexCallback);
	//	gluTessCallback(tobj, GLU_TESS_VERTEX, glVertex3dv);
		gluTessCallback(tobj, GLU_TESS_COMBINE, tessCombineCallback);

		gluTessProperty(tobj, GLU_TESS_WINDING_RULE, GLU_TESS_WINDING_POSITIVE);
	}
	
debug("begin list polygon");
	polygon=1;

	curOrig=curO;
	for (i=0;i<=9;i++) {
		//todo -- optimize, not efficient to go through the list this way 
		curO=curOrig;

		dlPolygon[i]=glGenLists(1);
		glNewList(dlPolygon[i], GL_COMPILE);
		while (curO != NULL) {
debug("\tbegin polygon");
			if ( (char)getAttribute(curO, "CALevel")[0]-'0' == i) {
				//every zoom level has its own display list
printf("a");

				glColor3f(0.3, 0.4, 0.4); //todo - color by Polygon type
				if (tesselation==1) {
printf("b");
					//tesselation active
					gluTessBeginPolygon(tobj, NULL);
printf("c");
						gluTessBeginContour(tobj);
printf("d ");

						while (curP != NULL) {
							//loop core
							//todo - check polygon vertex order
printf("e");

							gluTessVertex(tobj, curP->v, curP->v);
debug("\t\tvertex");
printf(".");
							curP=curP->next; //next point
						}

						gluTessEndContour(tobj);
					gluTessEndPolygon(tobj);
				} else {
					//no tesselation
					glBegin(GL_POLYGON);
//					glColor3f(0.3, 0.4, 0.4); //todo - color by Polygon type

					while (curP != NULL) {
						//loop core
						//todo - check polygon vertex order 
						glVertex3f(curP->x, curP->y, curP->z);
debug("\t\tvertex");
						curP=curP->next; //next point
					}
debug("\tend");
					glEnd(); //end polygon
				}
			}

			curO=curO->next; //next object
			if (curO!=NULL) curP=curO->firstPoint; //next object, first point
		}
		glEndList();

/***********/
		//polygon border lines with a different color
		curO=curOrig;

		dlPolygonL[i]=glGenLists(1);
		glNewList(dlPolygonL[i], GL_COMPILE);
		while (curO != NULL) {
debug("\tbegin polygon");
			if ( (char)getAttribute(curO, "CALevel")[0]-'0' == i) {
				//every zoom level has its own display list

				glBegin(GL_POLYGON);
				glColor3f(0.6, 0.6, 1.0); //todo - color by Polygon type
		
				while (curP != NULL) {
					//loop core
					//todo - check polygon vertex order 
					glVertex3f(curP->x, curP->y, curP->z);
debug("\t\tvertex");
					curP=curP->next; //next point
				}
debug("\tend");
				glEnd(); //end polygon
			}

			curO=curO->next; //next object
			if (curO!=NULL) curP=curO->firstPoint; //next object, first point
		}
		glEndList();


	}
}

void displayPolyline(object *curO, point *curP) {
	//display all Polyline
	int i;
	object *curOrig;
debug("begin list polyline");
	polyline=1;

	curOrig=curO;
	for (i=0;i<=9;i++) {
		//todo -- optimize, not efficient to go through the list this way 
		curO=curOrig;
				
		dlPolyline[i]=glGenLists(1);
		glNewList(dlPolyline[i], GL_COMPILE);
		while (curO != NULL) {
debug("\tbegin line strip");
			if ( (char)getAttribute(curO, "CALevel")[0]-'0' == i) {
				//every zoom level has its own display list

				glBegin(GL_LINE_STRIP);
				glColor3f(0.0, 1.0, 0.0); //todo - color by Polyline type
		
				while (curP != NULL) {
					//loop core
					glVertex3f(curP->x, curP->y, curP->z);
debug("\t\tvertex");
					curP=curP->next; //next point
				}
debug("\tend");
				glEnd(); //end polyline
			}
			curO=curO->next; //next object
			if (curO!=NULL) curP=curO->firstPoint; //next object, first point
		}
		glEndList();
	}
}

void computeCoordinates(void) {
	//update coordinates in every point object
	objectList *curOL;
	object *curO;
	point *curP;

	if (rootObjectList == NULL) {
		printf("Root object list is NULL, no coordinates to compute!\n");
		return;
	}

/*	centerlat=(maxlat+minlat)/2.0;
	centerlon=(maxlon+minlon)/2.0;
	centerlatRad=toRadian(centerlat);
	centerlonRad=toRadian(centerlon);
	centerlatSin=sin(centerlatRad);
	centerlatCos=cos(centerlatRad);
	centerlonSin=sin(centerlonRad);
	centerlonCos=cos(centerlonRad);
*/
	minlatRad=toRadian(minlat);
	minlonRad=toRadian(minlon);
	minlatSin=sin(minlatRad);
	minlatCos=cos(minlatRad);
	minlonSin=sin(minlonRad);
	minlonCos=cos(minlonRad);

/*
printf("	maxlat=%f \t	 maxlon=%f\n", maxlat, maxlon);
printf("centerlat=%f \t centerlon=%f\n", centerlat, centerlon);
printf("	minlat=%f \t	 minlon=%f\n", minlat, minlon);
*/
	curOL=rootObjectList;
	curO=curOL->firstObject;
	curP=curO->firstPoint;
	while (curOL != NULL) {
		while (curO != NULL) {
			while (curP != NULL) {
				//loop core
				//convertCoordinateToDistance(curP->lat, curP->lon, centerlat, centerlon, &(curP->x), &(curP->z)); //the other format is more obvious
				//test todo - no conversion to distance, using lon and lat
				//CurP->x=convertCoordinateToDistanceX(curP->lon);
				curP->x=curP->lon;
				curP->y=0.0; //todo - correct height for every point
				//test todo - no conversion to distance, using lon and lat
				//curP->z=convertCoordinateToDistanceZ(curP->lat);
				curP->z=curP->lat;
				//todo - modify every reference to use only v vertex vektor
				//todo - modify all computation from float to double
				curP->v[0]=curP->x;
				curP->v[1]=curP->y;
				curP->v[2]=curP->z;
				//set border values
				if (curP->x<minx) minx=curP->x; 
				if (curP->x>maxx) maxx=curP->x; 
				if (curP->y<miny) miny=curP->y; 
				if (curP->y>maxy) maxy=curP->y; 
				if (curP->z<minz) minz=curP->z; 
				if (curP->z>maxz) maxz=curP->z; 

				curP=curP->next;
			}
			curO=curO->next;
			if (curO!=NULL) curP=curO->firstPoint;
		}
		curOL=curOL->next;
		if (curOL!=NULL) curO=curOL->firstObject;
		if (curO!=NULL) curP=curO->firstPoint;
	} 

	centerx=(maxx+minx)/2.0;
	centery=(maxy+miny)/2.0;
	centerz=(maxz+minz)/2.0;
/**/
printf("	minx=%f \t	 miny=%f \t	 minz=%f\n", minx, miny, minz);
printf("centerx=%f \t centery=%f \t centerz=%f\n", centerx, centery, centerz);
printf("	maxx=%f \t	 maxy=%f \t	 maxz=%f\n", maxx, maxy, maxz);
/**/

}

