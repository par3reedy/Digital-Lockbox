//Patrick Reedy and Oscar Gonzalez, Cal Poly SLO, 4/12/2021
//This header file contains information used to describe the board and KEYPAD
//This specific keypad is formatted in a 4x4 array with 0-9, A-D, #, and *
//Keypad Datasheet: https://www.parallax.com/product/4x4-matrix-membrane-keypad/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define RGB_LED     0x07                            //Pins 2.0-2.2 are dedicated to RGB LED
#define COLSBITS    (BIT4 | BIT5 | BIT6 | BIT7)     //Pins 4-7 are dedicated for COLS inputs
#define ROWSBITS    (BIT0 | BIT1 | BIT2 | BIT3)     //Pins 0-3 are dedicated for ROWS outputs
#define KCOLS       P2                              //Port 2 has a section dedicated for COLS
#define KROWS       P4                              //Port 4 has a section dedicated for ROWS

#define COL1        0x10                            //Column 1 represented as 0001_0000 but occupies pin 2.4
#define COL2        0x20                            //Column 2 represented as 0010_0000 but occupies pin 2.5
#define COL3        0x40                            //Column 3 represented as 0100_0000 but occupies pin 2.6
#define COL4        0x80                            //Column 4 represented as 1000_0000 but occupies pin 2.7

#define ROW1        0x01                            //Row 1 represented as 0000_0001 but occupies pin 4.0
#define ROW2        0x02                            //Row 2 represented as 0000_0010 but occupies pin 4.1
#define ROW3        0x04                            //Row 3 represented as 0000_0100 but occupies pin 4.2
#define ROW4        0x08                            //Row 4 represented as 0000_1000 but occupies pin 4.3

#define BTNA        10                              //All buttons below are given a specific value that can be passed
#define BTNB        11                              // to the LED. LED only operates on bits XXXX_X111 (bits 0-2 on port 2)
#define BTNC        12                              // by pressing button A, 0000_1010 would be read from the keypad, resulting
#define BTND        13                              // as XXXX_X010 for the LED or green low, red high, blue low.
#define BTNSTR      15
#define BTNPND      14
#define BTN0        0
#define BTN1        1
#define BTN2        2
#define BTN3        3
#define BTN4        4
#define BTN5        5
#define BTN6        6
#define BTN7        7
#define BTN8        8
#define BTN9        9
#define BTNMISS     -1


#endif /* KEYPAD_H_ */
