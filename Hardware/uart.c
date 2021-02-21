//
// Created by 罗屺 on 2021/2/19.
//

#include "uart.h"
UART_HandleTypeDef UART1_Handler;
unsigned char aRxBuffer[RXBUFFERSIZE];
unsigned short UART_RX_STA = 0;
unsigned char USART_RX_BUF[USART_REC_LEN];
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if(huart->Instance==USART1)
  {
      if((UART_RX_STA&0x8000)==0)//接收未完成
      {
          if(UART_RX_STA&0x4000)//接收到了0x0d
          {
              if(aRxBuffer[0]!=0x0a)UART_RX_STA=0;//接收错误,重新开始
              else UART_RX_STA|=0x8000;	//接收完成了
          }
          else //还没收到0X0D
          {
              if(aRxBuffer[0]==0x0d)UART_RX_STA|=0x4000;
              else
              {
                  USART_RX_BUF[UART_RX_STA&0X3FFF]=aRxBuffer[0] ;
                  UART_RX_STA++;
                  if(UART_RX_STA>(USART_REC_LEN-1))UART_RX_STA=0;//接收数据错误,重新开始接收
              }
          }
      }


  }
}
