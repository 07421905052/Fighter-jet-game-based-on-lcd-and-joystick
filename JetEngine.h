#ifndef JETENGINE_H
#define JETENGINE_H

#include "mbed.h"
#include "N5110.h"
#include "bullet.h"
#include "Jet.h"
#include "Enemy_jet.h"
#include "Enemy_bullet.h"
#include "Buff.h"
#include "Utils.h"

const int score[21][5] = {
    {1,0,1,1,1},
    {1,0,1,0,1},
    {1,1,1,0,1},

    {0,0,0,0,0},

    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,0,0,0,1},

    {0,0,0,0,0},

    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,1,1,1,1},

    {0,0,0,0,0},

    {1,1,1,1,1},
    {0,0,1,0,1},
    {1,1,0,1,1},

    {0,0,0,0,0},

    {1,1,1,1,1},
    {1,0,1,0,1},
    {1,0,1,0,1},

    {0,0,0,0,0},

    {0,1,0,1,0},
};

const int zero[3][5]{
    {1,1,1,1,1},
    {1,0,0,0,1},
    {1,1,1,1,1},
};

const int one[3][5]{
    {0,0,0,0,0},
    {0,0,0,0,0},
    {1,1,1,1,1},
};

const int two[3][5]{
    {1,1,1,0,1},
    {1,0,1,0,1},
    {1,0,1,1,1},
};

const int three[3][5]{
    {1,0,1,0,1},
    {1,0,1,0,1},
    {1,1,1,1,1},
};

const int four[3][5]{
    {0,0,1,1,1},
    {0,0,1,0,0},
    {1,1,1,1,1},
};

const int five[3][5]{
    {1,0,1,1,1},
    {1,0,1,0,1},
    {1,1,1,0,1},
};

const int six[3][5]{
    {1,1,1,1,1},
    {1,0,1,0,1},
    {1,1,1,0,1},
};

const int seven[3][5]{
    {0,0,0,0,1},
    {0,0,0,0,1},
    {1,1,1,1,1},
};

const int eight[3][5]{
    {1,1,1,1,1},
    {1,0,1,0,1},
    {1,1,1,1,1},
};

const int nine[3][5]{
    {1,0,1,1,1},
    {1,0,1,0,1},
    {1,1,1,1,1},
};

const int lives[2][3]{
    {1,1,1},
    {1,1,1},
};

#define CENTER1  262    //octave 4 - middle c
#define CENTER2  294
#define CENTER3  330
#define CENTER4  349
#define CENTER5  392
#define CENTER6  440
#define CENTER7  494
#define HIGH1  523

/*class PongEngine {
    public:
        PongEngine();  // pass in the lcd object from the main file
        void init(int paddle_position,int paddle_height,int paddle_width,int ball_size,int speed);
        int update(UserInput input);
        void draw(N5110 &lcd);
    private:
        void check_wall_collision();
        void check_paddle_collision();
        void check_goal();
        Ball _ball;
        Paddle _paddle;
        int _lives;
};*/

class JetEngine{
    public:
        JetEngine();
        
        void draw(N5110 &lcd);
        int update(UserInput input, bool &CD, bool &bullet_shoot, bool &bullet_move, bool &enemy_jet_move, bool &enemy_jet_generate, bool &enemy_bullet_shoot, bool &enemy_bullet_move, DigitalIn &click, volatile char &random_number);
        int get_score();
        void init();
        void hit_sound(PwmOut &buzzer);
        void hitted_sound(PwmOut &buzzer);
        
    private:
        Bullet _bullet;
        Jet _jet;
        Enemy_jet _enemy_jet;
        Enemy_bullet _enemy_bullet;
        Buff _buff;
        
        int _lives;
        //int _shields;
        int _score;
        int _counter = 0;
        int _counter1 = 0;

        char _buffer;
};

#endif