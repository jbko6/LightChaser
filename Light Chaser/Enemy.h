#pragma once
#include <list>
#include <SDL.h>
#include "Player.h"
#include <random>


class Enemy
{
private:
	struct point {
		int x = 0;
		int y = 0;
	};
	struct Vector2 {
		float x = 0;
		float y = 0;
	};
	double direction = 90;
	std::list<Vector2> trail = {};
	std::list<Vector2>::iterator it;
	Vector2 unscaledVelocity;
	Vector2 lastTrailPos = { -99999, -99999 };
public:
	float speed = 0.5;
	Vector2 location = { 1, 1 }; // AKA position
	Vector2 target = { 0, 0 }; // Where the enemy will seek to
	Vector2 velocity = { 0, 0 };
	int deathDistance = 5;
	float wildness = 0.5;
	bool UpdateAndDraw(SDL_Renderer* renderer, Player player);
	void setPos(int x, int y);
};

