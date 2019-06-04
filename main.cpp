#include "game.hpp"

int main(int argc, char** argv) {

    Game game(WinRen("Platformer", 80, 80, SCREENWIDTH, SCREENHEIGHT, 0));

    game.loop();
	return 0;
}
