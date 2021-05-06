//
// Created by 罗屺 on 2021/2/19.
//

#include "uart.h"
UART_HandleTypeDef UART1_Handler;
DMA_HandleTypeDef hdma_usart1_tx;
DMA_HandleTypeDef hdma_usart1_rx;
unsigned char aRxBuffer[RXBUFFERSIZE];
unsigned short UART_RX_STA = 0;
unsigned char USART_RX_BUF[USART_REC_LEN];
unsigned char len = 0;
/*在gcc环境下的串口打印函数*/
void print_usart1(const char *fmt, ...) {
    char Buffer[128] = {0};
    va_list ap;
    memset(Buffer, '\0', sizeof(Buffer));
    va_start(ap, fmt);
    vsprintf((char *) Buffer, fmt, ap);
    HAL_UART_Transmit(&UART1_Handler, (unsigned char *) Buffer, strlen(Buffer), 0xFFFFFFFFUL);
    va_end(ap);
}
void USART1_Init(void) {
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();
    __HAL_RCC_AFIO_CLK_ENABLE();

    GPIO_Initure.Pin = GPIO_PIN_9;
    GPIO_Initure.Mode = GPIO_MODE_AF_PP;
    GPIO_Initure.Pull = GPIO_PULLUP;
    GPIO_Initure.Speed = GPIO_SPEED_HIGH;
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);

    GPIO_Initure.Pin = GPIO_PIN_10;
    GPIO_Initure.Mode = GPIO_MODE_AF_INPUT;
    HAL_GPIO_Init(GPIOA, &GPIO_Initure);

    HAL_NVIC_EnableIRQ(USART1_IRQn);
    HAL_NVIC_SetPriority(USART1_IRQn, 3, 3);
    UART1_Handler.Instance = USART1;
    UART1_Handler.Init.BaudRate = 460800;
    UART1_Handler.Init.WordLength = UART_WORDLENGTH_8B;
    UART1_Handler.Init.Mode = UART_MODE_TX_RX;
    UART1_Handler.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UART1_Handler.Init.Parity = UART_PARITY_NONE;
    UART1_Handler.Init.StopBits = UART_STOPBITS_1;
    UART1_Handler.Init.OverSampling = UART_OVERSAMPLING_16;
    HAL_UART_Init(&UART1_Handler);
    HAL_UART_Receive_IT(&UART1_Handler, (unsigned char *) aRxBuffer, RXBUFFERSIZE);
}
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
    if (huart->Instance == USART1) {
        if ((UART_RX_STA & 0x8000) == 0)//接收未完成
        {
            if (UART_RX_STA & 0x4000)//接收到了0x0d
            {
                if (aRxBuffer[0] != 0x0a)UART_RX_STA = 0;//接收错误,重新开始
                else UART_RX_STA |= 0x8000;    //接收完成了
            } else //还没收到0X0D
            {
                if (aRxBuffer[0] == 0x0d)UART_RX_STA |= 0x4000;
                else {
                    USART_RX_BUF[UART_RX_STA & 0X3FFF] = aRxBuffer[0];
                    UART_RX_STA++;
                    if (UART_RX_STA > (USART_REC_LEN - 1))UART_RX_STA = 0;//接收数据错误,重新开始接收
                }
            }
        }

    }
}
void Context_in_while_for_uart1(void) {

    unsigned short times = 0;
    Ledreset_2;
    if (UART_RX_STA & 0x8000) {
        len = UART_RX_STA & 0x3fff;
        HAL_UART_Transmit(&UART1_Handler, (unsigned char *) USART_RX_BUF, len, 1000);
        while (__HAL_UART_GET_FLAG(&UART1_Handler, UART_FLAG_TC) != SET);
        UART_RX_STA = 0;
    } else {
        times++;
        if (times % 200 == 0)printf("请输入数据,以回车键结束\r\n");
        HAL_Delay(10);
    }
}
int fputc(int ch, FILE *f) {
    HAL_UART_Transmit_IT(&UART1_Handler, (unsigned char *) USART_RX_BUF, len);
    while (__HAL_UART_GET_FLAG(&UART1_Handler, UART_FLAG_TC) != SET);
    return ch;
}
