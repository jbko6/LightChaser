#pragma once
class Math
{
public:
	static void normalize(float* x, float* y);
	static float magnitude(float x, float y);
	static float distance(float x1, float y1, float x2, float y2);
	static float lerp(float a, float b, float f);
};

