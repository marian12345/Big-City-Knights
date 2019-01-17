#include "Healthbar.h"
#include "Window.h"
#include "Mixer.h"

enum stats_attribute { HEALTH, MAX_HEALTH, PERCENTAGE };

Healthbar::Healthbar(bool left) {
	int window_size_h = Window::getInstance()->getWindowSizeH();
	int window_size_w = Window::getInstance()->getWindowSizeW();

	//Set up attributes
	appearance.w = window_size_w / 5;
	appearance.h = window_size_h / 35;
	if (left) {
		appearance.x = window_size_w / 20;
		appearance.y = (window_size_h / 20);
	}
	else {
		appearance.x = window_size_w - (appearance.w + (window_size_w / 20));
		appearance.y = (window_size_h / 20);
	}
	this->left = left;
	stats[HEALTH] = 1000.0;
	stats[MAX_HEALTH] = 1000.0;
	stats[PERCENTAGE] = 100.0;
	color.r = 0x00;
	color.g = 0xFF;
	color.b = 0x00;
	color.a = 0xA0;
};

Healthbar::~Healthbar() {};

void Healthbar::render() {
	SDL_Renderer* renderer = Window::getInstance()->getRenderer();
	
	//Saving the old rendercolor
	SDL_Color old_color;
	SDL_GetRenderDrawColor(renderer, &old_color.r, &old_color.g, &old_color.b, &old_color.a);

	SDL_Rect colored_rect, black_rect;
	colored_rect.x = appearance.x;
	colored_rect.y = appearance.y;
	colored_rect.w = (double)appearance.w * (stats[PERCENTAGE] / 100.0);
	colored_rect.h = appearance.h;

	black_rect.x = appearance.x + colored_rect.w;
	black_rect.y = appearance.y;
	black_rect.w = appearance.w - colored_rect.w;
	black_rect.h = appearance.h;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	if (left) {
		//Draw Colored Rect
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, &colored_rect);

		//Draw Black Rect
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, color.a);
		SDL_RenderFillRect(renderer, &black_rect);
	}
	else {
		black_rect.x = appearance.x;
		colored_rect.x = appearance.x + black_rect.w;

		//Draw Black Rect
		SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, color.a);
		SDL_RenderFillRect(renderer, &black_rect);

		//Draw Colored Rect
		SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		SDL_RenderFillRect(renderer, &colored_rect);
	}

	//Reset the old rendercolor
	SDL_SetRenderDrawColor(renderer, old_color.r, old_color.g, old_color.b, old_color.a);
};

bool Healthbar::takeDamage(double damage) {
	bool dead = false;

	if (damage >= stats[HEALTH] ) {
		stats[HEALTH] = 0.0;
		stats[PERCENTAGE] = 0.0;
		setColor();
		dead = true;
		Mixer::getInstance()->play(Mixer::DYING);
	}
	else {
		stats[HEALTH] -= damage;
		stats[PERCENTAGE] -= ((damage / stats[MAX_HEALTH]) * 100);

		//Set Color
		double tmp = (510.0 * (stats[PERCENTAGE] / 100.0)) - 255.0;
		if (tmp >= 0) {
			setColor();
		}
		else {
			setColor();
		}
	}

	return dead;
};

bool Healthbar::isEmpty() {
	bool empty = false;

	if (stats[HEALTH] <= 0) {
		empty = true;
	}

	return empty;
};

void Healthbar::refill() {
	stats[HEALTH] = stats[MAX_HEALTH];
	stats[PERCENTAGE] = 100.0;
	setColor();
};

void Healthbar::setColor() {
	//Set Color
	double tmp = (510.0 * (stats[PERCENTAGE] / 100.0)) - 255.0;
	if (tmp >= 0) {
		color.r = 0xFF - tmp;
		color.g = 0xFF;
	}
	else {
		color.r = 0xFF;
		color.g = 0xFF+tmp;
	}
};