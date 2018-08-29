#include "MenuControlsTexture.h"
#include "Window.h"

MenuControlsTexture::MenuControlsTexture(std::string path) {
	controls_tx = NULL;
	this->path = path;
};

MenuControlsTexture::~MenuControlsTexture() {
	free();
};

void MenuControlsTexture::free() {
	SDL_DestroyTexture(controls_tx);
	controls_tx = NULL;
};

bool MenuControlsTexture::loadMedia() {
	bool success = true;

	//Load Control texture
	controls_tx = loadTexture(path.c_str());
	if (controls_tx == NULL) {
		printf("Failed to create controls texture. SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	appearance.w = 283;
	appearance.h = 266;

	return success;
};

void MenuControlsTexture::render() {
	SDL_RenderCopy(Window::getInstance()->getRenderer(), controls_tx, NULL, &appearance);
};

void MenuControlsTexture::tick() {};

void MenuControlsTexture::setX(int x) {
	appearance.x = x;
};

void MenuControlsTexture::setY(int y) {
	appearance.y = y;
};

int MenuControlsTexture::getX() {
	return appearance.x;
};

int MenuControlsTexture::getY() {
	return appearance.y;
};

int MenuControlsTexture::getW() {
	return appearance.w;
}

int MenuControlsTexture::getH() {
	return appearance.h;
};

std::string MenuControlsTexture::getType() {
	return "CONTROLSTX";
};