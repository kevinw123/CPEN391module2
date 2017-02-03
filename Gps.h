#define GPS_Control (*(volatile unsigned char *)(0x84000210))
#define GPS_Status (*(volatile unsigned char *)(0x84000210))
#define GPS_TxData (*(volatile unsigned char *)(0x84000212))
#define GPS_RxData (*(volatile unsigned char *)(0x84000212))
#define GPS_Baud (*(volatile unsigned char *)(0x84000214))

#define DATASIZE 20
int session_started;

char current_time[DATASIZE];
char latitude[DATASIZE];
char longitude[DATASIZE];
char fix[DATASIZE];
char satellites[DATASIZE];
char HDOP[DATASIZE];
char altitude[DATASIZE];
char geoidalSeparation[DATASIZE];

void Init_GPS(void);
char getDataGPS(void);
void getTime(char *current_time);
void getField(char *field);
void getLatitude(char *latitude);
void getLongitude(char *longitude);
void getFieldWithUnit(char *field_with_unit);
void PrintLog(void);
