/*
 * File:   matrix.c
 * Author: varun
 *
 * Created on December 31, 2024, 1:52 PM
 */


#include <xc.h>
#include "clcd_matrix.h"

// Function to scan a single key from the keypad
unsigned char scan_key()
{
    RB5 = 0;             // Activate first row (RB5 connected to the first row of keypad)
    RB6 = RB7 = 1;       // Deactivate other rows (RB6, RB7 connected to other rows)

    // Check if a key in the first column (RB1-RB4) is pressed
    if (RB1 == 0)        // Check if key in column 1 is pressed
        return 1;        // Return key code for the pressed key
    
    if (RB2 == 0)        // Check if key in column 2 is pressed
        return 4;        // Return key code for the pressed key
    
    if (RB3 == 0)        // Check if key in column 3 is pressed
        return 7;        // Return key code for the pressed key
    
    if (RB4 == 0)        // Check if key in column 4 is pressed
        return 10;       // Return key code for the pressed key

    RB6 = 0;             // Activate second row (RB6 connected to second row of keypad)
    RB5 = RB7 = 1;       // Deactivate other rows

    // Check if a key in the second column (RB1-RB4) is pressed
    if (RB1 == 0)        // Check if key in column 1 is pressed
        return 2;        // Return key code for the pressed key
    
    if (RB2 == 0)        // Check if key in column 2 is pressed
        return 5;        // Return key code for the pressed key
    
    if (RB3 == 0)        // Check if key in column 3 is pressed
        return 8;        // Return key code for the pressed key
    
    if (RB4 == 0)        // Check if key in column 4 is pressed
        return 11;       // Return key code for the pressed key
    
    RB7 = 0;             // Activate third row (RB7 connected to third row of keypad)
    RB5 = RB6 = 1;       // Deactivate other rows

    // Check if a key in the third column (RB1-RB4) is pressed
    if (RB1 == 0)        // Check if key in column 1 is pressed
        return 3;        // Return key code for the pressed key

    if (RB2 == 0)        // Check if key in column 2 is pressed
        return 6;        // Return key code for the pressed key

    if (RB3 == 0)        // Check if key in column 3 is pressed
        return 9;        // Return key code for the pressed key

    if (RB4 == 0)        // Check if key in column 4 is pressed
        return 12;       // Return key code for the pressed key

    return 0xFF;         // Return 0xFF if no key is pressed
}

// Function to read key press from the matrix keypad
// detection: 0 for level detection, 1 for edge detection
unsigned char read_matrix(unsigned char detection)
{
    static unsigned char once = 1;  // Flag for edge detection (to avoid multiple detections for the same key)
    unsigned char key = scan_key(); // Scan the keypad for a pressed key

    if (detection == LEVEL)  // Level detection
    {
        return key;          // Return the detected key (constant detection)
    }
    else if (detection == EDGE)  // Edge detection
    {
        if (key != 0xFF && once)  // If a key is pressed and not already detected
        {
            once = 0;         // Set flag to indicate key press is processed
            return key;       // Return the detected key
        }
        else if (key == 0xFF) // If no key is pressed
        {
            once = 1;         // Reset the flag for the next key press
        }
    }
    return 0xFF;              // Return 0xFF if no new key press is detected
}
