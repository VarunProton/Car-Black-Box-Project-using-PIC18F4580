/*
 * File:   time_log.c
 * Author: varun
 *
 * Created on January 9, 2025, 5:00 PM
 */


#include <xc.h>
#include "clcd_matrix.h"
#include "ds1307.h"

// Function to handle time setting process
void time_set() {
    if (f_c == 0) {
        // Extract initial hours, minutes, and seconds from the time string
        h = ((time[0] - 48) * 10) + (time[1] - 48);
        m = ((time[3] - 48) * 10) + (time[4] - 48);
        s = ((time[6] - 48) * 10) + (time[7] - 48);
        f_c = 1;  // First configuration flag set
        set();    // Update the time display string
        index = 0;
    }

    // Blinking effect for the current index (hours, minutes, or seconds)
    if (wait++ == 75) {
        wait = 0;

        if (index == 0) {
            if (c_f) {  // Toggle blinking for hours
                c_f = 0;
                t[0] = ' ';
                t[1] = ' ';
            } else {
                c_f = 1;
                t[0] = (h / 10) + 48;
                t[1] = (h % 10) + 48;
            }
        } else if (index == 1) {
            if (c_f) {  // Toggle blinking for minutes
                c_f = 0;
                t[3] = ' ';
                t[4] = ' ';
            } else {
                c_f = 1;
                t[3] = (m / 10) + 48;
                t[4] = (m % 10) + 48;
            }
        } else if (index == 2) {
            if (c_f) {  // Toggle blinking for seconds
                c_f = 0;
                t[6] = ' ';
                t[7] = ' ';
            } else {
                c_f = 1;
                t[6] = (s / 10) + 48;
                t[7] = (s % 10) + 48;
            }
        }
    }

    // Check for keypad input (gear) and update values
    if (gear == 1) {
        gear = 0;
        if (index == 0) {  // Increment hours
            h++;
            if (h > 23) h = 0;
        } else if (index == 1) {  // Increment minutes
            m++;
            if (m > 59) m = 0;
        } else if (index == 2) {  // Increment seconds
            s++;
            if (s > 59) s = 0;
        }
    } else if (gear == 2) {
        gear = 0;
        index++;  // Move to the next field (hours -> minutes -> seconds)
        set();
        if (index > 2) index = 0;  // Wrap around to hours
    } else if (gear == 11) {  // Save the time to DS1307
        gear = 0;
        set_time_rtc(h, m, s);  // Write updated time to RTC
        choice = 0;
        f_c = 0;
    } else if (gear == 12) {  // Cancel and go back to main menu
        gear = 0;
        choice = 1;
        f_c = 0;
        CLEAR_DISP_SCREEN;
    }

    // Display time-setting screen
    clcd_print("  Setting TIME  ", LINE1(0));
    clcd_print(t, LINE2(0));
    if (flag) flag++;
}

// Function to write time to DS1307 RTC
void set_time_rtc(unsigned char h, unsigned char m, unsigned char s) {
    unsigned char h_1, m_1, s_1;

    s_1 = bcd_convertor(s);       // Convert seconds to BCD
    write_ds1307(SEC_ADDR, s_1);  // Write seconds to RTC

    m_1 = bcd_convertor(m);       // Convert minutes to BCD
    write_ds1307(MIN_ADDR, m_1);  // Write minutes to RTC

    h_1 = bcd_convertor(h);       // Convert hours to BCD
    write_ds1307(HOUR_ADDR, h_1); // Write hours to RTC
}

// Function to convert a decimal number to packed BCD
unsigned char bcd_convertor(unsigned char number) {
    unsigned char packedBCD = 0, shift = 0;

    while (number > 0) {
        int digit = number % 10;         // Extract the last digit
        packedBCD |= (digit << shift);   // Pack digit into BCD format
        shift += 4;                      // Move to the next nibble
        number /= 10;                    // Remove the last digit
    }
    return packedBCD;
}

// Update time display string
void set(void) {
    t[0] = (h / 10) + 48;  // Tens place of hours
    t[1] = (h % 10) + 48;  // Units place of hours
    t[3] = (m / 10) + 48;  // Tens place of minutes
    t[4] = (m % 10) + 48;  // Units place of minutes
    t[6] = (s / 10) + 48;  // Tens place of seconds
    t[7] = (s % 10) + 48;  // Units place of seconds
}
