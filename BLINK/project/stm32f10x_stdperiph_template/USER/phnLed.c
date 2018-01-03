#include "phnLed.h"


#include <stdio.h>
#include <stm32f10x.h>


void phnLed_Init()
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable the Clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);
	
	/**
	 *	Pin B.11 
	 */
	
	/* Configure pin as output pull-up */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/**
	 *	Pin B.12 
	 */
	
	/* Configure pin as output pull-up */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/**
	 *	Pin B.13 
	 */
	
	/* Configure pin as output pull-up */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/**
	 *	Pin B.14 
	 */
	
	/* Configure pin as output pull-up */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
}


void phnLed_SetLeds(uint8_t status)
{
	if(status)
	{
		GPIO_SetBits(GPIOB, GPIO_Pin_14);
	}
	else
	{
		GPIO_ResetBits(GPIOB, GPIO_Pin_14);
	}
}


