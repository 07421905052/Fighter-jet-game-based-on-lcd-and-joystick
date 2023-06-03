#ifndef BULLET_H
#define BULLET_H
#include "N5110.h"


class Bullet{
    public:
        Bullet();
        Bullet(int coordinate, int speed);
        
        void draw(N5110 &lcd);
        void update(bool &bullet_shoot, bool &bullet_move, int x, int y);
        void init();

        void set_coordinate(int x, int y, bool value);
        int get_coordinate(int a, int b);
        

    private:
        bool _coordinate[46][82]={0}; //all zero initialization
        
        
        
};


#endif