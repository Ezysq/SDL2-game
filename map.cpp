#include "map.hpp"

#include <iostream>
#include <fstream>


bool Character::fall=1;
bool Tile::prevTile=1;
Map::Map(){
    tiles.push_back(new VoidTile());
    tiles.push_back(new VoidTile());
    tiles.push_back(new PlatformTile());
    tiles.push_back(new PlatformTile());
    tiles.push_back(new PlatformTile());
    tiles.push_back(new TeleTile());
    tiles.push_back(new GhostTile());
    tiles.push_back(new BlackScreenTile());
    tiles.push_back(new SpikesTile());
    tiles.push_back(new OnlyWalkTile());
    tiles.push_back(new LevelUpTile());
    tiles.push_back(new LevelDownTile());
    tiles.push_back(new WinTile());

    mapCoord = new int **[LEVEL];
	for (size_t i = 0; i < LEVEL; ++i) {
		mapCoord[i] = new int *[SCREENHEIGHT/TILE];
        for (size_t y = 0; y < SCREENHEIGHT/TILE; ++y) {
            mapCoord[i][y] = new int [SCREENWIDTH/TILE];
        }
	}
}

Map::~Map(){
    for(size_t i=0; tiles.size() > i; ++i){
        delete tiles[i];
    }
    tiles.clear();

	for (size_t i = 0; i < LEVEL; ++i) {
        for (size_t y = 0; y < SCREENHEIGHT/TILE; ++y) {
            delete[] mapCoord[i][y];
        }
        delete[] mapCoord[i];
	}
	delete mapCoord;
}

void Map::loadTexture(SDL_Renderer* ren){
    tiles[0]->setTexture(ren, "assets/purple.bmp");

    tiles[1]->setTexture(ren, "assets/dirt.bmp");

    tiles[2]->setTexture(ren, "assets/platM.bmp");

    tiles[3]->setTexture(ren, "assets/platL.bmp");

    tiles[4]->setTexture(ren, "assets/platR.bmp");

    tiles[5]->setTexture(ren, "assets/tele.bmp");

    tiles[6]->setTexture(ren, "assets/ghost.bmp");

    tiles[7]->setTexture(ren, "assets/platM.bmp");

    tiles[8]->setTexture(ren, "assets/spikes.bmp");

    tiles[9]->setTexture(ren, "assets/platMBroken.bmp");

    tiles[10]->setTexture(ren, "assets/levelup.bmp");

    tiles[11]->setTexture(ren, "assets/leveldown.bmp");

    tiles[12]->setTexture(ren, "assets/win.bmp");

    for(size_t i = 0; i < tiles.size(); i++)
        if(tiles[i]->tileIsHidden()) tiles[i]->setTextureImitation(ren, "assets/platM.bmp");
}

void Map::loadMap(){
    std::ifstream fw("map1.txt");
    for(size_t column = 0; column < SCREENHEIGHT/TILE; column++){
        for(size_t row = 0; row < SCREENWIDTH/TILE; row++){
            fw >> mapCoord[0][column][row];
        }
    }
   fw.close();

    std::ifstream fw2("map2.txt");
    for(size_t column = 0; column < SCREENHEIGHT/TILE; column++){
        for(size_t row = 0; row < SCREENWIDTH/TILE; row++){
            fw2 >> mapCoord[1][column][row];
        }
    }
    fw2.close();
}

void Map::drawMap(SDL_Renderer* ren, int x, int y){
    int i = Levels::levelCountG();
    targetTexture = SDL_CreateTexture(ren, SDL_PIXELTYPE_UNKNOWN, SDL_TEXTUREACCESS_TARGET, SCREENWIDTH, SCREENHEIGHT);
    SDL_SetRenderTarget(ren, targetTexture);
    int tile=TILE;
    bool reveal=1;
    for(int column=0; column<SCREENHEIGHT/TILE; column++){
        for(int row=0; row<SCREENWIDTH/TILE; row++){
            tiles[mapCoord[i][column][row]]->setPos ({row * tile, column * tile, tile, tile});
            if(x == column && y == row) reveal=0;
            if(tiles[mapCoord[i][column][row]]->tileIsHidden() && reveal) tiles[mapCoord[i][column][row]]->drawImitation(ren);
            else tiles[mapCoord[i][column][row]]->draw(ren);
            reveal=1;
        }
    }
    SDL_SetRenderTarget(ren, nullptr);
}

int Map::tileCheck(SDL_Renderer* ren, Character& player, int x, int y){
    int xc = x / TILE;
    int yc = y / TILE;
    static int drawCounter = 0;

    if(yc >= 30) Character::fall = 1;

    if(tiles[mapCoord[Levels::levelCountG()][yc][xc]]->tileIsHidden() && drawCounter == 0){
        drawMap(ren, yc, xc);
        drawCounter = 50;
    }
    else if(drawCounter > 0) drawCounter--;

    return tiles[mapCoord[Levels::levelCountG()][yc][xc]]->action(player);

    return 0;
}

void Map::update(SDL_Renderer* ren, Character& player){
    if( LifeCounter::fallCounterG() == 0) LifeCounter::finalScrS(2);
    const auto state = SDL_GetKeyboardState(NULL);

    static int jumpPos = 0;
    static int jump = 0;
    static int velocity = 0;

// player updateent
  if(!jump){
        if (state[SDL_SCANCODE_A]) {
            player.left();
        }
        if (state[SDL_SCANCODE_D]) {
            player.right();
        }
  }
// player jump
    // jump counter
    static int counter = 0;
    static bool bo;
    if(state[SDL_SCANCODE_SPACE]) bo=1;
    else bo=0;
    if (bo && jump <= 0) {
        jump ++;
        velocity = 11;
        jumpPos = player.gypos();
        //std::cout << jump << std::endl;
        counter = 20;
    }

    if (bo && jump == 1 && counter == 0){
        jump ++;
        velocity = 7;
        jumpPos = player.gypos();
       // std::cout << jump << std::endl;
    }
    counter--;

    if(jump > 0 && jump < 3) player.jumpf(velocity);
    if(tileCheck(ren, player, player.gxpos()+CHARWIDTH/2, player.gypos()+CHARHEIGHT)) drawMap(ren);
    if(!Character::fall && jump <= 2){
        jump = 0;
    }
    if(jumpPos > player.gypos()) velocity--;

// player falling

    if(Character::fall && !jump){
        player.setYpos(player.gypos() +8);
    }

    //LifeCounter::finalScrS(0);
}
