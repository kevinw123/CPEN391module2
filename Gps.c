#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "graphics.h"
#include "Colours.h"
#include "Gps.h"

#define pi 3.141592653589793238462643383279502884197169399375105820974944592307816406286

float latitude_test[11];
float longitude_test[11];
float x_map[11];
float y_map[11];

void initPointsTest(void) {
	latitude_test[0] = 49.262477;
	longitude_test[0] = -123.250759;
	x_map[0] = 797;
	y_map[0] = 105;

	latitude_test[1] = 49.261933;
	longitude_test[1] = -123.250289;
	x_map[1] = 600;
	y_map[1] = 105;

	latitude_test[2] = 49.261556;
	longitude_test[2] = -123.249967;
	x_map[2] = 400;
	y_map[2] = 105;

	latitude_test[3] = 49.261061;
	longitude_test[3] = -123.249583;
	x_map[3] = 200;
	y_map[3] = 105;

	latitude_test[4] = 49.260568;
	longitude_test[4] = -123.249158;
	x_map[4] = 21;
	y_map[4] = 105;

	latitude_test[5] = 49.260988;
	longitude_test[5] = -123.248062;
	x_map[5] = 21;
	y_map[5] = 243;

	latitude_test[6] = 49.261360;
	longitude_test[6] = -123.246977;
	x_map[6] = 21;
	y_map[6] = 400;

	latitude_test[7] = 49.261885;
	longitude_test[7] = -123.247312;
	x_map[7] = 200;
	y_map[7] = 400;

	latitude_test[8] = 49.262316;
	longitude_test[8] = -123.247709;
	x_map[8] = 400;
	y_map[8] = 400;

	latitude_test[9] = 49.262838;
	longitude_test[9] = -123.248073;
	x_map[9] = 600;
	y_map[9] = 397;

	latitude_test[10] = 49.262477;
	longitude_test[10] = -123.250759;
	x_map[10] = 797;
	y_map[10] = 105;
}

void Init_GPS(void) {
	// Set up 6850 Control Register to utilize a divide by 16 clock,
	// use 8 bits of data, no parity, 1 stop bit,
	// Program baud rate generator to use 9600 baud
	GPS_Control = 0x15;  // 0 00 101 01
	GPS_Baud = 0x05; // 0b101
	printf("Initialized GPS\n");
}


char getDataGPS(void) {
	// Poll Rx bit in 6850 status register. Wait for it to become '1'.
	while ((GPS_Status & 1) == 0) {
		// Wait for it to become '1'
	}

	// Read received character from 6850 RxData register.
	return GPS_RxData;
}

void getTime(char *current_time) {

	char c = getDataGPS();
	if (c != ',') {
		char hours_utc[3];
		char minutes[3];
		char seconds[7];

		// Extract hh
		hours_utc[0] = c;
		hours_utc[1] = getDataGPS();
		hours_utc[2] = '\0';

		// Extract mm
		int i;
		for (i = 0; i < 2; i++) {
			minutes[i] = getDataGPS();
		}
		minutes[i] = '\0';
		int minutes_int = atoi(minutes);

		// Extract ss.sss
		for (i = 0; i < 6; i++) {
			seconds[i] = getDataGPS();
		}
		seconds[i] = '\0';
		int seconds_int = (int)(atof(seconds));

		// Convert hours from UTC to PST
		int hours_pst = atoi(hours_utc);
		if (hours_pst - 8 < 0) {
			hours_pst += 16;
		} else {
			hours_pst -= 8;
		}

		time_seconds = hours_pst * 3600 + minutes_int * 60 + seconds_int;

		sprintf(current_time, "%d:%d:%d PST", hours_pst, minutes_int, seconds_int);

		// Extract comma and return
		getDataGPS();
	} else {
		sprintf(current_time, "Invalid/Empty");
	}

	if (extracted_first_log == 0) {
		start_time_seconds = time_seconds;
		sprintf(start_time, "%s", current_time);
	}
}

void getTimeElapsed(void) {
	time_elapsed_seconds = time_seconds - start_time_seconds;
	int hours_elapsed = time_elapsed_seconds / 3600;
	int seconds_elapsed = time_elapsed_seconds % 3600;
	int minutes_elapsed = time_elapsed_seconds / 60;
	seconds_elapsed = seconds_elapsed % 60;
	sprintf(time_elapsed, "%d:%d:%d ", hours_elapsed, minutes_elapsed, seconds_elapsed);
}

void getField(char *field) {
	char c = getDataGPS();
	if (c != ',') {
		char temp[DATASIZE];

		int i = 0;
		while ((c != ',')) {
			temp[i] = c;
			c = getDataGPS();
			i++;
		}

		temp[i] = '\0';
		sprintf(field, &temp[0]);
	} else {
		sprintf(field, "Invalid/Empty");
	}
}

float getTestLatitude() {
	return latitude_test[test_index];
}

void getLatitude(char *latitude) {

	char c = getDataGPS();
	if (c != ',') {
		char degrees[3];
		char minutes[8];

		// Extract dd
		degrees[0] = c;
		degrees[1] = getDataGPS();
		degrees[2] = '\0';

		// Extract mm.mmmm
		int i;
		for (i = 0; i < 7; i++) {
			minutes[i] = getDataGPS();
		}
		minutes[i] = '\0';

		// latitude = dd + mm.mmmm / 60
		float degrees_float = atof(degrees);
		float minutes_float = atof(minutes);
		latitude_float = degrees_float + minutes_float / 60;

		// Comma
		getDataGPS();

		char *direction;
		getField(direction);
		sprintf(latitude, "%f %s", latitude_float, direction);

	} else {
		sprintf(latitude, "Invalid/Empty");
	}

	latitude_float = getTestLatitude();
	if (extracted_first_log == 0) {
		start_latitude_float = latitude_float;
		previous_latitude_float = latitude_float;
		sprintf(start_latitude, "%s", latitude);
	}
}

