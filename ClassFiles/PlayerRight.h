#ifndef PLAYERRIGHT_H
#define PLAYERRIGHT_H
#endif
#ifndef PLAYER_H
#define PLAYER_H
#include "Player.h"
#endif

class PlayerRight : public Player {
public:
	PlayerRight();
	~PlayerRight();
	void checkInput();
	void restart();
	void tick();
	std::string getType(); //"PLAYERRIGHT", "PLAYERLEFT", "BOTTLE", "BACKGROUND", "PLAYER" (from player class) 
};