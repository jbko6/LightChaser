#include "Player.h"
#include "Math.h"
#include "StageManager.h"
#include "Enemy.h"
#include <list>
#include<iostream>
#include <SDL.h>

Player::Player() {
	srand(time(NULL));
	playerColor = { rand() % 254 + 1, rand() % 254 + 1 , rand() % 254 + 1 , 255 };
	std::cout << "Player color randomly chosen: " << playerColor.r << " " << playerColor.g << " " << playerColor.b << std::endl;
	if (playerColor.r >= 150 && (playerColor.b + playerColor.g) <= 120) {
		srand(time(NULL) * 2);
		playerColor = { rand() % 254 + 1, rand() % 254 + 1 , rand() % 254 + 1 , 255 };
		std::cout << "Color was mostly red, so color was randomly chosen again: " << playerColor.r << " " << playerColor.g << " " << playerColor.b << std::endl;
	}
}

Player::~Player() {

}

bool Player::UpdateAndDraw(SDL_Renderer* renderer, SDL_Event ev) {

	// ---------------------------------------------------------------------------------------- TRAIL --------------------------------------------------------------------------------------------- \\

	trail.push_back(location);

	if (trail.size() >= 128) {
		trail.pop_front();
	}

	lastTrailPos = { -99999, -99999 };

	for (it = trail.begin(); it != trail.end(); it++) {
		float distance = std::distance(trail.begin(), it);
		SDL_SetRenderDrawColor(renderer, ((float) Player::playerColor.r / 255) * distance * 2, ((float)Player::playerColor.g / 255) * distance * 2, ((float)Player::playerColor.b / 255) * distance * 2, ((float)Player::playerColor.a / 255) * distance * 2);
		//SDL_RenderDrawPoint(renderer, it->x, it->y);
		if (lastTrailPos.x != -99999 && lastTrailPos.y != -99999) {
			SDL_RenderDrawLine(renderer, lastTrailPos.x, lastTrailPos.y, it->x, it->y);
		}
		lastTrailPos = { it->x, it->y };
		//std::cout << std::distance(it, trail.begin()) << std::endl;
	}

	// ---------------------------------------------------------------------------------------- MOVEMENT ---------------------------------------------------------------------------------------- \\

	SDL_GetMouseState(&mousePos.x, &mousePos.y);
	direction = atan2(mousePos.y - location.y, mousePos.x - location.x);

	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	//SDL_RenderDrawLine(renderer, location.x, location.y, location.x + 1 * ((long double) cos(direction) * 180 / M_PI), location.y + 1 * ((long double) sin(direction) * 180 / M_PI));  // Use for debugging

	speed = (StageManager::getStage() * 0.5) + 1;
	unscaledVelocity = {(float) cos(direction),(float) sin(direction) };
	Math::normalize(&unscaledVelocity.x, &unscaledVelocity.y);
	velocity.x = unscaledVelocity.x * speed;
	velocity.y = unscaledVelocity.y * speed;
	location.x += velocity.x; // location is also known as the position of the player
	location.y += velocity.y;

	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// ---------------------------------------------------------------------------------------- COLLISION --------------------------------------------------------------------------------------- \\

	if (Math::distance(location.x, location.y, mousePos.x, mousePos.y) <= deathDistance) {
		return true;
	}

	// ---------------------------------------------------------------------------------------- END --------------------------------------------------------------------------------------------

	return false;
}

void Player::getPos(float* x, float* y) {
	*x = location.x;
	*y = location.y;
}