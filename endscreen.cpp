#include "endscreen.hpp"

void EndScreen::load(SDL_Renderer* ren){
    success.loadBMP(ren, "assets/success.bmp");
    gameOver.loadBMP(ren, "assets/gameOver.bmp");
}

void LifeCounter::load(SDL_Renderer* ren){
    icon.loadBMP(ren, "assets/livesicon.bmp");
}

void LifeCounter::drawIcon(SDL_Renderer* ren){
    for(int i = 0; i < fallCounterG(); i++){
        icon.draw(ren, {(150 + TILE) + TILE*i, TILE , TILE, TILE});
    }
}
