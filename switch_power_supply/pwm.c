/**************************************************************************** 
 * File name :   pwm.c
 * 
 * Author   Date            V   Description
 * SH       22 Dec.2021     1.0 Clean up and add prolog headers     
 ***************************************************************************/

#include <xc.h>
#include <sys/attribs.h>
#include "config.h"

#define RESOL   255

/**************************************************************************** 
 * NAME :   timer3_init
 * 
 * DESCRIPTION :    Initializes timer3 with a resolution of 256
 *                  PWM frequency is FCY/256
 *                  Microstick II:  40000000/256 = 156 250 Hz
 *                  MX3:            80000000/256 = 315 500 Hz
 ***************************************************************************/
void timer3_init( void){
// Initialize and enable Timer3
    T3CONbits.TON = 0; // Disable Timer
    T3CONbits.TCS = 0; // Select internal instruction cycle clock
    T3CONbits.TGATE = 0; // Disable Gated Timer mode
    //    TCKPS<2:0>: Timer Input Clock Prescale Select bits(3)
    //111 = 1:256 prescale value
    //110 = 1:64 prescale value
    //101 = 1:32 prescale value
    //100 = 1:16 prescale value
    //011 = 1:8 prescale value
    //010 = 1:4 prescale value
    //001 = 1:2 prescale value
    //000 = 1:1 prescale value
    //T3CONbits.TCKPS = 0b111; // Select 1:256 Prescaler
    //T3CONbits.TCKPS = 0b110; // Select 1:64 Prescaler
    //T3CONbits.TCKPS = 0b011; // Select 1:8 Prescaler
    T3CONbits.TCKPS = 0b010; // Select 1:4 Prescaler
    //T3CONbits.TCKPS = 0b001; // Select 1:2 Prescaler
    //T3CONbits.TCKPS = 0b000; // Select 1:1 Prescaler
    TMR3 = 0x00; // Clear timer register
    PR3=RESOL; // Load the period value. PR3 = (int)((float)((float)BOARD_FRQ/FREQ_SINE) + 0.5);    
    //__builtin_disable_interrupts();   // disable interrupts
    //IPC3bits.T3IP = 0x01; // Set Timer  Interrupt Priority Level
    //IFS0bits.T3IF = 0; // Clear Timer  Interrupt Flag
    //INTCONbits.MVEC=1;
    //IEC0bits.T3IE = 1; // Enable Timer  interrupt
    // _T3IP = 6; // Enable Timer  interrupt
    //__builtin_enable_interrupts();   // enable interrupts
    T3CONbits.TON = 1; // Start Timer              
} // init


/**************************************************************************** 
 * NAME :   pwm_init
 * 
 * DESCRIPTION :    Initializes the OC module to generate a PWM waveform
 *                  on a pin:
 *                  Microstick II:  pin RPB4
 *                  MX3:            pin RPB14                 
 ***************************************************************************/
void pwm_init( void){
    timer3_init();
#if defined  MX3
    TRISBbits.TRISB14 = 0;    
    RPB14R = 0x0C; // 1100 = OC1
    // disable analog (set pins as digital)
    ANSELBbits.ANSB14 = 0;
#elif defined MICROSTICK_II
    TRISBbits.TRISB4 = 0;    
    RPB4R = 0b0101; // 0101 = OC1
#endif
    OC1CONbits.ON = 0;       // Turn off OC1 while doing setup.
    OC1CONbits.OCM = 6;      // PWM mode on OC1; Fault pin is disabled
    OC1CONbits.OCTSEL = 1;   // Timer3 is the clock source for this Output Compare module
    //OC1CONbits.OCTSEL = 0;   // Timer2 is the clock source for this Output Compare module
    OC1CONbits.ON = 1;       // Start the OC1 module      
	OC1R = OC1RS = 25;  
}

/**************************************************************************** 
 * NAME :   pwm_set( int pwm)
 * 
 * DESCRIPTION :    Sets the PWM value.
 *                  The argument range is 0-255
 *                  0 means 0% duty cycle
 *                  255 means 100% duty cycle
 *                                 
 ***************************************************************************/
void pwm_set( int pwm){
    OC1RS = pwm;
}

