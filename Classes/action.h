
#pragma once
#include "cocos2d.h"

using namespace cocos2d;

class action {
	public:
		static float Lerp(float firstFloat, float secondFloat, float by);
		static Vec2 Lerp(Vec2 firstVector, Vec2 secondVector, float by);
};