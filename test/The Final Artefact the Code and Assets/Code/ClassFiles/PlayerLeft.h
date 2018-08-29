#ifndef PLAYERLEFT_H
#define PLAYERLEFT_H
#endif
#ifndef PLAYER_H
#define PLAYER_H
#include "Player.h"
#endif

class PlayerLeft : public Player {
	public:
		PlayerLeft();
		~PlayerLeft();
		void checkInput();
		void tick();
		void restart();
		std::string getType(); //"PLAYERRIGHT", "PLAYERLEFT", "BOTTLE", "BACKGROUND", "PLAYER"
};