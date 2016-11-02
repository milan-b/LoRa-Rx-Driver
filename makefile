hex:
	avr-gcc -Os -DF_CPU=8000000 -mmcu=atmega328p -c main.c
	avr-gcc -DF_CPU=8000000 -mmcu=atmega328p -o main.elf main.o
	avr-objcopy -O ihex main.elf main.hex
	rm main.o
	rm main.elf
	
flash:
	avrdude -c arduino -p atmega328p -P /dev/ttyUSB0 -U flash:w:main.hex