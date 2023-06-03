#include "BGM.h"

void note(int frequency,int time, PwmOut &buzzer){
    buzzer.period_us((float) 1000000.0f/ (float) frequency);    //set the period of the pwm signal (in us)
    buzzer.pulsewidth_us(buzzer.read_period_us()/2);            //set pulse width of the pwm to 1/2 the period   
    thread_sleep_for(time);                           //play sound for 500ms
}

void ImperialMarch(PwmOut &buzzer){
    note(HIGH5,600,buzzer),note(HIGH5,600,buzzer),note(HIGH5,600,buzzer),note(HIGH2RISE,450,buzzer),note(HIGH6RISE,150,buzzer),
    note(HIGH5,600,buzzer),note(HIGH2RISE,450,buzzer),note(HIGH6RISE,150,buzzer),note(HIGH5,1200,buzzer),

    note(HIGHER2,600,buzzer),note(HIGHER2,600,buzzer),note(HIGHER2,600,buzzer),note(HIGHER2RISE,450,buzzer),note(HIGH6,150,buzzer),
    note(HIGH4RISE,600,buzzer),note(HIGH2RISE,450,buzzer),note(HIGH6RISE,150,buzzer),note(HIGH5,1200,buzzer);

    note(HIGHER5,600,buzzer),note(HIGH5,450,buzzer),note(HIGH5,150,buzzer),note(HIGHER5,600,buzzer),note(HIGHER4RISE,450,buzzer),note(HIGHER4RISE,150,buzzer);

    note(HIGHER3,150,buzzer),note(HIGHER2RISE,150,buzzer),note(HIGHER3,150,buzzer),buzzer.pulsewidth_us(0),thread_sleep_for(450); 
    note(HIGH5RISE,150,buzzer),buzzer.pulsewidth_us(0),thread_sleep_for(150); 
    note(HIGHER1RISE,600,buzzer),note(HIGHER1,450,buzzer),note(HIGH7,150,buzzer);

    note(HIGH6RISE,150,buzzer),note(HIGH6,150,buzzer),note(HIGH6RISE,150,buzzer),buzzer.pulsewidth_us(0),thread_sleep_for(450);
    note(HIGH2RISE,150,buzzer),buzzer.pulsewidth_us(0),thread_sleep_for(150),note(HIGH4RISE,600,buzzer);
    note(HIGH2,450,buzzer),note(HIGH5,150,buzzer);

    note(HIGH6RISE,600,buzzer),note(HIGH5,450,buzzer),note(HIGH6,150,buzzer),note(HIGHER2,1200,buzzer);

    buzzer.pulsewidth_us(0);
}

void StartgameWelcome(N5110 &lcd){
    lcd.clear();
    lcd.printString("FIGHTER JET",10,2);
    lcd.printString("SIMULATOR",15,3);
    lcd.drawRect(0,0,84,48,FILL_TRANSPARENT);
    lcd.drawRect(1,1,82,46,FILL_TRANSPARENT);
    lcd.drawRect(3,3,78,42,FILL_TRANSPARENT);
    lcd.drawRect(5,5,74,38,FILL_TRANSPARENT);
    lcd.drawRect(8,8,68,5,FILL_BLACK);
    lcd.drawRect(8,35,68,5,FILL_BLACK);
    lcd.refresh();
}