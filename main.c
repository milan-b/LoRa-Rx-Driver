// #include <avr/io.h>
// #include <util/delay.h>
// 
// #define registerSetOutput(register) register = 0b11111111
// #define DALAY 1000
// 
// int main (void)
// {
//   registerSetOutput(DDRB); //svi out 
//   while(1)
//   {
//     PORTB ^= 1;
//     _delay_ms(DALAY);
//   }
// }

#include <avr/io.h>
#include <util/delay.h>

#define register_set_output(register) (register = register | 0b00111111)   // Sets all B pins to output
#define enable_light(port) (port = 0xFF)       // Sets digital pin 8 to high
#define disable_light(port) (port = 0x00)     // Sets digital pin 8 to low

#define DELAY 2000

int main( void )
{
 register_set_output( DDRB );
 DDRB = 0xFF;

 	while(1)
	{
  		_delay_ms(DELAY);
  		enable_light(PORTB);
  		_delay_ms(DELAY);
  		disable_light(PORTB);
 	}
}

