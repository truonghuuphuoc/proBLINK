/**
  ******************************************************************************
  * @file    USART/Printf/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 


#include "main.h"

#include "stm32f10x.h"
#include "phnUsart.h"
#include "phnRf443.h"
#include "phnOsal.h"
#include "phnMessage.h"
#include "phnCompile.h"
#include "phnExInt.h"
#include "phnLed.h"


#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
  




/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void)
{
	uint32_t currTime = 0;
	uint32_t deltaTime = 0;
	
	phnUsart1_Init();
	phnOsal_Init();
	phnExInt_Init();
	
	phnLed_Init();
	
	phnNvic_InitGroup();
	
	
#if(PLATFORM_MASTER)
	phnMaster_Processing();
#elif(PLATFORM_SALVE)
	phnSlave_Processing();
#endif
	
	while(1)
	{
		if(gMachineStatus.mCurrCommand != PHN_COMMAND_NONE)
		{
			gMachineStatus.mPrevCommand = gMachineStatus.mCurrCommand;
			
			switch(gMachineStatus.mPrevCommand)
			{
				case PHN_COMMAND_UP: //increase ligth up
					if(gMachineStatus.mCurrStatus == PHN_STAT_LED_OFF)
					{
						gMachineStatus.mFrequence	= 1100;
						gMachineStatus.mCurrStatus  = PHN_STAT_LED_BLINK;
					}
					else if(gMachineStatus.mCurrStatus == PHN_STAT_LED_BLINK)
					{
												
						if(gMachineStatus.mFrequence > 200)
						{
							gMachineStatus.mFrequence -= 200;
						}
					}
					break;
				
				case PHN_COMMAND_DOWN: //decrease ligth down
					if(gMachineStatus.mCurrStatus == PHN_STAT_LED_ON)
					{
						gMachineStatus.mFrequence	= 100;
						gMachineStatus.mCurrStatus  = PHN_STAT_LED_BLINK;
					}
					else if(gMachineStatus.mCurrStatus == PHN_STAT_LED_BLINK)
					{
						if(gMachineStatus.mFrequence < 900)
						{
							gMachineStatus.mFrequence += 200;
						}
					}
					break;
				
				case PHN_COMMAND_ONOFF:
					if(gMachineStatus.mCurrStatus == PHN_STAT_LED_OFF)
					{
						gMachineStatus.mCurrStatus = PHN_STAT_LED_ON;
					}
					else
					{
						gMachineStatus.mCurrStatus = PHN_STAT_LED_OFF;
					}
					
					break;
				
				case PHN_COMMAND_BLINK:
					if(gMachineStatus.mCurrStatus == PHN_STAT_LED_BLINK)
					{
						gMachineStatus.mCurrStatus = PHN_STAT_LED_OFF;
					}
					else
					{
						gMachineStatus.mCurrStatus = PHN_STAT_LED_BLINK;
						gMachineStatus.mFrequence = 500;
					}
					break;
				
				default:
					break;
			}
			
			gMachineStatus.mCurrCommand = PHN_COMMAND_NONE;
		}
		
		switch(gMachineStatus.mCurrStatus)
		{
			case PHN_STAT_LED_ON:
				if(gMachineStatus.mCurrStatus != gMachineStatus.mPrevStatus)
				{
					phnLed_SetLeds(1);
				}
				break;
			
			case PHN_STAT_LED_OFF:
				if(gMachineStatus.mCurrStatus != gMachineStatus.mPrevStatus)
				{
					phnLed_SetLeds(0);
				}
				break;
			
			case PHN_STAT_LED_BLINK:
				if(gMachineStatus.mCurrStatus != gMachineStatus.mPrevStatus)
				{
					phnLed_ToggleLeds();
					currTime = phnOsal_GetCurrentTickCount();
				}
				
				deltaTime = phnOsal_GetElapseTime(currTime);
				
				if(deltaTime > gMachineStatus.mFrequence)
				{
					phnLed_ToggleLeds();
					currTime = phnOsal_GetCurrentTickCount();
				}
				
				break;
			
			default:
				break;
		}
		
		gMachineStatus.mPrevStatus = gMachineStatus.mCurrStatus;
	}		

}

#if(PLATFORM_MASTER)
void phnMaster_Processing()
{
	
}
#endif

#if(PLATFORM_SALVE)
void phnSlave_Processing()
{
	
}
#endif


void phnNvic_InitGroup()
{
	NVIC_InitTypeDef NVIC_InitStructure;

	// Configure the NVIC Preemption Priority Bits   
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	// Enable the USART1 Interrupt 
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);

	
	// Enable the USART2 Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	// Enable the EXTI3_IRQn Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	// Enable the EXTI4_IRQn Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	// Enable the EXTI9_5_IRQn Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	// Enable the EXTI15_10_IRQn Interrupt
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
}


PUTCHAR_PROTOTYPE
{
	
	/* Loop until the end of transmission */
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
	//while (USART_GetFlagStatus(USART2, USART_FLAG_TC) == RESET)
	{}
		
	/* Place your implementation of fputc here */
	/* e.g. write a character to the USART */
	USART_SendData(USART1, (uint8_t) ch);
	//USART_SendData(USART2, (uint8_t) ch);

	return ch;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
	/* User can add his own implementation to report the file name and line number,
	 ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

	/* Infinite loop */
	while (1)
	{
	}
}

#endif

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
