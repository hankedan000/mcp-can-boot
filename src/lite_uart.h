#ifndef LITE_UART_H_
#define LITE_UART_H_

inline
void lite_uart_init() {
  UCSR0A = _BV(1);
  UCSR0B = _BV(4) | _BV(3);// RX enable TX enable
  UCSR0C = _BV(7) | _BV(2) | _BV(1);  // config USART; 8N1
  UBRR0L = (uint8_t)(( (16000000L + 115200L * 4L) / ((115200L * 8L))) - 1 );// set baud to 115200
}

inline
void lite_uart_putch(char ch) {
  while (!(UCSR0A & _BV(UDRE0))) {  /* Spin */ }
  UDR0 = ch;
}

inline
void lite_uart_putstr(const char *str) {
  while (*str != '\0') {
    lite_uart_putch(*str);
    str++;
  }
}

inline
void lite_uart_puthex8(uint8_t n) {
  const char *HEX_LUT = "0123456789abcdef";
  lite_uart_putch('0');
  lite_uart_putch('x');
  lite_uart_putch(HEX_LUT[(n >> 4) & 0xf]);
  lite_uart_putch(HEX_LUT[n & 0xf]);
}

#endif