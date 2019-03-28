#ifndef COMMUNICATION_H_
#define COMMUNICATION_H_
#include "UARTDriver.h"
void COMM_vfnDriverInit (void);
uint_8 COMM_bfnSendMsg (uint_8* bpMsgToSend, uint_8 bMsgSize);
uint_8 COMM_bfnReceiveMsg (uint_8* bpDataRx);
#endif
