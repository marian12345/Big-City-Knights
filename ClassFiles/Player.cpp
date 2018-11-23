#include "Player.h"
#include "SDL_image.h"
#include "Window.h"
#include "math.h"
#include "Collider.h"
#include "ObservableCollisionDetection.h"
#include "Mixer.h"

Player::Player(bool headLeft){ 
	//Getting the Window Sizes
	int window_size_h = Window::getInstance()->getWindowSizeH();
	int window_size_w = Window::getInstance()->getWindowSizeW();

	//Setting up Size, Position, States, Direction in which the Player heads, ticked (same as PlayerLeft)   
	appearance.x = 50;
	appearance.y = window_size_h - (window_size_h / 5);
	appearance.w = 128;
	appearance.h = 128;
	this->headLeft = headLeft;
	for (int i = 0; i < spritesheets.size(); i++) {
		spritesheets[i] = NULL;
	}
	blocking = false;
	jumping = false;
	ticked = 0;
	heightAboveTheGround = 0;
	curr_state[0] = 0;
	curr_state[1] = IDLE;
	max_sprites = { 4,8,3,4,5,5,5 };
	while (!height_stack.empty()) {
		height_stack.pop();
	}
};

bool Player::loadMedia() {
	bool success = true;

	std::string sources[9];
	if (headLeft == true) {
		sources[0] = { "assets/sprite_sheets/player/Right_Player/sheet_hero_idle.png" };
		sources[1] = { "assets/sprite_sheets/player/Right_Player/sheet_hero_block.png" };
		sources[2] = { "assets/sprite_sheets/player/Right_Player/sheet_hero_walk.png" };
		sources[3] = { "assets/sprite_sheets/player/Right_Player/sheet_hero_hurt.png" };
		sources[4] = { "assets/sprite_sheets/player/Right_Player/sheet_hero_jump.png" };
		sources[5] = { "assets/sprite_sheets/player/Right_Player/sheet_hero_stab.png" };
		sources[6] = { "assets/sprite_sheets/player/Right_Player/sheet_hero_throw_bottle.png" };
	}
	else {
		sources[0] = { "assets/sprite_sheets/player/Left_Player/sheet_hero_idle.png" };
		sources[1] = { "assets/sprite_sheets/player/Left_Player/sheet_hero_block.png" }; 
		sources[2] = { "assets/sprite_sheets/player/Left_Player/sheet_hero_walk.png" };
		sources[3] = { "assets/sprite_sheets/player/Left_Player/sheet_hero_hurt.png" };
		sources[4] = { "assets/sprite_sheets/player/Left_Player/sheet_hero_jump.png" };
		sources[5] = { "assets/sprite_sheets/player/Left_Player/sheet_hero_stab.png" };
		sources[6] = { "assets/sprite_sheets/player/Left_Player/sheet_hero_throw_bottle.png" };
	}

	//Load Spritesheets
	for (int i = 0; i < spritesheets.size(); i++) {
		spritesheets[i] = loadTexture(sources[i]);
		if (spritesheets[i] == NULL) {
			printf("Failed to create texture. SDL Error: %s\n", SDL_GetError());
			success = false;
		}
	}

	//Create Healthbar
	healthbar = new Healthbar(!headLeft);
	if (healthbar == NULL) {
		printf("Failed to create Healthbar\n");
		success = false;
	}
	
	return success;
};

void Player::renderUnflipped() {
	//Set up Clip Rectangle
	SDL_Rect clip_rect;
	clip_rect.x = curr_state[0] * 64;
	clip_rect.y = 0;
	clip_rect.w = 64;
	clip_rect.h = 64;

	//Render
	SDL_RenderCopy(Window::getInstance()->getRenderer(), 
		spritesheets[curr_state[1]], &clip_rect, &appearance);
};

