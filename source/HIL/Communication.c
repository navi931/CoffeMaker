#include "Communication.h"

void COMM_vfnDriverInit (void)
{
        UART_vfnDriverInitPorts();
}

uint_8 COMM_bfnSendMsg (uint_8* bpMsgToSend, uint_8 bMsgSize)
{
	uint_8 state = ERROR;
    uint_8 checksum = bMsgSize;
    while(bMsgSize>=1)
    {
            if(UART_bfnSend(*bpMsgToSend))
            {
                    bpMsgToSend++;
                    checksum--;
                    bMsgSize--;
            }
            else
            {
            	//No se pudo mandar el msg y se reintentara
            }
    }

    if(checksum == 0)
    {
    	state = SUCCESS;
    }
    else
    {
     	state = ERROR;
    }

    return state;
}
uint_8 COMM_bfnReceiveMsg (uint_8* bpDataRx)
{
        UART_bfnRead(bpDataRx);
             return SUCCESS;
}
