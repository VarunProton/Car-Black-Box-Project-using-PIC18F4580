/*
 * File:   clear_download.c
 * Author: varun
 *
 * Created on January 9, 2025, 4:59 PM
 */


#include <xc.h>
#include "clcd_matrix.h"

// Function to clear all recorded logs
void clear()
{
    // Display clearing message on CLCD
    clcd_print("LOGS ARE GETTING", LINE1(0));
    clcd_print("  CLEARED.....  ", LINE2(0));

    // Reset log counters and EEPROM pointers
    count_1 = 0;  // Reset log count
    eep = 0x00;   // Reset EEPROM start pointer
    addr = 0x00;  // Reset EEPROM address
    flag2 = 0;
    res = 0;

    // Delay to simulate clearing process
    for (unsigned long wait = 800000; wait--;);

    // Return to main menu
    choice = 1;
    CLEAR_DISP_SCREEN; // Clear CLCD display
    f = 0;             // Reset flag
    save_data();       // Save updated state in EEPROM
    set_config();
}

// Function to download logs through UART
void download()
{
    if (count_1 != 0) // Check if there are logs to download
    {
        // Display downloading message on CLCD
        clcd_print("DOWNLOADING....", LINE1(0));
        clcd_print("THROUGH UART....", LINE2(0));

        // Delay to simulate download process
        for (unsigned long wait = 800000; wait--;);

        read_data(); // Load recorded data from EEPROM

        // Send recorded data over UART
        puts("Recorded data\n\r");
        for (char i = 0; i < count_1; i++)
        {
            puts(eep_data[i]); // Transmit each log entry
            puts("\n\r");      // New line after each entry
        }
        puts("\n\r"); // Additional newline after all logs
    }
    else
    {
        // Display message if no logs are available
        clcd_print("NO LOGS TO", LINE1(0));
        clcd_print("DOWNLOAD", LINE2(8));

        // Delay to keep message on screen
        for (unsigned long wait = 800000; wait--;);

        // Send no data message over UART
        puts("No Recorded data\n\n\r");
    }

    // Return to main menu
    choice = 1;
    i = j = 0;           // Reset menu navigation indices
    flag2 = 0;
    CLEAR_DISP_SCREEN;   // Clear CLCD display
}
