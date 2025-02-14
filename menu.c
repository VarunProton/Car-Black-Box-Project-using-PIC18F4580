/*
 * File:   menu.c
 * Author: varun
 *
 * Created on December 31, 2024, 5:55 PM
 */


#include <xc.h>
#include "clcd_matrix.h"
#include "ds1307.h"

extern char temp;

void menu_log(void) {
    if (flag) {
        if (gear == 2) { // Gear value indicates downward menu navigation
            gear = 0; // Reset gear
            if (j < 1) {
                j++; // Move to the next item in the menu
            } else if (j == 1 && i < 2) {
                i++; // Move to the next page in the menu
            }
            CLEAR_DISP_SCREEN; // Clear the display screen
        } else if (gear == 1) { // Gear value indicates upward menu navigation
            gear = 0; // Reset gear
            if (j > 0) {
                j--; // Move to the previous item in the menu
            } else if (j == 0 && i > 0) {
                i--; // Move to the previous page in the menu
            }
            CLEAR_DISP_SCREEN; // Clear the display screen
        }

        if (j == 0) {
            clcd_putch('*', LINE1(0)); // Highlight the first menu item
        } else if (j == 1) {
            clcd_putch('*', LINE2(0)); // Highlight the second menu item
        }

        clcd_print(menu_l[i], LINE1(1));     // Print the first menu line
        clcd_print(menu_l[i + 1], LINE2(1)); // Print the second menu line
    }

    if (gear == 11 && flag == 1) { // Gear value 11 selects the menu item
        CLEAR_DISP_SCREEN; // Clear the display screen
        if (j == 0 && i == 0) {
            choice = 2; // Assign choice for the first menu item
        } else if ((i == 0 && j == 1) || (i == 1 && j == 0)) {
            choice = 3; // Assign choice for the second menu item
        } else if ((i == 1 && j == 1) || (j == 0 && i == 2)) {
            choice = 4; // Assign choice for the third menu item
        } else if (j == 1 && i == 2) {
            choice = 5; // Assign choice for the fourth menu item
        }
    }

    if (gear == 12 && flag == 1) { // Gear value 12 exits the menu
        choice = 0; // Reset choice
    }

    if (flag == 0) { // Increment flag on first execution
        flag++;
    }
}
