#ifndef PLAYER_H
#define PLAYER_H
#include "Player.h"
#endif
class Collider {
	private:
		SDL_Rect* getColliderForStateStabThrowbottle(int curr_sprite, bool headLeft, SDL_Rect* appearance);
		SDL_Rect* getColliderForStateBlock(int curr_sprite, bool headLeft, SDL_Rect* appearance);
		SDL_Rect* getColliderForStateIdleHurtWalk(int curr_sprite, bool headLeft, SDL_Rect* appearance);
		SDL_Rect* getColliderForStateJump(int curr_sprite, bool headLeft, SDL_Rect* appearance);
		SDL_Rect* getColliderForStateJumpHeadLeft(int curr_sprite, SDL_Rect* appearance);
		SDL_Rect* getColliderForStateJumpHeadRight(int curr_sprite, SDL_Rect* appearance);
		SDL_Rect* getColliderForPlayerSwordHeadLeft(int curr_sprite, SDL_Rect* appearance);
		SDL_Rect* getColliderForPlayerSwordHeadRight(int curr_sprite, SDL_Rect* appearance);
	public:
		Collider();
		SDL_Rect getColliderForPlayer(int state, int curr_sprite, bool headLeft, SDL_Rect appearance);
		SDL_Rect getColliderForPlayerSword(int state, int curr_sprite, bool headLeft, SDL_Rect appearance);
};