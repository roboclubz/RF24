#define  BAUD 9600UL
#include <util/setbaud.h>
#include <util/delay.h>
#include <stdlib.h>
#include <inttypes.h>

static int uart_putchar(char c, FILE *stream);

void init_uart()
{
	UCSRB |= (1<<TXEN) | (1<<RXEN);
	UCSRC |= (1<<UCSZ1) | (1<<UCSZ0);
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
}
static FILE mystdout = FDEV_SETUP_STREAM(uart_putchar, NULL,_FDEV_SETUP_WRITE);
static int uart_putchar(char c, FILE *stream)
{
	if (c == '\n')
	{
		uart_putchar('\r', stream);
	}
	loop_until_bit_is_set(UCSRA, UDRE);
	UDR = c;
	return 0;
}
