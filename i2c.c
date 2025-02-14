/*
 * File:   i2c.c
 * Author: varun
 *
 * Created on January 7, 2025, 1:28 PM
 */



#include <xc.h>
#include "ds1307.h"
#include "clcd_matrix.h"

// Function to initialize I2C communication
void init_i2c(void)
{
	/* Set SCL (clock) and SDA (data) pins as inputs */
	TRISC3 = 1;
	TRISC4 = 1;
	/* Set I2C in master mode */
	SSPCON1 = 0x28;

	SSPADD = 0x31;  // Set the I2C baud rate (adjusted for clock speed)
	/* Use I2C levels for communication */
	CKE = 0;
	/* Disable slew rate control for proper communication */
	SMP = 1;
	/* Clear the SSPIF interrupt flag */
	SSPIF = 0;
	/* Clear the bus collision flag */
	BCLIF = 0;
}

// Function to wait for I2C to become idle
void i2c_idle(void)
{
	while (!SSPIF);  // Wait until the SSPIF (I2C interrupt flag) is set
	SSPIF = 0;       // Clear the SSPIF interrupt flag
}

// Function to send a start condition on the I2C bus
void i2c_start(void)
{
	SEN = 1;          // Initiate start condition
	i2c_idle();       // Wait until the I2C is idle (start condition complete)
}

// Function to send a stop condition on the I2C bus
void i2c_stop(void)
{
	PEN = 1;          // Initiate stop condition
	i2c_idle();       // Wait until the I2C is idle (stop condition complete)
}

// Function to send a repeated start condition on the I2C bus
void i2c_rep_start(void)
{
	RSEN = 1;         // Initiate repeated start condition
	i2c_idle();       // Wait until the I2C is idle (repeated start complete)
}

// Function to write data to the I2C bus
void i2c_write(unsigned char data)
{
	SSPBUF = data;    // Load data to SSPBUF register for transmission
	i2c_idle();       // Wait until the I2C is idle (data transmission complete)
}

// Function to enable I2C receive mode
void i2c_rx_mode(void)
{
	RCEN = 1;         // Enable receive mode (RCEN bit)
	i2c_idle();       // Wait until the I2C is idle (ready to receive data)
}

// Function to send a no-acknowledge signal on the I2C bus
void i2c_no_ack(void)
{
	ACKDT = 1;        // Set ACKDT to 1 for no-acknowledge
	ACKEN = 1;        // Initiate the no-acknowledge action
}

// Function to read a byte of data from the I2C bus
unsigned char i2c_read(void)
{
	i2c_rx_mode();    // Set the I2C to receive mode
	i2c_no_ack();     // Send no-acknowledge signal after receiving data

	return SSPBUF;    // Return the received data from the SSPBUF register
}
