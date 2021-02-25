//
// Created by 罗屺 on 2021/2/25.
//

#ifndef NEWFOLDER_HARDWARE_IWG_H_
#define NEWFOLDER_HARDWARE_IWG_H_
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_iwdg.h"
#include "Led.h"
void MX_IWDG_Init(void);
void IWDG_Feed(void);

#endif //NEWFOLDER_HARDWARE_IWG_H_
