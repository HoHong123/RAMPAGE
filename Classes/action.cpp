#include "action.h"

Vec2 action::Lerp(Vec2 firstVector, Vec2 secondVector, float by)
{
	float retX = Lerp(firstVector.x, secondVector.x, by);
	float retY = Lerp(firstVector.y, secondVector.y, by);
	return Vec2(retX, retY);
}

float action::Lerp(float firstFloat, float secondFloat, float by)
{
	return firstFloat * by + secondFloat * (1 - by);
}