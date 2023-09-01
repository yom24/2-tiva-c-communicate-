#include "DIO.h"
#include "PORT.h"
#include "tm4c123gh6pm.h"
#include "Interrupt.h"
#include "Timer.h"
#include <stdbool.h>

/* Global variable store the Os Time */
static uint16 g_Time_Tick_Count;
extern int state;
extern bool reset;
static uint16 g_reset_time;

/*******************************************************************************
*                                APP prototypes                                *
*******************************************************************************/

void LED_TOGGLE();

void GPIO_fake();