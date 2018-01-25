#ifndef __PHN_MESSAGE_H
#define __PHN_MESSAGE_H

#ifdef __cplusplus
 extern "C" {
#endif

#include <stdint.h>
	 
#include "phnCompile.h"	 
	 
#define MESG_BUFFER_SIZE	50	 

/*Start message*/
#define MESG_STX			0x02

/*End message*/	 
#define MESG_ETX			0x03

typedef enum
{
	PHN_STAT_LED_ON		= 0x00,
	PHN_STAT_LED_OFF	= 0x01,
	PHN_STAT_LED_BLINK	= 0x02,
}phnMachineState_t;

typedef enum
{
	PHN_COMMAND_NONE	= 0x00,
	PHN_COMMAND_ONOFF	= 0x01,
	PHN_COMMAND_BLINK	= 0x02,
	PHN_COMMAND_UP		= 0x03,
	PHN_COMMAND_DOWN	= 0x04,
}phnCommand_t;

typedef struct
{
	uint8_t		mPrevCommand;
	uint8_t		mCurrCommand;
	uint8_t		mPrevStatus;
	uint8_t		mCurrStatus;
	uint32_t	mFrequence;
}phnMessageStatus_t;


extern phnMessageStatus_t gMachineStatus;
	 
/**
  * @brief  
  * @param  None
  * @retval None
  */
void phnMessage_GetMessageFormat(uint8_t *data, uint16_t inLength, uint8_t *message, uint16_t *outLength);


/**
  * @brief  
  * @param  None
  * @retval None
  */	 
void phnMessage_LogDebug(char* message, uint8_t *data, uint16_t length);

#ifdef __cplusplus
}
#endif

#endif /*__PHN_MESSAGE_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
