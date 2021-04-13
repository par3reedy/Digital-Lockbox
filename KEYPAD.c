//Patrick Reedy and Oscar Gonzalez, Cal Poly SLO, 4/12/2021
//This c file contains functions used to describe the board and KEYPAD
//This specific keypad is formatted in a 4x4 array with 0-9, A-D, #, and *
//Keypad Datasheet: https://www.parallax.com/product/4x4-matrix-membrane-keypad/
//An LED on the MSP432 board is used to represent button presses.
//           GRB
// LED:XXXX_X111, the LED uses pins 0-2 on port 2 to configure its color based on
// standard RGB format.

#include "msp.h"
#include "KEYPAD.h"

//keypad_init is used to initialize the keypad's pins to allow information to be sent and read from
// the keypad. In this code we are using the COLS and pins to read from, whereas the ROWS are used
// to send a voltage value.
void keypad_init(void){
    //COLS on pins 2.4-2.7
    //COLS are control dimension
    KCOLS->SEL0 &= ~(COLSBITS);                             //set sel0 to 0 (GPIO)
    KCOLS->SEL1 &= ~(COLSBITS);                             //set sel1 to 0
    KCOLS->DIR &= ~(COLSBITS);                              //set COLS as inputs
    KCOLS->REN |= (COLSBITS);                               //enable pull resistor
    KCOLS->OUT &= ~(COLSBITS);                              //set COLS out to 0 for pull down resistor

    //ROWS on pins 4.0-4.3
    //ROWS are output dimension
    KROWS->SEL0 &= ~(ROWSBITS);                             //set sel0 to 0 (GPIO)
    KROWS->SEL1 &= ~(ROWSBITS);                             //set sel1 to 0
    KROWS->DIR |= (ROWSBITS);                               //set ROWS as outputs
    KROWS->REN &= ~(ROWSBITS);                              //disable pull resistor (does not matter for output GPIO)
    KROWS->OUT |= (ROWSBITS);                               //set COLS out to 1 for output high
}

//get_key is used to check if a button is pressed and if one is pressed then determine the button that was pressed
// and then send that cols and rows values to a decode function. The keypad works off the idea that if a ROW is
// set high, and a button is pressed the COL corresponding to the press will send a voltage back to the MSP432.
char get_key(void){
    char cols, rows;                                        //initialize ROWS and COLS
    cols = (P2->IN & ~(ROWSBITS));                          //read only COLS pins to detect a button press
    if (cols != 0){                                         //detect a button press
        KROWS->OUT &= ~(ROWSBITS);                          //set out to 0 to set all ROWS low
        rows = 1;                                           //set row starting point
        while(1){                                           //always run until a button is found or missed
            KROWS->OUT |= rows;                             //set current ROW to high
            __delay_cycles(25);                             //delay for button setting
            cols = (P2->IN & ~(ROWSBITS));                  //read only COLS pins to detect a button press
            if (cols != 0){                                 //detect a button press
                KROWS->OUT |= (ROWSBITS);                   //set out to 0 to set all ROWS high
                return decode_keypad(cols,rows);            //return the key pressed
            }
            else{
                rows <<= 1;                                 //increment the rows
                if (rows > 0x08){                           //if the rows exceed the amount on the keypad
                    KROWS->OUT |= (ROWSBITS);               //set out to 0 to set all ROWS high
                    return -1;                              //button press missed
                }
            }
        }
    }
    else{
        return -1;                                          //no button was pressed
    }
}

//decode_keypad is a function that is hardcoded to receive a row value and a column value and then determine the
// corresponding button that was pressed. Depending on similar keypads these buttons could be different.
char decode_keypad(char cols, char rows){
    switch(rows){
        case ROW1:                                          //row 1
            if (cols == COL1) return BTND;                  //button D
            else if (cols == COL2) return BTNPND;           //button #
            else if (cols == COL3) return BTN0;             //button 0
            else if (cols == COL4) return BTNSTR;           //button *
            else return BTNMISS;                            //button missed
        case ROW2:
            if (cols == COL1) return BTNC;                  //button C
            else if (cols == COL2) return BTN9;             //button 9
            else if (cols == COL3) return BTN8;             //button 8
            else if (cols == COL4) return BTN7;             //button 7
            else return BTNMISS;
        case ROW3:
            if (cols == COL1) return 11;                    //button B
            else if (cols == COL2) return 6;                //button 6
            else if (cols == COL3) return 5;                //button 5
            else if (cols == COL4) return 4;                //button 4
            else return BTNMISS;
        case ROW4:
            if (cols == COL1) return BTNA;                  //button A
            else if (cols == COL2) return BTN3;             //button 3
            else if (cols == COL3) return BTN2;             //button 2
            else if (cols == COL4) return BTN1;             //button 1
            else return BTNMISS;
        default:
            return BTNMISS;                                 //button missed
    }
}
