//
// Created by 罗屺 on 2021/2/10.
//
//PB5 RED 0
// PB0 GREEN 0
// PB1 BLUE 0
#include "Led.h"
void Led_init(void) {
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_Initure.Pin = GPIO_PIN_0;
    GPIO_Initure.Mode = GPIO_MODE_AF_INPUT;
    GPIO_Initure.Pull = GPIO_PULLDOWN;
    GPIO_Initure.Speed = GPIO_SPEED_FREQ_MEDIUM;
    HAL_GPIO_Init(GPIOB, &GPIO_Initure);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

}
