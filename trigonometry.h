
#ifndef __trigonometry_h_ 
#define __trigonometry_h_

void convertCoordinateToDistance(float lat, float lon, float centerlat, float centerlon, float *x, float *z);
float convertCoordinateToDistanceX(float lon);
float convertCoordinateToDistanceZ(float lat);
float toRadian(float degree);

#endif /* __trigonometry_h_ */ 

