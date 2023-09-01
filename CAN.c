#include "CAN.h"

volatile uint32_t g_ui32MsgCount = 0;

volatile bool g_bRXFlag = 0;

volatile bool g_bErrFlag = 0;

uint8 value = 0;

void
CANIntHandler_receive(void)
{
    uint32_t ui32Status;

    ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);

    if(ui32Status == CAN_INT_INTID_STATUS)
    {
        ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);

        g_bErrFlag = 1;
    }

    else if(ui32Status == 1)
    {
        CANIntClear(CAN0_BASE, 1);

        g_ui32MsgCount++;

        g_bRXFlag = 1;

        g_bErrFlag = 0;
        
        /*receive can message here */
        value = can_receive();
    }
    else
    {
        // Spurious interrupt handling can go here.
    }
}

void
CANIntHandler_send(void)
{
  uint32_t ui32Status;

    ui32Status = CANIntStatus(CAN0_BASE, CAN_INT_STS_CAUSE);

    if(ui32Status == CAN_INT_INTID_STATUS)
    {
        ui32Status = CANStatusGet(CAN0_BASE, CAN_STS_CONTROL);
        g_bErrFlag = 1;
    }

    else if(ui32Status == 1)
    {
        CANIntClear(CAN0_BASE, 1);

        g_ui32MsgCount++;

        g_bErrFlag = 0;
    }

    else
    {
        // Spurious interrupt handling can go here.
    }
}

void
InitConsole(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOA));

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    while(!SysCtlPeripheralReady(SYSCTL_PERIPH_UART0));

    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);


    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTStdioConfig(0, 115200, 16000000);
}

void
CAN_init_receive()
{    
  SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);
  
  InitConsole();
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB));
  
  GPIOPinConfigure(GPIO_PB4_CAN0RX);
  GPIOPinConfigure(GPIO_PB5_CAN0TX);
  
  GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);

  CANInit(CAN0_BASE);
  
  CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
  
  CANIntRegister(CAN0_BASE, CANIntHandler_receive); // if using dynamic vectors

  CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

  IntEnable(INT_CAN0);

  CANEnable(CAN0_BASE);
}

void
CAN_init_send()
{
  SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN |
                   SYSCTL_XTAL_16MHZ);
  
  InitConsole();
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
  while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOB));
  
  GPIOPinConfigure(GPIO_PB4_CAN0RX);
  GPIOPinConfigure(GPIO_PB5_CAN0TX);
  
  GPIOPinTypeCAN(GPIO_PORTB_BASE, GPIO_PIN_4 | GPIO_PIN_5);
  
  SysCtlPeripheralEnable(SYSCTL_PERIPH_CAN0);

  CANInit(CAN0_BASE);
  
  CANBitRateSet(CAN0_BASE, SysCtlClockGet(), 500000);
  
  CANIntRegister(CAN0_BASE, CANIntHandler_send); // if using dynamic vectors

  CANIntEnable(CAN0_BASE, CAN_INT_MASTER | CAN_INT_ERROR | CAN_INT_STATUS);

  IntEnable(INT_CAN0);
  
  CANEnable(CAN0_BASE);
}