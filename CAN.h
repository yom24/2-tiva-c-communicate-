#include "can_HAL.h"
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_can.h"
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/can.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

extern volatile uint32_t g_ui32MsgCount;

extern volatile bool g_bRXFlag;

extern volatile bool g_bErrFlag;

extern uint8 value;

void InitConsole(void);

void CAN_init_receive();

void CAN_init_send();

