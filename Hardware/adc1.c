//
// Created by 罗屺 on 2021/3/5.
//

#include "adc1.h"
ADC_HandleTypeDef hadc1;
void MX_ADC1_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;

    __HAL_RCC_ADC1_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    GPIO_Initure.Pin = GPIO_PIN_0;
    GPIO_Initure.Mode = GPIO_MODE_ANALOG;
    GPIO_Initure.Pull = GPIO_NOPULL;
    HAL_GPIO_Init(GPIOC,&GPIO_Initure);

    hadc1.Instance = ADC1;
    hadc1.Init.ScanConvMode = ADC_SCAN_DISABLE;
    hadc1.Init.ContinuousConvMode = DISABLE;
    hadc1.Init.DiscontinuousConvMode = DISABLE;
    hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
    hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
    hadc1.Init.NbrOfConversion = 1;
    HAL_ADC_Init(&hadc1);
    HAL_ADCEx_Calibration_Start(&hadc1);

}
int ADC1_GET()
{
    ADC_ChannelConfTypeDef sConfig = {0};
    sConfig.Channel = ADC_CHANNEL_10;
    sConfig.Rank = ADC_REGULAR_RANK_1;
    sConfig.SamplingTime = ADC_SAMPLETIME_71CYCLES_5;
    HAL_ADC_ConfigChannel(&hadc1,&sConfig);
    HAL_ADC_Start(&hadc1);
    HAL_ADC_PollForConversion(&hadc1,15);
    return (int)HAL_ADC_GetValue(&hadc1);
}
unsigned int Get_Adc_Average(unsigned int ch,unsigned short times)
{
    unsigned int temp_val=0;
    unsigned short t;
    for(t=0;t<times;t++)
    {
        temp_val+=ADC1_GET();
        HAL_Delay(5);
    }
    return temp_val/times;
}