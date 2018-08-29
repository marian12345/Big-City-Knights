#ifndef ABSTRACTTEXTURE_H
#define ABSTRACTTEXTURE_H
#include "AbstractTexture.h"
#endif
#include "SDL.h"
#include <stdio.h>
#include <string>
#include "Bat.h"
#include <array>
#ifndef LEVELELEMENTINTERFACE_H
#define LEVELELEMENTINTERFACE_H
#include "LevelElementInterface.h"
#endif

class Background : public AbstractTexture, public LevelElementInterface {
private:
	std::array<SDL_Texture*, 6> far_buildings; //First one is the current shown Texture
	std::array<SDL_Texture*, 26> foregrounds; //First one is the current shown Texture
	std::array < Bat*, 6 > bats;
	SDL_Texture* backgroundTX;
	int far_buildings_ticker;
	int foreground_ticker;
	bool filling_up_the_bottle;
public:
	Background();
	~Background();
	//LevelElementInterface
	void render();
	void tick();
	void restart();
	void close();
	bool loadMedia();
	std::string getType(); //returns "PLAYERRIGHT", "PLAYERLEFT", "BOTTLE", "BACKGROUND" 
	Bottle* spawnBottle();
	void checkInput();
	std::string isDead(); //returns "NOTDEAD", "DEADPLAYER", "BROKENBOTTLE"
};
