/*
 * File:   test.c
 * Author: Lorens
 *
 * Created on April 19, 2024, 11:06 AM
 */


#include "config.h"

unsigned int millis(); 
volatile unsigned int milli = 0;
volatile unsigned int curr_time = 0;
volatile unsigned int prev_time = 0;
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
    OPTION_REGbits.PS =2;
    INTCONbits.T0IF = 0;
    INTCONbits.T0IE = 1;
    INTCONbits.GIE = 1;
    counter();
    
    return;
}

void counter() {
   while(1){
        PORTB = TMR0;
        
        // this is like a clock pulse where every transition happens in 1000ms interval
        // as every increment from the tmr0 until it overflows, it will generate an interrupt incrementing milli
        curr_time = millis();
        if((curr_time - prev_time) >= 1000 ){ // where every 1000ms interval from between curr_time and prev_time
            prev_time = curr_time;
            //operation....
        }
    }
}


unsigned int millis(){
    return milli;
}

void __interrupt() ISR() {
    if(INTCONbits.T0IF){
        TMR0 = 6;
        milli++;
        INTCONbits.T0IF = 0;
    }
}