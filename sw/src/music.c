// File **********music.c***********
// Programs to play pre-programmed music and respond to switch
// inputs. MSPM0
// EE445L Fall 2026
//    Jonathan W. Valvano 6/28/26

// the 64 comes from the length of the sine wave table
// Bus cycle runs at 80MHz
// freq =80,000,000/64/Period = 1,250,000/Period

#include <stdint.h>
#include <ti/devices/msp/msp.h>
#include "Switch.h"
#include "../inc/MCP4921.h"
#include "../inc/Timer.h"
#include "../inc/Clock.h"
#include "Lab7.h"
#include "music.h"
#include "mailbox.h"
#include "piano256-data.h"
#include "Dump.h"

#define WAVE_STEP 2 // Advance N samples per interrupt; scale timer period by N to preserve pitch ; 1 is normal
#define NOTE_FADE_TICKS 32

// 0=SysTick, 1=TIMA0, 2=TIMA1,
// 3=TIMG6, 4=TIMG7, 5=TIMG12
volatile uint32_t ISRMaxTicks[6] = {0};
volatile uint32_t MeasurementSongTicks = 0;

volatile uint8_t SongPlaying;

volatile AudioChannel_t Channels[NUM_CHANNELS];
// IMASK registers of each channel's timer in case of pause/play.
volatile uint8_t savedChannelStatus[NUM_CHANNELS];

void SysTick_InitArm(uint32_t period, uint32_t priority){
  SysTick->CTRL = 0x00;      // disable SysTick during setup
  SysTick->LOAD = period-1;  // reload value
  SCB->SHP[1] = (SCB->SHP[1]&(~0xC0000000))|(priority<<30); // priority 2
  SysTick->VAL = 0;          // any write to VAL clears COUNT and sets VAL equal to LOAD
  SysTick->CTRL = 0x07;      // enable SysTick with 80 MHz bus clock and interrupts
}

void channelInit(void){
  #if FFFFF_FULL_MODE
  // Channel 0
  Channels[0].Timer = TIMA0;
  Channels[0].noteData = fffffCh0;
  Channels[0].noteIncrement = 0;
  Channels[0].noteProgress = 13440;
  Channels[0].isDelay = 1;
  Channels[0].currentOutput = 0;
  // Channel 1
  Channels[1].Timer = TIMA1;
  Channels[1].noteData = fffffCh1;
  Channels[1].noteIncrement = 0;
  Channels[1].noteProgress = 11520;
  Channels[1].isDelay = 1;
  Channels[1].currentOutput = 0;
  // Channel 2
  Channels[2].Timer = TIMG6;
  Channels[2].noteData = fffffCh2;
  Channels[2].noteIncrement = 0;
  Channels[2].noteProgress = 7680;
  Channels[2].isDelay = 1;
  Channels[2].currentOutput = 0;
  // Channel 3
  Channels[3].Timer = TIMG7;
  Channels[3].noteData = fffffCh3;
  Channels[3].noteIncrement = 0;
  Channels[3].noteProgress = 3840;
  Channels[3].isDelay = 1;
  Channels[3].currentOutput = 0;
  // Channel 4
  Channels[4].Timer = TIMG12;
  Channels[4].noteData = fffffCh4;
  Channels[4].noteIncrement = 0;
  Channels[4].noteProgress = 0;
  Channels[4].isDelay = 1;
  Channels[4].currentOutput = 0;
  #else
  // Channel 0
  Channels[0].Timer = TIMA0;
  Channels[0].noteData = fffffLeft;
  Channels[0].noteIncrement = 0;
  Channels[0].noteProgress = 0;
  Channels[0].isDelay = 1;
  Channels[0].currentOutput = 0;
  // Channel 1
  Channels[1].Timer = TIMA1;
  Channels[1].noteData = fffffRight;
  Channels[1].noteIncrement = 0;
  Channels[1].noteProgress = 3840;
  Channels[1].isDelay = 1;
  Channels[1].currentOutput = 0;
  #endif
  for(uint8_t i = 0; i < NUM_CHANNELS; i++){
    Channels[i].Timer->CPU_INT.IMASK = 0;
    Channels[i].currentOutput = 128;
    Channels[i].envelopeLevel = 0;
  }
}
void Song_Init2(void){
  SysTick_InitArm(36232, 0);
}
void Song_Init(void){
  __disable_irq();
  // Initialize channel timers. Each timer starts out disarmed. 
  TimerA0_IntArm(1000, 1, 1);
  TIMA0->CPU_INT.IMASK = 0;
  TimerA1_IntArm(1000, 1, 1);
  TIMA1->CPU_INT.IMASK = 0;
  #if FFFFF_FULL_MODE
  TimerG6_IntArm(1000, 1, 1);
  TIMG6->CPU_INT.IMASK = 0;
  TimerG7_IntArm(1000, 1, 1);
  TIMG7->CPU_INT.IMASK = 0;
  TimerG12_IntArm(0, 1);
  TIMG12->CPU_INT.IMASK = 0;
  #endif
  channelInit();
  // 8e7 counts/sec * 60 secs/min / 276 beats/min / 480 ticks/beat ~= 36232 counts/tick
  SysTick_InitArm(36232, 0);
  SongPlaying = 1;
  __enable_irq();
}

