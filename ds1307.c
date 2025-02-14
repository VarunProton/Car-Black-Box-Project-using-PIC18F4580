/*
 * File:   ds1307.c
 * Author: varun
 *
 * Created on January 7, 2025, 1:29 PM
 */




#include <xc.h>
#include "ds1307.h"
#include "clcd_matrix.h"

/* 
 * DS1307 Slave address
 * D0  -  Write Mode
 * D1  -  Read Mode
 */

// Function to initialize the DS1307 RTC (Real-Time Clock)
void init_ds1307(void)
{
	unsigned char dummy;

	/* Setting the CH bit of the RTC to Stop the Clock */
	dummy = read_ds1307(SEC_ADDR);  // Read the current value from the SEC register
	write_ds1307(SEC_ADDR, dummy | 0x80);  // Set the CH (Clock Halt) bit to stop the clock

	/* Setting 12 Hr Format */
	dummy = read_ds1307(HOUR_ADDR);  // Read the current value from the HOUR register
	write_ds1307(HOUR_ADDR, dummy | 0x00);  // Set 12-hour format (clear 24-hour format bit)

	/* 
	 * Control Register of DS1307
	 * Bit 7 - OUT (Output control for SQW)
	 * Bit 6 - 0
	 * Bit 5 - OSF (Oscillator Stop Flag)
	 * Bit 4 - SQWE (Square Wave Enable)
	 * Bit 3 - 0
	 * Bit 2 - 0
	 * Bit 1 - RS1 (Square Wave Frequency Select)
	 * Bit 0 - RS0 (Square Wave Frequency Select)
	 * 
	 * Setting RS0 and RS1 as 11 to achieve SQW output at 32.768 KHz
	 */ 
	write_ds1307(CNTL_ADDR, 0x93);  // Write to the control register to configure the square wave

	/* Clearing the CH bit of the RTC to Start the Clock */
	dummy = read_ds1307(SEC_ADDR);  // Read the current value from the SEC register
	write_ds1307(SEC_ADDR, dummy & 0x7F);  // Clear the CH (Clock Halt) bit to start the clock

}

// Function to write data to the DS1307 at a specific address
void write_ds1307(unsigned char address, unsigned char data)
{
	i2c_start();          // Send I2C start condition
	i2c_write(SLAVE_WRITE);  // Write mode to the DS1307
	i2c_write(address);   // Send the register address
	i2c_write(data);      // Send the data to be written
	i2c_stop();           // Send I2C stop condition
}

// Function to read data from the DS1307 at a specific address
unsigned char read_ds1307(unsigned char address)
{
	unsigned char data;

	i2c_start();            // Send I2C start condition
	i2c_write(SLAVE_WRITE); // Write mode to the DS1307
	i2c_write(address);     // Send the register address
	i2c_rep_start();        // Send repeated start condition for read mode
	i2c_write(SLAVE_READ);  // Read mode to the DS1307
	data = i2c_read();      // Read the data from the DS1307
	i2c_stop();             // Send I2C stop condition

	return data;           // Return the read data
}
