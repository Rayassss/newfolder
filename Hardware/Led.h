//
// Created by 罗屺 on 2021/2/10.
//
#ifndef _STM32F1_HARDWARE_LED_H_
#define _STM32F1_HARDWARE_LED_H_
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_rcc.h"
#define Ledreset_1 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET)
#define Ledset_1 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET)
#define Ledreset_2 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET)
#define Ledset_2 HAL_GPIO_WritePin(GPIOD, GPIO_PIN_4, GPIO_PIN_SET)
void Led_init(void);

#endif //STM32F1_HARDWARE_LED_H_

