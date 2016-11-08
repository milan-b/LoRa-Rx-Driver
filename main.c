#include <avr/io.h>
#include <util/delay.h>
#include "UART/uart.h"
#include "SPI/spi.h"

#define DELAY 2000


int main( void )
{
 
 sei();
 UART_Init();
 
 SPI_MasterInit(); 
 
 //PORTB config MOSI SCK SS SDN as output , MISO as input
 DDRB=0x2F;

 PORTB=PORTB | 0x04; //set SS H

 //buffers
 char txt_buf[128]; //char buffer
 unsigned char rec_buf[FIELD_LENGTH]; //receive buffer
 unsigned char tx_buf[FIELD_LENGTH]; //send buffer
 unsigned char tmp;

 _delay_ms(DELAY);
 uartSend("Lora init begins.");
 
 

 uint8_t c = 0x38;
 	while(1)
	{
  		//_delay_ms(DELAY);
  		//enable_light(PORTB);
  		_delay_ms(DELAY);
  		//disable_light(PORTB);
		uartSend("Nikoal konj :)");
		//c = UART_ReceiveByte();
		//UART_SendByte(c);
		
 	}
}

