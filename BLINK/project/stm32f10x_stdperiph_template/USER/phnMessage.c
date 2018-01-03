#include "phnMessage.h"
#include "phnCrc.h"
#include "phnOsal.h"


void phnMessage_GetMessageFormat(uint8_t *data, uint16_t inLength, uint8_t *message, uint16_t *outLength)
{
	uint8_t value, crc;
	uint16_t index;
	uint16_t position = 0;
	
	//Start message
	message[position] = MESG_STX;
	position ++;
	
	//Data
	for (index = 0; index < inLength; index++)
	{
		//Data first nibble
		value = data[index] >> 4;
		message[position] = ((value << 4) | (value ^ 0x0F));
		position ++;

		//Data second nibble
		value = data[index] & 0x0F;
		message[position] =  ((value << 4) | (value ^ 0x0F));
		position ++;
	}
	
	//End message
	message[position] = MESG_ETX;
	position ++;
	
	//Crc
	crc = phnCrc_Calculate(data, inLength);
	
	//Crc first nibble
	value = crc >> 4;
	message[position] = ((value << 4) | (value ^ 0x0F));
	position ++;

	//Crc second nibble
	value = crc & 0x0F;
	message[position] =  ((value << 4) | (value ^ 0x0F));
	position ++;
	
	*outLength = position;
}





void phnMessage_LogDebug(char* message, uint8_t *data, uint16_t length)
{
	uint16_t index;
	
	printf("%s: ", message);
	for(index = 0; index < length; index ++)
	{
		printf("%02X ", data[index]); 
	}
	printf("\r\n");
}

