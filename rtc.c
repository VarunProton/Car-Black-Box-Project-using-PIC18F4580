/*
 * File:   rtc.c
 * Author: varun
 *
 * Created on January 12, 2025, 12:07 PM
 */


#include <xc.h>
#include "clcd_matrix.h"
#include "ds1307.h"

// Function to set configuration by reading values from external EEPROM
void set_config()
{
    secret[0] = read_external_eeprom(0x84);  // Read the first byte of the secret from EEPROM
    secret[1] = read_external_eeprom(0x85);  // Read the second byte of the secret
    secret[2] = read_external_eeprom(0x86);  // Read the third byte of the secret
    secret[3] = '\0';                        // Null-terminate the secret string

    // Check if the secret string matches "yes"
    if(secret[0] == 'y' && secret[1] == 'e' && secret[2] == 's')
    {
        eep = read_external_eeprom(0x74);     // Read the start address of EEPROM
        count_1 = read_external_eeprom(0x75); // Read the count value from EEPROM
        res = read_external_eeprom(0x76);
        addr = 10 * (res % 10); 
        read_data();                         // Optionally read data if condition met
    }
    else
    {
        res = 0;
        eep = 0x00;    // Initialize EEPROM address to 0 if secret doesn't match
        count_1 = 0;   // Reset the count value to 0
    }
}

// Function to store time and event data to EEPROM
void str_eeprom()
{
    if(count_1 < 10)  // Increment count_1 if it's less than 10
    {
        count_1++;
    }
    res++;
    if(res > 10 && res < 250)
    {
        addr = 10 * (res % 10);
    }
    else if(res == 250)
    {
        addr = 0x00;
        res = 0;
    }
    else
    {
        addr = 0x00;
    }
    if(eep == 0x64)  // If EEPROM address reaches 0x64, reset to 0x00
    {
        eep = 0x00;
    }
    
    addr = 0x00;
    // Write time and event data to EEPROM starting from the current address
    write_external_eeprom(eep++, time[0]);     // Write the first byte of time to EEPROM
    write_external_eeprom(eep++, time[1]);     // Write the second byte of time
    write_external_eeprom(eep++, time[3]);     // Write the third byte of time
    write_external_eeprom(eep++, time[4]);     // Write the fourth byte of time
    write_external_eeprom(eep++, time[6]);     // Write the fifth byte of time
    write_external_eeprom(eep++, time[7]);     // Write the sixth byte of time
    write_external_eeprom(eep++, ev[count][0]); // Write the first event byte to EEPROM
    write_external_eeprom(eep++, ev[count][1]); // Write the second event byte
    write_external_eeprom(eep++, speed_disp[0]); // Write the first speed display byte
    write_external_eeprom(eep++, speed_disp[1]); // Write the second speed display byte
}
