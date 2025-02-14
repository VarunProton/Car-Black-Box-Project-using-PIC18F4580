/*
 * File:   view_log.c
 * Author: varun
 *
 * Created on January 9, 2025, 4:58 PM
 */


#include <xc.h>
#include "clcd_matrix.h"
#include "ds1307.h"

// Function to display logs from EEPROM
void view() {
    
    
    if (count_1 != 0) { // Check if there are logs to display
        if (flag2 == 0) { // Perform data reading only once
            read_data(); // Read log data from EEPROM
            flag2 = 1; // Set the flag to avoid multiple reads
            k = 0; // Reset index for log navigation
        }
//        read_data();
        clcd_print("#  TIME  GEAR SP", LINE1(0)); // Print log header
        clcd_print(eep_data[k], LINE2(0)); // Print log data for the current index
        
        if (gear == 1) { // If gear 1 is pressed (next log)
            gear = 0; // Reset gear
            k++; // Move to the next log
            if (k > count_1 - 1) { // Prevent going out of bounds
                k = count_1 - 1;
            }
        } else if (gear == 2) { // If gear 2 is pressed (previous log)
            gear = 0; // Reset gear
            k--; // Move to the previous log
            if (k < 0) { // Prevent going below the first log
                k = 0;
            }
        }

        if (gear == 12) { // If gear 12 is pressed (exit log view)
            CLEAR_DISP_SCREEN; // Clear the display
            choice = 1; // Return to the main menu
        }
    } else { // If there are no logs to display
        clcd_print("NO LOGS TO", LINE1(0)); // Print "No logs" message
        clcd_print("DISPLAY :(", LINE2(6)); // Print sad face

        for (unsigned long wait = 800000; wait--;); // Delay for the message display
        choice = 1; // Return to the main menu
    }
}

// Function to read log data from external EEPROM
void read_data(void) {
    l = 0; // Reset line counter and EEPROM address
    unsigned char once = 1;

    for (char k = 0; k < count_1; k++) { // Iterate over the number of logs
        for (char i = 0; i < 16; i++) { // Fill 16 characters for each log
            if (i == 0) {
                eep_data[k][i] = l++ + '0'; // Assign log number
            } else if (i == 1 || i == 10 || i == 13) {
                eep_data[k][i] = ' '; // Add spaces for formatting
            } else if (i == 4 || i == 7) {
                eep_data[k][i] = ':'; // Add colons for time format
            } else {
                eep_data[k][i] = read_external_eeprom(addr); // Read data from EEPROM
                addr++; // Increment EEPROM address
            }
        }
        eep_data[k][16] = '\0'; // Null-terminate the string
        if(addr == 0x64)
        {
            save_data(); // Save the current log state to EEPROM
            once = 0;
            addr = 0x00;
        }
    }
    if(once)
    {
        save_data(); // Save the current log state to EEPROM
        once = 0;
    }
}

// Function to save log metadata to external EEPROM
void save_data() {
    if (addr < 0x64) { // Check if address is below the limit
        write_external_eeprom(0x74, addr); // Save the current address
    } else {
        write_external_eeprom(0x74, 0x00); // Reset address to 0 if exceeded
    }
    
    write_external_eeprom(0x76, res);
    write_external_eeprom(0x75, count_1); // Save the count of logs
    write_external_eeprom(0x84, 'y'); // Save metadata ('yes')
    write_external_eeprom(0x85, 'e');
    write_external_eeprom(0x86, 's');
}
