#include "accessories.hpp"

int const SCREENWIDTH(1440);
int const SCREENHEIGHT(960);
int const CHARHEIGHT(50);
int const CHARWIDTH(25);
int const TILE(32);
int const LEVEL(2);
int const MAXFALL(5);

int Levels::levelCount=0;

void ImgTexture::loadBMP(SDL_Renderer* ren, const std::string& filename) {
	// Užkraunam BMP į atmintį
	SDL_Surface* surface = SDL_LoadBMP(filename.c_str());

	if (surface) {
		// Iš paveiksliuko padarom tekstūrą, kurią galima piešti į ekraną
		texture = SDL_CreateTextureFromSurface(ren, surface);

		// Paveiksliuko daugiau nebereikia, nes turim tekstūrą
		SDL_FreeSurface(surface);
	}
}


