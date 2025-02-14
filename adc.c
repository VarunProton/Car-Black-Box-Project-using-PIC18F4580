/*
 * File:   adc.c
 * Author: varun
 *
 * Created on December 31, 2024, 1:59 PM
 */


#include <xc.h>

// Function to initialize the ADC (Analog to Digital Converter)
void init_adc()
{
    CHS3 = 0;  // Set the ADC channel selection bits for CHS (channel 0)
    CHS2 = 1;
    CHS1 = 0;
    CHS0 = 0;
    
    GO = 0;    // Clear the GO (start conversion) bit
    
    ADON = 1;  // Turn on the ADC module
    
    VCFG1 = 0; // Set the reference voltage source (0: Vss, 1: Vdd)
    VCFG0 = 0; // Set the reference voltage source (0: Vss, 1: Vdd)
    
    PCFG3 = 1; // Set the analog input pins (0: analog, 1: digital)
    PCFG2 = 0;
    PCFG1 = 1;
    PCFG0 = 0;
    
    ADCS2 = 0; // Set the ADC clock source (ADC conversion clock)
    ADCS1 = 1;
    ADCS0 = 0;
    
    ACQT2 = 1; // Set the acquisition time (time to charge the capacitor)
    ACQT1 = 0;
    ACQT0 = 0;
    
    ADFM = 1;  // Set the ADC result format (1: right justified, 0: left justified)
    
    ADRESL = ADRESH = 0x00;  // Clear the ADC result registers
}

// Function to start an ADC conversion and return the result
unsigned short read_adc()
{
    GO = 1;  // Start the ADC conversion by setting the GO bit
    while(GO); // Wait for the conversion to complete (GO will be cleared when done)
    
    // Combine the lower and upper 8 bits of the ADC result
    return ADRESL | ADRESH << 8;
}
