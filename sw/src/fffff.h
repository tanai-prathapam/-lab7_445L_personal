typedef struct noteData NoteData_t;
#include <ti/devices/msp/msp.h>

struct noteData {
  uint16_t prepauseDuration;
  uint16_t notePauseDuration;
  uint16_t counterLoadVal;
};

extern const NoteData_t fffffLeft[824];
extern const NoteData_t fffffRight[856];