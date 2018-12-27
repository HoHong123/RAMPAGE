#pragma once

#include "cocos2d.h"
#include "Level1.h"
#include <vector>
using namespace cocos2d;

class Player1 : public Sprite
{
private:

	float x, y;

	Player1(void);
	Player1(Level1* level);
	virtual ~Player1(void);

	Rect getCollisionBox();
	Rect getUpperCollisionBox();

	void animation(string s);

	void hazard_collision(Point tmp);

	void player_collusion(float f);
	void updateState(float f);
	void setupAnimation(const char* name);

protected:

	Level1* level;
	std::vector<EventKeyboard::KeyCode> heldKeys;

public:

	float velocityX;
	float velocityY;

	int direction;
	int facing_left;
	int facing_right;
	bool grounded;
	bool jumping;

	static Player1* create(Level1* levels);

	Animate *walk;
	Size player_size;

	Point gun_point;
};
