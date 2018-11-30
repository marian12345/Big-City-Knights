#include "LevelTexture.h"
#include "Window.h"

LevelTexture::LevelTexture(std::string text, std::string fontpath, int fontsize, SDL_Color color) : MenuTexture(text, fontpath, fontsize, color){
	alpha = 150;
	alpha_increasing = true;
};

bool LevelTexture::loadMedia() { 
	bool success = false;

	if (MenuTexture::loadMedia() == true) {
		//Align the Texture in the middle of the Frame
		int window_height = Window::getInstance()->getWindowSizeH();
		int window_width = Window::getInstance()->getWindowSizeW();

		appearance.x = (window_width - appearance.w)/2;
		appearance.y = (window_height - appearance.h)/3;
		
		success = true;
	}
	else {
		printf("Level Texture failed to load Media\n");
		success = false;
	}

	return success; 
};

void LevelTexture::render() {
	SDL_Renderer* renderer = Window::getInstance()->getRenderer();
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(texture, alpha);
	SDL_RenderCopy(renderer, texture, NULL, &appearance);
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_NONE);
};

void LevelTexture::tick() {
	//Changing the Opacity

	//Deciding whether the opacity is getting increased or decreased
	if (alpha >= 252)
		alpha_increasing = false;
	else if (alpha <= 150)
		alpha_increasing = true;
	
	//Deacreasing and Increasing the Opacity
	if (alpha_increasing) { 
		alpha += 2;
	}
	else {
		alpha -= 2;
	}

};

std::string LevelTexture::getType() {
	return "LEVELTEXTURE";
};

//Methods were just created for the LevelElementInterface - They aren't needed
void LevelTexture::checkInput() {};
void LevelTexture::restart() {};
Bottle* LevelTexture::spawnBottle() { return NULL; };
std::string LevelTexture::isDead() { return "NOTDEAD"; };
void LevelTexture::close() {};