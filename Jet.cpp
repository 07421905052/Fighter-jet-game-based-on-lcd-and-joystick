#include "Jet.h"

Jet::Jet(){}
void CD_isr();




void Jet::init(){
    _x = 10;
    _y = 23;
}
void Jet::update(UserInput input, bool &CD){

        
    
        if((input.d == N) && (CD == 0) ){
            _y++;
            CD = 1; //After each movement, the next movement will be blocked until the ticker(timer interrupt) removes this limitation. Using timer interrupt to control the moving speed will allow the spaceship to shoot while moving.

        }else if((input.d == S) && (CD == 0)){
            _y--;
            CD = 1;
        
        }else if((input.d == E) && (CD == 0)){
            _x--;
            CD = 1;

        }else if((input.d == W) && (CD == 0)){
            _x++;
            CD = 1;

        }else if((input.d == NE) && (CD == 0)){
            _y++;
            _x--;
            CD = 1;

        }else if((input.d == NW) && (CD == 0)){
            _y++;
            _x++;
            CD = 1;

        }else if((input.d == SE) && (CD == 0)){
            _y--;
            _x--;
            CD = 1;

        }else if((input.d == SW) && (CD == 0)){
            _y--;
            _x++;
            CD = 1;
        } 

        boundary(_x,_y);
        
}

void Jet::draw(N5110 &lcd){
    lcd.drawSprite(_x, _y, 5,8,(int*)Spaceship);
}

void Jet::boundary(int x, int y){
    if (x < 1 ){        //ensure that the point doesnt pass beyond the left hand side of the screen
        _x = 1;
    }else if (x > 75){  //ensure that the point doesnt pass beyond the right hand side of the screen-
        _x = 75;
    }

    if(y < 1){          //ensure that the point doesnt pass beyond the top of the screen
        _y = 1;
    }else if(y > 42){   //ensure that the point doesnt pass beyond the bottom of the screen
        _y = 42;
    }
}

int Jet::get_x(){
    return _x;
}
int Jet::get_y(){
    return _y;
}