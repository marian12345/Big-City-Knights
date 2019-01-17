#include "Game.h"
#include <SDL.h>
#include <stdio.h>
#include <SDL_image.h>
#include "Window.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "Mixer.h"

Game::Game(bool fullscreen) {
	runningFlag = false;
	restartFlag = false;

	//Setting up Window Singletonn
	Window* window = Window::getInstance();

	if (!window->setFullscreen(fullscreen)) {
		printf("Unable to set Window::window->fullscreen to %d\n", fullscreen);
	}

	if (!window->setSize(640, 400)) {
		printf("Unable to set window size\n");
	}

	lvl_elements.clear();
	menu = NULL;
};

Game::Game(int width, int height) {
	runningFlag = false;
	restartFlag = false;

	//Setting up Singleton Window
	Window* window = Window::getInstance();

	if (!window->setFullscreen(false)) {
		printf("Unable to set Window::window->fullscreen to %d\n", false);
	}

	if (!window->setSize(640, 400)) {
		printf("Unable to set Window Size");
	}

	lvl_elements.clear();
	menu = NULL;
};

bool Game::init() {
	bool success = true;
	SDL_Window* global_window = NULL;
	SDL_Renderer* renderer = NULL;
	int window_size_w = Window::getInstance()->getWindowSizeW();
	int window_size_h = Window::getInstance()->getWindowSizeH();

	//Initializing SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("Failed to initialize SDL! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else {

		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Creating the window
		if (Window::getInstance()->isFullscreen()) {
			global_window = SDL_CreateWindow("Prototype1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_size_w, window_size_h, SDL_WINDOW_FULLSCREEN_DESKTOP);
		}
		else {
			global_window = SDL_CreateWindow("Prototype1", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_size_w, window_size_h, SDL_WINDOW_SHOWN);
		}
		if (global_window == NULL) {
			printf("Failed to create window! SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else {

			//Create renderer for window
			renderer = SDL_CreateRenderer(global_window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {

				//Initialize renderer color
				SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading 
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				//Initialize SDL_ttf
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize. SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}

				//Initialize SDL_mixer 
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) { 
					printf( "SDL_mixer could not initialize. SDL_mixer Error: %s\n", Mix_GetError() ); 
					success = false; 
				}

				//Disable Mouse
				SDL_ShowCursor(SDL_DISABLE);

				//adapt global window size variables
				if (Window::getInstance()->isFullscreen()) {
					SDL_GetWindowSize(global_window, &window_size_w, &window_size_h);
					if (!Window::getInstance()->setSize(window_size_w, window_size_h)) {
						printf("Unable to adapt window size variables");
					}
				}

				if (!Window::getInstance()->setWindowAndRenderer(global_window, renderer)) {
					printf("Window Could not be set up. Failure in Window::setWindow(..).");
					success = false;
				}
				
				//Create Menu
				menu = new Menu();
				if (menu->init() != true) {
					printf("Failed to initiate Menu.\n");
				}

				//Setting up the Player
				PlayerLeft* pl = new PlayerLeft();
				PlayerRight* pr = new PlayerRight();
				lvl_elements.push_back(pl);
				lvl_elements.push_back(pr);

				//Attach them to the Collision Detection System. If one attachment fails print error
				ObservableCollisionDetection* cd = ObservableCollisionDetection::getInstance();
				if ((!cd->attach(pl)) || (!cd->attach(pr))) {
					printf("Failed to attach one or both players to Collision Detection System");
				}
				pl = NULL;
				pr = NULL;

				//Attach Background
				lvl_elements.push_back(new Background());
			}
		}
	}

	global_window = NULL;
	renderer = NULL;

	return success;
}

