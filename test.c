/*
 * File:   test.c
 * Author: Lorens
 *
 * Created on April 19, 2024, 11:06 AM
 */


#include "config.h"

void counter();

void main(void) {
    TRISA = 0x00;
    TRISB = 0x00;
    PORTB = 0x00;
    PORTA = 0x00;
    
    // set T0CS to
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.T0SE = 0;
    OPTION_REGbits.PSA = 0;
    
    // will have 4 transitions to increment
    OPTION_REGbits.PS = 7;
    INTCONbits.T0IF = 0;
    INTCONbits.T0IE = 1;
    INTCONbits.GIE = 1;
    counter();
    
    return;
}

void counter() {
   while(1){
        PORTB = TMR0;
    }
}

void __interrupt() ISR() {
    if(INTCONbits.T0IF){
        PORTA++;
        INTCONbits.T0IF = 0;
    }
}