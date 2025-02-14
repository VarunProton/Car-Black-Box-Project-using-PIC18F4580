/*
 * File:   main.c
 * Author: varun
 *
 * Created on December 31, 2024, 2:03 PM
 */


#include <xc.h>
#include "clcd_matrix.h"
#include "ds1307.h"

// Function to configure and initialize all peripherals
void init_config() {
    init_matrix();  // Initialize matrix keypad
    init_clcd();    // Initialize CLCD
    init_adc();     // Initialize ADC module
    init_i2c();     // Initialize I2C module
    init_ds1307();  // Initialize DS1307 RTC module
    init_uart();    // Initialize UART module
    puts("welcome\n"); // Print a welcome message over UART
}

// Function to initialize the matrix keypad
void init_matrix() {
    ADCON1 = 0x0F;  // Configure all pins as digital
    TRISB = 0x1E;   // Set RB1-RB4 as inputs
    RBPU = 0;       // Enable PORTB pull-ups
    RB0 = 0;        // Clear RB0 (used for an LED indicator)
}

// Main function
void main(void) {
    init_config();  // Call configuration initialization

    while (1) { // Infinite loop to keep the program running
        gear = read_matrix(EDGE); // Read key press from matrix keypad

        switch (choice) { // Switch case to handle menu navigation
            case e_dashboard: 
                dash_disp(); // Display dashboard screen
                break;

            case e_main_menu:
                menu_log(); // Display and navigate the main menu
                break;

            case view_log:
                i = 0; // Reset index for viewing log
                view(); // View log data
                break;

            case clear_log:
                clear(); // Clear log data
                eep = 0x00;
                count_1 = 0;
                res = 0;
                break;

            case download_log:
                download(); // Download log data
                break;

            case set_time:
                time_set(); // Set the time
                break;
        }
    }
}
