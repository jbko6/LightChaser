#pragma once
#include<list>
#include<SDL.h>
#include <list>
#include "Player.h"

class Player {
private:
	struct point {
		int x = 0;
		int y = 0;
	};
	struct Vector2 {
		float x = 0;
		float y = 0;
	};
	struct Color {
		int r = 0;
		int g = 0;
		int b = 0;
		int a = 255;
	};
	double direction = 90;
	point mousePos = { 0, 0 };
	Vector2 unscaledVelocity;
	std::list<Vector2> trail = {};
	std::list<Vector2>::iterator it;
	Vector2 lastTrailPos = {-99999, -99999};
public:
	float speed = 1;
	Vector2 location = { 320, 240 };
	Vector2 velocity = { 0, 0 };
	Color playerColor = { 255, 0, 255, 255 };
	int deathDistance = 2;
	bool UpdateAndDraw(SDL_Renderer* renderer, SDL_Event ev);
	void getPos(float* x, float* y);
	Player();
	~Player();
};