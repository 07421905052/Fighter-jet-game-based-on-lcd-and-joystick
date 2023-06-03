# ifndef BUFF_H
# define BUFF_H
#include "N5110.h"

class Buff{
    public:
        Buff();

        void draw(N5110 &lcd);
        void update(bool &buff_move);
        void set_coordinate(int x, int y, bool value);
        int get_coordinate(int a, int b);
        bool get_exist();
        void set_exist(bool value);
    private:
        int _counter = 0;
        bool _coordinate_1[46][82] = {0};
        bool _coordinate_2[46][82] = {0};
        bool _ud = 1; //0 for up and 1 for down
        bool _lr = 1; //0 for left and 1 for right
        bool _change;
        bool _exist;
};
#endif