//Patrick Reedy and Oscar Gonzalez, Cal Poly SLO, 4/12/2021
//This header file contains information used to describe the board and LCD

#ifndef LCD_H_
#define LCD_H_

#define RS BIT5                                             //RS control pin set as 5th bit of port
#define RW BIT6                                             //Read write pin
#define E  BIT7                                             //Enable pin

#define LCDCONTROLPORT  P3                                  //Port 3, Pins 3.5-3.7
#define LCDDATAPORT     P2                                  //Port 2, Pins 2.4-2.7
#define DATAPINS        (BIT4 | BIT5 | BIT6 | BIT7)         //Pins 4-7 used for DATA values
#define CONTROLPINS     (RS | RW | E)                       //Pins RS RW E used to control functions
#define DDADDRESS       0x7F                                //Address for DDRAM at bits 0111_1111
#define NEWLINE         0x40                                //Address extension for second line of LCD

//Instructions, Located on Page 15
#define CLEAR_DISPLAY   0x01                                //Clear the Display
#define RETURN_HOME     0x02                                //Return Home
#define DISPLAY_ON      0x0C                                //Display on
#define CURSOR_ON       0x0A                                //Cursor on
#define CURSOR_BLINK    0x09                                //Cursor blink on
#define FUNCTION_SET1   0x30                                //Set data length of interface
#define FUNCTION_SET2   0x28                                //Specific to this LCD (4-bit mode, 2 line, 5x8 font)
#define ENTRY_MODE_SET  0x06                                //Assign cursor direction and no shoft of display

//Delay definition
#define CPU_FREQ 3000000
//coverting the clock frequency and delay_cycles to provide time in microseconds rather than cycles
#define __delay_us(t_us) (__delay_cycles((((uint64_t)t_us)*CPU_FREQ) / 1000000))

#endif /* LCD_H_ */
