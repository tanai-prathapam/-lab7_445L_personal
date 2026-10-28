/* Lab7main.c
 * This is a C language project that implements ECE445L Lab5.
 * Jonathan Valvano
 * June 29, 2026
 */
// Possible hardware interface
// 2-bit input, positive logic switches, positive logic software
//   bit1 PA28 Voice switch 
//   bit0 PA27 Play switch 

// TLV5616
// pin signal MSPM0   mode
//  1   DIN   PB17   SPI_PICO
//  2   SCLK  PB18   SPII_SCK
//  3   /CS   GND    
//  4   FS    PA8    SPI0_CS0
//  5   AGND         ground
//  6   REF          1.255 V refernce
//  7   OUT          DAC output
//  8   Vdd   +3.3V

#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "../inc/Clock.h"
#include "../TLV5616.h"
#include "../inc/ST7735_SDC.h"
#include "Lab7.h"
#include "Switch.h"
#include "music.h"
#include "mailbox.h"
#include "jacketart.h"
#include "Dump.h"

volatile uint32_t JitterReady = 0;

void (*PeriodicTask)(void);   // user function to be called periodically

#if DEBUG_MODE == 1
int main(void){ // main0 is used to test the DAC interface
  uint32_t n=0;
  __disable_irq(); 
  LaunchPad_Init();
  Clock_Init_HFXT_40_80MHz(0);  // 0.005% accurate running off external crystal oscillator

  ST7735_InitR(INITR_REDTAB); //INITR_REDTAB for AdaFruit, INITR_BLACKTAB for SPI HiLetgo ST7735R
  ST7735_FillScreen(ST7735_BLACK);
  ST7735_SetCursor(0, 0);  
  ST7735_OutString("ECE445L main0\n");
  ST7735_OutString("Ramp output to DAC\n");
  TIMG0->COUNTERREGS.CTRCTL &= ~0x01; // disarm if not using SDC
  TLV5616_Init(0);
  while(1){
    TLV5616_OutNonBlocking(n);
    n = (n+1)&0x0FFF; // 0 to 4095
    Clock_Delay(43);
  }
}
#elif DEBUG_MODE == 2
// *************main1 creates one continuous sin wave
// 12-bit 64-element sine wave
const uint16_t Wave[64] = {
  2048,2244,2438,2629,2813,2991,3159,3317,3462,3594,3711,
  3812,3896,3962,4010,4038,4048,4038,4010,3962,3896,3812,
  3711,3594,3462,3317,3159,2991,2813,2629,2438,2244,2048,
  1852,1658,1467,1283,1105,937,779,634,502,385,284,
  200,134,86,58,48,58,86,134,200,284,385,
  502,634,779,937,1105,1283,1467,1658,1852
}; 
uint32_t Index64;
void OutputSineWave(void){
  TLV5616_OutNonBlocking(Wave[Index64]);
  Index64 = (Index64+1)&0x3F; // 0 to 63
}
int main(void){ // main1 output sine wave to DAC
  __disable_irq(); 

  LaunchPad_Init();
  Clock_Init_HFXT_40_80MHz(0);  // 0.005% accurate running off external crystal oscillator
  Switch_Init();

  ST7735_InitR(INITR_REDTAB); //INITR_REDTAB for AdaFruit, INITR_BLACKTAB for SPI HiLetgo ST7735R
  ST7735_FillScreen(ST7735_BLACK);
  ST7735_SetCursor(0, 0);  
  ST7735_OutString("ECE445L main1\n");
  ST7735_OutString("Sine wave out to DAC\n");
  TIMG0->COUNTERREGS.CTRCTL &= ~0x01; // disarm G0 if not using SDC
  TLV5616_Init(2048);
  Index64 = 0;
  SysTick_InitArm(80000/64,0);
  //SysTick_InitArm(36232,0);
  SysTick->CTRL = 0x07;      // enable SysTick with 80 MHz bus clock and interrupts
  // 64 kHz interrupt, generating 1kHz sine wave
  __enable_irq();
  while(1){
    __WFI();
  }
}
#else
int main(void){ 
  __disable_irq(); 
   // ****ECE445L write this ****
   
  // TIMG0 647 load value with prescale of 27
  // store arrays of uint16 create two macros one get 10 left bits and 6 for the right
  // struct with arrays 16 bit for the note and 16 bit for the delay
  // struct time ; tone

  LaunchPad_Init();
  Clock_Init_HFXT_40_80MHz(0);  // 0.005% accurate running off external crystal oscillator
  // TIMG0->COUNTERREGS.CTRCTL &= ~0x01; // disarm G0 if not using SDC
  ST7735_InitR(INITR_REDTAB); //INITR_REDTAB for AdaFruit, INITR_BLACKTAB for SPI HiLetgo ST7735R
  ST7735_FillScreen(ST7735_BLACK);
  ST7735_SetRotation(2);
  ST7735_DrawBitmap(0, 128, jacketart, 128, 128);
  ST7735_SetCursor(0, 12);
  Switch_Init();
  Debug_Init();
  JitterReady = 0;
  
  ST7735_OutString("ECE445L main\n");
  ST7735_OutString("FFFFF out to DAC\n");
  TLV5616_Init(2048);

  // 64 kHz interrupt, generating 1kHz sine wave
  Song_Init();
  while(1){
    //__WFI();
     if(Switch_PlayPressed()){
      int32_t mix = 0;
      for(uint8_t i = 0; i < NUM_CHANNELS; i ++) {
        // Subtract 128 to make 0 be silence. Without this,
        // the envelope scales the DC level too, and the speaker thumps at every note boundary
        // mix += ((int32_t)Channels[i].currentOutput - 128) * (int32_t)Channels[i].envelopeLevel;
        // mix += Channels[i].currentOutput;
        // int32_t proOutput = Channels[i].currentOutput;
        // int32_t proEnvelope = Channels[i].envelopeLevel;
        mix += (uint32_t)Channels[i].currentOutput * (uint32_t)Channels[i].envelopeLevel;
      }
      // int32_t sample = 2048 + (mix >> MIX_SHIFT);
      int32_t sample = ((mix/5) >> 4);

      if(sample < 0) {
        sample = 0;
      } else if (sample > 4095) {
        sample = 4095;
      }

      // Start this capture about 10 seconds into default-tempo playback.
      if(!JitterReady && MeasurementSongTicks >= 22080){
        Debug_Dump((uint32_t)sample);
      }

      TLV5616_OutNonBlocking((uint32_t)sample);

      if(!JitterReady && DebugCnt == MAXBUF) {
        CalculateJitter();
        JitterReady = 1;
      }
     }

     Switch_SlowSpeed();
     Switch_Restart();
  }
}
#endif

// -------------------      SysTick_Handler    -------------------------------
// Interrupt service routine
// Executed every 12.5ns*(period)
#if DEBUG_MODE == 2
void SysTick_Handler(void){
// ****ECE445L write this ****
  if(Switch_PlayPressed()) OutputSineWave();
}
#endif
