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

	Vec2 offsetPlus = Vec2(pos.x + dir, pos.y); // �Ѿ��� �߻�Ǵ� ����
	Vec2 offset = (offsetPlus - pos); // �Ѿ��� ���ư��� ����

	offset.normalize(); // ����ȭ
	Vec2 shootAmount = offset * 200; // 200�� �Ÿ��� �̵�

	realDest = shootAmount + pos; // ���� �����ǿ��� 200��ŭ �̵�

	// �׼� ����
	MoveTo* actionMove = MoveTo::create(PLAYER_BULLET_VELOCITY, realDest);
	RemoveSelf* actionRemove = RemoveSelf::create();
	runAction(Sequence::create(actionMove, actionRemove, nullptr));

}
Bullet::~Bullet(void) {}
