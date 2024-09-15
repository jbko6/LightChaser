#include "Math.h"
#include<iostream>

void Math::normalize(float* x, float* y) {
	if (x != 0 && y != 0 && magnitude(*x, *y) != 0) {
		*x /= magnitude(*x, *y);
		*y /= magnitude(*x, *y);
	}
}

float Math::magnitude(float x, float y) {
	return sqrt(pow(x, 2) + pow(y, 2));
}

float Math::distance(float x1, float y1, float x2, float y2) {
	return abs(sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
}

float Math::lerp(float a, float b, float f)
{
	return a + f * (b - a);
}