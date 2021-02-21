//
// Created by 罗屺 on 2021/2/19.
//

#ifndef NEWFOLDER_HARDWARE_UART_H_
#define NEWFOLDER_HARDWARE_UART_H_
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_uart.h"
#include "stm32f1xx_it.h"
#include "stdio.h"
#include "Led.h"
#define EN_USART1_RX 1
#define RXBUFFERSIZE 1
#define USART_REC_LEN 200

extern UART_HandleTypeDef UART1_Handler;
extern unsigned char aRxBuffer[RXBUFFERSIZE];
extern unsigned short UART_RX_STA;
extern unsigned char USART_RX_BUF[USART_REC_LEN];
void UART1_Init(unsigned int boudrate);
void MX_USART1_UART_Init(void);
void Context_in_while_for_uart1(void);
#endif //NEWFOLDER_HARDWARE_UART_H_
