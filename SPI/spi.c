#include "spi.h"
#include <avr/io.h>

/******************************************************************************
 * @brief - Initializes the master                                            *
 ******************************************************************************/

void SPI_MasterInit() {
	// Set MOSI, SCK, SS as Output
    DDRB = (1 << MOSI) | (1 << SCK) | (1 << SS);

    // Enable SPI, Set as Master
    // Prescaler: Fosc/16, Enable Interrupts
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
	
	//SPI init
	//SPCR=0x52; //MSB first, master, clock polarity low, data sampling rising edge, 62.5KHz clock
	//SPSR=0x00;
}

void SPI_SlaveInit() {
	// Set MISO as OUTPUT
	DDRB = (1 << MISO);

	// Enable SPI and SPI interrupts
	SPCR = (1 << SPE) | (1 << SPIE);

	// Enable global Interrupts
	sei();
}


//send and receive data byte via SPI
unsigned char SPI_byte(unsigned char data){
	unsigned int err=0;
	SPDR=data;
	while(!(SPSR & (1<<SPIF))){ //waiting for send
		err++;
		if(err==65535){
			global_err=global_err|1; //err SPI not responding
			break;
		}
		_delay_us(10);
	}
	return SPDR;
}

//read data from register
unsigned char SPIRead(unsigned char adr){
	unsigned char tmp;
	PORTB=PORTB & 0xFB; //set SS L
	_delay_us(50);
	
	SPI_byte(adr);
	tmp=SPI_byte(0xFF);
	PORTB=PORTB | 0x04; //set SS H
	return tmp;
}

//write data to register
void SPIWrite(unsigned char adr, unsigned char data){

	PORTB=PORTB & 0xFB; //set SS L
	_delay_us(50);
	
	SPI_byte(adr|0x80);
	SPI_byte(data);
	
	PORTB=PORTB | 0x04; //set SS H
	
}

//Burst read
void SPIBurstRead(unsigned char *data,unsigned char n,unsigned char adr){
	unsigned char t;

	PORTB=PORTB & 0xFB; //set SS L
	_delay_us(50);

	SPI_byte(adr);

	for(t=0;t<n;t++)
		data[t]=SPI_byte(0xFF);
		
	PORTB=PORTB | 0x04; //set SS H
}

//Burst write
void SPIBurstWrite(unsigned char *data,unsigned char n,unsigned char adr){
	unsigned char t;

	PORTB=PORTB & 0xFB; //set SS L
	_delay_us(50);

	SPI_byte(adr|0x80);

	for(t=0;t<n;t++)
		SPI_byte(data[t]);
	
	PORTB=PORTB | 0x04; //set SS H
}

//