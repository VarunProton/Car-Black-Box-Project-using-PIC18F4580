/*
 * File:   dashboard.c
 * Author: varun
 *
 * Created on December 31, 2024, 2:06 PM
 */


#include <xc.h>
#include "clcd_matrix.h"
#include "ds1307.h"

// Function to get the current time from the DS1307 RTC
static void get_time(void)
{
    clock_reg[0] = read_ds1307(HOUR_ADDR); // Read hours from RTC
    clock_reg[1] = read_ds1307(MIN_ADDR); // Read minutes from RTC
    clock_reg[2] = read_ds1307(SEC_ADDR); // Read seconds from RTC

    // Check if 12-hour format is enabled
    if (clock_reg[0] & 0x40)
    {
        // Format time in 12-hour format
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    }
    else
    {
        // Format time in 24-hour format
        time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);
        time[1] = '0' + (clock_reg[0] & 0x0F);
    }

    time[2] = ':'; // Add colon separator for time
    time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F); // Format minutes
    time[4] = '0' + (clock_reg[1] & 0x0F);
    time[5] = ':'; // Add colon separator for time
    time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F); // Format seconds
    time[7] = '0' + (clock_reg[2] & 0x0F);
    time[8] = '\0'; // Null-terminate the string
}

// Function to display the dashboard
void dash_disp()
{
    if (f == 0) // Check if configuration is needed
    {
        set_config(); // Perform initial setup
        f = 1; // Set flag to indicate setup is done
    }

    // Calculate speed using ADC value
    speed = (read_adc() / 10.3); 
    speed_disp[0] = (speed / 10) + '0'; // Convert tens place to character
    speed_disp[1] = (speed % 10) + '0'; // Convert units place to character
    speed_disp[2] = '\0'; // Null-terminate the speed string

    if (flag) // Check if gear change is allowed
    {
        if (count < 6) // Check if gear can be increased
        {
            if (gear == 2) // Increment gear
            {
                gear = 0; // Reset gear value
                count++; // Increment gear count
                str_eeprom(); // Store the state in EEPROM
            }
        }

        if (count > 1 && count < 7) // Check if gear can be decreased
        {
            if (gear == 3) // Decrement gear
            {
                gear = 0; // Reset gear value
                count--; // Decrement gear count
                str_eeprom(); // Store the state in EEPROM
            }
        }
    }

    if (gear == 1) // Reset gear when neutral is selected
    {
        flag = 0; // Reset flag
        gear = 0; // Reset gear value
        count = 7; // Set count to the highest gear
        str_eeprom(); // Store the state in EEPROM
    }

    if (flag == 0) // Check if flag is cleared
    {
        if (gear == 2 || gear == 3) // Change to the first gear
        {
            count = 1; // Set count to first gear
            gear = 0; // Reset gear value
            flag = 1; // Set flag to allow further gear changes
            str_eeprom(); // Store the state in EEPROM
        }
    }

    get_time(); // Fetch the current time

    // Display the dashboard information on CLCD
    clcd_print(hed, LINE1(0)); // Print header
    clcd_print(time, LINE2(0)); // Print current time
    clcd_print("  ", LINE2(8)); // Add spacing
    clcd_print(ev[count], LINE2(10)); // Print current gear
    clcd_print("  ", LINE2(12)); // Add spacing
    clcd_print(speed_disp, LINE2(14)); // Print current speed

    if (gear == 11) // Check if exit condition is met
    {
        CLEAR_DISP_SCREEN; // Clear the display
        choice = 1; // Return to the main menu
        i = 0; // Reset menu index
        j = 0; // Reset menu sub-index
        k = 0;
        flag2 = 0;
    }
}
