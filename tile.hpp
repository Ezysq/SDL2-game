#pragma once
#include <string>
#include "accessories.hpp"
#include "character.hpp"

class Tile{
    ImgTexture texture;
    SDL_Rect position;
    static bool prevTile;
public:
    Tile(): position({0, 0, 0, 0}), texture(){}
    virtual ~Tile(){ }

    // calls texture setter function
    void setTexture(SDL_Renderer* ren, const std::string& filename)
         { texture.loadBMP(ren, filename); }

    // calls texture's draw function
    void draw(SDL_Renderer* ren) const
        { texture.draw(ren, position); }

    // sets rectangle position
    void setPos(const SDL_Rect& pos){ position=pos; }

    // gets rectangle position
    SDL_Rect gposition() const { return position; }

    // calls Imitation texture's setter function
    virtual void setTextureImitation(SDL_Renderer* ren, const std::string& filename) { return; }

    // calls Imitation texture's draw function
    virtual void drawImitation(SDL_Renderer* ren) const { return; }

    // what tile action performs
    virtual bool action(Character& player) {return 0; } //=0;

    // is tile is hidden
    virtual bool tileIsHidden() const =0;

    bool prevTileG(){ return prevTile;}

    void prevTileS(bool x) { prevTile = x;}
};

class HiddenTile: public Tile{
    ImgTexture hiddenTexture;
public:
    HiddenTile(): Tile(), hiddenTexture(){}
    ~HiddenTile(){  }

    // calls Imitation texture's setter function
    void setTextureImitation(SDL_Renderer* ren, const std::string& filename) override
        { hiddenTexture.loadBMP(ren, filename); }

    // calls Imitation texture's draw function
    void drawImitation(SDL_Renderer* ren) const override
       { hiddenTexture.draw(ren, gposition()); }
};
//1
class PlatformTile: public Tile{
public:
    PlatformTile(): Tile(){}
    ~PlatformTile(){}
    bool action(Character& player) override {
        prevTileS(1);
        Character::fall = 0;
        return 0;
    }
    bool tileIsHidden() const override { return 0; }
};
//0
class VoidTile: public Tile{
public:
    VoidTile(): Tile(){}
    ~VoidTile(){}
    bool action(Character& player) override {
        prevTileS(0);
        Character::fall = 1;
        return 0;
    }
    bool tileIsHidden() const override { return 0; }
};
//2
class TeleTile: public HiddenTile{
public:
    TeleTile(): HiddenTile(){}
    ~TeleTile(){}
    bool action(Character& player) override {
        player.teleport();
        prevTileS(1);
        return 0;
    }
    bool tileIsHidden() const override { return 1; }
};
//0
class GhostTile: public HiddenTile{
public:
    GhostTile(): HiddenTile(){}
    ~GhostTile(){}
    bool action(Character& player) override {
        Character::fall=1;
        prevTileS(0);
        return 0;
    }
    bool tileIsHidden() const override { return 1; }

};
//3
class BlackScreenTile: public Tile{
public:
    BlackScreenTile(): Tile(){}
    ~BlackScreenTile(){}
    bool action(Character& player) override {
        BlackOut::blackOut = 100;
        prevTileS(1);
        return 0;
    }
    bool tileIsHidden() const override { return 0; }
};
//4
class SpikesTile: public HiddenTile{
public:
    SpikesTile(): HiddenTile(){}
    ~SpikesTile(){}
    bool action(Character& player) override {
        LifeCounter::fell();
        player.restart();
        return 0;
    }
    bool tileIsHidden() const override { return 1; }
};
//5
class OnlyWalkTile: public Tile{
public:
    OnlyWalkTile(): Tile(){}
    ~OnlyWalkTile(){}
    bool action(Character& player) override {
        if( prevTileG()) return 1;
        return 0;
    }
    bool tileIsHidden() const override { return 0; }
};
//6
class LevelUpTile: public Tile{
public:
    LevelUpTile(): Tile(){}
    ~LevelUpTile(){}
    bool action(Character& player) override {
        Levels::levelUp();
        player.setArt( { 18, 140, CHARWIDTH, CHARHEIGHT } );
        player.restart();
        prevTileS(1);
        return 1;
    }
    bool tileIsHidden() const override { return 0; }
};
//7
class LevelDownTile: public Tile{
public:
    LevelDownTile(): Tile(){}
    ~LevelDownTile(){}
    bool action(Character& player) override {
        Levels::levelDown();
        player.setArt( { 18, 140, CHARWIDTH, CHARHEIGHT } );
        player.restart();
        prevTileS(1);
        return 1;
    }
    bool tileIsHidden() const override { return 0; }
};
//8
class WinTile: public Tile{
public:
    WinTile(): Tile(){}
    ~WinTile(){}
    bool action(Character& player) override {
        LifeCounter::resetFallCounter();
        LifeCounter::finalScrS(1);
        return 1;
    }
    bool tileIsHidden() const override { return 0; }
};
