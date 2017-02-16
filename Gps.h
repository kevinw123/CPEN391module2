#define GPS_Control (*(volatile unsigned char *)(0x84000210))
#define GPS_Status (*(volatile unsigned char *)(0x84000210))
#define GPS_TxData (*(volatile unsigned char *)(0x84000212))
#define GPS_RxData (*(volatile unsigned char *)(0x84000212))
#define GPS_Baud (*(volatile unsigned char *)(0x84000214))

#define DATASIZE 50

#define pi 3.141592653589793238462643383279502884197169399375105820974944592307816406286

int session_started;

// start time, time elapsed, average speed, calories burned, start coordinates, end coordinates
int extracted_first_log;

// Start time, current time, and time elapsed
int time_seconds;
int start_time_seconds;
char start_time[DATASIZE];
char current_time[DATASIZE];
int time_elapsed_seconds;
char time_elapsed[DATASIZE];

// Starting point, ending point, and distance
float start_latitude_float;
float start_longitude_float;
char start_latitude[DATASIZE];
char start_longitude[DATASIZE];

int test_index;
float previous_latitude_float;
float previous_longitude_float;
float latitude_float;
float longitude_float;
char latitude[DATASIZE];
char longitude[DATASIZE];
int distance_int;
char distance[DATASIZE];

// Current speed and average speed
int speed_int;
char speed[DATASIZE];
char average_speed[DATASIZE];
int max_speed_int;
char max_speed[DATASIZE];
// Remaining GPS data
char fix[DATASIZE];
char satellites[DATASIZE];
char HDOP[DATASIZE];
char altitude[DATASIZE];
char geoidalSeparation[DATASIZE];

void Init_GPS(void);
char getDataGPS(void);
void getTime(char *current_time);
void getTimeElapsed(char *time_elapsed);
void getField(char *field);
void initPointsTest(void);
void getLatitude(char *latitude);
void getLongitude(char *longitude);
double deg2rad(double degree);
double rad2deg(double rad);
void getDistanceAndSpeed(char *speed, char *distance);
void getAverageSpeed(char *average_speed);
void getFieldWithUnit(char *field_with_unit);
void PrintLog(void);
