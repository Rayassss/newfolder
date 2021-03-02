//
// Created by 罗屺 on 2021/2/25.
//

#include "wwdg.h"
WWDG_HandleTypeDef WWDG_Handler;
void MX_WWDG_Init(void)
{
    __HAL_RCC_WWDG_CLK_ENABLE();
    HAL_NVIC_SetPriority(WWDG_IRQn,2,3);
    HAL_NVIC_EnableIRQ(WWDG_IRQn);

    WWDG_Handler.Instance = WWDG;
    WWDG_Handler.Init.Prescaler = WWDG_PRESCALER_8;
    WWDG_Handler.Init.Window = 0x5f;
    WWDG_Handler.Init.Counter = 0x7f;
    WWDG_Handler.Init.EWIMode = WWDG_EWI_DISABLE;
    HAL_WWDG_Init(&WWDG_Handler);
}
void HAL_WWDG_EarlyWakeupCallback(WWDG_HandleTypeDef* hwwdg)
{
    static int flag = 0;
    HAL_WWDG_Refresh(&WWDG_Handler);//更新窗口看门狗值
    flag++;
    if((flag/2) == 0)Ledreset_1;
    if((flag/2) != 0)Ledset_1;

}