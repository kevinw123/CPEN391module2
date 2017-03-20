#define BlueTooth_Control (*(volatile unsigned char *)(0x84000220))
#define BlueTooth_Status (*(volatile unsigned char *)(0x84000220))
#define BlueTooth_TxData (*(volatile unsigned char *)(0x84000222))
#define BlueTooth_RxData (*(volatile unsigned char *)(0x84000222))
#define BlueTooth_Baud (*(volatile unsigned char *)(0x84000224))

#define MOVE_COMMAND "0"
#define QUESTION_COMMAND "1"

void initBluetooth();
void enterCommandMode();
char getcharBluetooth();
void sendStringBluetooth(char *string);
void changeName();
void factoryResetDevice();
void changePassword();
