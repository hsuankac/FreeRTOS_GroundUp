#ifndef INC_UART_H_
#define INC_UART_H_

void USART2_UART_TX_Init(void);
void USART2_UART_RX_Init(void);
int USART2_write(int ch);
int USART2_read(void);
int __io_putchar(int ch);

#endif /* INC_UART_H_ */
