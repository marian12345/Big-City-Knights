#ifndef MENUTEXTURE_H
#define MENUTEXTURE_H
#endif
#ifndef MENUITEMINTERFACE
#define MENUITEMINTERFACE
#include "MenuItemInterface.h"
#endif
#include "SDL_ttf.h"

class MenuTexture : public MenuItemInterface{
	protected:
		SDL_Texture* texture;
		std::string text;
		std::string fontpath;
		TTF_Font* font;
		SDL_Color color;
		SDL_Rect appearance;
		int fontsize;
		SDL_Texture* loadTextTexture();
		void setColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
		bool setFont(std::string path);
	public:
		MenuTexture(std::string text, std::string fontpath, int fontsize, SDL_Color color);
		bool loadMedia();
		void render();
		void free();
		void setX(int x);
		void setY(int y);
		int getX();
		int getY();
		int getW();
		int getH();
		void tick();
		std::string getType();
		~MenuTexture();
};