void Player::renderFlipped() {
	//Set up Clip Rectangle
	SDL_Rect clip_rect;
	clip_rect.x = curr_state[0] * 64;
	clip_rect.y = 0;
	clip_rect.w = 64;
	clip_rect.h = 64;

	//Render
	SDL_RenderCopyEx(Window::getInstance()->getRenderer(), spritesheets[curr_state[1]], 
		&clip_rect, &appearance, 0.0, NULL, SDL_FLIP_HORIZONTAL);
};

void Player::renderColliders() {
	//Saving the old rendercolor
	SDL_Color old_color;
	SDL_GetRenderDrawColor(Window::getInstance()->getRenderer(), &old_color.r, &old_color.g, &old_color.b, &old_color.a);
	
	//Set player color
	SDL_Color color;
	color.r = 0x00;
	color.g = 0xFF;
	color.b = 0x00;
	color.a = 0x70;

	SDL_SetRenderDrawColor(Window::getInstance()->getRenderer(), color.r, color.g, color.b, color.a);

	//Get colliders
	std::vector<SDL_Rect> colliders = getColliders();

	//Render
	for (int i = 0; i < colliders.size(); i++) {
		if (i == 1) {
			//Set Sword Color
			color.r = 0xFF;
			color.g = 0x00;
			SDL_SetRenderDrawColor(Window::getInstance()->getRenderer(), color.r, color.g, color.b, color.a);
		}
		SDL_RenderFillRect(Window::getInstance()->getRenderer(), &(colliders.at(i)));
	}

	//Reset the old rendercolor
	SDL_SetRenderDrawColor(Window::getInstance()->getRenderer(), old_color.r, old_color.g, old_color.b, old_color.a);
};

void Player::render() {
	//Render Player
	if (headLeft) {
		renderFlipped();
	}
	else {
		renderUnflipped();
	}

	//Render Healthbar
	healthbar->render();

	//Render Colliders from Player
	if (false) { renderColliders(); }
};

void Player::tick() {   /*METHOD GETS OVERWRITTEN IN SUBCLASSES*/ };  

void Player::moveX(bool caused_by_collision, int distance) {
	//If no hurt and 
	if (caused_by_collision == false) {	
		if (headLeft == true) {
			//Left Border/Edge of the Screen
			if (appearance.x > -32) {
				int i = 0;
				while ((i < distance) && (appearance.x > -32)) {
					appearance.x -= 1;
					i++;
				}
			}
		}
		else {
			//Right Border/Edge of the Screen
			if ((appearance.x + appearance.w) < Window::getInstance()->getWindowSizeW() + 32) {
				int i = 0;
				while ((i < distance) && ((appearance.x + appearance.w + 1) < Window::getInstance()->getWindowSizeW() + 32)) {
					appearance.x += 1;
					i++;
				}
			}
		}
	}
	else{
		if (collision_direction.compare("RIGHT") == 0) {
			//Left Border/Edge of the Screen
			if (appearance.x > -32) {
				int i = 0;
				while ((i < distance) && (appearance.x > -32)) {
					appearance.x -= 1;
					i++;
				}
			}
		}
		else if(collision_direction.compare("LEFT") == 0){
			//Right Border/Edge of the Screen
			if ((appearance.x + appearance.w) < Window::getInstance()->getWindowSizeW() + 32) {
				int i = 0;
				while ((i < distance) && ((appearance.x + appearance.w + 1) < Window::getInstance()->getWindowSizeW() + 32)) {
					appearance.x += 1;
					i++;
				}
			}
		}
	}
};

void Player::changeStateTo(int state) {
	//Making sure that HURT and JUMP can not be interrupted
	if ((curr_state[1] != HURT)){
		if ((state == JUMP) && (heightAboveTheGround > 0)) {}
		/*It has to be possible to stab/throw a bottle while walking, 
			therefore WALK can not interrupt STAB/THROWBOTTLE*/
		else if ((state == WALK) && ((curr_state[1] == STAB) || (curr_state[1] == THROWBOTTLE))) {}
		else {
			curr_state[0] = 0;
			curr_state[1] = state;
			ticked = 0;
		}
	}
};

