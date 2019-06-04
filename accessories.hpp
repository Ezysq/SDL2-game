#pragma once

#include <SDL.h>
#include <string>
#include <iostream>

extern const int SCREENWIDTH;
extern const int SCREENHEIGHT;
extern const int CHARHEIGHT;
extern const int CHARWIDTH;
extern const int TILE;
extern const int LEVEL;
extern const int MAXFALL;

class ImgTexture{
    SDL_Texture* texture;
public:
    ImgTexture(): texture(nullptr){}
    ImgTexture(SDL_Renderer* ren, const std::string& filename){ loadBMP(ren, filename);}
    ~ImgTexture(){ SDL_DestroyTexture( texture) ;}

    // loads texture from bmp
    void loadBMP(SDL_Renderer* ren, const std::string& filename);
    SDL_Texture* gTexture(){ return texture; }

    // draw function to render
    void draw(SDL_Renderer* ren,const SDL_Rect& art, const SDL_Rect& position) const{
        SDL_RenderCopy(ren, texture, &art, &position);
    }
    void draw(SDL_Renderer* ren, const SDL_Rect& position) const{
        SDL_RenderCopy(ren, texture, NULL, &position);
    }
};

class Rect{
    SDL_Rect position;
    SDL_Rect art;
public:
    Rect(): position({0, 0, 0, 0}), art({0, 0, 0, 0}){}
    ~Rect(){}
    Rect(const SDL_Rect& ar, const SDL_Rect& pos): art(ar), position(pos){}

    // setting rectangle for positioning in destination
    void setPos(const SDL_Rect& pos){ position=pos; }

    // setting rectangle for positioning in source
    void setArt(const SDL_Rect& ar){ art=ar; }

    // get destination position
    SDL_Rect gPosition() const { return position; }

    //get source position
    SDL_Rect gArt() const {return art;}

};

struct BlackOut{
    static int blackOut;
};

class Levels{
    static int levelCount;
public:
    // to next level
    static void levelUp(){
        if( levelCount + 1 < LEVEL) levelCount++;
    }
    // to previous level
    static void levelDown(){
        if( levelCount > 0) levelCount--;
    }
    // reset to level one
    static void levelOne(){ levelCount = 0; }
    // return level counter
    static int levelCountG() { return levelCount; }
};
