//
// Created by 罗屺 on 2021/3/5.
//

#ifndef NEWFOLDER_HARDWARE_ADC1_H_
#define NEWFOLDER_HARDWARE_ADC1_H_
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_adc.h"
#include "stm32f1xx_hal_gpio.h"

void MX_ADC1_Init(void);
int ADC1_GET();
#endif //NEWFOLDER_HARDWARE_ADC1_H_
