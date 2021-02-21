//
// Created by 罗屺 on 2021/2/10.
//

#ifndef STM32F1_HARDWARE_KEY_H_
#define STM32F1_HARDWARE_KEY_H_

#define Key1 HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_14)
#define Key2 HAL_GPIO_ReadPin(GPIOD, GPIO_PIN_15)
#define Key1_rst 1
#define Key2_rst 2
void Key_init(void);
unsigned char Key_Scan(void);
#endif //STM32F1_HARDWARE_KEY_H_