float getTestLongitude(void) {
	return longitude_test[test_index];
}

void getLongitude(char *longitude) {

	char c = getDataGPS();
	if (c != ',') {
		char degrees[4];
		char minutes[8];

		// Extract dd
		degrees[0] = c;
		int i;
		for (i = 1; i < 3; i++) {
			degrees[i] = getDataGPS();
		}
		degrees[i] = '\0';

		// Extract mmm.mmmm
		for (i = 0; i < 7; i++) {
			minutes[i] = getDataGPS();
		}
		minutes[i] = '\0';

		// longitude = dd + mmm.mmmm / 60
		float degrees_float = atof(degrees);
		float minutes_float = atof(minutes);
		longitude_float = degrees_float + minutes_float / 60;

		// Comma
		getDataGPS();

		char *direction;
		getField(direction);
		sprintf(longitude, "%f %s", longitude_float, direction);
	} else {
		sprintf(longitude, "Invalid/Empty");
	}

	longitude_float = getTestLongitude();
	if (extracted_first_log == 0) {
		start_longitude_float = longitude_float;
		previous_longitude_float = longitude_float;
		sprintf(start_longitude, "%s", longitude);
	}
}

double deg2rad(double degree) {
	return degree * pi / 180;
}

double rad2deg(double rad) {
	return rad * 180 / pi;
}

void getDistanceAndSpeed(void) {
	printf("\nPrevious longitude: %f, Longitude: %f, Previous Latitude: %f, Latitude: %f\n", previous_longitude_float, longitude_float, previous_latitude_float, latitude_float);
	double theta = previous_longitude_float - longitude_float;

	double distance_float = sin(deg2rad(((double)previous_latitude_float)));
	distance_float *= sin(deg2rad((double)latitude_float));
	distance_float += cos(deg2rad((double)previous_latitude_float)) * cos(deg2rad((double)latitude_float)) * cos(deg2rad(theta));
	distance_float = acos(distance_float);
	distance_float = rad2deg(distance_float);
	distance_float = distance_float * 60 * 1.1515;
	distance_float = distance_float * 1.609344 * 1000;
	sprintf(speed, "%d M/S", (int)distance_float);

	if (extracted_first_log == 0) {
		distance_int = (int)distance_float;
	}
	distance_int += (int)distance_float;

	sprintf(distance, "%d M", distance_int);
}

void getAverageSpeed(void) {
	sprintf(average_speed, "%d M/S", (distance_int / time_elapsed_seconds));
}

void getFieldWithUnit(char *field_with_unit) {
	char field[DATASIZE];
	getField(field);

	char unit[DATASIZE];
	getField(unit);

	sprintf(field_with_unit, "%s %s", field, unit);
}

void getSessionData(void) {
	printf("Start time: %s ", start_time);
	printf("Time Elapsed: %s ", time_elapsed);
	printf("Start Latitude: %s ", start_latitude);
	printf("Start Longitude: %s ", start_longitude);
	printf("End Latitude: %s ", latitude);
	printf("End Longitude: %s ", longitude);
	printf("Total Distance: %s ", distance);

	getAverageSpeed();
	printf("Average Speed: %s, \n\n", average_speed);
}

int previousLatitudeToX(float lat_point){
	return x_map[test_index - 1];
}

int previousLongitudeToY(float long_point) {
	return y_map[test_index - 1];
}

int latitudeToX(float lat_point) {
	return x_map[test_index];
}

int longitudeToY(float long_point) {
	return y_map[test_index];
}

void drawPath(void) {
	int x1, y1, x2, y2;
	if (test_index > 0) {
		x1 = previousLatitudeToX(previous_latitude_float);
		y1 = previousLongitudeToY(previous_longitude_float);
		x2 = latitudeToX(latitude_float);
		y2 = longitudeToY(longitude_float);
		WriteLine(x1, x2, y1, y2, RED);
	}

	test_index++;
	if (test_index == 11) {
		test_index = 1;
	}
}

void PrintLog(void) {
	char startArray[7] = "$GPGGA,";
	int startArray_idx = 0;

	char c;
	int extracted_log = 0;

	while (extracted_log == 0) {
		c = getDataGPS();

		// Check for $GPGGA,
		if (c != startArray[startArray_idx]) {
			startArray_idx = 0;
		} else {
			startArray_idx++;
			if (startArray_idx == 7) {
				getTime(current_time);
				printf("Time: %s, ", current_time);

				getTimeElapsed();
				printf("Time Elapsed: %s, ", time_elapsed);

				getLatitude(latitude);
				printf("Latitude: %s, ", latitude);

				getLongitude(longitude);
				printf("Longitude: %s, ", longitude);

				getField(fix);
				printf("Fix: %s, ", fix);

				getField(satellites);
				printf("Satellites: %s, ", satellites);

				getField(HDOP);
				printf("HDOP: %s, ", HDOP);

				getFieldWithUnit(altitude);
				printf("Altitude: %s, ", altitude);

				getFieldWithUnit(geoidalSeparation);
				printf("Geoidal Separation: %s, ", geoidalSeparation);

				getDistanceAndSpeed();
				printf("Distance: %s, ", distance);
				printf("Speed: %s \n\n", speed);

				if (session_started == 1) {
					drawPath();
					previous_latitude_float = latitude_float;
					previous_longitude_float = longitude_float;
					if (extracted_first_log == 0) {
						extracted_first_log = 1;
					}
				}

				extracted_log = 1;
			}
		}
	}
}
