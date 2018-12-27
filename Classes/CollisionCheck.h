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
	
	// 각 총알과 플레이어, 적을 넣는 배열
	Sprite *player;
	CCArray *eBullet;
	CCArray *pBullet;
	CCArray *Enemy;

	// 각 객체 추가하는 함수 
	void addPlayerB(Sprite* bullet);
	void addEnemyB(Sprite* bullet);
	void addEnemy(Sprite* bullet);
	CCArray *getEBullet();

	// 무적 함수
	void setInvincibility();
	// 체력 회복 함수
	void addHealth(int heal);
	// 데미지를 받는 함수 
	void dmgHealth(int dmg);

	void collisionDetection();
};