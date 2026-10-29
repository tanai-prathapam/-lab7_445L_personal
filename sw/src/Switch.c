// File **********Switch.c***********
// Lab7
// Programs to interface with Switch buttons   
// ECE445L Fall 2026
//    Jonathan W. Valvano 6/29/26
// 2-bit input, positive logic switches, positive logic software
// define your hardware interface
// bit1 PA28 Voice switch 
// bit0 PA27 Play switch 


#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
 
#define PB1MASK 2
#define PB4MASK 16
#define PB2MASK 4


//---------------------Switch_Init---------------------
// initialize switch interface
// Input: none
// Output: none 
void Switch_Init(void){ 
   //IOMUX->SECCFG.PINCM[PB1INDEX] = (uint32_t) 0x00040081; // input, no pull-up
   //IOMUX->SECCFG.PINCM[PB4INDEX] = (uint32_t) 0x00040081; // input, no pull-up
   //IOMUX->SECCFG.PINCM[PB2INDEX] = (uint32_t) 0x00040081; // input, no pull-up
}

//---------------------Switch_Play---------------------
// read the play/pause switch
// Input: none
// Output: false the Play switch not pressed
//         true the Play switch is pressed
int Switch_Play(void){ 
  // uint32_t in = (GPIOB->DIN31_0 & (PB1MASK));
   return 0;
}
