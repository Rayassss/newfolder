//
// Created by 罗屺 on 2021/2/25.
//

#include "iwg.h"

/**
  * @brief IWDG Initialization Function
  * @param None
  * @retval None
  */  /*
   * timeout = (4*2^pres)*reload)/32ms = 4*16*500/32 = 1s = (0.2reload)ms
   */
IWDG_HandleTypeDef IWDG_Handler;
void MX_IWDG_Init(void)
{

    IWDG_Handler.Instance = IWDG;
    IWDG_Handler.Init.Prescaler = IWDG_PRESCALER_256;
    IWDG_Handler.Init.Reload = 50000;
    HAL_IWDG_Init(&IWDG_Handler);
}
void IWDG_Feed(void)
{

    HAL_IWDG_Refresh(&IWDG_Handler);
}