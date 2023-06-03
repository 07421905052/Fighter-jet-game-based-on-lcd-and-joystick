#include "Buff.h"

Buff::Buff(){}

void Buff::set_coordinate(int x, int y, bool value){
    if(_change == 0){
        _coordinate_1[x][y] = value;
    }
    else{
        _coordinate_2[x][y] = value;
    }
}

int Buff::get_coordinate(int a, int b){
    if(_change == 0){
        return _coordinate_1[a][b];
    }
    else{
        return _coordinate_2[a][b];
    }  
}

bool Buff::get_exist(){
    return _exist;
}

void Buff::set_exist(bool value){
    _exist = value;
}

void Buff::draw(N5110 &lcd){
    for(int i = 0; i < 46; i++){
        for(int j = 0; j< 82; j++){
            
            if(_change == 0){
                if(_coordinate_1[i][j] == 1){
                    lcd.drawCircle(i,j,3,FILL_BLACK);
                }
            }
            if(_change == 1){
                if(_coordinate_2[i][j] == 1){
                    lcd.drawCircle(i,j,3,FILL_BLACK);
                }
            }
            
        }
    }
}

void Buff::update(bool &buff_move){
    

    if(buff_move == 1){
        buff_move = 0;
        for(int i = 0; i<81; i++){
            for(int j=0; j<45; j++){
                if(_change == 0){
                    if(_coordinate_1[i][j] == 1){
                        _coordinate_1[i][j] = 0;
                        if((_ud == 1) && (_lr == 1)){ //down right
                            _coordinate_2[i+1][j-1] = 1;
                        }
                        else if((_ud == 0) && (_lr == 1)){ //up right
                            _coordinate_2[i+1][j+1] = 1;
                        }
                        else if((_ud == 1) && (_lr == 0)){ //down left
                            _coordinate_2[i-1][j-1] = 1;
                        }
                        else{ //up left
                            _coordinate_2[i-1][j+1] = 1; 
                        }
                    }
                }
                else{
                    if(_coordinate_2[i][j] == 1){
                        _coordinate_2[i][j] = 0;
                        if((_ud == 1) && (_lr == 1)){ //down right
                            _coordinate_1[i+1][j-1] = 1;
                        }
                        else if((_ud == 0) && (_lr == 1)){ //up right
                            _coordinate_1[i+1][j+1] = 1;
                        }
                        else if((_ud == 1) && (_lr == 0)){ //down left
                            _coordinate_1[i-1][j-1] = 1;
                        }
                        else{ //up left
                            _coordinate_1[i-1][j+1] = 1; 
                        }
                    }
                }
            }
        }
        _change = !_change;
    }
}