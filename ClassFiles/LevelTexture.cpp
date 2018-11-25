#include "LevelTexture.h"

LevelTexture::LevelTexture(std::string text, std::string fontpath, int fontsize, SDL_Color color) : MenuTexture(text, fontpath, fontsize, color){};

bool LevelTexture::loadMedia() { return false; };

void LevelTexture::close() {};

std::string LevelTexture::isDead() { return "NOTDEAD"; };

void LevelTexture::render() {
	printf("rendering LevelTexture\n");
	//render...
};

void LevelTexture::checkInput() {};
void LevelTexture::restart() {};

void LevelTexture::tick() {
	//Change Opacity
};

std::string LevelTexture::getType() {
	return "LEVELTEXTURE";
};

Bottle* LevelTexture::spawnBottle() { return NULL; };