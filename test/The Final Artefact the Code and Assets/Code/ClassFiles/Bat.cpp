#include "Bat.h"
#include "SDL_image.h"
#include "Window.h"

Uint8 Bat::bat_count = 0;

Bat::Bat() {
	bat_count = bat_count + 1;
	batTx = NULL;
	appearance.x = Window::getInstance()->getWindowSizeW() + rand() % 100;
	appearance.y = (Window::getInstance()->getWindowSizeH() / 5) + (32 * bat_count);
	appearance.w = 32;
	appearance.h = 32;
	z_index = rand() % 100 + 1;
	if (z_index > 80) {
		z_index = 2;
	}
	else {
		z_index = 1;
	}
	ticked = 0;
	curr_tx = 0;
	flipped = false;
	speed = rand() % 3 + 1;
};

Bat::~Bat() {
	SDL_DestroyTexture(batTx);
	bat_count = bat_count - 1;
};

int Bat::getZIndex() {
	return z_index;
};

void Bat::restart() {
	appearance.x = Window::getInstance()->getWindowSizeW() + rand() % 100;
	appearance.y = (Window::getInstance()->getWindowSizeH() / 5) + (32 * bat_count);
	flipped = false;
	ticked = 0;
	curr_tx = 0;
};

bool Bat::loadMedia() {
	bool success = true;

	//Load Bat texture
	batTx = loadTexture("assets/sprite_sheets/bat/sheet_bat_fly.png");
	if (batTx == NULL) {
		printf("Failed to create bat texture. SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	return success;
};

void Bat::renderFlipped() {
	SDL_Rect clip_rect;

	//Set up Clip Rectangle
	clip_rect.x = curr_tx * 32;
	clip_rect.y = 0;
	clip_rect.w = 32;
	clip_rect.h = 32;
	
	SDL_RenderCopyEx(Window::getInstance()->getRenderer(), batTx, &clip_rect, &appearance, 0.0, NULL, SDL_FLIP_HORIZONTAL);
};

void Bat::renderUnflipped() {
	SDL_Rect clip_rect;

	//Set up Clip Rectangle
	clip_rect.x = curr_tx * 32;
	clip_rect.y = 0;
	clip_rect.w = 32;
	clip_rect.h = 32;

	SDL_RenderCopy(Window::getInstance()->getRenderer(), batTx, &clip_rect, &appearance);
};

void Bat::flipIfNecessary() {
	//If bat reached the left side of the window
	if ((appearance.x <= (-1 * appearance.w)) && (!flipped)) {
		flipped = true;
		z_index++;
		if (z_index > 2)
			z_index = 1;
	}
	else if ((appearance.x >= Window::getInstance()->getWindowSizeW() + appearance.w) && (flipped)) {
		flipped = false;
		z_index++;
		if (z_index > 2)
			z_index = 1;
	}
};

void Bat::render() {
	//render appropriately
	if (flipped) {
		renderFlipped();
	}
	else {
		renderUnflipped();
	}
};

void Bat::tick() {
	//Tick Bat
	ticked++;
	
	//Move Bat
	if (!flipped)
		appearance.x = appearance.x - speed;
	else
		appearance.x = appearance.x + speed;

	//Change textures to create the animation
	if (ticked == speed + 5) {
		curr_tx++;
		if (curr_tx >= 4) {
			curr_tx = 0;
		}
		ticked = 0;
	}

	//flip if necessary
	flipIfNecessary();
};