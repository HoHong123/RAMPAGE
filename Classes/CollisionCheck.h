#pragma once
#include "cocos2d.h"
#include "defines.h"

using namespace cocos2d;
using namespace experimental;



class Collision : public Sprite {
private:

	int pHealth;
	bool isInvincible;

public :

	Collision();
	Collision(Sprite* player);
	Collision(Sprite* player, int health);
	~Collision();
	
	// �� �Ѿ˰� �÷��̾�, ���� �ִ� �迭
	Sprite *player;
	CCArray *eBullet;
	CCArray *pBullet;
	CCArray *Enemy;

	// �� ��ü �߰��ϴ� �Լ� 
	void addPlayerB(Sprite* bullet);
	void addEnemyB(Sprite* bullet);
	void addEnemy(Sprite* bullet);
	CCArray *getEBullet();

	// ���� �Լ�
	void setInvincibility();
	// ü�� ȸ�� �Լ�
	void addHealth(int heal);
	// �������� �޴� �Լ� 
	void dmgHealth(int dmg);

	void collisionDetection();
};