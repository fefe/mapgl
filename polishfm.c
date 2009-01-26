
/*

Read Polish File Format

Based on: cGPSmapper-UsrMan-v02.4.3.pdf
Source: http://cgpsmapper.com/manual.htm

*/

#include <stdio.h>
#include <string.h>
#include "stringhandling.h"
#include "datastructure.h"
#include "polishfm.h"

void processSection (char *sSection) {
	int iTmp, bodyObject=0;
	/* Body */
	if (strcmp("POI", sSection) == 0 || strcmp("RGN10", sSection) == 0 || strcmp("RGN20", sSection) == 0) {
		bodyObject=1;
	} else if (strcmp("POLYGON", sSection) == 0 || strcmp("RGN80", sSection) == 0) {
		/* Body */
		bodyObject=1;
	} else if (strcmp("POLYLINE", sSection) == 0 || strcmp("RGN40", sSection) == 0) {
		/* Body */
		bodyObject=1;
	} else if (strcmp("WPT", sSection) == 0) {
		/* Body */
		bodyObject=1;
	} else if (strcmp("PLT", sSection) == 0) {
		/* Body */
		bodyObject=1;
	} else if (strcmp("SHP", sSection) == 0) {
		/* Body */
		bodyObject=1;
	} else if (strcmp("DBX", sSection) == 0) {
		/* Body */
		bodyObject=1;
		//undocumented
		printf("--- Undocumented section found: %s\n", sSection);
		return;
	} else if (strcmp("FILE", sSection) == 0) {
		/* Body */
		bodyObject=1;
	} else {
		printf("--- Not body object: %s\n", sSection);
		return;
	}
	//filtering done, valid sections were found
	if (bodyObject == 1) {
		if (activeObjectList == NULL || strcmp(activeObjectList->sType, sSection) != 0) {
			activeObjectList=getObjectList(sSection);
		}
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
	if (strcmp("IMG_ID", sSection) == 0) {
		/* Header */
		//mandatory
		if (strcmp("ID", sKey) == 0) {
			//mandatory
			sscanf(sValue, "%d", &iImgId);
		} else if (strcmp("Name", sKey) == 0) {
			//mandatory
			sImgName=(char*)malloc(sizeof(char)*(strlen(sValue)+1));
			strcpy(sImgName, sValue);
		} else if (strcmp("LBLcoding", sKey) == 0) {
		} else if (strcmp("Codepage", sKey) == 0) {
		} else if (strcmp("Datum", sKey) == 0) {
		} else if (strcmp("Transparent", sKey) == 0) {
		} else if (strcmp("MG", sKey) == 0) {
		} else if (strcmp("Numbering", sKey) == 0) {
		} else if (strcmp("Routing", sKey) == 0) {
		} else if (strcmp("Lock", sKey) == 0) {
		} else if (strcmp("ProductCode", sKey) == 0) {
		} else if (strcmp("CopyRight", sKey) == 0) {
		} else if (strcmp("Elevation", sKey) == 0) {
		} else if (strcmp("POIOnly", sKey) == 0) {
		} else if (strcmp("POIIndex", sKey) == 0) {
		} else if (strcmp("POINumberFirst", sKey) == 0) {
		} else if (strcmp("POIZipFirst", sKey) == 0) {
		} else if (strcmp("DefaultCityCountry", sKey) == 0) {
		} else if (strcmp("DefaultRegionCount", sKey) == 0) {
		} else if (strcmp("TreSize", sKey) == 0) {
			//mandatory
		} else if (strcmp("RgnLimit", sKey) == 0) {
			//mandatory
		} else if (strcmp("SimplifyLevel", sKey) == 0) {
		} else if (strcmp("PreProcess", sKey) == 0) {
		} else if (strcmp("Levels", sKey) == 0) {
			//mandatory
		} else if (strcmp("Level#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else if (strcmp("Zoom#", sKey) == 0) {
			//todo - # has to be replaced in matching patter to a real digit
		} else if (strcmp("Preview", sKey) == 0) {
		} else if (strcmp("AlighMethod", sKey) == 0) {
		} else if (strcmp("BlockSize", sKey) == 0) {
		} else if (strcmp("LevelFill", sKey) == 0) {
		} else if (strcmp("LevelLimit", sKey) == 0) {
		} else if (strcmp("WorldMap", sKey) == 0) {
		} else if (strcmp("DrawPriority", sKey) == 0) {
		} else if (strcmp("Marine", sKey) == 0) {
		} else if (strcmp("", sKey) == 0) {
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (strcmp("COUNTRIES", sSection) == 0) {
		/*  Declarations */
		if (strcmp("Country#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (strcmp("REGIONS", sSection) == 0) {
		/*  Declarations */
		if (strcmp("Region#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else if (strcmp("CountryIdx#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (strcmp("CITIES", sSection) == 0) {
		/*  Declarations */
		if (strcmp("City#", sKey) == 0) {
		} else if (strcmp("RegionIdx#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (strcmp("CHART_INFO", sSection) == 0) {
		/*  Declarations */
		if (strcmp("Name", sKey) == 0) {
		} else if (strcmp("Number", sKey) == 0) {
		} else if (strcmp("Projection", sKey) == 0) {
		} else if (strcmp("Published", sKey) == 0) {
		} else if (strcmp("Scale", sKey) == 0) {
		} else if (strcmp("DeltaSN", sKey) == 0) {
		} else if (strcmp("DeltaWE", sKey) == 0) {
		} else if (strcmp("IALA", sKey) == 0) {
		} else if (strcmp("Print", sKey) == 0) {
		} else if (strcmp("Edition", sKey) == 0) {
		} else if (strcmp("Correction", sKey) == 0) {
		} else if (strcmp("Text", sKey) == 0) {
		} else if (strcmp("TextFile", sKey) == 0) {
		} else if (strcmp("ReferenceEllipsoid", sKey) == 0) {
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (strcmp("BACKGROUND", sSection) == 0) {
		/* Advanced declarations */
		if (strcmp("Name", sKey) == 0) {
			//mandatory
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (strcmp("DICTIONARY", sSection) == 0) {
		/* Advanced declarations */
		if (strcmp("Level#RGNnn", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
			//todo - nn has to be replaced in matching patter to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (strcmp("HIGHWAYS", sSection) == 0) {
		/* Advanced declarations */
		//undocumented
		printf("--- Undocumented section found: %s\n", sSection);
		return;
	} else if (strcmp("ZIPCODES", sSection) == 0) {
		/* Advanced declarations */
		//undocumented
		printf("--- Undocumented section found: %s\n", sSection);
		return;
	} else if (strcmp("DEFINITIONS", sSection) == 0) {
		/* Advanced declarations */
		//undocumented
		printf("--- Undocumented section found: %s\n", sSection);
		return;
	} else if (strcmp("POI", sSection) == 0 || strcmp("RGN10", sSection) == 0 || strcmp("RGN20", sSection) == 0) {
		/* Body */
		bodyObject=1;
		if (strcmp("Type", sKey) == 0) {
			//mandatory
		} else if (strcmp("SubType", sKey) == 0) {
		} else if (strcmp("Marine", sKey) == 0) {
		} else if (strcmp("City", sKey) == 0) {
		} else if (strcmp("Label", sKey) == 0) {
		} else if (strcmp("EndLevel", sKey) == 0) {
		} else if (strcmp("Data1", sKey) == 0) {
			//mandatory
		} else if (strcmp("Data#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else if (strcmp("StreetDesc", sKey) == 0) {
		} else if (strcmp("OvernightParking", sKey) == 0) {
		} else if (strcmp("Highway", sKey) == 0) {
		} else if (strcmp("CityName", sKey) == 0) {
		} else if (strcmp("RegionName", sKey) == 0) {
		} else if (strcmp("CountryName", sKey) == 0) {
		} else if (strcmp("Zip", sKey) == 0) {
		} else if (strcmp("Exit#", sKey) == 0) {
			//todo - # has to be replaced in matching patter to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (strcmp("POLYGON", sSection) == 0 || strcmp("RGN80", sSection) == 0) {
		/* Body */
		bodyObject=1;
		if (strcmp("Type", sKey) == 0) {
			//mandatory
		} else if (strcmp("SubType", sKey) == 0) {
		} else if (strcmp("Marine", sKey) == 0) {
		} else if (strcmp("Label", sKey) == 0) {
		} else if (strcmp("EndLevel", sKey) == 0) {
		} else if (strcmp("Background", sKey) == 0) {
		} else if (strcmp("Data1", sKey) == 0) {
			//mandatory
		} else if (strcmp("Data#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (strcmp("POLYLINE", sSection) == 0 || strcmp("RGN40", sSection) == 0) {
		/* Body */
		bodyObject=1;
		if (strcmp("Type", sKey) == 0) {
		} else if (strcmp("SubType", sKey) == 0) {
		} else if (strcmp("Marine", sKey) == 0) {
		} else if (strcmp("Label", sKey) == 0) {
		} else if (strcmp("Label2", sKey) == 0) {
		} else if (strcmp("EndLevel", sKey) == 0) {
		} else if (strcmp("Data1", sKey) == 0) {
			//mandatory
		} else if (strcmp("Data#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else if (strcmp("StreetDesc", sKey) == 0) {
		} else if (strcmp("DirIndicator", sKey) == 0) {
		} else if (strcmp("CityName", sKey) == 0) {
		} else if (strcmp("RegionName", sKey) == 0) {
		} else if (strcmp("CountryName", sKey) == 0) {
		} else if (strcmp("Zip", sKey) == 0) {
		} else if (strcmp("RoadID", sKey) == 0) {
		} else if (strcmp("Numbers#", sKey) == 0) {
			//todo - # has to be replaced in matching patter to a real digit
		} else if (strcmp("Routeparam", sKey) == 0) {
		} else if (strcmp("NodID", sKey) == 0) {
			//todo - # has to be replaced in matching patter to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (strcmp("WPT", sSection) == 0) {
		/* Body */
		bodyObject=1;
		if (strcmp("", sKey) == 0) {
		} else if (strcmp("RgnType", sKey) == 0) {
			//mandatory
		} else if (strcmp("Type", sKey) == 0) {
			//mandatory
		} else if (strcmp("EndLevel", sKey) == 0) {
		} else if (strcmp("File#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (strcmp("PLT", sSection) == 0) {
		/* Body */
		bodyObject=1;
		if (strcmp("RgnType", sKey) == 0) {
			//mandatory
		} else if (strcmp("Type", sKey) == 0) {
			//mandatory
		} else if (strcmp("Label", sKey) == 0) {
		} else if (strcmp("DirIndicator", sKey) == 0) {
		} else if (strcmp("EndLevel", sKey) == 0) {
		} else if (strcmp("File#", sKey) == 0) {
			//mandatory
			//todo - # has to be replaced in matching patter to a real digit
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (strcmp("SHP", sSection) == 0) {
		/* Body */
		bodyObject=1;
		if (strcmp("name", sKey) == 0) {
			//mandatory
		} else if (strcmp("Type", sKey) == 0) {
			//mandatory
		} else if (strcmp("LabelField", sKey) == 0) {
		} else if (strcmp("Label2Field", sKey) == 0) {
			//mandatory
		} else if (strcmp("TypeField", sKey) == 0) {
		} else if (strcmp("SubTypeField", sKey) == 0) {
		} else if (strcmp("DirField", sKey) == 0) {
		} else if (strcmp("Level", sKey) == 0) {
			//mandatory
		} else if (strcmp("EndLevel", sKey) == 0) {
			//mandatory
		} else if (strcmp("DefaultType", sKey) == 0) {
		} else if (strcmp("CityName", sKey) == 0) {
		} else if (strcmp("RegionName", sKey) == 0) {
		} else if (strcmp("CountryName", sKey) == 0) {
		} else if (strcmp("HouseNumber", sKey) == 0) {
		} else if (strcmp("StreetDesc", sKey) == 0) {
		} else if (strcmp("PhoneNumber", sKey) == 0) {
		} else if (strcmp("Zip", sKey) == 0) {
		} else if (strcmp("RoatID", sKey) == 0) {
		} else if (strcmp("SpeedType", sKey) == 0) {
		} else if (strcmp("RoadClass", sKey) == 0) {
		} else if (strcmp("OneWay", sKey) == 0) {
		} else if (strcmp("Toll", sKey) == 0) {
		} else if (strcmp("VehicleD", sKey) == 0) {
		} else if (strcmp("VehicleC", sKey) == 0) {
		} else if (strcmp("VehicleB", sKey) == 0) {
		} else if (strcmp("VehicleT", sKey) == 0) {
		} else if (strcmp("VehicleP", sKey) == 0) {
		} else if (strcmp("VehicleI", sKey) == 0) {
		} else if (strcmp("VehicleR", sKey) == 0) {
		} else if (strcmp("TextFileLines", sKey) == 0) {
		} else if (strcmp("TextStart", sKey) == 0) {
		} else if (strcmp("TextEnd", sKey) == 0) {
		} else if (strcmp("TextFile", sKey) == 0) {
		} else if (strcmp("Color", sKey) == 0) {
		} else if (strcmp("Style", sKey) == 0) {
		} else if (strcmp("Height", sKey) == 0) {
		} else if (strcmp("Depth", sKey) == 0) {
		} else if (strcmp("DepthUnit", sKey) == 0) {
		} else if (strcmp("HeightUnit", sKey) == 0) {
		} else if (strcmp("Position", sKey) == 0) {
		} else if (strcmp("DepthFlag", sKey) == 0) {
		} else if (strcmp("FoundationColor", sKey) == 0) {
		} else if (strcmp("Light", sKey) == 0) {
		} else if (strcmp("LightType", sKey) == 0) {
		} else if (strcmp("Note", sKey) == 0) {
		} else if (strcmp("LocalDesignator", sKey) == 0) {
		} else if (strcmp("IngernationalDesignator", sKey) == 0) {
		} else if (strcmp("Period", sKey) == 0) {
		} else if (strcmp("HeightAboveFoundation", sKey) == 0) {
		} else if (strcmp("HeightAboveDatum", sKey) == 0) {
		} else if (strcmp("HeightAboveFoundationUnit", sKey) == 0) {
		} else if (strcmp("HeightAboveDatumUnit", sKey) == 0) {
		} else if (strcmp("LeadingAngle", sKey) == 0) {
		} else if (strcmp("Racon", sKey) == 0) {
		} else if (strcmp("DoubleLights", sKey) == 0) {
		} else if (strcmp("DoubleLightsHorizontal", sKey) == 0) {
		} else if (strcmp("FacilityPoint", sKey) == 0) {
		} else {
			printf("--- Unknown tag found in section %s: %s\n", sSection, sKey);
			return;
		}
	} else if (strcmp("DBX", sSection) == 0) {
		/* Body */
		bodyObject=1;
		//undocumented
		printf("--- Undocumented section found: %s\n", sSection);
		return;
	} else if (strcmp("FILE", sSection) == 0) {
		/* Body */
		bodyObject=1;
		if (strcmp("name", sKey) == 0) {
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
	if (bodyObject == 1) {
		if (strcmp(sTmp, "Data") != 0) {
printf("xxxx---process tag\n");
			addAttributeToObject(activeObject, sKey, sValue);
		} else {
			processData(sValue);
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
		iTmp=sscanf(sData, "%f,%f", &x, &z);
		if (iTmp == 1) {
printf("xxxx---process data\n");
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
		printf("error opening file: %s", sFileName);
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
			//printf("strcmp:%d char:%d\n", strcmp("", sLine), sLine[0]); //debug
			
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
							
						} else {
							printf("%d: section not found: length=%d\n", iLineNo, iTmp);
						}
					} else {
						//we are in a section, this is the close tag
						int iTmp=strlen(sLine);
						char sTmp[iTmp+1];
						sscanf(sLine, "[%3s", sTmp);
						sTmp[3]='\0';
						if (strcmp(sTmp, "END") != 0) {
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
					printf("%d: sec:%s key:%s value:%s\n", iLineNo, sSection, sKey, sValue);
					processTag(sSection, sKey, sValue);
				}
			}
		}
		free(sLine);
	}
} 


