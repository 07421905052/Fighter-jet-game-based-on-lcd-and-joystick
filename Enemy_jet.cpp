#include "Enemy_jet.h"


Enemy_jet::Enemy_jet(){}

void Enemy_jet::set_coordinate(int x, int y, bool value){
    _coordinate[x][y] = value;
}

int Enemy_jet::get_coordinate(int a, int b){
    return _coordinate[a][b];
}

void Enemy_jet::init(){
    for(int i=0; i<41; i++){
        for(int j=0; j<74; j++){
            _coordinate[i][j] = 0;
        }
    }
}

void Enemy_jet::update(bool &enemy_jet_move, bool &enemy_jet_generate){
    if(enemy_jet_generate == 1){ //generate a jet each 3s
        enemy_jet_generate = 0;
        int position = rand()%42; //generate a random number from 0 to 41
        _coordinate[position][73] = 1;
        
    }

    if(enemy_jet_move == 1){
        enemy_jet_move = 0;

        for(int i = 0; i<41; i++){ ////////////////////
            for(int j = 0; j<74; j++){ 
                if((_coordinate[i][j]) == 1){
                
                    _coordinate[i][j] = 0;
                    _coordinate[i][j-1] = 1;
                }
                else if((_coordinate[i][0]) == 1){
                    (_coordinate[i][0]) = 0;
                }
                //到边界之后消除

            }
        
        }
    }
}

void Enemy_jet::draw(N5110 &lcd) {
    //printf("Ball: Draw\n");
    for(int i = 1; i<41; i++){
        for(int j = 1; j < 74; j++){
            if(_coordinate[i][j] == 1){
                lcd.drawSprite(1+j,1+i,5,8,(int*)Enemy_Spaceship);
            }
        }
    }
}