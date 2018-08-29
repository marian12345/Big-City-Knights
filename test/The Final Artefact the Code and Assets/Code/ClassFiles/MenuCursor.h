#ifndef MENUCURSOR_H
#define MENUCURSOR_H
#endif 
#ifndef MENUITEMINTERFACE_H
#define MENUITEMINTERFACE_H
#include "MenuItemInterface.h"
#endif
#ifndef ABSTRACTTEXTURE_H
#define ABSTRACTTEXTURE_H
#include "AbstractTexture.h"
#endif
#include "SDL.h"
#include "SDL_image.h"

class MenuCursor : public MenuItemInterface, public AbstractTexture{
	private:
		SDL_Texture* cursor_tx;
		int ticked;
		bool left;
		int tick2;
	public:
		MenuCursor();
		~MenuCursor();
		bool loadMedia();
		void tick();
		void render();
		void free();
		void setX(int x);
		void setY(int y);
		int getX();
		int getY();
		int getW();
		int getH();
		std::string getType();
};
