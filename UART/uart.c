#include "uart.h"
#include <avr/io.h>

/******************************************************************************
 * @brief - Initializes the UART                                              *
 ******************************************************************************/

void UART_Init() {
	// Set the TX pin as output and RX pin as input
	DDRD |= TX;
	DDRD &= ~RX;

	// Set the baud rate
	UBRR0H = ((UBRR) & 0x0F00);
	UBRR0L = (uint8_t) ((UBRR) & 0xFF);

	// Enable the RX and TX
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);

	// Set frame format
	UCSR0C = DATA;
}

/******************************************************************************
 * @brief - Sends one byte                                                    *
 ******************************************************************************/

void UART_SendByte(uint8_t byte) {
	while(!(UCSR0A & (1 << UDRE0)));
	UDR0 = (uint8_t) byte;
}

/******************************************************************************
 * @brief - Sends string                                                    *
 ******************************************************************************/

void uartSend(const char* str)
{
	uint8_t i = 0;
	char c;
	while(1)
	{
		c = str[i];
		if (c == '\0')
		{
			UART_SendByte('\r');
			UART_SendByte('\n');
			break;
		}
		UART_SendByte((uint8_t)c);
		i++;
	}
}

/******************************************************************************
 * @brief - Receives one byte 												  *
 ******************************************************************************/

uint8_t UART_ReceiveByte() {
	// Wait for reception
	while (!(UCSR0A & (1 << RXC0)))
		;
	return (uint8_t) UDR0;
}
