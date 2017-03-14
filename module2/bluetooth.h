#define BlueTooth_Control (*(volatile unsigned char *)(0x84000220))
#define BlueTooth_Status (*(volatile unsigned char *)(0x84000220))
#define BlueTooth_TxData (*(volatile unsigned char *)(0x84000222))
#define BlueTooth_RxData (*(volatile unsigned char *)(0x84000222))
#define BlueTooth_Baud (*(volatile unsigned char *)(0x84000224))

void initBluetooth(void);
char getcharBluetooth(void);
void enterCommandMode(void);
void changeName(void);
void factoryReset(void);
void setBluetoothPassword(void);
void sendStringBluetooth(char *s);