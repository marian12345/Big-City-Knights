#include "Window.h"
#include <stdio.h>
Window* Window::window = NULL;

Window::Window() {
	sdl_window = NULL;
	renderer = NULL;
	fullscreen = false;
};

Window* Window::getInstance() {
	if (window == NULL) {
		window = new Window();
	}
	return window;
}

bool Window::setWindowAndRenderer(SDL_Window* window, SDL_Renderer* renderer) {
	bool success = true;

	this->sdl_window = window;
	if (this->sdl_window != window) {
		printf("Window.setWindow(..) failed to set up window\n");
		success = false;
	}

	this->renderer = renderer;
	if (this->renderer != renderer){
		printf("Window.setWindow(..) failed to set up renderer\n");
		success = false;
	}

	return success;
}

bool Window::setSize(int w, int h) {
	bool success = false;

	if (sdl_window == NULL) {
		window_size_w = w;
		window_size_h = h;
		success = true;
	}

	return success;
};

bool Window::setFullscreen(bool fullscreen) {
	bool success = false;

	if (sdl_window == NULL) {
		this->fullscreen = fullscreen;
		success = true;
	}

	return success;
};

SDL_Window* Window::getSDL_Window() {
	if (sdl_window != NULL) {
		return sdl_window;
	}
	else {
		printf("Window::window was not set up yet. Failure in Window::getWindow()");
		return NULL;
	}
};

SDL_Renderer* Window::getRenderer() {
	if (renderer != NULL) {
		return renderer;
	}
	else {
		printf("Window::renderer was not set up yet. Failure in Window::getRenderer()");
		return NULL;
	}
}

bool Window::isFullscreen() {
	return fullscreen;
};

int Window::getWindowSizeH() {
	if (sdl_window != NULL) {
		int width = 0, height = 0;
		SDL_GetWindowSize(sdl_window, &width, &height);
		return height;
	}
	else {
		return window_size_h;
	}
}

int Window::getWindowSizeW() {
	if (sdl_window != NULL) {
		int width = 0, height = 0;
		SDL_GetWindowSize(sdl_window, &width, &height);
		return width;
	}
	else {
		return window_size_w;
	}
};

Window::~Window() {
	//Destroy SDL Components
	if (renderer != NULL) {
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}
	if (sdl_window != NULL) {
		SDL_DestroyWindow(sdl_window);
		sdl_window = NULL;
	}
	//free window
	Window::window = NULL;
};