#pragma once

#include "accessories.hpp"
#include <vector>
#include <iostream>
#include "character.hpp"
#include "tile.hpp"

class Map{
    std::vector<Tile *> tiles;
    SDL_Texture* targetTexture;
    int*** mapCoord;
public:

    Map();
    ~Map();
    // loads map from txt
    void loadMap();
    // renders tiles to 1 texture
    void drawMap(SDL_Renderer* ren, int x = 0, int y = 0);
    // loads texture to tiles
    void loadTexture(SDL_Renderer* ren);
    // renders texture
    void renderMap(SDL_Renderer* ren)
        { SDL_RenderCopy(ren, targetTexture, NULL, NULL); }
    // checks tile for different action
    int tileCheck(SDL_Renderer* ren, Character& player, int x, int y);

    // updates platform
    void update(SDL_Renderer* ren, Character& player);
};
