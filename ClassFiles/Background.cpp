#include "SDL.h"
#include "Background.h"
#include "SDL_image.h"
#include "Window.h"

Background::Background() {
	for (int i = 0; i < far_buildings.size(); i++) {
		far_buildings[i] = NULL;
	}
	for (int i = 0; i < foregrounds.size(); i++) {
		foregrounds[i] = NULL;
	}
	filling_up_the_bottle = true;
	backgroundTX = NULL;
	far_buildings_ticker = 0;
	foreground_ticker = 0;
	for (int i = 0; i < bats.size(); i++) {
		bats[i] = NULL;
	}
};

bool Background::loadMedia() {
	bool success = true;

	//Set up bats
	for (int i = 0; i < bats.size(); i++) {
		bats[i] = new Bat();
	}

	//FAR BUILDINGS
	//set up an array with the paths for all the far buildings
	std::array<std::string, 5> paths;
	for (int i = 0; i < paths.size(); i++) {
		paths[i] = "assets/sprite_sheets/background/far_buildings/far_buildings" + std::to_string(i + 1) + ".png";
	}

	//Load far buildings
	for (int i = 0; i < far_buildings.size()-1; i++) {
		far_buildings[i+1] = loadTexture(paths[i].c_str());
		if (far_buildings[i+1] == NULL) {
			printf("Failed to create texture, far_buildings[%d]. SDL Error: %s\n",i+1, SDL_GetError());
			success = false;
		}
	}
	far_buildings[0] = far_buildings[1];

	//BACKGROUND BUILDINGS
	//Load background buildings
	backgroundTX = loadTexture("assets/sprite_sheets/background/background_buildings.png");
	if (backgroundTX == NULL) {
		printf("Failed to create texture. SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	//FOREGROUND BUILDINGS
	//set up an array with the paths for all the far buildings
	std::array<std::string, 25> paths_foreground;
	for (int i = 0; i < paths_foreground.size(); i++) {
		paths_foreground[i] = "assets/sprite_sheets/background/foreground/foreground" + std::to_string(i + 1) + ".png";
	}

	//Load foregrounds
	for (int i = 0; i < foregrounds.size() - 1; i++) {
		foregrounds[i + 1] = loadTexture(paths_foreground[i].c_str());
		if (foregrounds[i + 1] == NULL) {
			printf("Failed to create texture, foregrounds[%d]. SDL Error: %s\n", i + 1, SDL_GetError());
			success = false;
		}
	}
	foregrounds[0] = foregrounds[25];

	//BATS
	for (int i = 0; i < bats.size(); i++) {
		//Load Bats
		if (!bats[i]->loadMedia()) {
			printf("Failed to create texture. SDL Error: %s\n", SDL_GetError());
			success = false;
		}
	}

	return success;
};

void Background::tick() {
	//FAR BUILDINGS
	//Tick and Choose Far Building Texture
	far_buildings_ticker++;

	if (far_buildings_ticker > 120) {
		far_buildings[0] = far_buildings[rand() % 5 + 1];
		far_buildings_ticker = 0;
	}
	if (far_buildings_ticker > 20) {
		far_buildings[0] = far_buildings[1];
	}

	//FOREGROUND
	foreground_ticker++;
	int number_of_ticks_till_tx_change = 60;

	//Filling up the bottle animation
	if ((foregrounds[0] == foregrounds[25]) && (foreground_ticker > number_of_ticks_till_tx_change)) {
		filling_up_the_bottle = true;
		number_of_ticks_till_tx_change = 2;
	}
	//To ensure that the texture gets changed after two ticks, which is only 
	//the case when we're filling up the bottle
	if (filling_up_the_bottle == true) {
		number_of_ticks_till_tx_change = 2;
	}

	//Changing the current image to the next one
	if ((foreground_ticker > number_of_ticks_till_tx_change) && (filling_up_the_bottle == false)) {
		foreground_ticker = 0;
		//finding out what spritesheet we're currently at and changing it to the next one
		for (int i = 0; i < foregrounds.size(); i++) {
			if ((foregrounds[0] == foregrounds[i]) && (i!=0)) {
				if (i == foregrounds.size() - 1) {
					foregrounds[0] = foregrounds[1];
				}
				else {
					foregrounds[0] = foregrounds[i + 1];
					break;
				}
			}
		}
	}
	//Filling up bottle
	else if ((foreground_ticker > number_of_ticks_till_tx_change) && (filling_up_the_bottle == true)) {
		foreground_ticker = 0;
		//finding out what spritesheet we're currently at
		for (int i = foregrounds.size()-1; i > 0; i--) {
			if ((foregrounds[0] == foregrounds[i]) && (i != 0)) {
				//changing it to the next one
				if (i == 1) {
					filling_up_the_bottle = false;
					number_of_ticks_till_tx_change = 150;
				}
				else {
					foregrounds[0] = foregrounds[i - 1];
					break;
				}
			}
		}
	}

	//Tick Bats
	for (int i = 0; i < bats.size(); i++) {
		bats[i]->tick();
	}
};

void Background::render() {
	//Get Renderer
	SDL_Renderer* renderer = Window::getInstance()->getRenderer();

	//Save old viewport
	SDL_Rect old_viewport;
	SDL_RenderGetViewport(renderer, &old_viewport);

	//Create viewport
	SDL_Rect topLeftViewport;
	topLeftViewport.x = 0;
	topLeftViewport.y = 0;
	topLeftViewport.w = Window::getInstance()->getWindowSizeW();
	topLeftViewport.h = Window::getInstance()->getWindowSizeH();

	//set viewport
	SDL_RenderSetViewport(renderer, &topLeftViewport);

	//Render far_buldings to screen
	SDL_RenderCopy(renderer, far_buildings[0], NULL, NULL);

	//Render back buildings to screen
	SDL_RenderCopy(renderer, backgroundTX, NULL, NULL);

	//Bats Flying in the back of the buildings
	for (int i = 0; i < bats.size(); i++) {
		if(bats[i]->getZIndex() == 1)
			bats[i]->render();
	}

	//Render foreground to frame
	SDL_RenderCopy(renderer, foregrounds[0], NULL, NULL);

	//Bats Flying in front of the building
	for (int i = 0; i < bats.size(); i++) {
		if (bats[i]->getZIndex() == 2)
			bats[i]->render();
	}

	//Reset viewport
	SDL_RenderSetViewport(renderer, &old_viewport);
}

void Background::restart() {
	for (int i = 0; i < bats.size(); i++) {
		bats[i]->~Bat();
		bats[i] = NULL;
	}
	
	for (int i = 0; i < bats.size(); i++) {
		bats[i] = new Bat();
		bats[i]->loadMedia();
	}

	filling_up_the_bottle = true;
	far_buildings_ticker = 0;
	foreground_ticker = 0;
	far_buildings[0] = far_buildings[1];
	foregrounds[0] = foregrounds[25];
};

void Background::close() {
	//Destroy Bats
	for (int i = 0; i < bats.size(); i++) {
		bats[i]->~Bat();
		bats[i] = NULL;
	}

	//Destroy Far Buildings
	for (int i = 0; i < far_buildings.size(); i++) {
		SDL_DestroyTexture(far_buildings[i]);
		far_buildings[i] = NULL;
	}

	//Destroy Background tx
	SDL_DestroyTexture(backgroundTX);
	backgroundTX = NULL;

	//Destroy Foregrounds
	for (int i = 0; i < foregrounds.size(); i++) {
		SDL_DestroyTexture(foregrounds[i]);
		foregrounds[i] = NULL;
	}
}

std::string Background::getType() { return "BACKGROUND"; };

Bottle* Background::spawnBottle() { return NULL; };

void Background::checkInput() { return; };

std::string Background::isDead() { return "NOTDEAD"; };

Background::~Background() {
	close();
};