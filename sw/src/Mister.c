// Mister on Slave MSPM0 PA1

#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "../inc/Clock.h"

#define PA1_MASK 0x02

#define MISTER_PRESS_MS 100
#define MISTER_RELEASE_MS 500

uint8_t mister_on = 0;

//---------------------Mister_Init---------------------
// initialize mister interface
// Input: none
// Output: none 
void Mister_Init(void){ 
    // PA1 output
    GPIOA->DOECLR31_0 = PA1_MASK; // high impedance
    GPIOA->DOESET31_0 = PA1_MASK; // grounded
    IOMUX->SECCFG.PINCM[PA1INDEX] = 0x81;
    mister_on = 0;
}

//---------------------Mister_Press_Button---------------------
// simulates a button press, so the on-board chip recognizes it
// Input: none
// Output: none 
void Mister_Press_Button(void) {
    GPIOA->DOESET31_0 = PA1_MASK; // grounded
    Clock_Delay1ms(MISTER_PRESS_MS);

    GPIOA->DOECLR31_0 = PA1_MASK; // high impedance
    Clock_Delay1ms(MISTER_RELEASE_MS);
}

//---------------------Mister_On---------------------
// turn on mister
// Input: none
// Output: none 
void Mister_On(void){
    // turn on mode
    if(mister_on) return;

    Mister_Press_Button();
    mister_on = 1;
    
}

//---------------------Mister_Off---------------------
// turn off mister
// Input: none
// Output: none 
void Mister_Off(void){
    // intermediate mode
    if(!mister_on) return;

    Mister_Press_Button();
    Mister_Press_Button();
    mister_on = 0;
    
}
