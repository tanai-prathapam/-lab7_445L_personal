// File **********Switch.h***********
// Lab 5
// Programs to interface with Switch buttons   
// EE445L Fall 2026
//    Jonathan W. Valvano 6/29/26
// 2-bit input, positive logic switches, positive logic software

    // write this
    // ***solution***
// PB1 Play/Pause switch 
// PB4 Speed switch 
// PB2 Restart switch

//---------------------Switch_Init---------------------
// initialize switch interface
// Input: none
// Output: none 
void Switch_Init(void);



//---------------------Switch_Play---------------------
// read the switches
// Input: none
// Output: false the Play switch not pressed
//         true the Play switch is pressed 
int Switch_Play(void);

//---------------------Switch_PlayPressed---------------------
// edge detection play switch
// Input: none
// Output: false the Play switch not pressed and released
//         true the Play switch is pressed and released
int Switch_PlayPressed(void);

//---------------------Switch_SlowSpeed---------------------
// read the speed switch
// Input: none
// Output: none
void Switch_SlowSpeed(void);

//---------------------Switch_Restart---------------------
// read the restart switch
// Input: none
// Output: none
void Switch_Restart(void);
