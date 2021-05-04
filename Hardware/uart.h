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
#include "string.h"
#include "stdarg.h"
#define EN_USART1_RX 1
#define RXBUFFERSIZE 1
#define USART_REC_LEN 200
typedef struct {//使用结构体可以指定特定的打印函数，实现类的功能
    UART_HandleTypeDef UART;
    void (*print)(const char *fmt, ...);
} usart_t;
extern UART_HandleTypeDef UART1_Handler;
extern unsigned char aRxBuffer[RXBUFFERSIZE];
extern unsigned short UART_RX_STA;
extern unsigned char USART_RX_BUF[USART_REC_LEN];
void USART1_Init(void);
void Context_in_while_for_uart1(void);
void print_usart1(const char *fmt, ...);
#endif //NEWFOLDER_HARDWARE_UART_H_
