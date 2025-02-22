/*
 * Copyright (c) 2010 by Cristian Maglie <c.maglie@bug.st>
 * Copyright (c) 2014 by Paul Stoffregen <paul@pjrc.com> (Transaction API)
 * Copyright (c) 2014 by Matthijs Kooijman <matthijs@stdin.nl> (SPISettings AVR)
 * 
 * SPI Master library for Arduino.
 * 
 * This library provides an interface for SPI communication on Arduino boards.
 * It supports various SPI settings, transactions, and transfer methods.
 * 
 * This file is free software; you can redistribute it and/or modify
 * it under the terms of either the GNU General Public License version 2
 */
#ifndef SPI_H
#define SPI_H

#include <Arduino.h>
#include <SPI.h>

#if defined(__AVR__)
  // AVR specific code
#endif

#define SPI_HAS_TRANSFER_ASYNC 1
#include <DMAChannel.h>
#include <EventResponder.h>

#define SPI_HAS_TRANSACTION 1

#ifndef LSBFIRST
#define LSBFIRST 0
#endif
#ifndef MSBFIRST
#define MSBFIRST 1
#endif

#define SPI_MODE0 0x00
#define SPI_MODE1 0x04
#define SPI_MODE2 0x08
#define SPI_MODE3 0x0C

#define SPI_CLOCK_DIV4 0x00
#define SPI_CLOCK_DIV16 0x01
#define SPI_CLOCK_DIV64 0x02
#define SPI_CLOCK_DIV128 0x03
#define SPI_CLOCK_DIV2 0x04
#define SPI_CLOCK_DIV8 0x05
#define SPI_CLOCK_DIV32 0x06

#define SPI_MODE_MASK 0x0C
#define SPI_CLOCK_MASK 0x03
#define SPI_2XCLOCK_MASK 0x01

#if defined(__AVR__)
#define SPI_ATOMIC_VERSION 1
#if defined(EIMSK)
  #define SPI_AVR_EIMSK	 EIMSK
#elif defined(GICR)
  #define SPI_AVR_EIMSK	 GICR
#endif

class SPISettings {
  // Class members and methods...
};
#endif // End of AVR specific code

#ifndef SPI_CLASS_H
#define SPI_CLASS_H
class SPIClass { // AVR
public:
	// Other class members and methods...

private:
	uint8_t clockDiv; // Declare clockDiv
	uint8_t spcr; // Declare spcr
	uint8_t spsr; // Declare spsr
	static uint8_t interruptMode; // Declare interruptMode
	uint8_t SREG; // Declare SREG
	static uint8_t interruptSave; // Declare interruptSave

	friend class SPIClass; // Correct placement of friend declaration
};
#endif // End of SPI_CLASS_H

#endif // End of SPI_H
