#include "EBullet.h"
#include "Level1.h"
#include "defines.h"
#include <stdlib.h>

EBullet* EBullet::create(Vec2 pos, int dir) {

	EBullet* pSprite = new EBullet(pos, dir);

	if (pSprite->initWithFile("Character/Fly/shot_fire.png")) {

		pSprite->setScale(SCALE_FACTOR);
		pSprite->setPosition(pos);

		if (dir == 1)
			pSprite->setFlipX(true);

		return pSprite;
	}

	return NULL;
}


EBullet::EBullet(void) {}
EBullet::EBullet(Vec2 pos, int dir) {

	Vec2 offsetPlus = Vec2(pos.x + dir, pos.y);
	Vec2 offset = (offsetPlus - pos);

	offset.normalize();
	Vec2 shootAmount = offset * 500;
	shootAmount.x *= dir;

	realDest = shootAmount + pos;

	MoveTo* actionMove = MoveTo::create(PLAYER_BULLET_VELOCITY, realDest);
	RemoveSelf* actionRemove = RemoveSelf::create();
	runAction(Sequence::create(actionMove, actionRemove, nullptr));

}
EBullet::~EBullet(void) {}
