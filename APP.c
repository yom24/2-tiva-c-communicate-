#include "APP.h"
#include "CAN.h"

int state;
bool reset;

/* Global variable to indicate the the timer has a new tick */
//static uint8 g_New_Time_Tick_Flag = 0;

//void interrupt_init()
//{  
  /* configure PORTF4, 0 for falling edge trigger interrupt */
 //   GPIO_PORTF_IS_R &= ~(1<<4)|~(1<<0);     /* make bit 4, 0 edge sensitive */
  //  GPIO_PORTF_IBE_R &=~(1<<4)|~(1<<0);     /* trigger is controlled by IEV */
  //  GPIO_PORTF_IEV_R &= ~(1<<4)|~(1<<0);      /* falling edge trigger */
  //  GPIO_PORTF_ICR_R |= (1<<4)|(1<<0);        /* clear any prior interrupt */
  //  GPIO_PORTF_IM_R  |= (1<<4)|(1<<0);        /* unmask interrupt */
    
    /* enable interrupt in NVIC and set priority to 3 */
  //  NVIC_PRI7_R = 3 << 5;     /* set interrupt priority to 3 */
  //  NVIC_EN0_R |= (1<<30);  /* enable IRQ30 (D30 of ISER[0]) */
//}

void LED_TOGGLE()
{
  /* Increment the Os time by OS_BASE_TIME */
  g_Time_Tick_Count   += 10;
  
  /* Increment the reser time by OS_BASE_TIME */
  g_reset_time += 10;
  
  /* Set the flag to 1 to indicate that there is a new timer tick */
    //g_New_Time_Tick_Flag = 1;
  
  if ((g_reset_time % 5000) == 0 && g_reset_time != 0)
  {
    reset = TRUE;
    state = 0;
    can_send(state);
  
    if(reset == TRUE)
    {
      reset = FALSE;
      Dio_WriteChannel(DioConf_RED_CHANNEL_ID_INDEX, STD_LOW);
      Dio_WriteChannel(DioConf_GREEN_CHANNEL_ID_INDEX, STD_LOW);
    }
  }
  /*
  switch (state)
  {
  
  default:
    Dio_WriteChannel(DioConf_RED_CHANNEL_ID_INDEX, STD_LOW);
    Dio_WriteChannel(DioConf_GREEN_CHANNEL_ID_INDEX, STD_LOW);
    break;
    
  case 1:
    Dio_WriteChannel(DioConf_GREEN_CHANNEL_ID_INDEX, STD_LOW);
    Dio_WriteChannel(DioConf_RED_CHANNEL_ID_INDEX, STD_HIGH);
    break;
    
  case 2:
    Dio_WriteChannel(DioConf_RED_CHANNEL_ID_INDEX, STD_LOW);
    Dio_WriteChannel(DioConf_GREEN_CHANNEL_ID_INDEX, STD_HIGH);
    break;
    
  }
  */
/*
  if (state == 1)
  {
    g_reset_time = 0;
    Dio_WriteChannel(DioConf_GREEN_CHANNEL_ID_INDEX, STD_LOW);
    Dio_WriteChannel(DioConf_RED_CHANNEL_ID_INDEX, STD_HIGH);
    //state = 0;
  }
  else if (state == 2)
  {
    g_reset_time = 0;
    Dio_WriteChannel(DioConf_RED_CHANNEL_ID_INDEX, STD_LOW);
    Dio_WriteChannel(DioConf_GREEN_CHANNEL_ID_INDEX, STD_HIGH);
  }
*/
}

void GPIO_fake()
{
  /*uint32 volatile c = GPIO_PORTF_MIS_REG;
  switch (c)
  {
  case GPIO_PORTF_MIS_REG & (1 << PORT_PIN4):
    state++;
    break;
  case GPIO_PORTF_MIS_REG & (1 << PORT_PIN0):
    state--;
    break;
    
  default:
    g_reset_time += 500;
    break;
    
  }*/
  
  if (GPIO_PORTF_MIS_REG & (1 << PORT_PIN4))
  {
    state++;
    can_send(state);
    reset = FALSE;
    
    g_reset_time = 0;
    if (state == 4)
    {
    state = 1;
    }
  }
  else if (GPIO_PORTF_MIS_REG & (1 << PORT_PIN0))
  {
    state--;
    can_send(state);
    reset = FALSE;
    g_reset_time = 0;
    if (state == 0 || state < 0)
    {
    state = 3;
    }
  }
}