#pragma once

#include "cocos2d.h"
#include "Level1.h"
#include "defines.h"
#include "Stage1.h"
#include "EBullet.h"
#include "CollisionCheck.h"
#include "audio/include/AudioEngine.h"
using namespace cocos2d;

class Enemy02 : public Sprite
{
private:

	Collision *collider;

	// �ѱ�
	Vec2 gunpoint;

	// �Ѿ� �߻� ��
	float fireRate;
	bool fire; // �Ѿ� �߻� ��/��

	Sprite *player; // �÷��̾�

	int health; // ü��

	bool inRange; // �÷��̾� �νİŸ�
	bool pRight, pLeft; 

	enum behavior {
		isSleep,
		isAttack
	} state;

	float sleepDu, lastPos;

protected:

public:
	float velocityX;
	float velocityY;

	int direction;
	int facing_left;
	int facing_right;

	Level1 *level;

	static Enemy02* create(Level1 *levels, Sprite *player, Collision *collider);
	Enemy02(void);
	Enemy02(Level1* level, Sprite *player, Collision *collider);
	virtual ~Enemy02(void);

	Size enemy_size;

	Rect getCollisionBox();
	Rect getUpperCollisionBox();

	virtual void update(float f);
	void enemyAI(float f);
	void enemyCollusion(float f);
	void updateState(float f);
	void setMove();

};
