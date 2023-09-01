/*
 * DIO.h
 *
 * Created: 12/17/2022
 */

#ifndef DIO_H_
#define DIO_H_
   
   //file includes
#include "STD_Types.h"
#include "PORT_HW.h"
#include "DIO_Cfg.h"
#include "BitMath.h"
//#include "tm4c123gh6pm.h"

/*******************************************************************************
 *                              Module Data Types                              *
 ******************************************************************************/

/* Type definition for Dio_ChannelType used by the DIO APIs */
typedef uint8 Dio_ChannelType;

/* Type definition for Dio_PortType used by the DIO APIs */
typedef uint8 Dio_PortType;

/* Type definition for Dio_LevelType used by the DIO APIs */
//[SWS_Dio_00185]
typedef uint8 Dio_LevelType;

/* Type definition for Dio_PortLevelType used by the DIO APIs */
//[SWS_Dio_00186]
//[SWS_Dio_00024]
typedef uint32 volatile Dio_PortLevelType;


//[SWS_Dio_00184]
//[SWS_Dio_00021]
//
/* Structure for Dio_ChannelGroup */
typedef struct
{
  /* Mask which defines the positions of the channel group */
  uint8 mask;
  /* Position of the group from LSB */
  uint8 offset;
  /* This shall be the port ID which the Channel group is defined. */
  Dio_PortType PortIndex;
} Dio_ChannelGroupType;

typedef struct
{
	/* Member contains the ID of the Port that this channel belongs to */
	Dio_PortType Port_Num;
	/* Member contains the ID of the Channel*/
	Dio_ChannelType Ch_Num;
}Dio_ConfigChannel;

/* Data Structure required for initializing the Dio Driver */
typedef struct Dio_ConfigType
{
	Dio_ConfigChannel Channels[DIO_CONFIGURED_CHANNELS];
        Dio_PortType ports[DIO_CONFIGURED_PORTS];
        Dio_ChannelGroupType groups[DIO_CONFIGURED_GROUPS];
} Dio_ConfigType;

//#define NUM_OF_PORTS           6
//#define NUM_OF_PINS_PER_PORT   8

//#define PORTA_ID               0
//#define PORTB_ID               1
//#define PORTC_ID               2
//#define PORTD_ID               3
//#define PORTE_ID               4
//#define PORTF_ID               5


//#define PIN0_ID                0
//#define PIN1_ID                1
//#define PIN2_ID                2
//#define PIN3_ID                3
//#define PIN4_ID                4
//#define PIN5_ID                5
//#define PIN6_ID                6
//#define PIN7_ID                7

/* Function for DIO read Channel API */
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);

/* Function for DIO write Channel API */
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);

/* Function for DIO read Port API */
Dio_LevelType Dio_ReadChannel(Dio_ChannelType ChannelId);

/* Function for DIO write Port API */
void Dio_WriteChannel(Dio_ChannelType ChannelId, Dio_LevelType Level);

/* Function for DIO Initialization API */
void Dio_Init(Dio_ConfigType * ConfigPtr);

#if (DIO_FLIP_CHANNEL_API == STD_ON)
/* Function for DIO flip channel API */
Dio_LevelType Dio_FlipChannel(Dio_ChannelType ChannelId);
#endif

Dio_PortLevelType Dio_ReadChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr);

void Dio_WriteChannelGroup(const Dio_ChannelGroupType* ChannelGroupIdPtr, Dio_PortLevelType Level);

extern Dio_ConfigType Dio_Configuration;
extern Dio_ChannelGroupType Group_Configuration;

#endif