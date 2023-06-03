#include "bullet.h"


Bullet::Bullet(){}



void Bullet::set_coordinate(int x, int y, bool value){
    _coordinate[x][y] = value;
}

int Bullet::get_coordinate(int a, int b){
    return _coordinate[a][b];
}

void Bullet::init(){
    for(int i = 0;i<45;i++){
        for(int j=0; j<81; j++){
            _coordinate[i][j] = 0;
        }
    }
}


void Bullet::draw(N5110 &lcd) {
    //printf("Ball: Draw\n");
    //lcd.drawSprite(1,1, 46, 82, (int*)_coordinate); 
    for(int i = 0; i < 46; i++){
        for(int j = 0; j< 82; j++){
            if(_coordinate[i][j] == 1){
                lcd.setPixel(j+1,i+1,1);
            }
        }
    }
}

void Bullet::update(bool &bullet_shoot, bool &bullet_move, int x, int y){
    if(bullet_shoot == 1){
        bullet_shoot = 0;
        _coordinate[y+1][x+7] = 1; //[shorter axis][longer axis] 数组的第一位是0，所以coordinate与spaceship重合的定位点是y-1和x-1
    }
    if(bullet_move == 1){
        bullet_move = 0;
        for(int i = 45; i>1; i--){ //i<46,j<81
            for(int j = 81; j>1; j--){ //为什么是81 0-81是82个数
                if((_coordinate[i][j]) == 1){
                
                    _coordinate[i][j] = 0;
                    _coordinate[i][j+1] = 1;
                }
                else if((_coordinate[i][81]) == 1){
                    (_coordinate[i][81]) = 0;
                }
                //到边界之后消除

                

            }
        
        }
    }
    
    

    /*for(int a = 0; a < 84; a++){
        for(int b = 0; b < 48; b++){
            if(_coordinate[a][b] == 1){
                _coordinate[a][b] = 0;
                _coordinate[a][b+1] = 1;
            }
        }
    }*/
}

