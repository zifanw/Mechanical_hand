/* Includes ------------------------------------------------------------------*/
#include "i2c_GY80.h"

/** @addtogroup STM32F10x_StdPeriph_Examples
  * @{
  */

/** @addtogroup I2C_GY80PROM
  * @{
  */ 

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define I2C_Speed              400000
#define I2C_SLAVE_ADDRESS7     0xD2

/* Private function prototypes -----------------------------------------------*/
void GPIO_Configuration(void);
void I2C_Configuration(void);
void LongDelay(u32 nCount);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Configure the used I/O ports pin
  * @param  None
  * @retval None
  */
void GPIO_Configuration(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 
  
  /* Configure I2C_GY80 pins: SCL and SDA */
  GPIO_InitStructure.GPIO_Pin =  I2C_GY80_SCL | I2C_GY80_SDA; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_OD;
  GPIO_Init(I2C_GY80_GPIO, &GPIO_InitStructure);
}

/**
  * @brief  I2C Configuration
  * @param  None
  * @retval None
  */
void I2C_Configuration(void)
{
  I2C_InitTypeDef  I2C_InitStructure; 
  
  /* I2C configuration */
  I2C_InitStructure.I2C_Mode = I2C_Mode_I2C;
  I2C_InitStructure.I2C_DutyCycle = I2C_DutyCycle_2;
  I2C_InitStructure.I2C_OwnAddress1 = I2C_SLAVE_ADDRESS7;
  I2C_InitStructure.I2C_Ack = I2C_Ack_Enable;
  I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
  I2C_InitStructure.I2C_ClockSpeed = I2C_Speed;
  
  /* I2C Peripheral Enable */
  I2C_Cmd(I2C_GY80, ENABLE);
  /* Apply I2C configuration after enabling it */
  I2C_Init(I2C_GY80, &I2C_InitStructure);
}


void I2C_GY80_Init()
{
  /* I2C Periph clock enable */
  RCC_APB1PeriphClockCmd(I2C_GY80_CLK, ENABLE);   
  
  /* GPIO Periph clock enable */
  RCC_APB2PeriphClockCmd(I2C_GY80_GPIO_CLK, ENABLE);    
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);    
  
  /* GPIO configuration */
  GPIO_Configuration();

  /* I2C configuration */
  I2C_Configuration();

}


void I2C_ByteWrite(uint8_t SlaveAddr, uint8_t WriteAddr, uint8_t WriteByte)
{

  /* Send STRAT condition */
  I2C_GenerateSTART(I2C_GY80, ENABLE);

  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C_GY80, I2C_EVENT_MASTER_MODE_SELECT));  

  /* Send EEPROM address for write */
  I2C_Send7bitAddress(I2C_GY80, SlaveAddr, I2C_Direction_Transmitter);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C_GY80, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  I2C_SendData(I2C_GY80, WriteAddr);
  
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C_GY80, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

  /* Send the byte to be written */
  I2C_SendData(I2C_GY80, WriteByte); 
   
  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C_GY80, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  /* Send STOP condition */
  I2C_GenerateSTOP(I2C_GY80, ENABLE);

  /* Delay */
  LongDelay(0x50);
}

uint8_t I2C_ByteRead(uint8_t SlaveAddr, uint8_t ReadAddr)
{ 
   uint8_t DataNotReady = 1;
   uint8_t temp;
   
  /* While the bus is busy */
  while(I2C_GetFlagStatus(I2C_GY80, I2C_FLAG_BUSY));
  
  /* Send START condition */
  I2C_GenerateSTART(I2C_GY80, ENABLE);
  
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C_GY80, I2C_EVENT_MASTER_MODE_SELECT));
   
  /* Send EEPROM address for write */
  I2C_Send7bitAddress(I2C_GY80, SlaveAddr, I2C_Direction_Transmitter);

  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C_GY80, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

  /* Send the EEPROM's internal address to read from: Only one byte address */
  I2C_SendData(I2C_GY80, ReadAddr);  

  /* Test on EV8 and clear it */
  while(!I2C_CheckEvent(I2C_GY80, I2C_EVENT_MASTER_BYTE_TRANSMITTED));
  
  /* Send STRAT condition a second time */  
  I2C_GenerateSTART(I2C_GY80, ENABLE);
  
  /* Test on EV5 and clear it */
  while(!I2C_CheckEvent(I2C_GY80, I2C_EVENT_MASTER_MODE_SELECT));
  
  /* Send EEPROM address for read */
  I2C_Send7bitAddress(I2C_GY80, SlaveAddr, I2C_Direction_Receiver);
  
  /* Test on EV6 and clear it */
  while(!I2C_CheckEvent(I2C_GY80, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED));
  
  /* While there is data to be read */
  while(DataNotReady)  
  {
    /* Disable Acknowledgement */
    I2C_AcknowledgeConfig(I2C_GY80, DISABLE);
      
    /* Send STOP Condition */
    I2C_GenerateSTOP(I2C_GY80, ENABLE);
    
    if(I2C_CheckEvent(I2C_GY80, I2C_EVENT_MASTER_BYTE_RECEIVED))  
    {      
      /* Read a byte from the EEPROM */
      temp=I2C_ReceiveData(I2C_GY80);

      /* Decrement the read bytes counter */
      DataNotReady=0;        
    }   
  }
  
  /* Enable Acknowledgement to be ready for another reception */
  I2C_AcknowledgeConfig(I2C_GY80, ENABLE);

  /* Delay */
  LongDelay(0x4000);

  return temp;
}


void LongDelay(u32 nCount)
{
  for(; nCount != 0; nCount--);
}

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