bool Game::load_media() {
	bool success = true;
	
	//Load lvl elements
	for (int i = 0; i < lvl_elements.size(); i++) {
		if (!lvl_elements.at(i)->loadMedia()) {
			printf("Failed to load lvl element: %s! SDL Error: %s\n", lvl_elements.at(i)-> getType().c_str(), SDL_GetError());
			success = false;
		}
	}

	if (!menu->loadMedia()) {
		printf("Failed to load Menu! SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	if (!Mixer::getInstance()->loadMedia()) {
		printf("Failed to load sound effects. SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
};

void Game::start() {
	printf("Loading...");
	if (init() == true) {
		if (load_media() == true) {
			printf("Done\n");
			if (menu->show(Menu::STARTGAME) == true) {
				run();
			}
		}
		else {
			printf("Failed to load Media!\n");
		}
	}
	else {
		printf("Failed to initialize!\n");
	}
};

void Game::run() {
	//The Timing
	const int FPS = 60;
	const int frame_delay = 1000 / FPS; // How much ms must pass for each frame
	Uint32 frame_start = 0;
	int frame_time = 0;

	//set flags
	runningFlag = true;
	restartFlag = false;
	
	//Game loop
	while (runningFlag) {
		frame_start = SDL_GetTicks();
		
		input();
		update();
		render();

		//Check if restartFlag is true
		if (restartFlag == true) {
			restart();
			restartFlag = false;
			runningFlag = true;
		}

		//If Frame is processed before its appropriate time
		frame_time = SDL_GetTicks() - frame_start;
		if (frame_delay > frame_time) {
			frame_time = frame_delay - frame_time;
			SDL_Delay(frame_time);
		}
	}
}

void Game::input() {
	//Check ESC and Quit Button
	SDL_Event e;
	while (SDL_PollEvent(&e)) {

		if (e.type == SDL_QUIT) {
			runningFlag = false;
		}

		if (e.type == SDL_KEYDOWN) {
			if (e.key.keysym.sym == SDLK_ESCAPE) {
				Mixer::getInstance()->playMusic(Mixer::LOBBYSONG);
				if (gameEnded() == true) {
					if (menu->show(Menu::RESTART) == false) {
						runningFlag = false;
					}
					else {
						restartFlag = true;
					}
				}
				else {
					if (menu->show(Menu::CONTINUE) == false) {
						runningFlag = false;
					}
				}
			}
		}
	}

	//check player inputs
	for (int i = 0; i < lvl_elements.size(); i++) {
		lvl_elements.at(i)->checkInput();
	}

	//Check if a bottle is thrown if yes try to spawn a bottle but check NULL pointer parameter
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	
	if (currentKeyStates[SDL_SCANCODE_I]) {
		for (int i = 0; i < lvl_elements.size(); i++) {
			if (lvl_elements.at(i)->getType().compare("PLAYERRIGHT") == 0) {
				Bottle* bottle = lvl_elements.at(i)->spawnBottle();
				if (bottle != NULL){
					lvl_elements.push_back(bottle);
				}
				break;
			}
		}
	}

	if (currentKeyStates[SDL_SCANCODE_C]) {
		for (int i = 0; i < lvl_elements.size(); i++) {
			if (lvl_elements.at(i)->getType().compare("PLAYERLEFT") == 0) {
				Bottle* bottle = lvl_elements.at(i)->spawnBottle();
				if (bottle != NULL) {
					lvl_elements.push_back(bottle);
				}
				break;
			}
		}
	}
};

void Game::tick() {
	for (int i = 0; i < lvl_elements.size(); i++) {
		lvl_elements.at(i)->tick();
	}
};

void Game::restart() {
	//Erase old level items
	for (int i = 0; i < lvl_elements.size(); i++) {
		if ((lvl_elements.at(i)->getType().compare("BOTTLE") == 0) || (lvl_elements.at(i)->getType().compare("LEVELTEXTURE") == 0)) {
			LevelElementInterface* tmp = lvl_elements.at(i);
			lvl_elements.erase(lvl_elements.begin() + i);
		}
	}

	//
	for (int i = 0; i < lvl_elements.size(); i++) {
		lvl_elements.at(i)->restart();
	}
};

void Game::update() {
	//Check Collisions
	ObservableCollisionDetection::getInstance()->checkCollisions();

	//CHECK IF BOTTLES ARE BROKEN AND READY TO GET DETACHED FROM GAME
	for (int i = 0; i < lvl_elements.size(); i++) {
		if (lvl_elements.at(i)->isDead().compare("BROKENBOTTLE") == 0) {
			LevelElementInterface* tmp = lvl_elements.at(i);
			lvl_elements.erase(lvl_elements.begin() + i);
		}
	}

	//Check if a player is dead - if yes create a LevelTexture - if it hasn't been created yet
	for (int i = 0; i < lvl_elements.size(); i++) {
		if (lvl_elements.at(i)->isDead().compare("DEADPLAYER") == 0) {
			bool level_texture_existing = false; // This LevelTexture tells the players that they must press ESC to Restart the Game
			
			for (int i = 0; i < lvl_elements.size(); i++) {
				if (lvl_elements.at(i)->getType().compare("LEVELTEXTURE") == 0)
					level_texture_existing = true;
			}

			if (level_texture_existing == false) {
				SDL_Color color1 = { 19, 249, 24, 255 };
				LevelTexture *lt = new LevelTexture("- Press  ESC  to  Restart  the  Game -", "assets/fonts/Butcherman-Regular.ttf", 48, color1);
				lt->loadMedia();
				lvl_elements.push_back(lt);
			}
		}
	}

	//tick players
	tick();
};

void Game::render() {
	SDL_Renderer* renderer = Window::getInstance()->getRenderer();

	//Clear Screen
	SDL_RenderClear(renderer);
	
	//Render Background
	int bg = 0;
	for (int i = 0; i < lvl_elements.size(); i++) {
		if (lvl_elements.at(i)->getType().compare("BACKGROUND") == 0) {
			bg = i;
			lvl_elements.at(i)->render();
		}
	}

	//Render other lvl elements
	for (int i = 0; i < lvl_elements.size(); i++) {
		if(i != bg)
			lvl_elements.at(i)->render();
	}

	//Update screen
	SDL_RenderPresent(renderer);
};

bool Game::gameEnded() {
	bool someoneDied = false;

	for (int i = 0; i < lvl_elements.size(); i++) {
		if (lvl_elements.at(i)->isDead().compare("DEADPLAYER") == 0) {
			someoneDied = true;
			break;
		}
	}

	return someoneDied;
};

void Game::close() {
	//Destroy Players
	for (int i = 0; i < lvl_elements.size(); i++) {
		lvl_elements.at(i)->close();
	}
	lvl_elements.clear();

	//Destroy Window, Collision Detection and Mixer - Singletons
	Window::getInstance()->~Window();
	ObservableCollisionDetection::getInstance()->~ObservableCollisionDetection();
	Mixer::getInstance()->~Mixer();

	//Close Menu
	menu->close();

	//Quit SDL Subsystems
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
};

Game::~Game() {
	close();
};