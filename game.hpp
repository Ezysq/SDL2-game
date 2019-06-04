#pragma once
#include <iostream>
#include <vector>
#include <string>

#include "character.hpp"
#include "accessories.hpp"
#include "map.hpp"
#include "endscreen.hpp"

class WinRen{
protected:
    SDL_Window* win;
    SDL_Renderer* ren;
public:
    // creates window and renderer
    WinRen( std::string const& name, int xCord, int yCord, int width, int height, bool fullscreen);

    // destroys renderer and window
    void destructWinRen(){
    	SDL_DestroyRenderer(ren);
        SDL_DestroyWindow(win);
        SDL_Quit();
    }
};

class Game: public WinRen{
    Character player;
    Map map;
    EndScreen finalScreen;
    LifeCounter livesCounter;
public:
    Game(WinRen init): WinRen(init){}
    ~Game(){ destructWinRen(); }

    // loads objects
    void load();

    // game loop
    void loop();
};
