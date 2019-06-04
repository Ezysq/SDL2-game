#ifndef ENDSCREEN_HPP
#define ENDSCREEN_HPP

#include "accessories.hpp"

class EndScreen{
    ImgTexture success;
    ImgTexture gameOver;
public:
    EndScreen(): success(), gameOver(){}
	~EndScreen(){ }

    // loads textures
	void load(SDL_Renderer* ren);

    // draw success
	void drawSuccess(SDL_Renderer* ren) { success.draw(ren, {0, 0, 1440, 960}); }

	// draw game over
	void drawGameOver(SDL_Renderer* ren) { gameOver.draw(ren, {0, 0, 1440, 960}); }

};

class LifeCounter{
    static int fallCounter;
    ImgTexture icon;
    Rect iconRectagle;
    static int finalScr;
public:

    LifeCounter(): icon(), iconRectagle() {}
    ~LifeCounter() {}

    // loads textures
    void load(SDL_Renderer* ren);

    // draws counter
    void drawIcon(SDL_Renderer* ren);

    // falls from platform
    static void fell(){ fallCounter--; }

    // return counter's value
    static int fallCounterG() { return fallCounter; }

    // set finalScr value
    static void finalScrS(int a) { finalScr = a; }

    // return finalScr value
    static int finalScrrG() { return finalScr; }

    // reset counter
    static void resetFallCounter() { fallCounter = MAXFALL; }
};

#endif
