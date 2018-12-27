#pragma once
#include "cocos2d.h"
#include "defines.h"

using namespace cocos2d;
using namespace std;

class BackGround : public Sprite {
private:

	bool Scrolling, parallax, checkLayer;

	Sprite* target;
	float targetX;
	Sprite* BGs[3];
	
	float paralaxSpeed, BgSize, viewPoint;
	int left, right;

	Vec2 pPos;

	float lastCameraX;

	BackGround(void);
	BackGround(Sprite* player, string fileName, float parallaxSpeed);
	virtual ~BackGround(void);

	void ScrollLeft();
	void ScrollRight();

public:
	static BackGround* create(Sprite* player, string fileName, float Y, float parallaxSpeed);

	virtual void update(float f);
};