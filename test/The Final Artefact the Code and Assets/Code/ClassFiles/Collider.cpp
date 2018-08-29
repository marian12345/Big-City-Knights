#include "Collider.h"

Collider::Collider() {};

SDL_Rect* Collider::getColliderForStateStabThrowbottle(int curr_sprite, bool headLeft, SDL_Rect* appearance) {
	SDL_Rect* collider = NULL;
	if (headLeft == true) {
		switch (curr_sprite)
		{
		case 0:
			collider = new SDL_Rect();
			collider->x = appearance->x + 38;
			collider->y = appearance->y + appearance->h / 2;
			collider->w = appearance->w - 48;
			collider->h = appearance->h / 2;
			break;
		default:
			collider = new SDL_Rect();
			collider->x = appearance->x + 38;
			collider->y = appearance->y + appearance->h / 2;
			collider->w = appearance->w - 70;
			collider->h = appearance->h / 2;
			break;
		}
	}
	else if (headLeft == false) {
		switch (curr_sprite)
		{
		case 0:
			collider = new SDL_Rect();
			collider->x = appearance->x + 10;
			collider->y = appearance->y + appearance->h / 2;
			collider->w = appearance->w - 48;
			collider->h = appearance->h / 2;
			break;
		default:
			collider = new SDL_Rect();
			collider->x = appearance->x + 32;
			collider->y = appearance->y + appearance->h / 2;
			collider->w = appearance->w - 70;
			collider->h = appearance->h / 2;
			break;
		}
	}

	if (collider == NULL) {
		printf("Failed to return collider from class Collider.getColliderForStateStabThrowbottle(...)\n");
	}

	return collider;
};

SDL_Rect* Collider::getColliderForStateBlock(int curr_sprite, bool headLeft, SDL_Rect* appearance) {
	SDL_Rect* collider = NULL;

	if (headLeft == true) {
		collider = new SDL_Rect();
		collider->x = appearance->x + 43;
		collider->y = appearance->y + appearance->h / 2;
		collider->w = appearance->w - 86;
		collider->h = appearance->h / 2;
	}
	else if (headLeft == false) {
		collider = new SDL_Rect();
		collider->x = appearance->x + 43;
		collider->y = appearance->y + appearance->h / 2;
		collider->w = appearance->w - 86;
		collider->h = appearance->h / 2;
	}

	if (collider == NULL) {
		printf("Failed to return Collider from class Collider.getColliderForStateBlock(...)\n");
	}

	return collider;
};

SDL_Rect* Collider::getColliderForStateIdleHurtWalk(int curr_sprite, bool headLeft, SDL_Rect* appearance) {
	SDL_Rect* collider = NULL;

	if (headLeft == true) {
		collider = new SDL_Rect();
		collider->x = appearance->x + 38;
		collider->y = appearance->y + appearance->h / 2;
		collider->w = appearance->w - 70;
		collider->h = appearance->h / 2;
	}
	else if (headLeft == false) {
		collider = new SDL_Rect();
		collider->x = appearance->x + 32;
		collider->y = appearance->y + appearance->h / 2;
		collider->w = appearance->w - 70;
		collider->h = appearance->h / 2;
	}

	if (collider == NULL) {
		printf("Failed to return collider from class Collider.getColliderForStateIdleHurtWalk(...)\n");
	}

	return collider;
};

SDL_Rect* Collider::getColliderForStateJump(int curr_sprite, bool headLeft, SDL_Rect* appearance) {
	SDL_Rect* collider = NULL;

	if (headLeft == true) {
		collider = getColliderForStateJumpHeadLeft(curr_sprite, appearance);
	}
	else if (headLeft == false) {
		collider = getColliderForStateJumpHeadRight(curr_sprite, appearance);
	}

	if (collider == NULL) {
		printf("Failed to return collider from class Collider.getColliderForStateJump(...)\n");
	}

	return collider;
};

SDL_Rect* Collider::getColliderForStateJumpHeadLeft(int curr_sprite, SDL_Rect* appearance) {
	SDL_Rect* collider = NULL;

	switch (curr_sprite)
	{
	case 0:
		collider = getColliderForStateIdleHurtWalk(curr_sprite,true,appearance);
		break;
	case 1:
		collider = getColliderForStateIdleHurtWalk(curr_sprite, true, appearance);
		collider->y -= 5;
		collider->h += 6;
		break;
	case 2:
		collider = getColliderForStateIdleHurtWalk(curr_sprite, true, appearance);
		collider->y -= 13;
		collider->h += 10;
		break;
	case 3:
		collider = getColliderForStateIdleHurtWalk(curr_sprite, true, appearance);
		collider->y -= 14;
		collider->h += 6;
		break;
	case 4:
		collider = getColliderForStateIdleHurtWalk(curr_sprite, true, appearance);
		collider->y -= 10;
		break;
	default:
		printf("Failed to return collider from class Collider.getColliderForStateJumpHeadLeft(...). Invalid curr_sprite.\n");
		break;
	}

	return collider;
};

