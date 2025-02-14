/*
 * File:   eatras.c
 * Author: varun
 *
 * Created on January 1, 2025, 5:29 PM
 */


#include <xc.h>
#include "clcd_matrix.h"

// Function to transmit a single character via UART
void putch(unsigned char data)
{
    while(TXIF == 0);     // Wait for the transmit buffer to be ready
    TXREG = data;         // Load the character into the transmit register
    TXIF = 0;             // Clear the transmit interrupt flag
}

// Function to transmit a string of characters via UART
void puts(unsigned char *str)
{
    while(*str)           // Loop through each character in the string
    {
        putch(*str);      // Transmit the current character
        str++;            // Move to the next character
    }
}

// Function to initialize the UART module for communication
void init_uart()
{
    TRISC6 = 0;           // Set the TX pin (RC6) as output for transmitting
    TRISC7 = 1;           // Set the RX pin (RC7) as input for receiving

    TX9 = 0;              // Set the data to be transmitted as 8-bit (not 9-bit)
    TXEN = 1;             // Enable the transmitter
    SYNC = 0;             // Set UART to asynchronous mode
    BRGH = 1;             // High speed baud rate

    SPEN = 1;             // Enable the serial port (TX/RX)
    RX9 = 0;              // Set data reception to 8-bit (not 9-bit)
    CREN = 1;             // Enable the continuous receive mode

    BRG16 = 0;            // Use 8-bit baud rate generator (16-bit mode disabled)
    SPBRG = 129;          // Set baud rate to 9600 (for 16 MHz clock)

    TXIF = 0;             // Clear the transmit interrupt flag
    RCIF = 0;             // Clear the receive interrupt flag
}
