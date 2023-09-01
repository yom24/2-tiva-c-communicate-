#include "APP.h"
#include "schedular.h"
#include "CAN.h"

int main()
{
  Disable_Interrupts();
  Port_Init(&Port_Configuration);
  Dio_Init(&Dio_Configuration);
  INTERRUPT_Init(&Interrupt_Configuration);
  Systick_oneshotConfig(10);
  SysTick_SetCallBack(LED_TOGGLE);
  PORTF_SetCallBack(GPIO_fake);
  Enable_Interrupts();
  
  CAN_init_send();
  
  //init_tasks();
  /* Start SysTickTimer to generate interrupt every 10ms */
  SysTick_Start();
  
  //scheduler();
  while(1)
  {
  }
  
  /* stuck in while no return */
  //return 0;
}


