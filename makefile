all: spi.o uart.o main.o hex flash
hex:
	avr-gcc -DF_CPU=8000000 -mmcu=atmega328p -o main.elf main.o spi.o uart.o
	#avr-gcc -DF_CPU=16000000 -mmcu=atmega328p -o main.elf main.o spi.o uart.o
	
	avr-objcopy -O ihex main.elf main.hex
	rm main.o
	rm main.hex
	rm spi.o
	rm uart.o
	rm main.elf
	
main.o:
	avr-gcc -Os -DF_CPU=8000000 -mmcu=atmega328p -c main.c
	#avr-gcc -Os -DF_CPU=16000000 -mmcu=atmega328p -c main.c
	
uart.o:
	avr-gcc -Os -DF_CPU=8000000 -mmcu=atmega328p -c UART/uart.c
	#avr-gcc -Os -DF_CPU=16000000 -mmcu=atmega328p -c UART/uart.c
	
spi.o:
	avr-gcc -Os -DF_CPU=8000000 -mmcu=atmega328p -c SPI/spi.c
	#avr-gcc -Os -DF_CPU=16000000 -mmcu=atmega328p -c SPI/spi.c
	
flash:
	avrdude -c arduino -p atmega328p -b57600 -P /dev/ttyUSB0 -U flash:w:main.hex
	#avrdude -c arduino -p atmega328p -P /dev/ttyACM0 -U flash:w:main.hex
	
perm:
	sudo chmod 777 /dev/ttyUSB0
	#sudo chmod 777 /dev/ttyACM0
