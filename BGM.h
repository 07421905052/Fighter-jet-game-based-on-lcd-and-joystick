#ifndef BGM_H
#define BGM_H
#include "Mbed.h"
#include "N5110.h"

#define LOW5 196
#define CENTER1  262    //octave 4 - middle c
#define CENTER2  294
#define CENTER3  330
#define CENTER4  349
#define CENTER5  392
#define CENTER6  440
#define CENTER7  494
#define HIGH1  523
#define HIGH2  587
#define HIGH2RISE 622
#define HIGH3  659
#define HIGH4  698
#define HIGH4RISE 740
#define HIGH5  784
#define HIGH5RISE 831
#define HIGH6  880
#define HIGH6RISE 932
#define HIGH7  988
#define HIGHER1  1047
#define HIGHER1RISE 1109
#define HIGHER2  1175
#define HIGHER2RISE 1245
#define HIGHER3  1319
#define HIGHER4  1397
#define HIGHER4RISE 1480
#define HIGHER5  1568
#define HIGHER6  1760
#define HIGHER7  1967


void note(int frequency,int time, PwmOut &buzzer);
void ImperialMarch(PwmOut &buzzer);
void StartgameWelcome(N5110 &lcd);

#endif