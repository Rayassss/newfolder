//
// Created by 罗屺 on 2021/2/10.
//
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "Key.h"

void Key_init(void) {
    __HAL_RCC_GPIOD_CLK_ENABLE();
    GPIO_InitTypeDef GPIO_Initure;
    GPIO_Initure.Pin = GPIO_PIN_14 | GPIO_PIN_15;
    GPIO_Initure.Mode = GPIO_MODE_INPUT;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOD, &GPIO_Initure);

}
unsigned char Key_Scan(void) {
    if ((Key1 == 0) || (Key2 == 0)) {
        if (Key1 == 0) {
            return Key1_rst;
        } else if (Key2 == 0) {
            return Key2_rst;
        } else return 0;
    }
}
