/* Define to prevent recursive inclusion ------------------------------------ */
#ifndef __I2C_GY80_H
#define __I2C_GY80_H

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Defines for the GPIO pins used for the I2C communication */
#define I2C_GY80             I2C2
#define I2C_GY80_CLK         RCC_APB1Periph_I2C2
#define I2C_GY80_GPIO        GPIOB
#define I2C_GY80_GPIO_CLK    RCC_APB2Periph_GPIOB
#define I2C_GY80_SCL         GPIO_Pin_10
#define I2C_GY80_SDA         GPIO_Pin_11

void I2C_GY80_Init(void);
void I2C_ByteWrite(uint8_t SlaveAddr, uint8_t WriteAddr, uint8_t WriteByte);
uint8_t I2C_ByteRead(uint8_t SlaveAddr, uint8_t ReadAddr);

#endif 

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/


