#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "Gps.h"

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

		// Extract ss.sss
		for (i = 0; i < 6; i++) {
			seconds[i] = getDataGPS();
		}
		seconds[i] = '\0';

		// Convert hours from UTC to PST
		int hours_pst = atoi(hours_utc);
		if (hours_pst - 8 < 0) {
			hours_pst += 16;
		} else {
			hours_pst -= 8;
		}

		sprintf(current_time, "%d:%s:%s PST", hours_pst, minutes, seconds);

		// Extract comma and return
		getDataGPS();
	} else {
		sprintf(current_time, "Invalid/Empty");
	}
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
		float latitude_float = degrees_float + minutes_float / 60;

		// Comma
		getDataGPS();

		char *direction;
		getField(direction);
		sprintf(latitude, "%f %s", latitude_float, direction);

	} else {
		sprintf(latitude, "Invalid/Empty");
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
		float longitude_float = degrees_float + minutes_float / 60;

		// Comma
		getDataGPS();

		char *direction;
		getField(direction);
		sprintf(longitude, "%f %s", longitude_float, direction);
	} else {
		sprintf(longitude, "Invalid/Empty");
	}
}


void getFieldWithUnit(char *field_with_unit) {
	char field[DATASIZE];
	getField(field);

	char unit[DATASIZE];
	getField(unit);

	sprintf(field_with_unit, "%s %s", field, unit);
}

void PrintLog(void) {
	char startArray[7] = "$GPGGA,";
	int startArray_idx = 0;

	char c;
	int extracted_log = 0;

	while (extracted_log == 0){
		c = getDataGPS();

		// Check for $GPGGA,
		if (c != startArray[startArray_idx]) {
			startArray_idx = 0;
		} else {
			startArray_idx++;
			if (startArray_idx == 7) {
				getTime(current_time);
				printf("Time: %s, ", current_time);

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
				printf("Geoidal Separation: %s\n\n", geoidalSeparation);

				extracted_log = 1;
			}
		}
	}
}
