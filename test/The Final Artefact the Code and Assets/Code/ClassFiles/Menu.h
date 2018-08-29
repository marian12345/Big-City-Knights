#ifndef MENU_H
#define MENU_H
#include "Menu.h"
#endif
#ifndef MENUTEXTURE_H
#define MENUTEXTURE_H
#include "MenuTexture.h"
#endif
#ifndef MENUCURSOR_H
#define MENUCURSOR_H
#include "MenuCursor.h"
#endif
#ifndef MENUCONTROLSTEXTURE_H
#define MENUCONTROLSTEXTURE_H
#include "MenuControlsTexture.h"
#endif
#include "vector"

class Menu {
	private:
		//Variables
		std::vector<MenuItemInterface*> menu_items;
		std::vector<MenuItemInterface*> unused_menu_items;
		bool running;
		bool firstMenuOptionPickedFlag;
		int distance_between_menu_option;
		int curr_cursor_pos;
		//Methods
		void render();
		void tick();
		void input();
		void moveCursor(std::string input);
	public:	
		Menu();
		bool show(int flag); //false for [exit], true for [Continue or Start new Game or Restart]
		bool loadMedia();
		bool init();
		void changeFirstMenuItemTo(int x);
		void close();
		enum used_menu_items {CONTINUE, RESTART, STARTGAME};
};
