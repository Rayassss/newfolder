

#include "string.h"
#include "stdarg.h"
void print(const char *fmt,...){
    char Buffer[128] = {0};
    va_list ap;
    memset(Buffer, '\0', sizeof(Buffer));
    va_start(ap, fmt);
    vsprintf((char *) Buffer, fmt, ap);
    HAL_UART_Transmit(&UART1_Handler,(unsigned char *)Buffer,strlen(Buffer),0xFFFFFFFFUL);//hal库的传参函数
    va_end(ap);
}