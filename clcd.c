/*
 * File:   clcd.c
 * Author: varun
 *
 * Created on December 31, 2024, 1:58 PM
 */


#include <xc.h>
#include "clcd_matrix.h"

// Function to write data/commands to the CLCD
void clcd_write(unsigned char byte, unsigned char control_bit)
{
    CLCD_RS = control_bit;  // Set control bit (instruction or data mode)
    CLCD_PORT = byte;       // Write the byte to CLCD port

    // Enable pulse (minimum 200ns)
    CLCD_EN = HI;
    CLCD_EN = LO;

    // Set port direction to input to check CLCD busy flag
    PORT_DIR = INPUT;
    CLCD_RW = HI;               // Set to read mode
    CLCD_RS = INSTRUCTION_COMMAND;  // Set to instruction mode

    // Wait until the CLCD is not busy
    do
    {
        CLCD_EN = HI;
        CLCD_EN = LO;
    } while (CLCD_BUSY);

    CLCD_RW = LO;   // Set back to write mode
    PORT_DIR = OUTPUT;  // Set port direction back to output
}

// Function to initialize the CLCD
void init_clcd()
{
    // Configure PortD as output for CLCD data
    TRISD = 0x00;
    // Configure PortC as output for CLCD control
    TRISC = TRISC & 0xF8;

    CLCD_RW = LO;  // Set CLCD to write mode

    // Startup delay for the CLCD controller
    __delay_ms(30);

    // CLCD initialization sequence
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND);  // Set to 8-bit mode
    __delay_us(4100);                                 // Delay for the first command
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND);  // Repeat 8-bit mode command
    __delay_us(100);                                  // Short delay
    clcd_write(EIGHT_BIT_MODE, INSTRUCTION_COMMAND);  // Final 8-bit mode command
    __delay_us(1);

    CURSOR_HOME;                // Move cursor to home
    __delay_us(100);
    TWO_LINE_5x8_MATRIX_8_BIT;  // Set display to 2 lines, 5x8 character matrix
    __delay_us(100);
    CLEAR_DISP_SCREEN;          // Clear the display
    __delay_us(500);
    DISP_ON_AND_CURSOR_OFF;     // Turn display on, turn cursor off
    __delay_us(100);
}

// Function to print a string on the CLCD at a specific address
void clcd_print(const unsigned char *data, unsigned char addr)
{
    clcd_write(addr, INSTRUCTION_COMMAND);  // Set the starting address
    while (*data != '\0')                   // Loop through the string
    {
        clcd_write(*data++, DATA_COMMAND);  // Write each character to the CLCD
    }
}

// Function to print a single character on the CLCD at a specific address
void clcd_putch(const unsigned char data, unsigned char addr)
{
    clcd_write(addr, INSTRUCTION_COMMAND);  // Set the starting address
    clcd_write(data, DATA_COMMAND);         // Write the character to the CLCD
}
