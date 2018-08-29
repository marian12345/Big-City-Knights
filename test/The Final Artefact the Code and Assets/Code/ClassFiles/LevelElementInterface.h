#ifndef LEVELELEMENTINTERFACE_H
#define LEVELELEMENTINTERFACE_H
#endif
#include "string"
#include "SDL.h"

class Bottle;

class LevelElementInterface {
public:
	virtual void render() = 0;
	virtual void tick() = 0;
	virtual void restart() = 0;
	virtual void close() = 0;
	virtual bool loadMedia() = 0;
	virtual std::string getType() = 0; //"PLAYERRIGHT", "PLAYERLEFT", "BOTTLE", "BACKGROUND" 
	virtual Bottle* spawnBottle() = 0;
	virtual void checkInput() = 0;
	virtual std::string isDead() = 0; //"NOTDEAD", "DEADPLAYER", "BROKENBOTTLE"
};

/*"NOTDEAD", "DEADPLAYER", "BROKENBOTTLE"
"NOTDEAD":
-DO NOTHING
"DEADPLAYER":
-RESTART
"BROKENBOTTLE":
-DETACH BOTTLE FROM GAME
-BOTTLE HAS TO DETACH ITSELF FROM THE CD SYSTEM
*/
