#include "JetEngine.h"

JetEngine::JetEngine(){
   
    _lives = 5;
    //_shields = 0;
    _score = 0;
}

int JetEngine::get_score(){
    return _score;
}
void JetEngine::init(){
    _lives = 5;
    _score = 0;
    _counter = 0;
    _counter1 = 0;
    _bullet.init();
    _enemy_jet.init();
    _enemy_bullet.init();
    _jet.init();
}

void JetEngine::draw(N5110 &lcd) {
    lcd.drawRect(0,0,84,48,FILL_TRANSPARENT);   //draws screen boarder
    
    _bullet.draw(lcd);
    _jet.draw(lcd);
    _enemy_jet.draw(lcd);
    _enemy_bullet.draw(lcd);
    //_buff.draw(lcd);
    lcd.drawSprite(78,1,21,5,(int*)score); //长边， 短边
    int gewei = _score%10;
    int shiwei = _score/10%10;
    int baiwei = _score/100%10;
    
    if(gewei == 0){
        lcd.drawSprite(78,31,3,5,(int*)zero);
    }
    else if(gewei == 1){
        lcd.drawSprite(78,31,3,5,(int*)one);
    }
    else if(gewei == 2){
        lcd.drawSprite(78,31,3,5,(int*)two);
    }
    else if(gewei == 3){
        lcd.drawSprite(78,31,3,5,(int*)three);
    }
    else if(gewei == 4){
        lcd.drawSprite(78,31,3,5,(int*)four);
    }
    else if(gewei == 5){
        lcd.drawSprite(78,31,3,5,(int*)five);
    }
    else if(gewei == 6){
        lcd.drawSprite(78,31,3,5,(int*)six);
    }
    else if(gewei == 7){
        lcd.drawSprite(78,31,3,5,(int*)seven);
    }
    else if(gewei == 8){
        lcd.drawSprite(78,31,3,5,(int*)eight);
    }
    else if(gewei == 9){
        lcd.drawSprite(78,31,3,5,(int*)nine);
    }
    else{
        lcd.drawSprite(78,31,3,5,(int*)zero);
    }
    
    if(shiwei == 0){
        lcd.drawSprite(78,27,3,5,(int*)zero);
    }
    else if(shiwei == 1){
        lcd.drawSprite(78,27,3,5,(int*)one);
    }
    else if(shiwei == 2){
        lcd.drawSprite(78,27,3,5,(int*)two);
    }
    else if(shiwei == 3){
        lcd.drawSprite(78,27,3,5,(int*)three);
    }
    else if(shiwei == 4){
        lcd.drawSprite(78,27,3,5,(int*)four);
    }
    else if(shiwei == 5){
        lcd.drawSprite(78,27,3,5,(int*)five);
    }
    else if(shiwei == 6){
        lcd.drawSprite(78,27,3,5,(int*)six);
    }
    else if(shiwei == 7){
        lcd.drawSprite(78,27,3,5,(int*)seven);
    }
    else if(shiwei == 8){
        lcd.drawSprite(78,27,3,5,(int*)eight);
    }
    else if(shiwei == 9){
        lcd.drawSprite(78,27,3,5,(int*)nine);
    }
    else{
        lcd.drawSprite(78,27,3,5,(int*)zero);
    }

    if(baiwei == 0){
        lcd.drawSprite(78,23,3,5,(int*)zero);
    }
    else if(baiwei == 1){
        lcd.drawSprite(78,23,3,5,(int*)one);
    }
    else if(baiwei == 2){
        lcd.drawSprite(78,23,3,5,(int*)two);
    }
    else if(baiwei == 3){
        lcd.drawSprite(78,23,3,5,(int*)three);
    }
    else if(baiwei == 4){
        lcd.drawSprite(78,23,3,5,(int*)four);
    }
    else if(baiwei == 5){
        lcd.drawSprite(78,23,3,5,(int*)five);
    }
    else if(baiwei == 6){
        lcd.drawSprite(78,23,3,5,(int*)six);
    }
    else if(baiwei == 7){
        lcd.drawSprite(78,23,3,5,(int*)seven);
    }
    else if(baiwei == 8){
        lcd.drawSprite(78,23,3,5,(int*)eight);
    }
    else if(baiwei == 9){
        lcd.drawSprite(78,23,3,5,(int*)nine);
    }
    else{
        lcd.drawSprite(78,23,3,5,(int*)zero);
    }

    if(_lives >= 1){
        lcd.drawSprite(79,36,2,3,(int*)lives);
    }
    if(_lives >= 2){
        lcd.drawSprite(79,38,2,3,(int*)lives);
    }
    if(_lives >= 3){
        lcd.drawSprite(79,40,2,3,(int*)lives);
    }
    if(_lives >= 4){
        lcd.drawSprite(79,42,2,3,(int*)lives);
    }
    if(_lives >= 5){
        lcd.drawSprite(79,44,2,3,(int*)lives);
    }
    
}


