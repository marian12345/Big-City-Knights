#include "MenuCursor.h"
#include "Window.h"



MenuCursor::MenuCursor() {
	ticked = 0;
	appearance.w = 32;
	appearance.h = 32;
	left = true;
	tick2 = 0;
};

bool MenuCursor::loadMedia() {
	bool success = true;

	//Load cursor texture
	cursor_tx = loadTexture("assets/sprite_sheets/menu/SmallSword.png");
	if (cursor_tx == NULL) {
		printf("Failed to create cursor texture. SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	return success;
};

void MenuCursor::tick() {
	//tick
	ticked++;
	tick2++;
	int distance = 400;
	int move_after_ticks = 20;
	if ((ticked >= move_after_ticks)) {
		if (left == true) {
			appearance.x -= 1;
			if (tick2 >= distance) {
				tick2 = 0;
				left = false;
			}
		}
		else {
			appearance.x += 1;
			if (tick2 >= distance) {
				tick2 = 0;
				left = true;
			}
		}
		ticked = 0;
	}
};

void MenuCursor::render() {
	SDL_RenderCopyEx(Window::getInstance()->getRenderer(), cursor_tx, NULL, &appearance, 45.0, NULL, SDL_FLIP_NONE);
}

MenuCursor::~MenuCursor() {
	//Free texture
	free();
};

void MenuCursor::free() {
	//Free Surface
	SDL_DestroyTexture(cursor_tx);
	cursor_tx = NULL;
}

void MenuCursor::setX(int x) {
	appearance.x = x;
};

void MenuCursor::setY(int y) {
	appearance.y = y;
};

int MenuCursor::getX() {
	return appearance.x;
};

int MenuCursor::getY() {
	return appearance.y;
};

int MenuCursor::getW() {
	return appearance.w;
}

int MenuCursor::getH() {
	return appearance.h;
};

std::string MenuCursor::getType() {
	return "CURSOR";
};