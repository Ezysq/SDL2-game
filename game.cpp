#include "game.hpp"

int LifeCounter::fallCounter = MAXFALL;
int LifeCounter::finalScr = 0;
int BlackOut::blackOut = 0;

WinRen :: WinRen( std::string const& name, int xCord, int yCord, int width, int height, bool fullscreen){

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw std::runtime_error(SDL_GetError() );
		return ;
	}

    int flag = SDL_WINDOW_SHOWN;
	if(fullscreen){
        flag = SDL_WINDOW_FULLSCREEN;
	}

	win = SDL_CreateWindow(name.c_str(), xCord, yCord, width, height, flag);
	if (win == nullptr) {
		throw std::runtime_error(SDL_GetError() );
		SDL_Quit();
		return ;
	}

	ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (ren == nullptr) {
		SDL_DestroyWindow(win);
		throw std::runtime_error(SDL_GetError() );
		SDL_Quit();
	}
}

void Game::load(){
    player.setArt({ 18, 140, CHARWIDTH, CHARHEIGHT });
    player.setPos({ 75, 800, CHARWIDTH, CHARHEIGHT });
    player.loadImg(ren, "pics/player.bmp");
    player.setXpos(75);
    player.setYpos(800);

    map.loadTexture(ren);
    map.loadMap();
    map.drawMap(ren);
    finalScreen.load(ren);
    livesCounter.load(ren);
}

void Game::loop(){
    load();
    const int framDelay = 1000/60;
    Uint32 frameStart;
    int frameTime;

	const auto state = SDL_GetKeyboardState(NULL);

    player.setArt( { 18, 140, CHARWIDTH, CHARHEIGHT } );
	while (1) {
        frameStart = SDL_GetTicks();

        player.setPos( { player.gxpos(), player.gypos(), CHARWIDTH, CHARHEIGHT } );
		SDL_PumpEvents();

    // closes program
        SDL_Event event;
        SDL_PollEvent(&event);
		if (state[SDL_SCANCODE_Q] || event.type == SDL_QUIT){
			break;
		}

    // restart whole game
        if (state[SDL_SCANCODE_R] && LifeCounter::finalScrrG() > 0){
            Levels::levelOne();
            player.restart();
            LifeCounter::finalScrS(0);
            LifeCounter::resetFallCounter();
            map.drawMap(ren);
        }

        map.update(ren, player);
        player.boundaries();

		SDL_RenderClear(ren);

    /* Draw objects here */

        if( LifeCounter::finalScrrG() == 1) finalScreen.drawSuccess(ren);
        else if( LifeCounter::finalScrrG() == 2) finalScreen.drawGameOver(ren);
        else{
            map.renderMap(ren);
            if(BlackOut::blackOut > 0){
                SDL_RenderClear(ren);
                BlackOut::blackOut--;
            }
            livesCounter.drawIcon(ren);
            player.draw(ren);
        }
		SDL_RenderPresent(ren);

    // fps
		frameTime = SDL_GetTicks() - frameStart;
		if(framDelay > frameTime){
            SDL_Delay(framDelay - frameTime);
		}
	}
}
