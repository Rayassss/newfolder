//
// Created by 罗屺 on 2021/2/23.
//

#include "Exti.h"
#include "Led.h"
#include "stm32f1xx_hal.h"
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if(GPIO_Pin == GPIO_PIN_15)
    {
        Ledreset_1;
        HAL_Delay(20);
        Ledset_1;
    }
    if(GPIO_Pin == GPIO_PIN_14)
    {
        Ledreset_2;
        HAL_Delay(20);
        Ledset_2;
    }
}
