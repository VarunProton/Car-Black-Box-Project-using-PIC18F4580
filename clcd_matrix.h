/* 
 * File:   matrix.h
 * Author: varun
 *
 * Created on December 31, 2024, 1:54 PM
 */

#ifndef MATRIX_H
#define MATRIX_H

#ifdef __cplusplus
extern "C" {
#endif

// Macros for detection levels
#define LEVEL 0 // Detection level 0
#define EDGE 1  // Detection level 1

// CLCD port and control pins
#define CLCD_PORT       PORTD // CLCD data port
#define CLCD_EN         RC2   // CLCD enable pin
#define CLCD_RS         RC1   // CLCD register select pin
#define CLCD_RW         RC0   // CLCD read/write pin
#define CLCD_BUSY       RD7   // CLCD busy flag pin
#define PORT_DIR        TRISD7 // CLCD port direction

// High/Low states
#define HI              1 // High state
#define LO              0 // Low state

// Port direction macros
#define INPUT           0xFF  // Set port direction as input
#define OUTPUT          0x00  // Set port direction as output

// Command types for CLCD
#define DATA_COMMAND        1  // Command for data write
#define INSTRUCTION_COMMAND 0  // Command for instruction write

// Microcontroller clock frequency
#define _XTAL_FREQ      20000000  // Clock frequency set to 20 MHz

// Macros for CLCD line addresses
#define LINE1(x)        (0x80 + (x)) // Line 1 address
#define LINE2(x)        (0xC0 + (x)) // Line 2 address

// CLCD command macros
#define TWO_LINE_5x8_MATRIX_8_BIT   clcd_write(0x38, INSTRUCTION_COMMAND) // 2-line, 5x8 matrix mode
#define CLEAR_DISP_SCREEN           clcd_write(0x01, INSTRUCTION_COMMAND) // Clear display screen
#define CURSOR_HOME                 clcd_write(0x02, INSTRUCTION_COMMAND) // Cursor home position
#define DISP_ON_AND_CURSOR_OFF      clcd_write(0x0C, INSTRUCTION_COMMAND) // Display on, cursor off
#define EIGHT_BIT_MODE              0x33 // Command for 8-bit mode

// Function prototypes
void init_clcd(void);                                 // Initialize CLCD
void clcd_print(const unsigned char *data, unsigned char addr); // Print string on CLCD
void clcd_putch(const unsigned char data, unsigned char addr);  // Print character on CLCD
void clcd_write(unsigned char bit_values, unsigned char control_bit); // Write to CLCD

unsigned char hed[17] = "  Time   GEAR SP"; // Header text
unsigned char time[11] = "00:00:00";        // Time display buffer
unsigned char clock_reg[3];                 // Clock register buffer
unsigned int speed = 0;                     // Speed value
unsigned char speed_disp[3];                // Speed display buffer
unsigned char i = 0;                        // Index variable i
unsigned char j = 0;                        // Index variable j
unsigned char t[17] = "00:00:00        ";   // Temporary buffer
unsigned char bcd[3][4];                    // BCD buffer
signed char k = 0;                          // Index variable k
unsigned char count_1,res;                      // Counter variable
unsigned char f = 0;                        // Flag variable
unsigned char l, addr;                      // Address variables
unsigned char eep_data[10][17];             // EEPROM data buffer

unsigned char gear = 0;                     // Gear value
unsigned char choice = 0;                   // User choice variable
unsigned char menu_c;                       // Menu counter
unsigned char index = 0;                    // Index variable

void save_data();                           // Save data to memory
unsigned char ev[8][3] = {"ON", "GN", "G1", "G2", "G3", "G4", "GR", "C "}; // Event buffer
unsigned char menu_l[4][17] ={ "  view log      ", "  clear log     ", "  download log  ", "  set time log  "}; // Menu options
unsigned char count = 0;                    // General counter
unsigned char flag = 1, flag1 = 1, wait = 0; // Flags for control
unsigned char flag2 = 0; // Flag to indicate first-time read
unsigned char h = 0, m = 0, s = 0, c_f=0, f_c = 0; // Time variables

unsigned char scan_key();                             // Scan single key
unsigned char read_matrix(unsigned char detection);   // Read key from matrix
void init_matrix();                                   // Initialize matrix keypad
void init_config();                                   // General initialization
int my_strcmp(const char *str1, const char *str2);    // String compare function
static void get_time(void);                          // Get current time
void set_config();                                   // Set configurations
void str_eeprom();                                   // Store string in EEPROM

void init_adc();                                     // Initialize ADC
unsigned short read_adc();                           // Read ADC value

void dash_disp();                                    // Display dashboard
void menu_log();                                     // Menu logging
void view();                                        // View logs
void clear();                                       // Clear logs
void download();                                    // Download logs
void time_set();                                    // Set time
static void get_time(void);                         // Fetch current time
void str_eeprom();                                  // Store string in EEPROM

unsigned char getche(void);                         // Get character with echo
void init_uart();                                   // Initialize UART
void puts(unsigned char *str);                     // Output string via UART
unsigned char getch ();                             // Get character
void putch (unsigned char data);                   // Send character via UART
void set();                                        // Set configurations

void write_external_eeprom(unsigned char address, unsigned char data); // Write to external EEPROM
unsigned char read_external_eeprom(unsigned char address); // Read from external EEPROM
unsigned char eep = 0x00;                                  // EEPROM data variable
unsigned char secret[4];                            // Secret code buffer
void set_config();                                  // Set configurations

void init_i2c(void);                                // Initialize I2C
void i2c_start(void);                               // Start I2C communication
void i2c_rep_start(void);                           // Restart I2C communication
void i2c_stop(void);                                // Stop I2C communication
void i2c_write(unsigned char data);                // Write data via I2C
unsigned char i2c_read(void);                      // Read data via I2C

void read_data();                                  // Read data function
void set_time_rtc(unsigned char h, unsigned char m, unsigned char s); // Set RTC time
unsigned char bcd_convertor(unsigned char number); // Convert to BCD format

typedef enum
{
    e_dashboard = 0, // Dashboard screen
    e_main_menu = 1, // Main menu screen
    view_log = 2,    // View log screen
    clear_log = 3,   // Clear log screen
    download_log = 4,// Download log screen
    set_time = 5     // Set time screen
}secreen_menu;

#ifdef __cplusplus
}
#endif

#endif /* MATRIX_H */
