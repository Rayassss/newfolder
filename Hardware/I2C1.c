//
// Created by 罗屺 on 2021/4/22.
//

#include "I2C1.h"

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
void MX_I2C1_Init(void) {
    hi2c1.Instance = I2C1;
    hi2c1.Init.ClockSpeed = 400000;
    hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
    hi2c1.Init.OwnAddress1 = 0;
    hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
    hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
    hi2c1.Init.OwnAddress2 = 0;
    hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
    hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
    if (HAL_I2C_Init(&hi2c1) != HAL_OK) {
        Error_Handler();
    }

}
void I2C_PIN_Init() {
    GPIO_InitTypeDef I2C1_IninStruct = {0};

    __HAL_RCC_GPIOB_CLK_ENABLE();

    I2C1_IninStruct.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    I2C1_IninStruct.Mode = GPIO_MODE_AF_OD;
    I2C1_IninStruct.Pull = GPIO_PULLUP;
    I2C1_IninStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOB, &I2C1_IninStruct);

    /* I2C1 clock enable */
    __HAL_RCC_I2C1_CLK_ENABLE();
}

