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
	
	pHealth = health; // ü��
	isInvincible = false; // ���� ����

	this->player = player;
	
	// �� �浹 ������ ���� ������Ʈ�� �ִ� ����Ʈ ����
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
	CCArray* bulletsToDelete = CCArray::create(); // �浹�� �������ϴ� ��� ������Ʈ�� ���� ����Ʈ
	bulletsToDelete->retain();

	CCObject* bulletP;
	CCObject* bulletE;
	CCObject* enemyO;
	CCObject* bt;

	Rect playerRect = player->getBoundingBox();

	// �����ð� �ʱ�ȭ
	// �÷��̾ ����Ǵ� �׼��� ���� ���� �����̸� ���� �ʱ�ȭ
	if (player->getNumberOfRunningActions() <= 0 && isInvincible)
		setInvincibility();

	// �浹 Ȯ��
	if (eBullet->begin() != NULL && !isInvincible) { // �� �Ѿ��� �����ϰ�, ������ �ƴϸ� ����
		CCARRAY_FOREACH(eBullet, bulletE) {
			Sprite* bullet = (Sprite*)bulletE;

			if (!bullet->isVisible())
			{
				continue;
			}
			// �� �Ѿ��� �÷��̾�� ������
			if (bullet->getBoundingBox().intersectsRect(playerRect))
			{
				// ü���� �����ϰ� ������ �ƴ� ���¸� ����
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

	// ���� �����ϸ� ����
	if (Enemy->begin() != NULL) {
		CCARRAY_FOREACH(Enemy, enemyO) {
			Sprite* enemyC = (Sprite*)enemyO;
			Rect enemyRect = enemyC->getBoundingBox();

			if (!enemyC->isVisible()) {
				continue;
			}

			// ���� �÷��̾�� �浹�ϸ� ����
			if (enemyRect.intersectsRect(playerRect)) {
				if (pHealth > 0 && !isInvincible) { // ������ �ƴϰ� ü���� 0�̻��̸� ����

					// �ǰ� ���� ����
					AudioProfile effect;
					effect.name = "phit";
					effect.maxInstances = 1000;

					sounds[1] = AudioEngine::play2d("Sounds/effect/player_gethit.ogg", false, EVOLUM, &effect);

					// ���� ����
					isInvincible = true;
					pHealth -= 1; // ü�� 1 ����

					// �����̴� ȿ�� ����
					Blink *blink = Blink::create(1.0f, 10); // 1�ʰ� 10���� ������

					player->runAction(blink); // �÷��̾� �����̱� ����
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

	// ����
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