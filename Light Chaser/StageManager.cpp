#include "StageManager.h"
#include <SDL.h>
#include <iostream>

int StageManager::stage = 0;
int StageManager::stageTiming = 5;
float StageManager::progressionTime = SDL_GetTicks() + (StageManager::stageTiming * 1000);
std::list<Enemy> StageManager::enemies = {};
std::list<Enemy>::iterator StageManager::it;

bool StageManager::updateStage(SDL_Window* window, SDL_Renderer* renderer, Player player)
{
	if (SDL_GetTicks() >= StageManager::progressionTime) {
		StageManager::progressionTime = SDL_GetTicks() + (StageManager::stageTiming * 1000);
		StageManager::stage++;

		srand(time(NULL));
		int winSizeX, winSizeY;
		SDL_GetWindowSize(window, &winSizeX, &winSizeY);
		Enemy newEnemy;
		newEnemy.location = { (float) (rand() % winSizeX - 1), (float) (rand() % winSizeY - 1) };
		StageManager::enemies.push_back(newEnemy);

		std::cout << "next stage! " << StageManager::stage << std::endl;
	}

	for (it = enemies.begin(); it != enemies.end(); it++) {
		if (it->UpdateAndDraw(renderer, player)) { return true; }
	}

	return false;
}

int StageManager::getStage()
{
	return StageManager::stage;
}

void StageManager::setStageTiming(int time)
{
	StageManager::stageTiming = time;
}

int StageManager::getStageTiming()
{
	return StageManager::stageTiming;
}