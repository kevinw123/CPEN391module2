#define WiFi_Control (*(volatile unsigned char *)(0x84000240))
#define WiFi_Status (*(volatile unsigned char *)(0x84000240))
#define WiFi_TxData (*(volatile unsigned char *)(0x84000242))
#define WiFi_RxData (*(volatile unsigned char *)(0x84000242))
#define WiFi_Baud (*(volatile unsigned char *)(0x84000244))
#define WiFi_MAC "5E-CF-7F-00-72-07"

#define twilio_sid (char *) "ACdf97e78cb75873b63b024c50327560d"
#define twilio_token (char *) "0ae19b7e6204d61f0f30abc9dd180112"
#define twilio_number (char *) "+12045002986"
#define SETUP_LUA "dofile(\"mongoDB.lua\")"
#define SEND_SMS "testPost()"
// twilio creds:
// chankchankchank@gmail.com
// CPEN39125!

void test_wifi(void);
int checkIfNewData(void);
int getcharWiFi(void);
int putcharWiFi(int c);
void Init_WiFi(void);
void writeReturnNewLine(void);
void sendCommand(char *string);
char* createInsertCommand(char *id, char *start_lat, char *start_long, char *end_lat, char *end_long, char *start_time, char *end_time, char *total_distance, char *speed);
char* createCallCommand(char *numberToCall);
char* waitForAPIResponse(int size);
char* createGetCommand(char *id);
char* createCallCommand(char *numberToCall);
char* createGetPrevSessionCountCommand();
char* createUpdatePrevSessionCountCommand(char *count);
char* createInsertAchieveCommand(char *id, char *dist1, char *dist2, char *ses1, char *ses2, char *speed1, char *speed2, char *numSessions, char *achieve_radius);