void Player::checkInput() {/*Gets overwritten in subclasses*/};

Bottle* Player::spawnBottle() {
	Bottle* bottle = NULL;

	//Only throw one bottle while throwing
	if ((curr_state[1] == THROWBOTTLE) && (curr_state[0] == 2) && (ticked == 0)) {
		if (headLeft == false) {
			bottle = new Bottle(appearance.x + (appearance.w / 2), appearance.y + appearance.h - 18, headLeft);
			bottle->loadMedia();
		}
		else {
			bottle = new Bottle(appearance.x - 64 + (appearance.w / 2), appearance.y + appearance.h - 18, headLeft);
			bottle->loadMedia();
		}
	}

	return bottle;
};

void Player::update(int collided_with, int own_collider, SDL_Rect rec) {
	//If blocking or Hurt nothing should happen
	if ((curr_state[1] == BLOCK) || (curr_state[1] == HURT)) {
		return;
	}

	//Find out from which side the hit came from and setting up the collision direction for it
	collision_direction = "NONE";
	std::vector<SDL_Rect> colliders = getColliders();

	//colliders.at(0) equals this players BODY rectangle
	//rec is the rectangle the player collided with
	if (rec.x + (rec.w/2) >= (colliders.at(0).x + (colliders.at(0).w/2))) {
		collision_direction = "RIGHT";
	}
	else {
		collision_direction = "LEFT";
	}

	//React
	switch (collided_with)
	{
	case BODY:
		if (own_collider == BODY) {
			moveX(true, 4);
		}
		break;
	case BOTTLE:
		changeStateTo(HURT);
		healthbar->takeDamage(50);
		Mixer::getInstance()->play(Mixer::HURT);
		break;
	case SWORD:
		if (own_collider != SWORD) {
			changeStateTo(HURT);
			healthbar->takeDamage(200);
			Mixer::getInstance()->play(Mixer::HURT);
		}
		else {
			Mixer::getInstance()->play(Mixer::SWORDDRAWN1);
		}
		break;
	default:
		break;
	}
};

int Player::getColliderType(int index_in_vector) {
	int type = -1;

	if (index_in_vector == 0) {
		type = Player::BODY;
	}
	else if ((index_in_vector == 1) && (curr_state[1] == Player::THROWBOTTLE)) {
		type = Player::BOTTLE;
	}
	else if (index_in_vector == 1) {
		type = Player::SWORD;
	}

	return type;
};

std::vector<SDL_Rect> Player::getColliders() {
	Collider colliderInst;
	std::vector<SDL_Rect> colliders;

	//Green Player Rectangle
	colliders.push_back(colliderInst.getColliderForPlayer(curr_state[1], curr_state[0], headLeft, appearance));

	//If Red Sword Rectangle exists
	SDL_Rect sword_rec = colliderInst.getColliderForPlayerSword(curr_state[1], curr_state[0], headLeft, appearance);
	if ((sword_rec.x == 0) && (sword_rec.y == 0) && (sword_rec.w == 0) && (sword_rec.h == 0)) {}
	else {
		colliders.push_back(sword_rec);
	}

	return colliders;
};

int Player::getState() {
	return curr_state[1];
};

std::string Player::isDead() {
	std::string isDead = "NOTDEAD";

	if (healthbar->isEmpty()) {
		isDead = "DEADPLAYER";
	}

	return isDead;
};

std::string Player::getType() {
	return "PLAYER";
};

void Player::restart() {/*Gets overwritten in sub classes*/};

void Player::close() {
	//Destroy Healthbar
	healthbar->~Healthbar();
	healthbar = NULL;

	//Destroy Textures
	for (int i = 0; i < spritesheets.size(); i++) {
		if (spritesheets[i] != NULL) {
			SDL_DestroyTexture(spritesheets[i]);
			spritesheets[i] = NULL;
		}
	}
	
};

Player::~Player() {
	close();
}