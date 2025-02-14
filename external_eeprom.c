/*
 * File:   external_eeprom.c
 * Author: varun
 *
 * Created on January 9, 2025, 5:39 PM
 */


#include <xc.h>
#include "ds1307.h"
#include "clcd_matrix.h"

// Function to write data to the external EEPROM at a specific address
void write_external_eeprom(unsigned char address, unsigned char data)
{
	i2c_start();             // Send I2C start condition
	i2c_write(SLAVE_WRITE_EEP);  // Write mode to the external EEPROM
	i2c_write(address);      // Send the EEPROM address
	i2c_write(data);         // Send the data to be written
	i2c_stop();              // Send I2C stop condition
    for(unsigned int wait = 3000; wait--;);  // Small delay for EEPROM write completion
}

// Function to read data from the external EEPROM at a specific address
unsigned char read_external_eeprom(unsigned char address)
{
	unsigned char data;

	i2c_start();             // Send I2C start condition
	i2c_write(SLAVE_WRITE_EEP);  // Write mode to the external EEPROM
	i2c_write(address);      // Send the EEPROM address
	i2c_rep_start();         // Send repeated start condition for read mode
	i2c_write(SLAVE_READ_EEP);  // Read mode to the external EEPROM
	data = i2c_read();       // Read the data from the EEPROM
	i2c_stop();              // Send I2C stop condition

	return data;            // Return the read data
}