/*int PongEngine::update(UserInput input) {   
    //printf("Pong Engine: Update\n");
    check_goal();  // checking for a goal is a priority 
    _ball.update();
    _paddle.update(input);
    // important to update paddles and ball before checking collisions so can
    // correct for it before updating the display
    check_wall_collision();
    check_paddle_collision();
    
    return _lives;
}*/
int JetEngine::update(UserInput input, bool &CD, bool &bullet_shoot, bool &bullet_move,bool &enemy_jet_move, bool &enemy_jet_generate, bool &enemy_bullet_shoot, bool &enemy_bullet_move, DigitalIn &click, volatile char &random_number){
    _jet.update(input, CD);
    int x = _jet.get_x();
    int y = _jet.get_y();
    _bullet.update(bullet_shoot, bullet_move, x, y);
    _enemy_jet.update(enemy_jet_move, enemy_jet_generate);
    _enemy_bullet.update(enemy_bullet_shoot, enemy_bullet_move, _enemy_jet,random_number);
    if(_buffer>0){
        _buffer--;
    }
    
    if( ((char)sqrt(abs(x-_enemy_bullet.get_shockwave_y())*abs(x-_enemy_bullet.get_shockwave_y()) + abs(y-_enemy_bullet.get_shockwave_x())*abs(y-_enemy_bullet.get_shockwave_x()))) == _enemy_bullet.get_radius() ){
        if((click == 1)&&(_buffer == 0)){
            _lives--;
            _counter1 = 15;
            _buffer = 10;
        }
    }

    for(int i = 0; i<45; i++){ 
        for(int j = 0; j<81; j++){

            if(_bullet.get_coordinate(i,j) == 1){//detect collision between player's bullet and enemy jet
                
                if(_enemy_jet.get_coordinate(i,j) == 1) {
                    _bullet.set_coordinate(i,j,0);
                    _enemy_jet.set_coordinate(i,j,0);
                    _score++;
                    _counter = 10;
                    /*if(_buff.get_exist() == 0){
                        _buff.set_coordinate(i,j,1);
                    }*/
                }
                if(_enemy_jet.get_coordinate(i-1,j) == 1){
                    _bullet.set_coordinate(i,j,0);
                    _enemy_jet.set_coordinate(i-1,j,0);
                    _score++;
                    _counter = 10;
                    /*if(_buff.get_exist() == 0){
                        _buff.set_coordinate(i-1,j,1);
                    }*/
                }
                if(_enemy_jet.get_coordinate(i-2,j) == 1){
                    _bullet.set_coordinate(i,j,0);
                    _enemy_jet.set_coordinate(i-2,j,0);
                    _score++;
                    _counter = 10;
                    /*if(_buff.get_exist() == 0){
                        _buff.set_coordinate(i-2,j,1);
                    }*/
                }
                if(_enemy_jet.get_coordinate(i-3,j) == 1){
                    _bullet.set_coordinate(i,j,0);
                    _enemy_jet.set_coordinate(i-3,j,0);
                    _score++;
                    _counter = 10;
                    /*if(_buff.get_exist() == 0){
                        _buff.set_coordinate(i-3,j,1);
                    }*/
                }
                if(_enemy_jet.get_coordinate(i-4,j) == 1){
                    _bullet.set_coordinate(i,j,0);
                    _enemy_jet.set_coordinate(i-4,j,0);
                    _score++;
                    _counter = 10;
                    /*if(_buff.get_exist() == 0){
                        _buff.set_coordinate(i-4,j,1);
                    }*/
                }
                if(_enemy_jet.get_coordinate(i,j-1) == 1) {
                    _bullet.set_coordinate(i,j,0);
                    _enemy_jet.set_coordinate(i,j-1,0);
                    _score++;
                    _counter = 10;
                    /*if(_buff.get_exist() == 0){
                        _buff.set_coordinate(i,j-1,1);
                    }*/
                }
                if(_enemy_jet.get_coordinate(i-1,j-1) == 1){
                    _bullet.set_coordinate(i,j,0);
                    _enemy_jet.set_coordinate(i-1,j-1,0);
                    _score++;
                    _counter = 10;
                    /*if(_buff.get_exist() == 0){
                        _buff.set_coordinate(i-1,j-1,1);
                    }*/
                }
                if(_enemy_jet.get_coordinate(i-2,j-1) == 1){
                    _bullet.set_coordinate(i,j,0);
                    _enemy_jet.set_coordinate(i-2,j-1,0);
                    _score++;
                    _counter = 10;
                    /*if(_buff.get_exist() == 0){
                        _buff.set_coordinate(i-2,j-1,1);
                    }*/
                }
                if(_enemy_jet.get_coordinate(i-3,j-1) == 1){
                    _bullet.set_coordinate(i,j,0);
                    _enemy_jet.set_coordinate(i-3,j-1,0);
                    _score++;
                    _counter = 10;
                    /*if(_buff.get_exist() == 0){
                        _buff.set_coordinate(i-3,j-1,1);
                    }*/
                }
                if(_enemy_jet.get_coordinate(i-4,j-1) == 1){
                    _bullet.set_coordinate(i,j,0);
                    _enemy_jet.set_coordinate(i-4,j-1,0);
                    _score++;
                    _counter = 10;
                    /*if(_buff.get_exist() == 0){
                        _buff.set_coordinate(i-4,j-1,1);
                    }*/
                }
            }

            if((_enemy_jet.get_coordinate(i,j) == 1) && ((_jet.get_x() >= j-6) && (_jet.get_x() <= j+8) ) && ( (_jet.get_y() >= (i - 3)) && (_jet.get_y() <= (i + 5)) )  ){ //detect the collision between player's jet and enemy jet
                //if( (_jet.get_y() > (i - 4)) && (_jet.get_y() < (i + 4)) ){
                    _enemy_jet.set_coordinate(i,j,0);
                    _lives--;
                    _counter1 = 15;
                //}
            }

            if( (_enemy_bullet.get_coordinate(i,j) == 1 ) && ( (_jet.get_x() >= j-6) && (_jet.get_x() <= j+1) ) &&  ( (_jet.get_y() >= i-3) && (_jet.get_y() <= i+1) ) ){
                _enemy_bullet.set_coordinate(i,j,0);
                _lives--;
                _counter1 = 15;
            }
            if( (_enemy_bullet.get_coordinate_lb(i,j) == 1 ) && ( (_jet.get_x() >= j-6) && (_jet.get_x() <= j+1) ) &&  ( (_jet.get_y() >= i-3) && (_jet.get_y() <= i+1) ) ){
                _enemy_bullet.set_coordinate_lb(i,j,0);
                _lives--;
                _counter1 = 15;
            }
            if( (_enemy_bullet.get_coordinate_rb(i,j) == 1 ) && ( (_jet.get_x() >= j-6) && (_jet.get_x() <= j+1) ) &&  ( (_jet.get_y() >= i-3) && (_jet.get_y() <= i+1) ) ){
                _enemy_bullet.set_coordinate_rb(i,j,0);
                _lives--;
                _counter1 = 15;
            }

            
        }
        
    }
    
    //对比

    return _lives;
}

void JetEngine::hit_sound(PwmOut &buzzer){
    if(_counter != 0){
        buzzer.period_us((float) 1000000.0f/ (float) CENTER3);    //set the period of the pwm signal (in us)
        buzzer.pulsewidth_us(buzzer.read_period_us()/2);            //set pulse width of the pwm to 1/2 the period
        _counter--;
    }
    else{
        buzzer.pulsewidth_us(0); 
    }

}

void JetEngine::hitted_sound(PwmOut &buzzer){
    if(_counter1 != 0){
        buzzer.period_us((float) 1000000.0f/ (float) (CENTER1 + 6.8*_counter1));    //set the period of the pwm signal (in us)
        buzzer.pulsewidth_us(buzzer.read_period_us()/2);            //set pulse width of the pwm to 1/2 the period
        _counter1--;
    }
    else{
        buzzer.pulsewidth_us(0); 
    }

}





