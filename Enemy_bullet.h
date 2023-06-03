#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H

#include "N5110.h"
#include "Enemy_jet.h"

class Enemy_bullet{
    public:
        Enemy_bullet();
        
        
        void draw(N5110 &lcd);
        void update(bool &enemy_bullet_shoot, bool &enemy_bullet_move, Enemy_jet &enemy_jet, volatile char &random_number);
        void init();

        void set_coordinate(int x, int y, bool value);
        void set_coordinate_lb(int x, int y, bool value);
        void set_coordinate_rb(int x, int y, bool value);
        
        int get_coordinate(int a, int b);
        int get_coordinate_lb(int a, int b);
        int get_coordinate_rb(int a, int b);

        char get_radius();
        char get_shockwave_x();
        char get_shockwave_y();
        
        

    private:
        bool _coordinate[46][82]={0}; //all zero initialization
        bool _coordinate_lb[46][82] = {0}; 
        bool _coordinate_rb_1[46][82] = {0};
        bool _coordinate_rb_2[46][82] = {0};
        bool _change = 0;

        char _shockwave_x = 0;
        char _shockwave_y = 0;
        bool _exist = 0;
        char _radius = 0;
        
        
        
        
        
};

#endif