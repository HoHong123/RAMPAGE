#pragma once

#include "cocos2d.h"
#include <vector>
using namespace cocos2d;
using namespace std;

class Bullet : public CCSprite
{
public:

	int direction;
	float velocityX;
	float velocityY;
	float duration;

	Vec2 realDest;

	static Bullet* create(Vec2 pos, int dir);

	Bullet(void);
	Bullet(Vec2 pos, int dir);
	virtual ~Bullet(void);
};