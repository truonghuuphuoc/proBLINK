#ifndef __PHN_LED_H
#define __PHN_LED_H

#ifdef __cplusplus
 extern "C" {
#endif


#include <stdint.h>	 	 

	 
/**
  * @brief  
  * @param  None
  * @retval None
  */
void phnLed_Init(void);


/**
  * @brief  Set led
  * @param  
  * @retval None
  */
void phnLed_SetLeds(uint8_t status);



#ifdef __cplusplus
}
#endif

#endif /*__PHN_LED_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
