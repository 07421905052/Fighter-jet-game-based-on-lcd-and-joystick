#ifndef JET_H
#define JET_H

#include "mbed.h"
#include "N5110.h"
#include "Utils.h"

/*class Paddle
{
public:

    Paddle();
    void init(int x,int height,int width);
    void draw(N5110 &lcd);
    void update(UserInput input);
    void add_score();
    int get_score();
    Position2D get_pos();
    int get_height();
    int get_width();

private:

    int _height;
    int _width;
    int _x;
    int _y;
    int _speed;
    int _score;

};*/

const int Spaceship[5][8] = {
    {1,1,1,0,0,0,0,0},
    {0,1,1,1,1,1,1,0},
    {1,1,1,1,1,1,1,1},
    {0,1,1,1,1,1,1,0},
    {1,1,1,0,0,0,0,0},
    
};

class Jet{
    public:
        Jet();
        void init(); //initial position
        void draw(N5110 &lcd);
        void update(UserInput input, bool &CD);
        void boundary(int x, int y);
        int get_x();
        int get_y();

    private:
        int _x;
        int _y;


};
#endif