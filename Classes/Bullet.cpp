#include "Bullet.h"
#include "Level1.h"
#include "defines.h"
#include <stdlib.h>

Bullet* Bullet::create(Vec2 pos, int dir) {

	Bullet* pSprite = new Bullet(pos, dir);

	if (pSprite->initWithFile("Character/Pug/pugs/shot_fire.png")) {

		pSprite->setScale(SCALE_FACTOR);
		pSprite->setPosition(pos);

		if (dir == 1)
			pSprite->setFlipX(true);

		return pSprite;
	}

	return NULL;
}


Bullet::Bullet(void) {}
Bullet::Bullet(Vec2 pos, int dir) {

	Vec2 offsetPlus = Vec2(pos.x + dir, pos.y); // 총알이 발사되는 지점
	Vec2 offset = (offsetPlus - pos); // 총알이 나아가는 방향

	offset.normalize(); // 정규화
	Vec2 shootAmount = offset * 200; // 200의 거리를 이동

	realDest = shootAmount + pos; // 현재 포지션에서 200만큼 이동

	// 액션 실행
	MoveTo* actionMove = MoveTo::create(PLAYER_BULLET_VELOCITY, realDest);
	RemoveSelf* actionRemove = RemoveSelf::create();
	runAction(Sequence::create(actionMove, actionRemove, nullptr));

}
Bullet::~Bullet(void) {}
