#include "Enemy01.h"
#include <string>
#include <stdlib.h>
#include <time.h>


Enemy01 * Enemy01::create(Level1 *level, Sprite* player) {

	Enemy01* pSprite = new Enemy01(level, player);

	if (pSprite->initWithFile("Character/Main/idle.png")) {

		pSprite->setAnchorPoint(Point::ZERO);
		pSprite->getTexture()->setAntiAliasTexParameters();
		pSprite->setScale(SCALE_FACTOR);
		pSprite->enemy_size = Size(pSprite->getBoundingBox().size.width, pSprite->getBoundingBox().size.height);
		pSprite->setTag(1);

		return pSprite;
	}

	return NULL;
}

Enemy01::Enemy01(void){}
Enemy01::Enemy01(Level1* levels, Sprite *player)
{
	this->player = player;

	inRange = pRight = pLeft = false;
	lastPos = 0.0f;

	srand((unsigned int)time(NULL));

	seekDu = 0.0f;
	sleepDu = 2.0f;
	state = isSleep;

	level = levels;

	velocityX = 0;
	velocityY = 0;
	direction = -1;

	facing_left = -1;
	facing_right = 1;

	grounded = true;
	jumping = false;
	onEdge = false;

	walk = NULL;

	setTag(1);

	setupAnimation("walk");

	scheduleUpdate();
}
Enemy01::~Enemy01(void){}


Rect Enemy01::getCollisionBox() {

	Rect bbox = getBoundingBox();

	Rect rect = Rect(
		bbox.getMinX() + velocityX,
		bbox.getMinY() + 1.0f,
		bbox.size.width,
		bbox.size.height);

	return rect;
}
Rect Enemy01::getUpperCollisionBox() {

	Rect bbox = getBoundingBox();

	Rect rect = Rect(
		bbox.getMinX() + bbox.size.width * 0.33f,
		bbox.getMidY(),
		bbox.size.width * 0.4f,
		bbox.size.height * 1.5f);

	return rect;
}

void Enemy01::update(float f) {

	if (getPositionX() + 450.0f > player->getPositionX()
		&& getPositionX() <= player->getPositionX()
		&& getPositionY() + 450.0f > player->getPositionY()
		&& getPositionY() <= player->getPositionY()) {

		direction = 1;

		inRange = true;

		state = isAttack;
	}
	else if (getPositionX() - 450.0f < player->getPositionX()
		&& getPositionX() >= player->getPositionX()
		&& getPositionY() + 450.0f > player->getPositionY()
		&& getPositionY() <= player->getPositionY()) {

		direction = -1;

		inRange = true;

		state = isAttack;
	}
	else {
		inRange = false;
	}

	enemyAI(f);

	enemyCollusion(f);
}

void Enemy01::enemyAI(float f) {

	switch (state) {
	case isAttack:

		velocityX = ENEMY_MAX_VELOCITY * direction;

		if (lastPos == getPositionX() + velocityX && grounded) {
			velocityY = ENEMY_JUMP_VELOCITY;
			grounded = false;
		}

		if (!inRange)
			state = isSleep;

		break;

	case isSleep:
		if (sleepDu < 0) {
			// isSleep 2초 진행
			sleepDu = 2.0f;

			// 탐색 시간 1~3초 설정
			seekDu = rand() % 3 + 1;
			state = isSeek;
		}
		else {
			sleepDu -= f;
		}

		break;
		
	case isSeek:
		if (seekDu < 0) {
			state = isSleep;
		}
		else {

			if (onEdge)
				direction *= -1;

			velocityX = ENEMY_MAX_VELOCITY * direction;

			seekDu -= f;
		}

		break;
	}

	lastPos = getPositionX() + velocityX;

}

void Enemy01::enemyCollusion(float f) {

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

	for (Rect tile : tiles) {

		if (tile.intersectsRect(enemy_rect)) {
			if (velocityY > 0) {
				// 플레이어가 수직으로 이동시
				setPositionY(getPositionY() - velocityY);
			}
			else {

				setPositionY(tile.getMaxY());
				// 플레이어가 수직이동이 없을때 tile의 위에 이동
				grounded = true;
				jumping = false;
			}

			velocityY = 0;
			break;
		}
		grounded = false;
	}

	if(state != isAttack)
		onEdge = level->getCollisionTilesEdge(tmp, direction);
	else
		onEdge = false;


	hazard_collision(tmp);
	updateState(f);
	velocityX = 0;
	velocityY -= GRAVITY;
}

void Enemy01::updateState(float f) {

	if (velocityX < 0) {
		if (walk == NULL || walk->isDone() || direction != facing_left) {
			direction = facing_left;
			walk->startWithTarget(this);
		}
	}

	if (velocityX > 0) {
		if (walk == NULL || walk->isDone() || direction != facing_right) {
			direction = facing_right;
			walk->startWithTarget(this);
		}
	}

	if (velocityX != 0)
		walk->step(f);


	if (direction == facing_right)
		setFlippedX(true);
	else
		setFlippedX(false);


	if (velocityX == 0 && velocityY == 0) {
		
		setTexture("Character/Main/idle.png");
		if (direction == facing_right) {
			setFlippedX(true);
		}
		else {
			setFlippedX(false);
		}
	}
	else if (velocityY > 0 || velocityY < 0) {

		setTexture("Character/Main/onAir.png");
		if (direction == facing_right) {
			setFlippedX(true);
		}
		else {
			setFlippedX(false);
		}
	}

	if (velocityX != 0) {
		setPositionX(getPositionX() + velocityX);
	}

	setPositionY(getPositionY() + velocityY);
}

void Enemy01::hazard_collision(Point tmp) {
	bool isTriggerd = false;

	isTriggerd = level->getCollisionTilesHazardsX(tmp, direction);

	if (!isTriggerd)
		isTriggerd = level->getCollisionTilesHazardsY(tmp, -1);

	if (isTriggerd)
		removeFromParent();
}

void Enemy01::setupAnimation(const char* name) {

	if (walk != NULL) {
		walk->release();
	}

	Animation *aWalk = Animation::create();
	aWalk->setDelayPerUnit(0.2f);
	aWalk->addSpriteFrameWithFile("Character/Main/walk/walk7.png");
	aWalk->addSpriteFrameWithFile("Character/Main/walk/walk6.png");
	aWalk->addSpriteFrameWithFile("Character/Main/walk/walk5.png");
	aWalk->addSpriteFrameWithFile("Character/Main/walk/walk4.png");
	aWalk->addSpriteFrameWithFile("Character/Main/walk/walk3.png");
	aWalk->addSpriteFrameWithFile("Character/Main/walk/walk2.png");
	aWalk->addSpriteFrameWithFile("Character/Main/walk/walk1.png");


	walk = Animate::create(aWalk);
	walk->startWithTarget(this);
	walk->setDuration(0.80f);
	walk->retain();
}