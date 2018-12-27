#include "Enemy02.h"
#include <string>
#include <stdlib.h>
#include <time.h>


extern int sounds[];
extern float VOLUM;
extern float EVOLUM;

Enemy02 * Enemy02::create(Level1 *level, Sprite* player, Collision *collider) {

	Enemy02* pSprite = new Enemy02(level, player, collider);

	if (pSprite->initWithFile("Character/Fly/fly.png")) {

		pSprite->setAnchorPoint(Point::ZERO);
		pSprite->getTexture()->setAntiAliasTexParameters();
		pSprite->setScale(SCALE_FACTOR);
		pSprite->enemy_size = Size(pSprite->getBoundingBox().size.width, pSprite->getBoundingBox().size.height);
		pSprite->setTag(1);

		return pSprite;
	}

	return NULL;
}

Enemy02::Enemy02(void) {}
Enemy02::Enemy02(Level1* levels, Sprite *player, Collision *collider)
{


	this->collider = collider;

	this->player = player;

	inRange = pRight = pLeft = false;
	lastPos = 0.0f;

	level = levels;

	fireRate = 2.0f;
	fire = false;

	velocityX = 0;
	velocityY = 0;
	direction = -1;

	facing_left = -1;
	facing_right = 1;

	setTag(3);

	scheduleUpdate();
}
Enemy02::~Enemy02(void) {}


Rect Enemy02::getCollisionBox() {

	Rect bbox = getBoundingBox();

	Rect rect = Rect(
		bbox.getMinX() + velocityX,
		bbox.getMinY() + 1.0f,
		bbox.size.width,
		bbox.size.height);

	return rect;
}
Rect Enemy02::getUpperCollisionBox() {

	Rect bbox = getBoundingBox();

	Rect rect = Rect(
		bbox.getMinX() + bbox.size.width * 0.33f,
		bbox.getMidY(),
		bbox.size.width * 0.4f,
		bbox.size.height * 1.5f);

	return rect;
}

void Enemy02::update(float f) {

	/*
	if (getPositionX() + 450.0f > player->getPositionX()
		&& getPositionX() < player->getPositionX()) {

		gunpoint = getPosition();

		direction = 1;

		inRange = true;

		state = isAttack;
	}
	else if (getPositionX() - 450.0f < player->getPositionX()
		&& getPositionX() > player->getPositionX()) {

		gunpoint = Vec2(getPositionX() + getBoundingBox().getMaxX(), getPositionY());

		direction = -1;

		inRange = true;

		state = isAttack;
	}
	else {
		inRange = false;
	}

	if (!fire) {
		fireRate -= f;

		if (fireRate <= 0) {
			fire = true;
			fireRate = 2.0f;
		}
	}
	*/

	//enemyAI(f);

	enemyCollusion(f);
}

void Enemy02::enemyAI(float f) {

	switch(state) {
	case isAttack:

		/*
		if (fire) {
			fire = false;

			EBullet *bullet = EBullet::create(gunpoint, direction);
			bullet->setVisible(false)
			collider->addEnemyB(bullet);


			AudioProfile effect;
			effect.name = "ebullet";
			effect.maxInstances = 1000;

			sounds[3] = AudioEngine::play2d("Sounds/effect/e2gunshot.mp3", false, EVOLUM, &effect);
		}
		*/
		
		if (!inRange)
			state = isSleep;

		break;

	case isSleep:

		break;
	}

}

void Enemy02::enemyCollusion(float f) {

	// 6
	Rect enemy_rect = getBoundingBox();

	Point tmp;
	std::vector<Rect> tiles;

	tiles.clear();

	tmp = level->positionToTileCoordinate(Point(getPositionX() + enemy_size.width * 0.5f,
		getPositionY() + enemy_size.height * 0.5f));
	// tmp의 x, y가 스프라이트의 중앙으로


	if (velocityX > 0)
		tiles = level->getCollisionTilesX(tmp, 1); // 전방 상, 중, 하
	else
		tiles = level->getCollisionTilesX(tmp, -1); // 후방 상, 중, 하


	enemy_rect.setRect(
		getBoundingBox().getMinX() + velocityX,
		getBoundingBox().getMinY() + 1.0f, // dont let the rectangle touch the ground otherwise, will count as collision
		enemy_size.width,
		enemy_size.height
	);

	for (Rect tile : tiles) {
		if (enemy_rect.intersectsRect(tile)) {
			velocityX = 0;
			break; // 캐릭터 전, 중, 후에 타일이 있으면 정지
		}
	}

	tiles.clear();

	if (velocityY > 0)
		tiles = level->getCollisionTilesY(tmp, 1); // 캐릭터 위쪽
	else if (velocityY < 0)
		tiles = level->getCollisionTilesY(tmp, -1); // 캐릭터 아래쪽

	enemy_rect.setRect(
		getBoundingBox().getMinX(),
		getBoundingBox().getMinY(),
		enemy_size.width,
		enemy_size.height
	);

	updateState(f);
}

void Enemy02::updateState(float f) {

	if (direction == facing_right)
		setFlippedX(true);
	else
		setFlippedX(false);

}

void Enemy02::setMove() {

	MoveTo *left = MoveTo::create(1.5f, Vec2(getPositionX() - 300.0f, getPositionY()));
	MoveTo *right = MoveTo::create(1.5f, Vec2(getPositionX() + 300.0f, getPositionY()));
	Sequence *action_2 = Sequence::create(left, right, NULL);
	RepeatForever *action_3 = RepeatForever::create(action_2);    // 액션 , 횟수
	this->runAction(action_3);
}