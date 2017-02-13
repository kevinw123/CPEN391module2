#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Gps.h"

#define pi 3.14159265358979323846

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

	if (extracted_first_log == 0) {
		start_latitude_float = latitude_float;
		sprintf(start_latitude, "%s", latitude);
	}
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

	if (extracted_first_log == 0) {
		start_longitude_float = longitude_float;
		sprintf(start_longitude, "%s", longitude);
	}
}

float deg2rad(float degree) {
	return degree * pi / 180;
}

float rad2deg(float rad) {
	return rad * 180 / pi;
}

void getDistanceAndSpeed(void) {
	float theta = longitude_float - start_longitude_float;
	float distance_float = sin(deg2rad(start_latitude_float)) * sin(deg2rad(latitude_float)) + cos(deg2rad(start_latitude_float)) * cos(deg2rad(latitude_float)) * cos(deg2rad(theta));
	distance_float = acos(distance_float);
	distance_float = rad2deg(distance_float);
	distance_float = distance_float * 60 * 1.1515;
	distance_float = distance_float * 1.609344 * 1000;

	sprintf(speed, "%d M/S", (int) distance_float);

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
	printf("Total Distance: %s", distance);

	getAverageSpeed();
	printf("Average Speed: %s, \n\n", average_speed);
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
				printf("Speed: %s ", speed);

				if (extracted_first_log == 0) {
					extracted_first_log = 1;
				}

				extracted_log = 1;
			}
		}
	}
}
