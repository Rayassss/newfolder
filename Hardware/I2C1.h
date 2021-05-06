//
// Created by 罗屺 on 2021/4/22.
//

#ifndef CPROJECT_HARDWARE_I2C1_H_
#define CPROJECT_HARDWARE_I2C1_H_
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_i2c.h"
#include "stm32f1xx_hal_gpio.h"
#include "main.h"
#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#ifndef I2C_Direction_Transmitter
#define  I2C_Direction_Transmitter      ((uint8_t)0x00)
#endif

#ifndef I2C_Direction_Receiver
#define  I2C_Direction_Receiver         ((uint8_t)0x01)
#endif
typedef enum {
    Bit_RESET = 0,
    Bit_SET = 1
} BitAction;
typedef struct BYTE_BIT {
    unsigned BIT0: 1;
    unsigned BIT1: 1;
    unsigned BIT2: 1;
    unsigned BIT3: 1;
    unsigned BIT4: 1;
    unsigned BIT5: 1;
    unsigned BIT6: 1;
    unsigned BIT7: 1;
} BYTEBIT;

typedef struct WORD_BIT {
    unsigned BIT0: 1;
    unsigned BIT1: 1;
    unsigned BIT2: 1;
    unsigned BIT3: 1;
    unsigned BIT4: 1;
    unsigned BIT5: 1;
    unsigned BIT6: 1;
    unsigned BIT7: 1;

    unsigned BIT8: 1;
    unsigned BIT9: 1;
    unsigned BIT10: 1;
    unsigned BIT11: 1;
    unsigned BIT12: 1;
    unsigned BIT13: 1;
    unsigned BIT14: 1;
    unsigned BIT15: 1;
} WORDBIT;

typedef union {
    uint16_t Word;
    WORDBIT Bit;
} Bit16_OperTypeDef;

typedef struct {
    uint8_t Count;
    GPIO_TypeDef *GPIOx;
    GPIO_InitTypeDef GPIO_InitType;
} GPIO_TypeStruct;

enum {
    I2C_SDA_IN,
    I2C_SDA_OUT
};

enum {
    I2C_ACK,
    I2C_NACK
};
#define BIT_8b(n)       ((unsigned char)(1 << n))
#define BIT_16b(n)      ((unsigned int) (1 << n))
#define I2C_SCL_PIN  GPIO_PIN_6
#define I2C_SDA_PIN  GPIO_PIN_7

#define I2C_SCL_Set()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET)
#define I2C_SCL_Clr()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET)

#define I2C_SDA_Set()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET)
#define I2C_SDA_Clr()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET)

#define I2C_SDA_Get()  HAL_GPIO_ReadPin(GPIOB, I2C_SDA_PIN)
void I2C_SDAMode(uint8_t Mode);
void I2C_Start(void);
void I2C_Stop(void);
bool I2C_WaiteForAck(void);
void I2C_Ack(void);
void I2C_NAck(void);
bool I2C_WriteOneBit(uint8_t DevAddr, uint8_t RegAddr, uint8_t BitNum, uint8_t Data);
bool I2C_WriteBits(uint8_t DevAddr, uint8_t RegAddr, uint8_t BitStart, uint8_t Length, uint8_t Data);
void I2C_WriteByte(uint8_t Data);
uint8_t I2C_ReadByte(uint8_t Ack);
void I2C_WriteOneByte(uint8_t DevAddr, uint8_t RegAddr, uint8_t Data);
uint8_t I2C_ReadOneByte(uint8_t DevAddr, uint8_t RegAddr);
bool I2C_WriteBuff(uint8_t DevAddr, uint8_t RegAddr, uint8_t Num, uint8_t *pBuff);
bool I2C_ReadBuff(uint8_t DevAddr, uint8_t RegAddr, uint8_t Num, uint8_t *pBuff);

void Delay_us(uint16_t Time);
void Delay_ms(uint16_t Time);

void i2c_GPIO_Config(void);

#endif //CPROJECT_HARDWARE_I2C1_H_
