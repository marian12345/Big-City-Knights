#include <string>
#ifndef ABSTRACTTEXTURE_H
#define ABSTRACTTEXTURE_H
#include "AbstractTexture.h"
#endif

class Bat : public AbstractTexture {

private:
	static Uint8 bat_count;
	SDL_Texture* batTx;
	int z_index;
	int ticked;
	int curr_tx;
	bool flipped;
	int speed;
public:
	Bat();
	~Bat();
	int getZIndex();
	bool loadMedia();
	void render();
	void renderFlipped();
	void renderUnflipped();
	void tick();
	void flipIfNecessary();
	void restart();
};