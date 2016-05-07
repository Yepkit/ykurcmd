#ifndef USBCOM_H
#define USBCOM_H

static int sendCommand(unsigned char *toSendBuffer, unsigned char *receivedBuffer);

int command(char cmd, char addr);

int commandBySerial(char *iSerial, char cmd, char addr);

int listDevices();


#endif // USBCOM_H
