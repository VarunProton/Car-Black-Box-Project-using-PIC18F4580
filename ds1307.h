/* 
 * File:   ds1307.h
 * Author: varun
 *
 * Created on January 7, 2025, 1:30 PM
 */

#ifndef DS1307_H
#define DS1307_H

// I2C Slave Addresses for DS1307 RTC
#define SLAVE_READ        0xD1  // Slave address for read operations
#define SLAVE_WRITE       0xD0  // Slave address for write operations

// I2C Slave Addresses for External EEPROM
#define SLAVE_READ_EEP    0xA1  // Slave address for reading from EEPROM
#define SLAVE_WRITE_EEP   0xA0  // Slave address for writing to EEPROM

// DS1307 Register Addresses
#define SEC_ADDR          0x00  // Address for Seconds register
#define MIN_ADDR          0x01  // Address for Minutes register
#define HOUR_ADDR         0x02  // Address for Hours register
#define DAY_ADDR          0x03  // Address for Day of the week register
#define DATE_ADDR         0x04  // Address for Date register
#define MONTH_ADDR        0x05  // Address for Month register
#define YEAR_ADDR         0x06  // Address for Year register
#define CNTL_ADDR         0x07  // Address for Control register

// Function Prototypes
void my_time_set(); // Sets the current time in the DS1307
void init_ds1307(void); // Initializes the DS1307 RTC module
void write_ds1307(unsigned char address1, unsigned char data); // Writes data to a DS1307 register
unsigned char read_ds1307(unsigned char address1); // Reads data from a DS1307 register

#endif // DS1307_H
