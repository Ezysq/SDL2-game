#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <iostream>
#include "accessories.hpp"
#include "endscreen.hpp"
//#include "map.hpp"

class Character {
    ImgTexture texture;
    Rect rectangle;
    int xpos, ypos;
public:
    static bool fall;
	Character(const ImgTexture& tex, const Rect& rec):
	     texture(tex), rectangle(rec){}
	Character(): texture(), rectangle(){}
	~Character(){ }

    // sets characters coordinates
    void setXpos(const int& x){ xpos=x; }
    void setYpos(const int& y){ ypos=y; }
    // gets character coordinates
    int gxpos() const { return xpos; }
    int gypos() const { return ypos; }

    // sets rectangle for positioning and art
    void setPos(const SDL_Rect& pos){ rectangle.setPos(pos); }
    void setArt(const SDL_Rect& ar){ rectangle.setArt(ar); }

    void loadRect(const SDL_Rect& pos, const SDL_Rect& art)
        {rectangle.setPos(pos); rectangle.setArt(art); }
    // calls texture for loading img
    void loadImg(SDL_Renderer* ren, const std::string& filename)
        { texture.loadBMP(ren, filename); }
    // calls texture for drawing
    void draw(SDL_Renderer* ren)
       { texture.draw(ren, rectangle.gArt(), rectangle.gPosition()); }

    // characters updateents
    void updateent(const int& action);

    void left();
    void right();
    void jumpf(int velocity);
    void teleport();
    void boundaries();
    void restart();
};

#endif // !CHARACTER_HPP
