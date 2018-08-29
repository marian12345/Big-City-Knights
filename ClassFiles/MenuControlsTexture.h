#ifndef MENUCONTROLSTEXTURE_H
#define MENUCONTROLSTEXTURE_H
#endif
#ifndef MENUITEMINTERFACE_H
#define MENUITEMINTERFACE_H
#include "MenuItemInterface.h"
#endif
#ifndef ABSTRACTTEXTURE_H
#define ABSTRACTTEXTURE_H
#include "AbstractTexture.h"
#endif

class MenuControlsTexture : public MenuItemInterface, public AbstractTexture {
	private:
		SDL_Texture* controls_tx;
		std::string path;
	public:
		MenuControlsTexture(std::string path);
		~MenuControlsTexture();
		void free();
		bool loadMedia();
		void render();
		void tick();
		void setX(int x);
		void setY(int y);
		int getX();
		int getY();
		int getW();
		int getH();
		std::string getType();
};
