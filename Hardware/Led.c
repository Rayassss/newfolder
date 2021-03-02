//
// Created by 罗屺 on 2021/2/10.
//
#include "Led.h"
void Led_init(void) {
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOD_CLK_ENABLE();

    GPIO_Initure.Pin = GPIO_PIN_3 | GPIO_PIN_4;
    GPIO_Initure.Mode = GPIO_MODE_INPUT;
    GPIO_Initure.Pull = GPIO_PULLDOWN;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOD, &GPIO_Initure);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3 | GPIO_PIN_4, GPIO_PIN_SET);

}