void Song_Pause(void){
  SysTick->CTRL = 0x00; // disable SysTick
  for(uint8_t i = 0; i < NUM_CHANNELS; i++){
    // save current timer state
    savedChannelStatus[i] = Channels[i].Timer->CPU_INT.IMASK; 
    // disarm timer interrupts
    Channels[i].Timer->CPU_INT.IMASK = 0;
  }
}

void Song_Play(void){
  for(uint8_t i = 0; i < NUM_CHANNELS; i++){
    // load current timer state
    Channels[i].Timer->CPU_INT.IMASK = savedChannelStatus[i]; 
  }
  SysTick->CTRL = 0x07; // enable SysTick with 80 MHz bus clock and interrupts 
}

void Song_Toggle(void){
  if(SongPlaying) {
    Song_Pause();
    SongPlaying = 0;
  } else {
    Song_Play();
    SongPlaying = 1;
  }
}

#if DEBUG_MODE != 2
void SysTick_Handler(void){
// ****ECE445L write this ****
  // if still 0 after iterating through all channels, playback is finished
  GPIOB->DOUTSET31_0 = SYS_MASK;  // ISR begins.
  uint32_t start = TIMG8->COUNTERREGS.CTR;
  MeasurementSongTicks++;

  static uint32_t restartTicks = 0;

  if(restartTicks != 0){
    restartTicks--;

    if(restartTicks == 0){
      channelInit();
    }

    // Record this short invocation before returning.
    uint32_t elapsed =
        (start - TIMG8->COUNTERREGS.CTR) & 0xFFFF;

    if(elapsed > ISRMaxTicks[0]){
      ISRMaxTicks[0] = elapsed;
    }
    GPIOB->DOUTCLR31_0 = SYS_MASK;
    return;
  }

  uint8_t stillPlaying = 0;
  for(uint8_t i = 0; i < NUM_CHANNELS; i++){

    // finish expired states. A zero length gap or note should advance to the next state
    while((Channels[i].noteProgress <= 0) && (Channels[i].noteData->counterLoadVal != 0)){
      if(Channels[i].isDelay ^= 0x01){
        // Note finished... advance to the next note's gap
        // now in next note's pre-note delay, so must advance note
        Channels[i].envelopeLevel = 0;
        Channels[i].noteProgress = (++(Channels[i].noteData))->prepauseDuration;
        // disable channel timer
        Channels[i].Timer->CPU_INT.IMASK = 0;
      }else{
        // Gap finished...begin the current note
        // pre-note delay ended, now playing note proper
        Channels[i].noteProgress = Channels[i].noteData->notePauseDuration;
        // Envelope time starts here actually when the note starts
        Channels[i].noteIncrement = 0;
        Channels[i].Timer->COUNTERREGS.LOAD = WAVE_STEP * ((Channels[i].noteData->counterLoadVal) + 1) - 1; // WAVE_STEP times as many timer counts between interrupts
        Channels[i].Timer->CPU_INT.IMASK = 1;
      }
    }

    // This channel reached the end of its song.
    if(!(Channels[i].noteData->counterLoadVal)) {
      Channels[i].Timer->CPU_INT.IMASK = 0;
      Channels[i].envelopeLevel = 0;
      continue;
    }

    stillPlaying = 1;

    Channels[i].noteProgress--;

    uint32_t level = 0;

    // only advance envelope during actual note
    if(!Channels[i].isDelay){
      // Number of song ticks since this note started.
      uint16_t age = Channels[i].noteIncrement;

      // Each envelope entry lasts two song ticks.
      uint16_t maskIndex = 3 * age >> 5;

      // Stop counting once the envelope has finished.
      if(maskIndex < 128){
        uint32_t fadeTicks = Channels[i].noteData->notePauseDuration / 4;
        if(fadeTicks > NOTE_FADE_TICKS) {
          fadeTicks = NOTE_FADE_TICKS;
        }

        if(fadeTicks == 0) {
          fadeTicks = 1;
        }

        level = piano_envelope[maskIndex];
        if(age < fadeTicks) {
          level = (level * age)/ fadeTicks;
        }

        uint16_t remaining = Channels[i].noteProgress;
        if(remaining < fadeTicks) {
          level = (level * remaining) / fadeTicks;
        }
        // stop adancing once the envelope is exhausted
        Channels[i].noteIncrement++;
      }
    }

    Channels[i].envelopeLevel = (uint8_t)level;
  }
  if(!stillPlaying){
    //Playback is finished, restart
    restartTicks = 2208;
  }
  uint32_t elapsed = (start - TIMG8->COUNTERREGS.CTR) & 0xFFFF;

  if(elapsed > ISRMaxTicks[0]){
    ISRMaxTicks[0] = elapsed;
  }
  GPIOB->DOUTCLR31_0 = SYS_MASK;  // ISR ends.
}
#endif

