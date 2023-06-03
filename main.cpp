#include "mbed.h"
#include "Joystick.h" 
#include "N5110.h"
#include "bullet.h"
#include "JetEngine.h"
#include "Enemy_jet.h"
#include "BGM.h"
#include "string.h"

// main() runs in its own thread in the OS
N5110 lcd(PC_7, PA_9, PB_10, PB_5, PB_3, PA_10);
Joystick joystick(PC_1, PC_0);
DigitalIn click(PC_10);
DigitalIn pausekey(PC_11);
PwmOut buzzer(PA_15);
PwmOut buzzer2(PC_8);

Ticker ticker_bullet_shoot;
Ticker ticker_CD;
Ticker ticker_bullet_move;
Ticker ticker_enemy_jet_generate;
Ticker ticker_enemy_jet_move;
Ticker ticker_enemy_bullet_shoot;
Ticker ticker_enemy_bullet_move;
//Ticker ticker_buff_move;

float y_pos = 24;
float x_pos = 42;

char alphabet[27] = {' ','A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

volatile int g_button_flag = 0;

volatile int bullet_shoot_flag = 0;
volatile bool CD_flag;
volatile bool bullet_move_flag;
volatile bool enemy_jet_generate_flag;
volatile bool enemy_jet_move_flag;
volatile bool enemy_bullet_shoot_flag;
volatile bool enemy_bullet_move_flag;
//volatile bool buff_move_flag;

volatile int difficulty = 100;
volatile double brightness = 0.5;
volatile char random_number = 5;

volatile char Name[5][8] = {0};
volatile char Score[5] = {0};


const int arrow[9][11] = {
    {0,0,0,0,0,0,1,0,0,0,0},
    {0,0,0,0,0,0,1,1,0,0,0},
    {0,0,0,0,0,0,1,1,1,0,0},
    {1,1,1,1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,1,1,1,0,0},
    {0,0,0,0,0,0,1,1,0,0,0},
    {0,0,0,0,0,0,1,0,0,0,0},
};

const int small_arrow[7][11] = {
    {0,0,0,0,0,0,0,1,0,0,0},
    {0,0,0,0,0,0,0,1,1,0,0},
    {1,1,1,1,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,0},
    {0,0,0,0,0,0,0,1,1,0,0},
    {0,0,0,0,0,0,0,1,0,0,0},
};

const int reverse_arrow[9][11] = {
    {0,0,0,0,1,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,0,0,0,0},
    {0,0,1,1,1,0,0,0,0,0,0},
    {0,1,1,1,1,1,1,1,1,1,1},
    {1,1,1,1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,1,1,1,1},
    {0,0,1,1,1,0,0,0,0,0,0},
    {0,0,0,1,1,0,0,0,0,0,0},
    {0,0,0,0,1,0,0,0,0,0,0},
};
void boundary(int x, int y);
void menu_display();
void joystick_button_isr();
void CD_isr();
void bullet_shoot_isr();
void bullet_move_isr();
void enemy_jet_generate_isr();
void enemy_jet_move_isr();
void enemy_bullet_shoot_isr();
void enemy_bullet_move_isr();
//void buff_move_isr();

void tutorial();
void settings();
void about();
void start_game();
void ranking();


void gameover();

//InterruptIn joystick_button(PC_10);

JetEngine jetengine;


bool CD = 0;
bool bullet_shoot = 0;
bool bullet_move = 0;
bool enemy_jet_generate = 0;
bool enemy_jet_move = 0;
bool enemy_bullet_shoot = 0;
bool enemy_bullet_move = 0;
//bool buff_move = 0;



int main(){
    click.mode(PullUp);
    pausekey.mode(PullUp);
    joystick.init();
    lcd.init(LPH7366_1);        //initialise for LPH7366-1 LCD (Options are LPH7366_1 and LPH7366_6)
    lcd.setContrast(0.55);      //set contrast to 55%
    lcd.setBrightness(0.5);     //set brightness to 50% (utilises the PWM)
    
    jetengine.init(); //jet,x, jet y,
    ticker_CD.attach(&CD_isr, 50ms); //by mudifying this value, the moving speed of the spaceship can be controlled.
    ticker_bullet_shoot.attach(&bullet_shoot_isr,500ms); //shoot every 0.5s
    ticker_bullet_move.attach(&bullet_move_isr, 100ms); //modify this value to adjust bullet's moving speed
    ticker_enemy_jet_generate.attach(&enemy_jet_generate_isr, 2500ms);
    ticker_enemy_jet_move.attach(&enemy_jet_move_isr, 150ms);
    //ticker_buff_move.attach(&buff_move_isr, 150ms);

    ticker_enemy_bullet_shoot.attach(&enemy_bullet_shoot_isr,4000ms);
    ticker_enemy_bullet_move.attach(&enemy_bullet_move_isr,100ms);
    //StartgameWelcome(lcd);
    //ImperialMarch(buzzer);
    //gameover();
    menu_display();
    

}

void gameover(){
    //joystick_button.fall(&joystick_button_isr);
    //joystick_button.mode(PullUp);
    char x[8] = {0};
    char bit = 0;
    char buffer1[8] = {0};
    buzzer.pulsewidth_us(0); 
    buzzer2.pulsewidth_us(0); 
    while(click == 1){
        lcd.clear();
        char buffer[14] = {0};
        sprintf(buffer, "Your score:%d",jetengine.get_score());
        lcd.printString(buffer,0,1);
        lcd.printString("Game Over!",12,0);
        lcd.printString("Press joystick",0,3);
        if(jetengine.get_score()>Score[4]){
            lcd.printString("to record your",0,4);
            lcd.printString("score!",30,5);
        }
        else{
            lcd.printString("to return main",0,4);
            lcd.printString("menu!",30,5);
        }
        
        lcd.refresh();
        if(click == 0){
            
            thread_sleep_for(20);
            while(click == 0){}
            thread_sleep_for(20);

            if(jetengine.get_score()<=Score[4]){ // if score less than the lowest score in ranking, no need to enter name.
                menu_display();
            }
            
            while(1){
                lcd.clear();
                lcd.printString("  Enter your",0,0);
                lcd.printString("    name:",0,1);
                
                if(joystick.get_direction()==N){                  
                    if(x[bit] == 26){
                        x[bit] = 0;
                    }
                    else{
                        x[bit]++;
                    }
                    thread_sleep_for(250);
                }
                else if(joystick.get_direction()==S){                  
                    if(x[bit] == 0){
                        x[bit] = 26;
                    }
                    else{
                        x[bit]--;
                    }
                    thread_sleep_for(250);
                }

                if((joystick.get_direction() == E) && (bit > 0)){
                    bit--;
                    thread_sleep_for(250);
                }
                else if((joystick.get_direction() == W) && (bit < 7)){
                    bit++;
                    thread_sleep_for(250);
                }

                buffer1[bit] = {alphabet[x[bit]]};
                
                lcd.drawLine(17,42,63,42,FILL_BLACK);
                if(bit == 0){
                    lcd.drawLine(17, 40, 21, 40, FILL_BLACK);
                }
                else if(bit == 1){
                    lcd.drawLine(23, 40, 27, 40, FILL_BLACK);
                }
                else if(bit == 2){
                    lcd.drawLine(29, 40, 33, 40, FILL_BLACK);
                }
                else if(bit == 3){
                    lcd.drawLine(35, 40, 39, 40, FILL_BLACK);
                }
                else if(bit == 4){
                    lcd.drawLine(41, 40, 45, 40, FILL_BLACK);
                }
                else if(bit == 5){
                    lcd.drawLine(47, 40, 51, 40, FILL_BLACK);
                }
                else if(bit == 6){
                    lcd.drawLine(53, 40, 57, 40, FILL_BLACK);
                }
                else if(bit == 7){
                    lcd.drawLine(59, 40, 63, 40, FILL_BLACK);
                }
                
                lcd.printString(buffer1,17,4);
                lcd.refresh();
                

                if(click == 0){
                    thread_sleep_for(20);
                    while(click==0){}
                    thread_sleep_for(20);
                    
                    if(jetengine.get_score() > Score[0]){
                        
                        
                        for(int i=0;i<8;i++){
                            Name[4][i] = Name[3][i];
                            Name[3][i] = Name[2][i];
                            Name[2][i] = Name[1][i];
                            Name[1][i] = Name[0][i];
                            Name[0][i] = buffer1[i];
                        }
                        Score[4] = Score[3];
                        Score[3] = Score[2];
                        Score[2] = Score[1];
                        Score[1] = Score[0];
                        Score[0] = jetengine.get_score();
                    }
                    else if(jetengine.get_score() > Score[1]){
                        
                        for(int i=0;i<8;i++){
                            Name[4][i] = Name[3][i];
                            Name[3][i] = Name[2][i];
                            Name[2][i] = Name[1][i];
                            Name[1][i] = buffer1[i];
                        }
                        Score[4] = Score[3];
                        Score[3] = Score[2];
                        Score[2] = Score[1];
                        Score[1] = jetengine.get_score();
                    }
                    else if(jetengine.get_score() > Score[2]){
                        
                        for(int i=0;i<8;i++){
                            Name[4][i] = Name[3][i];
                            Name[3][i] = Name[2][i];
                            Name[2][i] = buffer1[i];
                        }
                        Score[4] = Score[3];
                        Score[3] = Score[2];
                        Score[2] = jetengine.get_score();
                    }
                    else if(jetengine.get_score() > Score[3]){
                        
                        for(int i=0;i<8;i++){
                            Name[4][i] = Name[3][i];
                            Name[3][i] = buffer1[i];
                        }
                        Score[4] = Score[3];
                        Score[3] = jetengine.get_score();
                    }
                    else if(jetengine.get_score() > Score[4]){
                        for(int i=0;i<8;i++){
                            Name[4][i] = buffer1[i];
                        }
                        Score[4] = jetengine.get_score();
                    }
                    break;
                }
            }
            
            menu_display();
        }
    }
    
    
}

void CD_isr(){
    CD_flag = 1;
}
void bullet_shoot_isr(){
    bullet_shoot_flag = 1;
}
void bullet_move_isr(){
    bullet_move_flag = 1;
}
void enemy_jet_generate_isr(){
    enemy_jet_generate_flag = 1;
}
void enemy_jet_move_isr(){
    enemy_jet_move_flag = 1;
}
void enemy_bullet_shoot_isr(){
    enemy_bullet_shoot_flag = 1;
}
void enemy_bullet_move_isr(){
    enemy_bullet_move_flag = 1;
}
void joystick_button_isr(){
    g_button_flag = 1;
    
}
/*void buff_move_isr(){
    buff_move_flag = 1;
}*/
void menu_display(){
    int tutorial_row = 2;
    int start_row = 3;
    int setting_row = 4;
    int about_row = 5;
    int ranking_row = 6;
    //joystick_button.fall(&joystick_button_isr);
    //joystick_button.mode(PullUp);
    while(1){
        
        lcd.clear();
        lcd.printString("Fighter Jet",8,0);
        lcd.drawSprite(0, 23, 9, 11, (int*)arrow);
        lcd.drawSprite(73, 23, 9, 11, (int*)reverse_arrow);
        lcd.printString("Tutorial",18,tutorial_row);
        lcd.printString("Start",27,start_row);
        lcd.printString("Settings",18,setting_row);
        lcd.printString("About",27,about_row);
        lcd.printString("Ranking",20,ranking_row);
        lcd.drawLine(0, 10, 84, 10, 1); 
        if(joystick.get_direction() == N){
            if(tutorial_row == 2){
                tutorial_row = 6;
            }
            else{
                tutorial_row--;
            }
            if(start_row == 2){
                start_row = 6;
            }
            else{
                start_row--;
            }
            if(setting_row == 2){
                setting_row = 6;
            }
            else{
                setting_row--;
            }
            if(about_row == 2){
                about_row = 6;
            }
            else{
                about_row--;
            }
            if(ranking_row == 2){
                ranking_row = 6;
            }
            else{
                ranking_row--;
            }
            ThisThread::sleep_for(250ms);
            lcd.refresh();
        }
        else if (joystick.get_direction() == S){
            if(tutorial_row == 6){
                tutorial_row = 2;
            }
            else{
                tutorial_row++;
            }
            if(start_row == 6){
                start_row = 2;
            }
            else{
                start_row++;
            }
            if(setting_row == 6){
                setting_row = 2;
            }
            else{
                setting_row++;
            }
            if(about_row == 6){
                about_row = 2;
            }
            else{
                about_row++;
            }
            if(ranking_row == 6){
                ranking_row = 2;
            }
            else{
                ranking_row++;
            }
            ThisThread::sleep_for(250ms);
            lcd.refresh();
        }

        if(click == 0){
            thread_sleep_for(20);
            //g_button_flag = 0;
            while(click == 0)
            thread_sleep_for(20);
            if(tutorial_row == 3){
                tutorial();
            }
            else if(start_row == 3){
                start_game();
            }
            else if(setting_row == 3){
                settings();
            }
            else if(about_row == 3){
                about();
            }
            else if(ranking_row == 3){
                ranking();
            }
            
        }

        lcd.refresh();
        
    }
}

void start_game(){
    
    int lives = 5;
    jetengine.init();

    while(lives>0){
        lcd.clear();
        //lcd.drawSprite(10,10,5,8,(int*)Enemy_Spaceship);
        if(CD_flag == 1){ // Timer interrupt, remove the limitation on next movement.
            CD_flag = 0;
            CD = 0;
        }
        if(bullet_shoot_flag == 1){
            bullet_shoot_flag = 0;
            bullet_shoot = 1;
        }
        if(bullet_move_flag == 1){
            bullet_move_flag = 0;
            bullet_move = 1;
        }
        if(enemy_jet_generate_flag == 1){
            enemy_jet_generate_flag = 0;
            enemy_jet_generate = 1;
        }
        if(enemy_jet_move_flag == 1){
            enemy_jet_move_flag = 0;
            enemy_jet_move = 1;
        }
        if(enemy_bullet_shoot_flag == 1){
            enemy_bullet_shoot_flag = 0;
            enemy_bullet_shoot = 1;
        }
        if(enemy_bullet_move_flag == 1){
            enemy_bullet_move_flag = 0;
            enemy_bullet_move = 1;
        }
        /*if(buff_move_flag == 1){
            buff_move_flag = 0;
            buff_move = 1;
        }*/
        UserInput input = {joystick.get_direction(),joystick.get_mag()};
        lives = jetengine.update(input,CD,bullet_shoot,bullet_move,enemy_jet_move, enemy_jet_generate, enemy_bullet_shoot, enemy_bullet_move,click,random_number);   // update the game engine based on input   
        jetengine.draw(lcd);
        jetengine.hit_sound(buzzer);
        jetengine.hitted_sound(buzzer2);
        
        lcd.refresh();

        if(pausekey == 0){
            thread_sleep_for(20);
            while(pausekey == 0)
            thread_sleep_for(20);
            int position = 1;
            while(1){
                lcd.clear();
                lcd.printString("   Pausing",4,0);
                char buffer[14] = {0};
                sprintf(buffer, "   Score:%d",jetengine.get_score());
                lcd.printString(buffer,4,2);
                char buffer1[14] = {0};
                sprintf(buffer1, "   Lives:%d",lives);
                lcd.printString(buffer1,4,3);
                lcd.printString("<Resume>",20,4);
                lcd.printString("<Quit>",25,5);
                
                
                if(position == 1){
                    lcd.drawSprite(0,32,7,11,(int*)small_arrow);
                }
                else if(position == 2){
                    lcd.drawSprite(0,40,7,11,(int*)small_arrow);
                }
                

                if((joystick.get_direction() == S) && (position > 1)){
                    position--;
                    thread_sleep_for(250);
                }
                else if((joystick.get_direction() == N) && (position < 2)){
                    position++;
                    thread_sleep_for(250);
                }

                if(click == 0){
                    thread_sleep_for(20);
                    while(click == 0)
                    thread_sleep_for(20);
                    if(position == 1){
                        break;
                    }
                    else if(position == 2){
                        menu_display();
                    }
                }

                lcd.refresh();
            }
        }
    }
    /*while(1){
        menu_display();
        lcd.clear();

        boundary(x_pos, y_pos); //pass the new x,y position to function
            
        lcd.refresh();
        ThisThread::sleep_for(30ms);

    }*/
    gameover();
}

void tutorial(){
    int page = 1;
    while(click == 1){
        
        if(page == 1){
            lcd.clear();
            lcd.printString("Welcome!",22,0);
            lcd.printString("Use joystick",5,3);
            lcd.printString("to switch",18,4);
            lcd.printString("between pages",3,5);
            lcd.refresh();  
        }
        else if(page==2){
            lcd.clear();
            lcd.printString("Mission",22,0);
            lcd.printString("Eliminate",0,1);
            lcd.printString("your enemy's",0,2);
            lcd.printString("jet,and dodge",1,3);
            lcd.printString("your enemy's",0,4);
            lcd.printString("bullets",0,5);
            lcd.refresh(); 
        }
        else if(page==3){
            lcd.clear();
            lcd.printString("Control",22,0);
            lcd.printString("Use joystick",0,1);
            lcd.printString("to move your",0,2);
            lcd.printString("jet,the jet",1,3);
            lcd.printString("will shoot",0,4);
            lcd.printString("automatically",0,5);
            lcd.refresh(); 
        }
        else if(page==4){
            lcd.clear();
            lcd.printString("Rules",22,0);
            lcd.printString("Each time you",0,1);
            lcd.printString("destroy an",0,2);
            lcd.printString("enemy's jet,",1,3);
            lcd.printString("you gain 1",0,4);
            lcd.printString("score",0,5);
            lcd.refresh(); 
        }
        else if(page==5){
            lcd.clear();
            lcd.printString("Rules",22,0);
            lcd.printString("Collide with",0,1);
            lcd.printString("enemy's jet or",0,2);
            lcd.printString("bullets will",1,3);
            lcd.printString("decrease",0,4);
            lcd.printString("your lives",0,5);
            lcd.refresh(); 
        }
        else if(page==6){
            lcd.clear();
            lcd.printString("Rules",22,0);
            lcd.printString("If you lose",0,1);
            lcd.printString("all your lives",0,2);
            lcd.printString(",game over",1,3);
            
            lcd.refresh(); 
        }
        else if(page==7){
            lcd.clear();
            lcd.drawSprite(79,36,2,3,(int*)lives);
            lcd.drawSprite(79,38,2,3,(int*)lives);
            lcd.drawSprite(79,40,2,3,(int*)lives);
            lcd.drawSprite(79,42,2,3,(int*)lives);
            lcd.drawSprite(79,44,2,3,(int*)lives);
            lcd.drawSprite(66,38,7,11,(int*)small_arrow);
            lcd.printString("This bar",0,3);
            lcd.printString("indicates",0,4);
            lcd.printString("your lives",0,5);
            lcd.refresh(); 
        }
        else if(page == 8){
            lcd.clear();
            lcd.drawSprite(78,1,21,5,(int*)score);
            lcd.drawSprite(78,31,3,5,(int*)zero);
            lcd.drawSprite(78,27,3,5,(int*)zero);
            lcd.drawSprite(78,23,3,5,(int*)zero);
            lcd.drawSprite(66,25,7,11,(int*)small_arrow);
            lcd.printString("Your current",0,1);
            lcd.printString("score is",0,2);
            lcd.printString("displayed",0,3);
            lcd.printString("here",0,4);
            lcd.refresh(); 
        }
        else if(page == 9){
            lcd.clear();
            lcd.drawRect(0,0,84,48,FILL_TRANSPARENT);   //draws screen boarder
            lcd.printString("You can't",1,1);
            lcd.printString("move your jet",1,2);
            lcd.printString("out of this",1,3);
            lcd.printString("boundary!",1,4);
            lcd.refresh(); 
        }
        else if(page == 10){
            lcd.clear();
              //draws screen boarder
            lcd.printString("Attention!",0,0);
            lcd.printString("sometimes the",0,2);
            lcd.printString("enemy may ",0,3);
            lcd.printString("release",0,4);
            lcd.printString("shockwaves",0,5);
            lcd.refresh(); 
        }
        else if(page == 11){
            lcd.clear();
              //draws screen boarder
            lcd.printString("Looks like",0,0);
            lcd.printString("this!",0,1);
            lcd.drawSprite(48,24,5,8,(int*)Enemy_Spaceship);
            lcd.drawCircle(48,24,30,FILL_TRANSPARENT);
            lcd.refresh(); 
        }
        else if(page == 12){
            lcd.clear();
              //draws screen boarder
            lcd.printString("Keep pressing",0,0);
            lcd.printString("the joystick",0,1);
            lcd.printString("when contact",0,2);
            lcd.printString("the shockwave!",0,3);
            lcd.printString("Otherwise,you",0,4);
            lcd.printString("lose lives!",0,5);
            lcd.refresh(); 
        }
        else if(page == 13){
            lcd.clear();
              //draws screen boarder
            lcd.printString("Have fun!",0,0);
            lcd.printString("Press the",0,2);
            lcd.printString("joystick to",0,3);
            lcd.printString("quit the",0,4);
            lcd.printString("tutorial",0,5);
            lcd.refresh(); 
        }


                
        
        if((joystick.get_direction() == W) && (page < 13)){
            thread_sleep_for(250);
            page++;
        }
        else if((joystick.get_direction() == E) && (page > 1) ){
            thread_sleep_for(250);
            page--;
        }

        if(click == 0){
            thread_sleep_for(20);
            while(click == 0)
            thread_sleep_for(20);
            menu_display();
        }
          
    }
}

void settings(){
    float time = 0;
    int time1 = 0;
    int position = 1;
    while(click == 1){
        lcd.clear();
        lcd.printString("Brightness",15,0);
        if(brightness == 0.4){
            lcd.printString("< 0.4 >",20,1);
        }
        else if(brightness == 0.5){
            lcd.printString("< 0.5 >",20,1);
        }
        else if(brightness == 0.6){
            lcd.printString("< 0.6 >",20,1);
        }
        else if(brightness == 0.7){
            lcd.printString("< 0.7 >",20,1);
        }
        

        lcd.printString("Difficulty",15,2);
        if(difficulty ==100){
            lcd.printString("< Medium >",15,3);
        }
        else if(difficulty == 125){
            lcd.printString("< Easy >",15,3);
        }
        else if(difficulty == 75){
            lcd.printString("< Hard >",15,3);
        }

        if(position == 1){
            lcd.drawSprite(0,8,7,11,(int*)small_arrow);
        }
        else if(position == 2){
            lcd.drawSprite(0,24,7,11,(int*)small_arrow);
        }
        else if(position == 3){
            lcd.drawSprite(0,40,7,11,(int*)small_arrow);
        }

        if((joystick.get_direction() == S) && (position > 1)){
            position--;
            thread_sleep_for(250);
        }
        else if((joystick.get_direction() == N) && (position < 2)){
            position++;
            thread_sleep_for(250);
        }
        else if(joystick.get_direction() == E){
            if((position == 1) && (brightness > 0.4)){
                brightness = brightness - 0.1;
                lcd.setBrightness(brightness);
                thread_sleep_for(250);
            }
            else if((position == 2) && (difficulty < 125)){
                difficulty = difficulty + 25;
                time = (float)difficulty/1000;
                ticker_enemy_bullet_move.attach(&enemy_bullet_move_isr,time);
                time1 = difficulty / 25;
                ticker_enemy_bullet_shoot.attach(&enemy_bullet_shoot_isr,time1);
                random_number = random_number + 4;
                thread_sleep_for(250);
            }

        }
        else if(joystick.get_direction() == W){
            if((position == 1) && (brightness < 0.7)){
                brightness = brightness + 0.1;
                lcd.setBrightness(brightness);
                thread_sleep_for(250);
            }
            else if((position == 2) && (difficulty > 75)){
                difficulty = difficulty - 25;
                time = (float)difficulty/1000;
                ticker_enemy_bullet_move.attach(&enemy_bullet_move_isr,time);
                time1 = difficulty / 25;
                ticker_enemy_bullet_shoot.attach(&enemy_bullet_shoot_isr,time1);
                random_number = random_number - 4;
                thread_sleep_for(250);
            }
        }

        lcd.refresh();
        if(click == 0){
            thread_sleep_for(20);
            while(click == 0)
            thread_sleep_for(20);
            menu_display();
        }
    }
}
void about(){
    while(click == 1){
        lcd.clear();
        lcd.printString("Author:",0,0);
        lcd.printString("L. Yuan",0,1);
        lcd.printString("Version:",0,3);
        lcd.printString("1.0",0,4);
        lcd.refresh();
        if(click == 0){
            thread_sleep_for(20);
            while(click == 0)
            thread_sleep_for(20);
            menu_display();
        }
    }
}

void ranking(){
    char buffer0[8] = {0};
    char buffer1[8] = {0};
    char buffer2[8] = {0};
    char buffer3[8] = {0};
    char buffer4[8] = {0};
    char buffera[3] = {0};
    char bufferb[3] = {0};
    char bufferc[3] = {0};
    char bufferd[3] = {0};
    char buffere[3] = {0};
    
    sprintf(buffera,"%d",Score[0]);
    sprintf(bufferb,"%d",Score[1]);
    sprintf(bufferc,"%d",Score[2]);
    sprintf(bufferd,"%d",Score[3]);
    sprintf(buffere,"%d",Score[4]);
    for(int i = 0; i<8; i++){
        buffer0[i] = Name[0][i];
        buffer1[i] = Name[1][i];
        buffer2[i] = Name[2][i];
        buffer3[i] = Name[3][i];
        buffer4[i] = Name[4][i];
    }
    
    while(1){
        lcd.clear();
        lcd.printString("Ranking",20,0);

        lcd.printString("1.",0,1);
        lcd.printString("2.",0,2);
        lcd.printString("3.",0,3);
        lcd.printString("4.",0,4);
        lcd.printString("5.",0,5);

        lcd.printString(buffer0,10,1);
        lcd.printString(buffer1,10,2);
        lcd.printString(buffer2,10,3);
        lcd.printString(buffer3,10,4);
        lcd.printString(buffer4,10,5);

        lcd.printString(buffera,65,1);
        lcd.printString(bufferb,65,2);
        lcd.printString(bufferc,65,3);
        lcd.printString(bufferd,65,4);
        lcd.printString(buffere,65,5);

       

        lcd.refresh();

        if(click == 0){
            thread_sleep_for(20);
            while(click == 0){}
            thread_sleep_for(20);
            menu_display();
        }
    }
}




