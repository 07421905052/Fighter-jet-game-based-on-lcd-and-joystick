#ifndef ENEMY_JET_H
#define ENEMY_JET_H
#include "N5110.h"
#include <cstdlib>

const int Enemy_Spaceship[5][8] = {
    {0,0,0,0,0,0,1,1},
    {0,1,0,1,1,1,1,0},
    {1,1,1,1,1,1,1,1},
    {0,1,0,1,1,1,1,0},
    {0,0,0,0,0,0,1,1},
    
};



class Enemy_jet{
    public:
        Enemy_jet();
        void draw(N5110 &lcd);
        void update(bool &enemy_jet_move, bool &enemy_jet_generate);
        int get_coordinate(int a, int b);
        void set_coordinate(int x, int y, bool value);
        void init();

    private:
        bool _coordinate[42][75]={0}; //all zero initialization
};

#endif