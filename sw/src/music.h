// File **********music.h***********
// Lab 5
// Programs to play pre-programmed music.
// EE445L Fall 2026
//    Jonathan W. Valvano 6/29/26

// Experimental setting to use a more faithful reproduction of the pop'n music soundtrack.
#define FFFFF_FULL_MODE 1

# if FFFFF_FULL_MODE
// Channels: 
// CH0: TIMA0
// CH1: TIMA0
// CH2: TIMG6
// CH3: TIMG7
// CH4: TIMG12
#define NUM_CHANNELS 5
#else
// We use 2 channels here, CH0 on TIMA0 and CH1 on TIMA1
#define NUM_CHANNELS 2
#endif

#if FFFFF_FULL_MODE
  #define MIX_SHIFT 7 // 5 channels
#else
  #define MIX_SHIFT 5 // 2 channels
#endif

#if FFFFF_FULL_MODE
#include "fffff5voices.h"
#else
#include "fffff.h"
#endif

typedef struct {
  // The timer associated with the channel. 
  GPTIMER_Regs *Timer;
  // Stores the position of the current NoteData being played. Has a NULL sentinel value at the end of the array.
  const NoteData_t *noteData;
  // Counts down from the delay fetched each tick. Advances to next note-half upon reaching 0.
  int16_t noteProgress;
  // Counts up each reset. Complements noteProgress. 
  uint16_t noteIncrement;
  // """Boolean""" value to store if the note versus gap delay is being played. 
  uint8_t isDelay;
  // Channel-specific contribution to output
  uint16_t currentOutput;
  // Current envelope amlitude, 0-255
  uint8_t envelopeLevel;
} AudioChannel_t;

extern volatile AudioChannel_t Channels[NUM_CHANNELS];
extern volatile uint8_t SongPlaying;

void SysTick_InitArm(uint32_t period, uint32_t priority);
//-------------- Song_Init ----------------
// activate SysTick, Timer0 and Timer1 periodic interrupts
// Inputs: none
// Outputs: none
// called once
void Song_Init(void);

void Song_Init2(void);
//-------------- Song_Pause ----------------
// Pauses the music, saving internal state.
// Inputs: none
// Outputs: none
void Song_Pause(void);
//-------------- Song_Play ----------------
// Plays the music, loading internal state from memory.
// Inputs: none
// Outputs: none
// Must be called after Song_Pause has already been called.
void Song_Play(void);
//-------------- Song_HalfSpeed ----------------
// Changes playback speed to 0.5x original. Does not affect pitch or envelopes.
// Inputs: none
// Outputs: none
// Macro, not function

void Song_Toggle(void);

void channelInit(void);

extern volatile uint32_t MeasurementSongTicks;

#define Song_HalfSpeed() SysTick->LOAD = 72464
//-------------- Song_FullSpeed ----------------
// Changes playback speed to original.
// Inputs: none
// Outputs: none
// Macro, not function
#define Song_FullSpeed() SysTick->LOAD = 36232

void test(void);