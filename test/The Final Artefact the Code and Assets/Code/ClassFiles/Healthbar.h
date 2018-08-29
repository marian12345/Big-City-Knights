#ifndef HEALTHBAR_H
#define HEALTHBAR_H
#endif
#include "SDL.h"
#include <array>

class Healthbar{
	private:
		SDL_Rect appearance;
		SDL_Color color;
		bool left;
		std::array<double, 3> stats; //{HEALTH, MAX_HEALTH, PERCENTAGE}
	public:
		Healthbar(bool left);
		~Healthbar();
		void setColor();
		bool isEmpty();
		void render();
		void refill();
		bool takeDamage(double damage);
};

