#include "Player.h"
#include "Enemy.h"
#include "StageManager.h"
#include<SDL.h>
#include<iostream>
#include<list>

int main(int argc, char* args[])
{
	SDL_Window *window = nullptr;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "Video initialization error: " << SDL_GetError() << std::endl;
	}
	else {
		window = SDL_CreateWindow("Title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
		if (window == NULL)
			std::cout << "Window creation error: " << SDL_GetError() << std::endl;
		else {
			SDL_UpdateWindowSurface(window);
		}
	}

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	bool running = true;
	SDL_Event ev;

	SDL_Rect testRect{50, 50, 200, 200};

	int i = 50;

	Player player;

	// Main loop
	while (running) {
		SDL_RenderClear(renderer);
		// Quit
		if (SDL_PollEvent(&ev)) {
			if (ev.type == SDL_QUIT)
				running = false;
			
		}

		if (StageManager::updateStage(window, renderer, player)) { SDL_Quit(); return 0; }

		if (player.UpdateAndDraw(renderer, ev)) { std::cout << "You hit the player!" << std::endl; SDL_Delay(2000); }

		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

	return 0;
}