#define WiFi_Control (*(volatile unsigned char *)(0x84000240))
#define WiFi_Status (*(volatile unsigned char *)(0x84000240))
#define WiFi_TxData (*(volatile unsigned char *)(0x84000242))
#define WiFi_RxData (*(volatile unsigned char *)(0x84000242))
#define WiFi_Baud (*(volatile unsigned char *)(0x84000244))
#define WiFi_MAC "5E-CF-7F-00-72-07"

#define twilio_sid (char *) "ACdf97e78cb75873b63b024c50327560d"
#define twilio_token (char *) "0ae19b7e6204d61f0f30abc9dd180112"
#define twilio_number (char *) "+12045002986"
#define SETUP_LUA "dofile(\"send_text_message.lua\")"
#define SEND_SMS "check_wifi()"
// twilio creds:
// chankchankchank@gmail.com
// CPEN39125!

void test_wifi(void);
int checkIfNewData(void);
int getcharWiFi(void);
int putcharWiFi(int c);
void Init_WiFi(void);
void writeReturnNewLine(void);
