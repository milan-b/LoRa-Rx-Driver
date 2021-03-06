/*
    SPI header file
    @brief - SPI library for ATmega328p microcontroller
*/

#ifndef SPI_H
#define SPI_H

/******************************************************************************
 * Includes                                                                   *
 ******************************************************************************/

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>

/******************************************************************************
 * Defines                                                                    *
 ******************************************************************************/

#define SS				2
#define MOSI			3
#define MISO			4
#define SCK				5

#define SS_LOW			0xFB
#define SS_HIGH			0x04

/******************************************************************************
 * @brief - Initializes the master                                            *
 ******************************************************************************/

void SPI_MasterInit();

/******************************************************************************
 * @brief - Initializes the slave                                             *
 ******************************************************************************/

void SPI_SlaveInit();

/******************************************************************************
 * @brief - Sends one byte to the slave                                       *
 ******************************************************************************/

uint8_t SPI_MasterSendByte(uint8_t);

/******************************************************************************
 * @brief - Receives one byte from the master                                 *
 ******************************************************************************/

uint8_t SPI_SlaveReceiveByte();

#endif
