#ifndef UTILS_H
#define UTILS_H
#include "Joystick.h"
struct Position2D {
  int x;
  int y;  
};



struct UserInput {
    Direction d;
    float mag;
};

#endif