#ifndef LEVELELEMENTINTERFACE_H
#define LEVELELEMENTINTERFACE_H
#include "LevelElementInterface.h"
#endif
#include "SDL.h"
#include "string"

class LevelTexture : public LevelElementInterface {
private:
public:
	//LevelElementInterface
	virtual void close();
	virtual std::string isDead();
	virtual void render();
	virtual void checkInput();
	virtual void restart();
	virtual void tick();
	virtual std::string getType(); //"PLAYERRIGHT", "PLAYERLEFT", "BOTTLE", "BACKGROUND", "PLAYER" (from player class) 
	Bottle* spawnBottle();
};