//Patrick Reedy, Cal Poly SLO, 4/12/2021
//This C file gives the structure and functions for the LCD Display used in the digital lockbox.
//LCD Datasheet: https://www.orientdisplay.com/pdf/CharFull/AMC1602C-full.pdf

#include "msp.h"                            //library used for the MSP32 micro controller
#include "LCD.h"                            //header file containing relative board and LCD definitions
#include "string.h"                         //library used for determining string length

//LCD function declarations for linking of LCD files
void lcd_command(uint8_t command);
void lcd_init(void);
void lcd_write_char(uint8_t letter);
void lcd_set_address(uint8_t address);
void lcd_write_string(char string[], uint8_t start_address);

//lcd_init is designed to initialize the LCD display according to the 4-bit interface located
//in the data sheet.
void lcd_init(void){
    //To initialize the LCD we must follow the initializing in the DATASHEET. Page 19
    //Begin by setting up GPIO for all LCD pins
    LCDDATAPORT->SEL0 &= ~(DATAPINS);       //Data pins SEL0 set to 0 for GPIO
    LCDDATAPORT->SEL1 &= ~(DATAPINS);       //Data pins SEL1 set to 0
    LCDDATAPORT->DIR |= (DATAPINS);         //Data pins set as output pins
    LCDDATAPORT->OUT &= ~(DATAPINS);        //Initialize output as 0
    LCDCONTROLPORT->SEL0 &= ~(CONTROLPINS); //Control pins SEL0 set to 0 for GPIO
    LCDCONTROLPORT->SEL1 &= ~(CONTROLPINS); //Control pins SEL1 set to 0
    LCDCONTROLPORT->DIR |= (CONTROLPINS);   //Control pins set as output pins
    LCDCONTROLPORT->OUT &= ~(CONTROLPINS);  //Initialize output as 0
    __delay_us(40000);                      //delay for 40ms

    //Now we must follow the minimum timing values to ensure operation.
    LCDCONTROLPORT->OUT &= ~(RS | RW);      //Set RS and RW to 0
    LCDDATAPORT->OUT |= (BIT4 | BIT5);      //Set data pins 4 and 5 to 1 (0011)
    LCDCONTROLPORT->OUT |= E;               //Set Enable to high
    __delay_us(1);                          //Delay for 1us (must be a delay greater than 140ns)
    LCDCONTROLPORT->OUT &= ~E;              //Set Enable low
    __delay_us(39);                         //Delay for 39us
    lcd_command(FUNCTION_SET);              //Set how the display works
    lcd_command(FUNCTION_SET);
    lcd_command(DISPLAY_ON);                //Display on, cursor off, blink off
    lcd_command(CLEAR_DISPLAY);             //Clear the display
    lcd_command(0x06);                      //Increment cursor, no shift
}

//lcd_command is designed to take in an 8-bit command and send that signal in 4-bit interface format
//to carry out a command. The timings used for this command are found directly from the datasheet.
void lcd_command(uint8_t command){
    uint8_t upper = command & 0xF0;         //set upper nibble
    uint8_t lower = command << 4;           //set lower nibble
    LCDDATAPORT->OUT &= ~(DATAPINS);        //Clear data pins
    LCDDATAPORT->OUT |= upper;              //Set data pins to upper nibble
    LCDCONTROLPORT->OUT |= E;               //Set Enable high
    __delay_us(1);                          //Delay for at least 140ns
    LCDCONTROLPORT->OUT &= ~E;              //Set Enable low
    __delay_us(2);                          //Delay for at least 1200ns
    LCDDATAPORT->OUT &= ~(DATAPINS);        //Clear data pins
    LCDDATAPORT->OUT |= lower;              //Set data pins to lower nibble
    LCDCONTROLPORT->OUT |= E;               //Set Enable High
    __delay_us(1);                          //Delay for at least 140ns
    LCDCONTROLPORT->OUT &= ~E;              //Set Enable low
    LCDDATAPORT->OUT &= ~(DATAPINS);        //Clear data pins
    if (command == 0x01 | command == 0x02){
        __delay_us(1600);                   //Delay for at least 1.53ms
    }
    else {
        __delay_us(39);                     //Delay for 39us
    }
}

//lcd_set_address is designed to set the address of the DDRAM. This function is utilized for the project
//as a method to write to specific parts of the LCD screen.
void lcd_set_address(uint8_t address){
    LCDCONTROLPORT->OUT &= ~RS;             //RS low
    LCDCONTROLPORT->OUT &= ~RW;             //RW low
    address |= BIT7;                        //Bit 7 must remain high to set the address
    lcd_command(address);                   //writing location set
}

//lcd_write_char is designed to pass a 8-bit instruction that represents a character that is determined
//by the Character Generator ROM Pattern on page 14 of the datasheet.
void lcd_write_char(uint8_t letter){
    LCDCONTROLPORT->OUT |= RS;              //RS high to enable writing
    LCDCONTROLPORT->OUT &= ~RW;             //RW low for writing
    lcd_command(letter);                    //write the letter to the DDRAM
    LCDCONTROLPORT->OUT &= ~RS;             //Reset RS for use with other functions
}

//lcd_write_string is designed to take a string of characters and write each character from left to right
//on the LCD screen. This function makes use of the string.h library.
void lcd_write_string(char string[], uint8_t start_address){
    uint32_t i = 0;                         //initialize counting variable
    lcd_set_address(start_address);         //set the address location to write
    for (i=0;i<strlen(string);i++){         //run for the length of the string
        lcd_write_char(string[i]);          //write each character of the string
    }
}
