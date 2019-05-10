/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__PIC24E__)
    	#include <p24Exxxx.h>
    #elif defined (__PIC24F__)||defined (__PIC24FK__)
	#include <p24Fxxxx.h>
    #elif defined(__PIC24H__)
	#include <p24Hxxxx.h>
    #endif
#endif

#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <math.h>
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/

#define BRIGHTNESS 60
#define DEG_PER_CYCLE 0.0336

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();

    /* TODO <INSERT USER APPLICATION CODE HERE> */
    
    //turn on LCD lights
    TRISCbits.TRISC5 = 0;
    TRISCbits.TRISC6 = 0;
    TRISCbits.TRISC7 = 0;

    _RP21R = 13;
    _RP22R = 14;
    _RP23R = 15;

    OC1RS = 0x3FF;                  //period
    OC1CON2bits.SYNCSEL = 0x1F;     //self-sync
    OC1CON2bits.OCTRIG = 0;         //sync mode
    OC1CON1bits.OCTSEL = 0b111;     //FOSC/2
    OC1CON1bits.OCM = 0b110;        //edge aligned
    OC1CON2bits.TRIGSTAT = 1;       //manually trigger

    OC2RS = 0x3FF;                  //period
    OC2CON2bits.SYNCSEL = 0x1F;     //self-sync
    OC2CON2bits.OCTRIG = 0;         //sync mode
    OC2CON1bits.OCTSEL = 0b111;     //FOSC/2
    OC2CON1bits.OCM = 0b110;        //edge aligned
    OC2CON2bits.TRIGSTAT = 1;       //manually trigger

    OC3RS = 0x3FF;                  //period
    OC3CON2bits.SYNCSEL = 0x1F;     //self-sync
    OC3CON2bits.OCTRIG = 0;         //sync mode
    OC3CON1bits.OCTSEL = 0b111;     //FOSC/2
    OC3CON1bits.OCM = 0b110;        //edge aligned
    OC3CON2bits.TRIGSTAT = 1;       //manually trigger
    
    uint16_t red, green, blue;
    
    double hue = 0.0;
    double huePrime = 0.0;
    double x = 0.0;
    
    while( 1 ) {
        
        //increase the hue 
        hue += DEG_PER_CYCLE;
        if( hue > 360.0 ) {
            hue = 0.0;
        }
        
        //helps us determine which color is most dominant in the given range
        huePrime = hue / 60;
        
        //in each range, there is a color that is increasing
        x = 1 - fabs( fmod( huePrime, 2 ) - 1 );
        
        if( 0 < huePrime && huePrime < 1 ) {
            red = BRIGHTNESS;
            green = x * BRIGHTNESS;
            blue = 0;
        }
        else if( 1 < huePrime && huePrime < 2 ) {
            red = x * BRIGHTNESS;
            green = BRIGHTNESS;
            blue = 0;
        }
        else if( 2 < huePrime && huePrime < 3 ) {
            red = 0;
            green = BRIGHTNESS;
            blue = x * BRIGHTNESS;
        }
        else if( 3 < huePrime && huePrime < 4 ) {
            red = 0;
            green = x * BRIGHTNESS;
            blue = BRIGHTNESS;
        }
        else if( 4 < huePrime && huePrime < 5 ) {
            red = x * BRIGHTNESS;
            green = 0;
            blue = BRIGHTNESS;
        }
        else if( 5 < huePrime && huePrime < 6 ) {
            red = BRIGHTNESS;
            green = 0;
            blue = x * BRIGHTNESS;
        }
        else { //THIS SHEILD SHOULD NEVER OCCUR!!!
            red = BRIGHTNESS;
            green = BRIGHTNESS;
            blue = BRIGHTNESS;
        }
        
        //sets the leds
        OC1R = red;
        OC2R = green;
        OC3R = blue;
    }
}
