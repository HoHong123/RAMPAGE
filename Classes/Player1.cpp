#include "Player1.h"
#include "defines.h"
#include <string>


Player1 * Player1::create(Level1* levels) {

	Player1* pSprite = new Player1(levels);

	if (pSprite->initWithFile("Character/Pug/pugs/idle.png")) {

		pSprite->setAnchorPoint(Point::ZERO);
		pSprite->getTexture()->setAntiAliasTexParameters();
		pSprite->setScale(SCALE_FACTOR);
		pSprite->player_size = Size(pSprite->getBoundingBox().size.width, pSprite->getBoundingBox().size.height);
		pSprite->setTag(3);

		return pSprite;
	}

	return NULL;
}

Player1::Player1(void)
{
	velocityX = 0;
	velocityY = 0;
	direction = -1;

	facing_left = -1;
	facing_right = 1;

	grounded = true;
	jumping = false;

	walk = NULL;

	setupAnimation("walk");
}
Player1::Player1(Level1* levels)
{
	level = levels;

	velocityX = 0;
	velocityY = 0;
	direction = -1;

	facing_left = -1;
	facing_right = 1;

	grounded = true;
	jumping = false;

	walk = NULL;

	setupAnimation("walk");

	setTag(3);

	schedule(schedule_selector(Player1::player_collusion));

}
Player1::~Player1(void){}


Rect Player1::getCollisionBox() {

	Rect bbox = getBoundingBox();

	Rect rect = Rect(
		bbox.getMinX() + velocityX,
		bbox.getMinY() + 1.0f,
		bbox.size.width,
		bbox.size.height);

	return rect;
}
Rect Player1::getUpperCollisionBox() {

	Rect bbox = getBoundingBox();

	Rect rect = Rect(
		bbox.getMinX() + bbox.size.width * 0.33f,
		bbox.getMidY(),
		bbox.size.width * 0.4f,
		bbox.size.height * 1.5f
	);

	return rect;
}


void Player1::player_collusion(float f) {
	x = getPositionX();
	y = getPositionY();
	// 6
	Rect player_rect = getBoundingBox();

	Point tmp;
	std::vector<Rect> tiles;

	tiles.clear();

	tmp = level->positionToTileCoordinate(Point(getPositionX() + player_size.width * 0.5f,
		getPositionY() + player_size.height * 0.5f));
	// tmp의 x, y가 스프라이트의 중앙으로

	try {

		if (velocityX > 0) {
			tiles = level->getCollisionTilesX(tmp, 1);
		}
		else {
			tiles = level->getCollisionTilesX(tmp, -1);
		}

	}
	catch(int e) {
		removeFromParent();
	}

	player_rect.setRect(
		getBoundingBox().getMinX() + velocityX,
		getBoundingBox().getMinY() + 1.0f, // dont let the rectangle touch the ground otherwise, will count as collision
		player_size.width,
		player_size.height
	);

	for (Rect tile : tiles) {
		if (player_rect.intersectsRect(tile)) {
			velocityX = 0;
			break;
		}
	}

	tiles.clear();

	if (velocityY > 0) {
		tiles = level->getCollisionTilesY(tmp, 1);
	}
	else if (velocityY < 0) {
		tiles = level->getCollisionTilesY(tmp, -1);
	}

	player_rect.setRect(
		getBoundingBox().getMinX(),
		getBoundingBox().getMinY(),
		player_size.width,
		player_size.height
	);

	for (Rect tile : tiles) {
		if (tile.intersectsRect(player_rect)) {
			if (velocityY > 0) {
				// 플레이어가 수직으로 이동시
				setPositionY(getPositionY() - velocityY);

			}
			else {

				setPositionY(tile.getMaxY());
				// 플레이어가 수직이동이 없을때 tile의 위에 플레이어 이동
				grounded = true;
				jumping = false;
			}

			velocityY = 0;
			break;
		}
		grounded = false;
	}

	hazard_collision(tmp);
	updateState(f);
	velocityX = 0;
}

void Player1::updateState(float f) {
	if (direction > 0)
		gun_point = getPosition() + Vec2(getContentSize().width * SCALE_FACTOR, ((getContentSize().height / 3) * 2) * SCALE_FACTOR);
	else
		gun_point = getPosition() + Vec2(0, ((getContentSize().height / 3) * 2) * SCALE_FACTOR);

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

	if (velocityX != 0) {
		walk->step(f);
	}

	if (direction == facing_right) {
		setFlippedX(true);
	}
	else {
		setFlippedX(false);
	}

	if (velocityX == 0 && velocityY == 0) {

		setTexture("Character/Pug/pugs/idle.png");
		if (direction == facing_right) {
			setFlippedX(true);
		}
		else {
			setFlippedX(false);
		}
	}
	else if (velocityY > 0 || velocityY < 0) {

		setTexture("Character/Pug/pugs/jump.png");
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


void Player1::hazard_collision(Point tmp) {
	bool isTriggerd = false;

	isTriggerd = level->getCollisionTilesHazardsX(tmp, direction);

	if (!isTriggerd)
		isTriggerd = level->getCollisionTilesHazardsY(tmp, -1);

	if (isTriggerd)
		removeFromParent();
}

void Player1::setupAnimation(const char* name) {

	if (walk != NULL) {
		walk->release();
	}

	Animation *aWalk = Animation::create();
	aWalk->setDelayPerUnit(0.3f);
	aWalk->addSpriteFrameWithFile("Character/Pug/pugs/walk1.png");
	aWalk->addSpriteFrameWithFile("Character/Pug/pugs/walk2.png");
	aWalk->addSpriteFrameWithFile("Character/Pug/pugs/walk3.png");
	aWalk->addSpriteFrameWithFile("Character/Pug/pugs/walk4.png");


	walk = Animate::create(aWalk);
	walk->startWithTarget(this);
	walk->setDuration(0.80f);
	walk->retain();
}