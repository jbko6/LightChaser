#pragma once
#include <SDL.h>
#include "Enemy.h"
#include "Player.h"

class StageManager
{
private:
	static int stage;
	static int stageTiming;
	static float progressionTime;
public:
	static bool updateStage(SDL_Window *window, SDL_Renderer* renderer, Player player);
	static int getStage();
	static void setStageTiming(int time);
	static int getStageTiming();
	static std::list<Enemy> enemies;
	static std::list<Enemy>::iterator it;
};

