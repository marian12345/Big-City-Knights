#ifndef ABSTRACTTEXTURE_H
#define ABSTRACTTEXTURE_H
#endif
#include <string>
#include <SDL.h>
#include "SDL_image.h"

class AbstractTexture {
	protected:
		SDL_Rect appearance;
	public:
		AbstractTexture();
		~AbstractTexture();
		SDL_Texture* loadTexture(std::string path);
		virtual bool loadMedia() = 0;
};