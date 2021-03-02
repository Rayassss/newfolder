//
// Created by 罗屺 on 2021/2/27.
//

#include "Timer2.h"
TIM_HandleTypeDef htim2;
void MX_TIM2_Init(void)
{
    __HAL_RCC_TIM2_CLK_ENABLE();

    TIM_ClockConfigTypeDef sClockSourceConfig = {0};
    TIM_SlaveConfigTypeDef sSlaveConfig = {0};
    TIM_MasterConfigTypeDef sMasterConfig = {0};

    htim2.Instance = TIM2;
    htim2.Init.Prescaler = 7199;
    htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim2.Init.Period = 4999;
    htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    sSlaveConfig.SlaveMode = TIM_SLAVEMODE_TRIGGER;
    sSlaveConfig.InputTrigger = TIM_TS_ITR0;
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIM_Base_Init(&htim2);
    HAL_TIM_Base_Start_IT(&htim2);
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&htim2)) {
        HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_3);
        HAL_GPIO_TogglePin(GPIOD,GPIO_PIN_4);
    }
}