void TIMA0_IRQHandler(void){ // Channel 0
  GPIOB->DOUTSET31_0 = A0_MASK;  // ISR begins.
  uint32_t start = TIMG8->COUNTERREGS.CTR;

  static uint8_t waveIndex;
  if((TIMA0->CPU_INT.IIDX) == 1){ // this will acknowledge
    Channels[0].currentOutput = piano_wave[waveIndex];
    waveIndex = (uint8_t)(waveIndex + WAVE_STEP); // 256-entry wave table means index naturally loops around by overflowing
  }

  uint32_t elapsed = (start - TIMG8->COUNTERREGS.CTR) & 0xFFFF;

  if(elapsed > ISRMaxTicks[1]){
    ISRMaxTicks[1] = elapsed;
  }
  GPIOB->DOUTCLR31_0 = A0_MASK;  // ISR ends.
}

void TIMA1_IRQHandler(void){ // Channel 1
  GPIOB->DOUTSET31_0 = A1_MASK;  // ISR begins.
  uint32_t start = TIMG8->COUNTERREGS.CTR;

  static uint8_t waveIndex;
  if((TIMA1->CPU_INT.IIDX) == 1){ // this will acknowledge
    Channels[1].currentOutput = piano_wave[waveIndex];
    waveIndex = (uint8_t)(waveIndex + WAVE_STEP); // 256-entry wave table means index naturally loops around by overflowing
  }

  uint32_t elapsed = (start - TIMG8->COUNTERREGS.CTR) & 0xFFFF;

  if(elapsed > ISRMaxTicks[2]){
    ISRMaxTicks[2] = elapsed;
  }
  GPIOB->DOUTCLR31_0 = A1_MASK;  // ISR ends.
}

#if FFFFF_FULL_MODE
void TIMG6_IRQHandler(void){ // Channel 1
  GPIOB->DOUTSET31_0 = G6_MASK;  // ISR begins.
  uint32_t start = TIMG8->COUNTERREGS.CTR;

  static uint8_t waveIndex;
  if((TIMG6->CPU_INT.IIDX) == 1){ // this will acknowledge
    Channels[2].currentOutput = piano_wave[waveIndex];
    waveIndex = (uint8_t)(waveIndex + WAVE_STEP); // 256-entry wave table means index naturally loops around by overflowing
  }

  uint32_t elapsed = (start - TIMG8->COUNTERREGS.CTR) & 0xFFFF;

  if(elapsed > ISRMaxTicks[3]){
    ISRMaxTicks[3] = elapsed;
  }
  GPIOB->DOUTCLR31_0 = G6_MASK;  // ISR ends.
}

void TIMG7_IRQHandler(void){ // Channel 1
  GPIOB->DOUTSET31_0 = G7_MASK;  // ISR begins.
  uint32_t start = TIMG8->COUNTERREGS.CTR;

  static uint8_t waveIndex;
  if((TIMG7->CPU_INT.IIDX) == 1){ // this will acknowledge
    Channels[3].currentOutput = piano_wave[waveIndex];
    waveIndex = (uint8_t)(waveIndex + WAVE_STEP); // 256-entry wave table means index naturally loops around by overflowing
  }

  uint32_t elapsed = (start - TIMG8->COUNTERREGS.CTR) & 0xFFFF;

  if(elapsed > ISRMaxTicks[4]){
    ISRMaxTicks[4] = elapsed;
  }
  GPIOB->DOUTCLR31_0 = G7_MASK;  // ISR ends.
}

void TIMG12_IRQHandler(void){ // Channel 1
  GPIOB->DOUTSET31_0 = G12_MASK;  // ISR begins.
  uint32_t start = TIMG8->COUNTERREGS.CTR;

  static uint8_t waveIndex;
  if((TIMG12->CPU_INT.IIDX) == 1){ // this will acknowledge
    Channels[4].currentOutput = piano_wave[waveIndex];
    waveIndex = (uint8_t)(waveIndex + WAVE_STEP); // 256-entry wave table means index naturally loops around by overflowing
  }

  uint32_t elapsed = (start - TIMG8->COUNTERREGS.CTR) & 0xFFFF;

  if(elapsed > ISRMaxTicks[5]){
    ISRMaxTicks[5] = elapsed;
  }
  GPIOB->DOUTCLR31_0 = G12_MASK;  // ISR ends.
}
#endif