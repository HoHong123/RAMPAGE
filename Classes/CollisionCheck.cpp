#include "CollisionCheck.h"


extern int sounds[];
extern float VOLUM;
extern float EVOLUM;

Collision::Collision(){
	pBullet = CCArray::create();
	pBullet->retain();
	eBullet = CCArray::create();
	eBullet->retain();
	Enemy = CCArray::create();
	Enemy->retain();
}
Collision::Collision(Sprite *player) {

	pHealth = 3;
	isInvincible = false;

	this->player = player;

	pBullet = CCArray::create();
	pBullet->retain();
	eBullet = CCArray::create();
	eBullet->retain();
	Enemy = CCArray::create();
	Enemy->retain();
}
Collision::Collision(Sprite *player, int health) {
	
	pHealth = health; // 체력
	isInvincible = false; // 무적 판정

	this->player = player;
	
	// 각 충돌 판정을 받을 오브젝트를 넣는 리스트 생성
	pBullet = CCArray::create();
	pBullet->retain();
	eBullet = CCArray::create();
	eBullet->retain();
	Enemy = CCArray::create();
	Enemy->retain();
}
Collision::~Collision(){
	pBullet->release();
	pBullet = NULL;
	eBullet->release();
	eBullet = NULL;
	Enemy->release();
	Enemy = NULL;
}

void Collision::addPlayerB(Sprite* bullet) {
	pBullet->addObject(bullet);
}
void Collision::addEnemyB(Sprite* bullet) {
	eBullet->addObject(bullet);
}
void Collision::addEnemy(Sprite* enemy) {
	Enemy->addObject(enemy);
}

CCArray *Collision::getEBullet() {
	return eBullet;
}

void Collision::collisionDetection() {
	CCArray* bulletsToDelete = CCArray::create(); // 충돌후 지워야하는 모든 오브젝트를 담을 리스트
	bulletsToDelete->retain();

	CCObject* bulletP;
	CCObject* bulletE;
	CCObject* enemyO;
	CCObject* bt;

	Rect playerRect = player->getBoundingBox();

	// 무적시간 초기화
	// 플레이어에 실행되는 액션이 없고 무적 상태이면 무적 초기화
	if (player->getNumberOfRunningActions() <= 0 && isInvincible)
		setInvincibility();

	// 충돌 확인
	if (eBullet->begin() != NULL && !isInvincible) { // 적 총알이 존재하고, 무적이 아니면 실행
		CCARRAY_FOREACH(eBullet, bulletE) {
			Sprite* bullet = (Sprite*)bulletE;

			if (!bullet->isVisible())
			{
				continue;
			}
			// 적 총알이 플레이어와 만나면
			if (bullet->getBoundingBox().intersectsRect(playerRect))
			{
				// 체력이 존재하고 무적이 아닌 상태면 실행
				if (pHealth > 0 && !isInvincible) {
					isInvincible = true;
					pHealth -= 1;

					Blink *blink = Blink::create(PLAYER_INVINCIBILITY_DURATION, 10);

					player->runAction(blink);
				}
				else if (pHealth <= 0)
					player->removeFromParent();
			}
		}
	}

	// 적이 존재하면 실행
	if (Enemy->begin() != NULL) {
		CCARRAY_FOREACH(Enemy, enemyO) {
			Sprite* enemyC = (Sprite*)enemyO;
			Rect enemyRect = enemyC->getBoundingBox();

			if (!enemyC->isVisible()) {
				continue;
			}

			// 적이 플레이어와 충돌하면 실행
			if (enemyRect.intersectsRect(playerRect)) {
				if (pHealth > 0 && !isInvincible) { // 무적이 아니고 체력이 0이상이면 실행

					// 피격 사운드 실행
					AudioProfile effect;
					effect.name = "phit";
					effect.maxInstances = 1000;

					sounds[1] = AudioEngine::play2d("Sounds/effect/player_gethit.ogg", false, EVOLUM, &effect);

					// 무적 적용
					isInvincible = true;
					pHealth -= 1; // 체력 1 감소

					// 깜빡이는 효과 적용
					Blink *blink = Blink::create(1.0f, 10); // 1초간 10번을 깜빡임

					player->runAction(blink); // 플레이어 깜빡이기 실행
				}
				else if (pHealth <= 0)
					player->removeFromParent();
			}

			if (pBullet != NULL) {
				CCARRAY_FOREACH(pBullet, bulletP) {
					Sprite* bullet = (Sprite*)bulletP;

					if (!bullet->isVisible())
					{
						continue;
					}
					if (bullet->getBoundingBox().intersectsRect(enemyRect))
					{
						bulletsToDelete->addObject(bullet);
						bulletsToDelete->addObject(enemyC);
						bullet->setVisible(false);
						enemyC->setVisible(false);
					}
				}
			}
		}
	}

	// 삭제
	CCARRAY_FOREACH(bulletsToDelete, bt)
	{
		Sprite* list = (Sprite*)bt;
		this->removeChild(list, true);
		list->release();
		bulletsToDelete->removeObject(list);
	}
	bulletsToDelete->removeAllObjects();

	bulletsToDelete->release();
}


void Collision::setInvincibility() {
	isInvincible = (isInvincible) ? false : true;
}
void Collision::addHealth(int heal) {
	pHealth += heal;
}
void Collision::dmgHealth(int dmg) {
	pHealth -= dmg;
}