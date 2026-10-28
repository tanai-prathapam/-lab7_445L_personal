typedef struct noteData NoteData_t;
#include <ti/devices/msp/msp.h>

struct noteData {
  uint16_t prepauseDuration;
  uint16_t notePauseDuration;
  uint16_t counterLoadVal;
};

extern const NoteData_t fffffCh0[606];
extern const NoteData_t fffffCh1[588];
extern const NoteData_t fffffCh2[672];
extern const NoteData_t fffffCh3[461];
extern const NoteData_t fffffCh4[735];
