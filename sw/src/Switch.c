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
#include "music.h"
#include "Lab7.h"
  // ****ECE445L write this ****
 
#define PB1MASK 2
#define PB4MASK 16
#define PB2MASK 4


//---------------------Switch_Init---------------------
// initialize switch interface
// Input: none
// Output: none 
void Switch_Init(void){ 
   IOMUX->SECCFG.PINCM[PB1INDEX] = (uint32_t) 0x00040081; // input, no pull-up
   IOMUX->SECCFG.PINCM[PB4INDEX] = (uint32_t) 0x00040081; // input, no pull-up
   IOMUX->SECCFG.PINCM[PB2INDEX] = (uint32_t) 0x00040081; // input, no pull-up
}

//---------------------Switch_Play---------------------
// read the play/pause switch
// Input: none
// Output: false the Play switch not pressed
//         true the Play switch is pressed
int Switch_Play(void){ 
   uint32_t in = (GPIOB->DIN31_0 & (PB1MASK));
   return (in > 0 ? 1 : 0);
}

//---------------------Switch_PlaySpeed---------------------
// read the speed switch
// Input: none
// Output: false the Play switch not pressed
//         true the Play switch is pressed
int Switch_PlaySpeed(void){ 
   uint32_t in = (GPIOB->DIN31_0 & (PB4MASK));
   return (in > 0 ? 1 : 0);
}

//---------------------Switch_PlayRestart---------------------
// read the speed switch
// Input: none
// Output: false the Play switch not pressed
//         true the Play switch is pressed
int Switch_PlayRestart(void){ 
   uint32_t in = (GPIOB->DIN31_0 & (PB2MASK));
   return (in > 0 ? 1 : 0);
}

//---------------------Switch_PlayPressed---------------------
// edge detection play switch
// Input: none
// Output: false the Play switch not pressed and released
//         true the Play switch is pressed and released
int Switch_PlayPressed(void){
   static int lastSample = 0;
   static int stable = 0; // debounced state
   int now = Switch_Play();

   if(now == lastSample) { // contacts have settled
      if(now != stable) {
         stable = now;
         if(now) {
            #if DEBUG_MODE == 0
               Song_Toggle(); // 0 -> 1 transition only
            #else
               SongPlaying ^= 1; // 0 -> 1 transition only
            #endif
         }
      }
   }
   lastSample = now;
   return SongPlaying;
}

//---------------------Switch_SlowSpeed---------------------
// read the speed switch
// Input: none
// Output: none
void Switch_SlowSpeed(void){
   static int toggleSpeed = 0;
   static int lastSampleSpeed = 0;
   static int stableSpeed = 0; // debounced state
   int now = Switch_PlaySpeed();

   if(now == lastSampleSpeed) { // contacts have settled
      if(now != stableSpeed) {
         stableSpeed = now;
         if(now) {
            toggleSpeed ^= 1;
            #if DEBUG_MODE == 0
               if(toggleSpeed){
                  Song_HalfSpeed(); // 0 -> 1 transition only
               } else {
                  Song_FullSpeed();
               }
            #elif DEBUG_MODE == 2
               if(toggleSpeed){
                  SysTick_InitArm(80000/32,0); // 0 -> 1 transition only
               } else {
                  SysTick_InitArm(80000/64,0);
               }
            #endif
         }
      }
   }
   lastSampleSpeed = now;
}

//---------------------Switch_Restart---------------------
// read the restart switch
// Input: none
// Output: none
void Switch_Restart(void){
   static int lastSampleRestart = 0;
   static int stableRestart = 0; // debounced state
   int now = Switch_PlayRestart();

   if(now == lastSampleRestart) { // contacts have settled
      if(now != stableRestart) {
         stableRestart = now;
         if(now) {
            #if DEBUG_MODE == 0
               Song_Pause();
               channelInit();
               if(SongPlaying) {
                  Song_Play();
               }
            #elif DEBUG_MODE == 2
               // do nothing
            #endif
         }
      }
   }
   lastSampleRestart = now;
}