//
// Created by 罗屺 on 2021/2/25.
//

#ifndef NEWFOLDER_HARDWARE_WWDG_H_
#define NEWFOLDER_HARDWARE_WWDG_H_
#include "stm32f1xx_hal.h"
#include "Led.h"
void MX_WWDG_Init(void);
void WWDG_IRQHandler(void);

#endif //NEWFOLDER_HARDWARE_WWDG_H_
