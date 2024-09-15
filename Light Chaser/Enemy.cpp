#include "Enemy.h"
#include "Player.h"
#include "Math.h"
#include "StageManager.h"
#include <SDL.h>
#include <iostream>

void Enemy::setPos(int x, int y) {
	location.x = x;
	location.y = y;
}

bool Enemy::UpdateAndDraw(SDL_Renderer* renderer, Player player) {
	trail.push_back(location);

	if (trail.size() >= 128) {
		trail.pop_front();
	}

	lastTrailPos = { -99999, -99999 };

	for (it = trail.begin(); it != trail.end(); it++) {
		SDL_SetRenderDrawColor(renderer, 256 - (std::distance(it, trail.begin()) * 2), 0, 0, 256 - (std::distance(it, trail.begin())) * 2);
		if (lastTrailPos.x != -99999 && lastTrailPos.y != -99999) {
			SDL_RenderDrawLine(renderer, lastTrailPos.x, lastTrailPos.y, it->x, it->y);
		}
		lastTrailPos = { it->x, it->y };
		//std::cout << std::distance(it, trail.begin()) << std::endl;
	}


	player.getPos(&target.x, &target.y);

	if (StageManager::getStage() >= 4) {
		target.x += player.velocity.x * 20;
		target.y += player.velocity.y * 20;
		//SDL_RenderDrawPoint(renderer, target.x, target.y);     // Debugging - shows where the enemy is tracking to.
	}
	direction = atan2(target.y - location.y, target.x - location.x);

	srand(time(NULL) * SDL_GetTicks());
	direction += (double) -wildness + (float)(rand()) / ((float)(RAND_MAX / (wildness - -wildness)));


	//SDL_RenderDrawLine(renderer, location.x, location.y, location.x + 1 * ((long double) cos(direction) * 180 / M_PI), location.y + 1 * ((long double) sin(direction) * 180 / M_PI));  - Use for debugging

	speed = (StageManager::getStage() * 0.45) + 1;
	unscaledVelocity = { (float)cos(direction),(float)sin(direction) };
	Math::normalize(&unscaledVelocity.x, &unscaledVelocity.y);
	velocity.x = unscaledVelocity.x * speed;
	velocity.y = unscaledVelocity.y * speed;
	location.x += velocity.x;
	location.y += velocity.y;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	if (Math::distance(location.x, location.y, player.location.x, player.location.y) <= deathDistance) {
		return true;
	}
}