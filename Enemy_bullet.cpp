#include "Enemy_bullet.h"


Enemy_bullet::Enemy_bullet(){
   
}

void Enemy_bullet::init(){
    _change = 0;
    _radius = 0;
    _shockwave_x = 0;
    _shockwave_y = 0;
    _exist = 0;
    for(int i=0; i<45; i++){
        for(int j=0; j<81; j++){
            _coordinate[i][j] = 0;
            _coordinate_lb[i][j] = 0;
            _coordinate_rb_1[i][j] = 0;
            _coordinate_rb_2[i][j] = 0;
            
            

            
        }
    }
}

void Enemy_bullet::set_coordinate(int x, int y, bool value){
    _coordinate[x][y] = value;
}
void Enemy_bullet::set_coordinate_lb(int x, int y, bool value){
    _coordinate_lb[x][y] = value;
}
void Enemy_bullet::set_coordinate_rb(int x, int y, bool value){
    if(_change == 0){
        _coordinate_rb_1[x][y] = value;
    }
    else{
        _coordinate_rb_2[x][y] = value;
    }
}


int Enemy_bullet::get_coordinate(int a, int b){
     return _coordinate[a][b];
}
int Enemy_bullet::get_coordinate_lb(int a, int b){
     return _coordinate_lb[a][b];
}
int Enemy_bullet::get_coordinate_rb(int a, int b){
    if(_change == 0){
        return _coordinate_rb_1[a][b];
    }
    else{
        return _coordinate_rb_2[a][b];
    }    
}



void Enemy_bullet::draw(N5110 &lcd) {

    if(_exist == 1){
        lcd.drawCircle(_shockwave_y, _shockwave_x, _radius, FILL_TRANSPARENT);
    }
    
    for(int i = 0; i < 46; i++){
        for(int j = 0; j< 82; j++){
            if(_coordinate[i][j] == 1){
                lcd.setPixel(j+1,i+1,1);
            }
            if(_coordinate_lb[i][j] == 1){
                lcd.setPixel(j+1,i+1,1);
            }
            /*if(_coordinate_rb[i][j] == 1){
                lcd.setPixel(j+1,i+1,1);
            }*/
            if(_change == 0){
                if(_coordinate_rb_1[i][j] == 1){
                    lcd.setPixel(j+1,i+1,1);
                }
            }
            if(_change == 1){
                if(_coordinate_rb_2[i][j] == 1){
                    lcd.setPixel(j+1,i+1,1);
                }
            }

            
            
        }
    }

}

void Enemy_bullet::update(bool &enemy_bullet_shoot, bool &enemy_bullet_move, Enemy_jet &_enemy_jet, volatile char &random_number){
    if(enemy_bullet_shoot == 1){
        enemy_bullet_shoot = 0;
        for (int i = 0; i < 42; i++){
            for(int j = 0; j< 75; j++){
                if(_enemy_jet.get_coordinate(i,j) == 1){ //if the current position has an enemy jet
                    _coordinate[i+2][j-1] = 1;
                    _coordinate_lb[i+1][j-1] = 1;
                    if(_change == 0){
                        _coordinate_rb_1[i+3][j-1] = 1;
                        
                    }
                    if(_change == 1){
                        _coordinate_rb_2[i+3][j-1] = 1;
                        
                    }

                    if(_exist == 0){
                        int token = rand()%random_number; //generate a random number from 0 to 9, so the possibility of generating a wave is 10%
                        if(token == 0){
                            _shockwave_x = i+2;
                            _shockwave_y = j-1;
                            _exist = 1;
                            
                        }
                    }

                    

                }
                

            }
        }
    }

    if(enemy_bullet_move == 1){
        enemy_bullet_move = 0;

        if(_exist == 1){
            if(_radius < 85){
                _radius++;
            }
            else{
                _radius = 0;
                _exist = 0;
            }
        }
        

        for(int i = 0; i<45; i++){ //i<46,j<81
            for(int j = 0; j<81; j++){ //为什么是81 0-81是82个数

                
                if((_coordinate[i][0]) == 1){ //remove the bullet when it reaches the edge
                    (_coordinate[i][0]) = 0;
                }
                else if((_coordinate[i][j]) == 1){ //move the bullet.
                    _coordinate[i][j] = 0;
                    _coordinate[i][j-1] = 1;   
                }

                
                if((_coordinate_lb[0][j]) == 1 ){ //reach left edge
                    (_coordinate_lb[0][j]) = 0;
                }
                else if(_coordinate_lb[i][0] == 1){ //reach bottom
                    _coordinate_lb[i][0] = 0;
                }
                else if((_coordinate_lb[i][j]) == 1){
                    _coordinate_lb[i][j] = 0;
                    _coordinate_lb[i-1][j-1] = 1;   
                }

                if(_change == 0){
                    if(_coordinate_rb_1[45][j] == 1){ //reach right edge
                        _coordinate_rb_1[45][j] = 0;  
                    }
                    else if(_coordinate_rb_1[i][0] == 1){//reach bottom
                        _coordinate_rb_1[i][0] = 0;
                    } 
                    else if(_coordinate_rb_1[i][j] == 1){
                        _coordinate_rb_1[i][j] = 0;
                        _coordinate_rb_2[i+1][j-1] = 1;     
                    }
                }
                if(_change == 1){
                    if(_coordinate_rb_2[45][j] == 1){ //reach right edge
                        _coordinate_rb_2[45][j] = 0;  
                    }
                    else if(_coordinate_rb_2[i][0] == 1){//reach bottom
                        _coordinate_rb_2[i][0] = 0;
                    } 
                    else if(_coordinate_rb_2[i][j] == 1){
                        _coordinate_rb_2[i][j] = 0;
                        _coordinate_rb_1[i+1][j-1] = 1;     
                    }
                }

                
                
                

            }
        }
        _change = !_change;
        
    }

   
}

char Enemy_bullet::get_radius(){
    return _radius;
}

char Enemy_bullet::get_shockwave_x(){
    return _shockwave_x;
}

char Enemy_bullet::get_shockwave_y(){
    return _shockwave_y;
}

