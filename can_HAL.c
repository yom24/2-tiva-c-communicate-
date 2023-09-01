#include "CAN.h"

uint8
can_receive()
{
  tCANMsgObject sCANMessage;
  uint32_t ui32MsgData;
  uint8_t *pui8MsgData;
  
  pui8MsgData = (uint8_t *)&ui32MsgData;
  
  ui32MsgData = 0;
    sCANMessage.ui32MsgID = 1;
    sCANMessage.ui32MsgIDMask = 1;
    sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage.ui32MsgLen = sizeof(pui8MsgData);
    sCANMessage.pui8MsgData = pui8MsgData;
    
  
      unsigned int uIdx;

        // If the flag is set, that means that the RX interrupt occurred and
        // there is a message ready to be read from the CAN
        if(g_bRXFlag)
        {
          sCANMessage.pui8MsgData = pui8MsgData;

            //CANMessageGet(CAN0_BASE, 1, &sCANMessage, 0);

          CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_TX);
            g_bRXFlag = 0;
            
            if(sCANMessage.ui32Flags & MSG_OBJ_DATA_LOST)
            {
                UARTprintf("CAN message loss detected\n");
            }
            
            UARTprintf("Msg ID=0x%08X len=%u data=0x",
                       sCANMessage.ui32MsgID, sCANMessage.ui32MsgLen);
            for(uIdx = 0; uIdx < sCANMessage.ui32MsgLen; uIdx++)
            {
                UARTprintf("%02X ", pui8MsgData[uIdx]);
            }
            UARTprintf("total count=%u\n", g_ui32MsgCount);
        }
        else
        {
          ui32MsgData = 0;
        }
  return ui32MsgData;
}

void
can_send(uint8 value)
{
  tCANMsgObject sCANMessage;
  uint32_t ui32MsgData;
  uint8_t *pui8MsgData;

  pui8MsgData = (uint8_t *)&ui32MsgData;
  
  ui32MsgData = 0;
    sCANMessage.ui32MsgID = 1;
    sCANMessage.ui32MsgIDMask = 1;
    sCANMessage.ui32Flags = MSG_OBJ_TX_INT_ENABLE;
    sCANMessage.ui32MsgLen = sizeof(pui8MsgData);
    sCANMessage.pui8MsgData = pui8MsgData;
    
          ui32MsgData = value;
          
          /* send can message */
          UARTprintf("Sending msg: 0x %X",
                   pui8MsgData[0]);

          CANMessageSet(CAN0_BASE, 1, &sCANMessage, MSG_OBJ_TYPE_TX);
	

          if(g_bErrFlag)
          {
            UARTprintf(" error - cable connected?\n");
          }
          else
          {
            //
            // If no errors then print the count of message sent
            //
            UARTprintf(" total count = %u\n", g_ui32MsgCount);
          }
        }