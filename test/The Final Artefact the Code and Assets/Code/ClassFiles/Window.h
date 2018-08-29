#include <SDL.h>

class Window {
	private:
		static Window* window;
		SDL_Window* sdl_window;
		SDL_Renderer* renderer;
		int window_size_w;
		int window_size_h;
		bool fullscreen;
		Window();
	public:
		static Window* getInstance();
		bool setWindowAndRenderer(SDL_Window* window, SDL_Renderer* renderer);
		bool setSize(int w, int h);
		bool setFullscreen(bool fullscreen);
		SDL_Window* getSDL_Window();
		SDL_Renderer* getRenderer();
		bool isFullscreen();
		int getWindowSizeH();
		int getWindowSizeW();
		~Window();
};