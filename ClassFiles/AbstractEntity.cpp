#include "AbstractTexture.h"
#include "Window.h"

AbstractTexture::AbstractTexture() {
	appearance = { 0,0,0,0 };
};

AbstractTexture::~AbstractTexture() {};

SDL_Texture* AbstractTexture::loadTexture(std::string path) {
	//final texture pointer
	SDL_Texture* new_texture = NULL;

	//create surface
	SDL_Surface* loaded_surface = IMG_Load(path.c_str());
	if (loaded_surface == NULL) {
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else {
		//Create texture
		new_texture = SDL_CreateTextureFromSurface(Window::getInstance()->getRenderer(), loaded_surface);
		if (new_texture == NULL) {
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loaded_surface);
	}

	return new_texture;
};
