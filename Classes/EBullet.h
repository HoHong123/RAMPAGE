#pragma once

#include "cocos2d.h"
#include <vector>
using namespace cocos2d;
using namespace std;

class EBullet : public CCSprite
{
public:

	int direction;
	float velocityX;
	float velocityY;
	float duration;

	Vec2 realDest;

	static EBullet* create(Vec2 pos, int dir);

	EBullet(void);
	EBullet(Vec2 pos, int dir);
	virtual ~EBullet(void);
};