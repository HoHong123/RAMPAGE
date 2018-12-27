#pragma once

#include "cocos2d.h"
#include "Level1.h"
#include "defines.h"
using namespace cocos2d;

class Enemy01 : public Sprite
{
private:

	float x, y;
	float pX, pY;

	Sprite *player;

	int health;

	bool inRange;
	bool pRight, pLeft;

	enum behavior {
		isSleep,
		isSeek,
		isAttack
	} state;

	float sleepDu, seekDu, lastPos;

protected:

public:
	float velocityX;
	float velocityY;

	int direction;
	int facing_left;
	int facing_right;
	bool grounded;
	bool jumping;
	bool onEdge;

	Level1 *level;

	static Enemy01* create(Level1 *levels, Sprite *player);
	Enemy01(void);
	Enemy01(Level1* level, Sprite *player);
	virtual ~Enemy01(void);

	Animate *walk;
	Size enemy_size;

	Rect getCollisionBox();
	Rect getUpperCollisionBox();
	void hazard_collision(Point tmp);

	virtual void update(float f);
	void enemyAI(float f);
	void enemyCollusion(float f);
	void updateState(float f);
	void setupAnimation(const char* name);

};
