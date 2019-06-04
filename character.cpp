#include "character.hpp"

void Character::left(){
    rectangle.setArt({18, 77, CHARWIDTH, CHARHEIGHT });
    setXpos(gxpos() - 5);
}

void Character::right(){
    rectangle.setArt({18, 205, CHARWIDTH, CHARHEIGHT });
    setXpos(gxpos() + 5);
}

void Character::jumpf(int velocity){
    const auto state = SDL_GetKeyboardState(NULL);

    if (state[SDL_SCANCODE_A])
        left();
    else if (state[SDL_SCANCODE_D])
        right();

    setYpos(gypos() - velocity);
}

void Character::teleport(){
    rectangle.setArt({18, 140, CHARWIDTH, CHARHEIGHT });
   if(gxpos() + 150 < SCREENWIDTH - CHARWIDTH) setXpos(gxpos() + 150);
        else setXpos(gxpos() - 150);
    if(gypos() - 300 > 0) setYpos(gypos() - 300);
        else setYpos(gypos() + 300);
}

void Character::boundaries(){
    if (gxpos() <= 5) setXpos(5);
    if (gxpos() >= SCREENWIDTH - CHARWIDTH - 5 ) setXpos(SCREENWIDTH - CHARWIDTH - 5);
    if (gypos() + 10 + CHARHEIGHT > SCREENHEIGHT){
        restart();
        LifeCounter::fell();
    }
    if (gypos() - 5  < 5 ) setYpos(5);
}

void Character::restart(){
    setXpos(75);
    setYpos(800);
}

void Character::updateent(const int& action){
/*
    const auto state = SDL_GetKeyboardState(NULL);


    static bool fall = 0;
    static int jumpPos;
    static int jump;
    static int velocity;


    switch(action){
    case 0:
        fall=1;
        break;
    case 1:
        break;
    case 2:
         teleport();
        break;
    }

// player updateent
  if(jump == 0){
        if (state[SDL_SCANCODE_A]) {
             left();
        }
        if (state[SDL_SCANCODE_D]) {
             right();
        }
  }
// player jump
    static int counter;
    bool bo;
    if(state[SDL_SCANCODE_SPACE]) bo=1;
    else bo=0;
    if (bo && jump <= 0) {
        jump ++;
        velocity = 11;
        jumpPos = gypos();
        counter = 20;
    }
    if (bo && jump == 1 && counter == 0){
        jump ++;
        velocity = 7;
        jumpPos = gypos();
    }
    counter--;

    if(jump > 0 && jump < 3) jumpf(velocity, fall);

    if(action == 1) fall=0;
    if(!fall && jump <= 2){
        jump = 0;
    }
    if(jumpPos >  gypos()) velocity--;
// player falling

    if(fall&& !jump){
        setYpos(gypos() +8);
    }

    boundaries();
*/
}