SDL_Rect* Collider::getColliderForStateJumpHeadRight(int curr_sprite, SDL_Rect* appearance) {
	SDL_Rect* collider = NULL;

	switch (curr_sprite)
	{
	case 0:
		collider = getColliderForStateIdleHurtWalk(curr_sprite, false, appearance);
		break;
	case 1:
		collider = getColliderForStateIdleHurtWalk(curr_sprite, false, appearance);
		collider->y -= 5;
		collider->h += 6;
		break;
	case 2:
		collider = getColliderForStateIdleHurtWalk(curr_sprite, false, appearance);
		collider->y -= 13;
		collider->h += 10;
		break;
	case 3:
		collider = getColliderForStateIdleHurtWalk(curr_sprite, false, appearance);
		collider->y -= 14;
		collider->h += 6;
		break;
	case 4:
		collider = getColliderForStateIdleHurtWalk(curr_sprite, false, appearance);
		collider->y -= 10;
		break;
	default:
		printf("Failed to return collider from class Collider.getColliderForStateJumpHeadLeft(...). Invalid curr_sprite.\n");
		break;
	}

	return collider;
};

SDL_Rect* Collider::getColliderForPlayerSwordHeadLeft(int curr_sprite, SDL_Rect* appearance){
	SDL_Rect* collider = NULL;

	if (curr_sprite == 0) {
		collider = new SDL_Rect();
		collider->x = appearance->x + 91;
		collider->y = appearance->y + 64 + 19;
		collider->w = 30;
		collider->h = 34;
	}
	else if ((curr_sprite == 1) || (curr_sprite == 2)) {
		collider = new SDL_Rect();
		collider->x = appearance->x;
		collider->y = appearance->y + appearance->h - 17;
		collider->w = 36;
		collider->h = 15;
	}
	else if (curr_sprite == 3) {
		collider = new SDL_Rect();
		collider->x = appearance->x + 70;
		collider->y = appearance->y + 75;
		collider->w = 15;
		collider->h = 36;
	}
	else if (curr_sprite == 4) {
		collider = new SDL_Rect();
		collider->x = appearance->x + 80;
		collider->y = appearance->y + 72;
		collider->w = 15;
		collider->h = 36;
	}

	if (collider == NULL) {
		printf("Failed to return collider from class Collider.getColliderForPlayerSwordHeadLeft(...). Invalid curr_sprite.\n");
	}

	return collider;
};

SDL_Rect* Collider::getColliderForPlayerSwordHeadRight(int curr_sprite, SDL_Rect* appearance){
	SDL_Rect* collider = NULL;

	if (curr_sprite == 0) {
		collider = new SDL_Rect();
		collider->x = appearance->x + 7;
		collider->y = appearance->y + 64 + 19;
		collider->w = 30;
		collider->h = 34;
	}
	else if ((curr_sprite == 1) || (curr_sprite == 2)) {
		collider = new SDL_Rect();
		collider->x = appearance->x + 64 + 28;
		collider->y = appearance->y + appearance->h - 17;
		collider->w = 36;
		collider->h = 15;
	}
	else if (curr_sprite == 3) {
		collider = new SDL_Rect();
		collider->x = appearance->x + 43;
		collider->y = appearance->y + 75;
		collider->w = 15;
		collider->h = 36;
	}
	else if (curr_sprite == 4) {
		collider = new SDL_Rect();
		collider->x = appearance->x + 33;
		collider->y = appearance->y + 73;
		collider->w = 15;
		collider->h = 36;
	}

	if (collider == NULL) {
		printf("Failed to return collider from class Collider.getColliderForPlayerSwordHeadRight(...). Invalid curr_sprite.\n");
	}

	return collider;
};

//ACCESS
SDL_Rect Collider::getColliderForPlayer(int state, int curr_sprite, bool headLeft, SDL_Rect appearance) {
	SDL_Rect* collider = NULL;

	if ((state == Player::STAB) || (state == Player::THROWBOTTLE)) {
		collider = getColliderForStateStabThrowbottle(curr_sprite, headLeft, &appearance);
	}
	else if ((state == Player::HURT) || (state == Player::IDLE) || (state == Player::WALK)) {
		collider = getColliderForStateIdleHurtWalk(curr_sprite, headLeft, &appearance);
	}
	else if ((state == Player::BLOCK)) {
		collider = getColliderForStateBlock(curr_sprite, headLeft, &appearance);
	}
	else if ((state == Player::JUMP)) {
		collider = getColliderForStateJump(curr_sprite, headLeft, &appearance);
	}

	if (collider == NULL) {
		printf("Failed to return Collider from class Collider.getColliderForPlayer(...)\n");
	}

	return *collider;
};

SDL_Rect Collider::getColliderForPlayerSword(int state, int curr_sprite, bool headLeft, SDL_Rect appearance) {
	SDL_Rect* collider = NULL;

	if ((state == Player::STAB) || (state == Player::THROWBOTTLE)) {
		if (headLeft == true)
		{
			collider = getColliderForPlayerSwordHeadLeft(curr_sprite, &appearance);
		}
		else if (headLeft == false) {
			collider = getColliderForPlayerSwordHeadRight(curr_sprite, &appearance);
		}

		if (collider == NULL) {
			printf("Failed to return Collider from class Collider.getColliderForPlayer(...)\n");
		}
	}

	if (collider == NULL) {
		collider = new SDL_Rect();
		collider->x = 0;
		collider->y = 0;
		collider->h = 0;
		collider->w = 0;
	}

	return *collider;
};