
#include <stdio.h>
//#include <stdlib.h>
#include <math.h>
#include "datastructure.h"
#include "stringhandling.h"
#include "trigonometry.h"

#define GL_PI 3.1415926536f

void convertCoordinateToDistance(float lat, float lon, float centerlat, float centerlon, float *x, float *z) {
	//converts lat,lon coordinates to world coordinates in km
//todo - optimize sine/cosine computations

/*
	cosD = sin(Lat1) * sin(Lat2) + cos(Lat1) * cos(Lat2) * cos(Long1 - Long2);
	if(cosD > 1.0)
		cosD = 1.0;
	else if(cosD < -1.0)
		cosD = -1.0;
	Distance = 6378.0 * acos(cosD);
 */

	//todo - optimize not to convert center every time
	float latRad=toRadian(lat);
	float lonRad=toRadian(lon);
	float cosD;
	// lat1=lat2 -> x coordinate
	cosD = centerlatSin * centerlatSin + centerlatCos * centerlatCos * cos(lonRad - centerlonRad);
	if(cosD > 1.0)
		cosD = 1.0;
	else if(cosD < -1.0)
		cosD = -1.0;
	*x = 6378.0 * acos(cosD);

	// lon1=lon2 -> z coordinate
	cosD = sin(latRad) * centerlatSin + cos(latRad) * centerlatCos;
	//cosD = sin(lat) * sin(centerlat) + cos(lat) * cos(centerlat) * cos(centerlon - centerlon); // but cos(0.0) == 1
	if(cosD > 1.0)
		cosD = 1.0;
	else if(cosD < -1.0)
		cosD = -1.0;
	*z = 6378.0 * acos(cosD);
}

float convertCoordinateToDistanceX(float lon) {
	float lonRad=toRadian(lon);
	float cosD;
	// lat1=lat2 -> x coordinate
	cosD = minlatSin * minlatSin + minlatCos * minlatCos * cos(lonRad - minlonRad);
	if(cosD > 1.0)
		cosD = 1.0;
	else if(cosD < -1.0)
		cosD = -1.0;
	return 6378.0 * acos(cosD);
}

float convertCoordinateToDistanceZ(float lat) {
	float latRad=toRadian(lat);
	float cosD;
	// lon1=lon2 -> z coordinate
	cosD = sin(latRad) * minlatSin + cos(latRad) * minlatCos;
	//cosD = sin(lat) * sin(centerlat) + cos(lat) * cos(centerlat) * cos(centerlon - centerlon); // but cos(0.0) == 1
	if(cosD > 1.0)
		cosD = 1.0;
	else if(cosD < -1.0)
		cosD = -1.0;
	return 6378.0 * acos(cosD);
}

/*
float convertCoordinateToDistanceX(float lon) {
	float lonRad=toRadian(lon);
	float cosD;
	// lat1=lat2 -> x coordinate
	cosD = centerlatSin * centerlatSin + centerlatCos * centerlatCos * cos(lonRad - centerlonRad);
	if(cosD > 1.0)
		cosD = 1.0;
	else if(cosD < -1.0)
		cosD = -1.0;
	return 6378.0 * acos(cosD);
}

float convertCoordinateToDistanceZ(float lat) {
	float latRad=toRadian(lat);
	float cosD;
	// lon1=lon2 -> z coordinate
	cosD = sin(latRad) * centerlatSin + cos(latRad) * centerlatCos;
	//cosD = sin(lat) * sin(centerlat) + cos(lat) * cos(centerlat) * cos(centerlon - centerlon); // but cos(0.0) == 1
	if(cosD > 1.0)
		cosD = 1.0;
	else if(cosD < -1.0)
		cosD = -1.0;
	return 6378.0 * acos(cosD);
}
*/

float toRadian(float degree) {
	return degree*GL_PI/180.0;
}

