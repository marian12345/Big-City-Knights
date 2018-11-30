#ifndef LEVELTEXTURE_H
#define LEVELTEXTURE_H
#endif
#ifndef BOTTLE_H
#define BOTTLE_H
#include "Bottle.h"
#endif
#ifndef LEVELELEMENTINTERFACE_H
#define LEVELELEMENTINTERFACE_H
#include "LevelElementInterface.h"
#endif
#ifndef MENUTEXTURE_H
#define MENUTEXTURE_H
#include "MenuTexture.h"
#endif

class LevelTexture : public LevelElementInterface, public MenuTexture {
private:
	int alpha;
	bool alpha_increasing;
public:
	LevelTexture(std::string text, std::string fontpath, int fontsize, SDL_Color color);
	//LevelElementInterface
	virtual bool loadMedia();
	virtual void close();
	virtual std::string isDead();
	virtual void render();
	virtual void checkInput();
	virtual void restart();
	virtual void tick();
	virtual std::string getType(); //"PLAYERRIGHT", "PLAYERLEFT", "BOTTLE", "BACKGROUND", "PLAYER" (from player class), "LEVELTEXTURE" 
	Bottle* spawnBottle();
};
