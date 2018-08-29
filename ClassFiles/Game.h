#include <SDL.h>
#include "Background.h"
#include <array>
#include "ObservableCollisionDetection.h"
#ifndef MENU_H
#define MENU_H
#include "Menu.h"
#endif
#include "vector"

class Game
{
	private:
		Menu* menu;
		std::vector<LevelElementInterface*> lvl_elements;
		bool runningFlag;
		bool restartFlag;
	public:
		Game(bool fullscreen);
		Game(int width, int height);
		void start();                  //start the Game with this method ( not with run(); )
		void run();
		bool init();
		bool load_media();
		void input();
		void tick();
		void update();
		void render();
		void restart();
		bool gameEnded();
		void close();
		~Game();
};

