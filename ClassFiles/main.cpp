//Using SDL and standard IO
#include "Game.h"
enum Screensize : bool { DISABLE_FULLSCREEN = false, ENABLE_FULLSCREEN = true };

int main(int argc, char* args[])
{
	Game* game = new Game(ENABLE_FULLSCREEN);
	game->start();
	delete game;
	
	return 0;
};