/* Lab7main.c
 * This is a C language project that implements ECE445L Lab5.
 * Jonathan Valvano
 * June 29, 2026
 */
// Possible hardware interface
// 2-bit input, positive logic switches, positive logic software
//   bit1 PA28 Voice switch 
//   bit0 PA27 Play switch 


#include <ti/devices/msp/msp.h>
#include "../inc/LaunchPad.h"
#include "../inc/Clock.h"
#include "../inc/ST7735_SDC.h"
#include "Lab7.h"
#include "Switch.h"
#include "Mister.h"
#include "Dump.h"

volatile uint32_t JitterReady = 0;

void (*PeriodicTask)(void);   // user function to be called periodically

void SysTick_InitArm(uint32_t period, uint32_t priority){
  SysTick->CTRL = 0x00;      // disable SysTick during setup
  SysTick->LOAD = period-1;  // reload value
  SCB->SHP[1] = (SCB->SHP[1]&(~0xC0000000))|(priority<<30); // priority 2
  SysTick->VAL = 0;          // any write to VAL clears COUNT and sets VAL equal to LOAD
  SysTick->CTRL = 0x07;      // enable SysTick with 80 MHz bus clock and interrupts
}

#if DEBUG_MODE == 2
// MISTER TESTER
int main(void){
  __disable_irq(); 
  LaunchPad_Init();
  Clock_Init_HFXT_40_80MHz(0);  // 0.005% accurate running off external crystal oscillator
  Mister_Init();
  __enable_irq();

  while(1){
    Mister_On();
    Mister_Off();
  }
}
#elif DEBUG_MODE == 3
// MOTOR TEST
int main(void){
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
#elif DEBUG_MODE == 4
// Barcode/RFID Test
int main(void){
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
#elif DEBUG_MODE == 0
// Master MSPM0
int main(void){
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
#else
int main(void){ 
  // Slave MSPM0
  __disable_irq(); 
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
  // Switch_Init();
  // Debug_Init();
  // JitterReady = 0;
  
  ST7735_OutString("ECE445L Lab 7 main\n");
  
}
#endif

// -------------------      SysTick_Handler    -------------------------------
// Interrupt service routine
// Executed every 12.5ns*(period)
#if DEBUG_MODE == 2
void SysTick_Handler(void){
}
#endif
