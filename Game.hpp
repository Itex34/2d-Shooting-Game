#pragma once
#ifndef Game_hpp
#define Game_hpp
#define SDL_MAIN_HANDLED
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include <iostream>


class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvents();
	void update();
	void render();
	void clean();
	bool running() { return isRunning; }
	SDL_Renderer* getRenderer() const;

private:
	int width = 100;
	int height = 100;
	int cnt = 0;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};


#endif // !Game_hpp
