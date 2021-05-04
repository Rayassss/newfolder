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

#define I2C_WR    0        /* Ð´¿ØÖÆbit */
#define I2C_RD    1        /* ¶Á¿ØÖÆbit */

void i2c_Start(void);
void i2c_Stop(void);
void i2c_SendByte(uint8_t _ucByte);
uint8_t i2c_ReadByte(uint8_t ack);
uint8_t i2c_WaitAck(void);
void i2c_Ack(void);
void i2c_NAck(void);
uint8_t i2c_CheckDevice(uint8_t _Address);
void i2c_GPIO_Config(void);

#endif //CPROJECT_HARDWARE_I2C1_H_
