#include "Stage1.h"

USING_NS_CC;


extern int sounds[]; // ��� ���� ID����Ʈ
extern float VOLUM; // ����� ����
extern float EVOLUM; // ����Ʈ ����

Scene* Stage1::createScene() {

	auto scene = Scene::create();

	Stage1 *layer = new Stage1();
	layer = Stage1::create();

	scene->addChild(layer);

	return scene;
}
void Stage1::restart(Ref *pSender) {
	Scene *stage1 = Stage1::createScene();

	Director::getInstance()->replaceScene(stage1);
}
void Stage1::gameover(cocos2d::Ref *pSender) {
	//���� ������ ȣ�� �Լ�
	//0.3���� Fade�� �߻��ϴ� ��ȯ�Լ� ȣ��
	Scene *gameover = TransitionCrossFade::create(1.2f, GameOver::createScene(1));
	//Director::sharedDirector()->pause();

	Director::getInstance()->pushScene(gameover);
}
void Stage1::Option(Ref *pSender) {
	// �ɼǾ� �غ�
	Scene* option = Option::createScene();

	Director::sharedDirector()->pushScene(option);
}

Stage1::Stage1() {
	setKeyboardEnabled(true); // Ű������ Ȱ��ȭ
}
Stage1::~Stage1() {
	player->release(); // ����� �÷��̾ �޸𸮿��� ����
	camera->release(); // ī�޶� �޸𸮿��� ����
	level->release(); // ������ �޸𸮿��� ����
	collision->release(); // �浹��ü�� �޸𸮿��� ����
}

void Stage1::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	return;
#endif

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}


bool Stage1::init() {

	if (!Layer::init()) {
		return false;
	}

	// ������ �߻� �ӵ� ����
	shotgunRate = 0.5f; // 0.5�ʸ��� �߻� ����
	fireRate = true; // �߻��� ��/�� ����

	////////////////////////////////////

	AudioEngine::stopAll(); // �̹� ���۵ǰ� �ִ� ���� ��� ���

	// ���ο� ������� ����
	AudioProfile bgm;
	bgm.name = "BG";
	bgm.maxInstances = 1000;

	sounds[0] = AudioEngine::play2d("Sounds/bgm/Battle Theme.mp3", true, VOLUM, &bgm);
	
	//////////////////////////////////////////

	// �� 
	level = new Level1(); // �� �� ����
	level->loadMap("level1.tmx"); // tmx������ �ҷ���
	level->retain(); // level�� �޸𸮿� �Ҵ�
	level->getMap()->setScale(SCALE_FACTOR); // level1.tmx�� ũ�⸦ ����

	this->addChild(level->getMap()); // level1.tmx �Ҵ�

	/////////////////

	//�÷��̾�
	player = Player1::create(level); // �÷��̾� �� ��ü ���� �� �÷��̾ ���� �� ������ ����
	player->retain(); // �޸𸮿� ����
	player->setPosition(level->tileCoordinateToPosition(Point(10, 4))); // ���� ���� 10,4�����Ϳ� �÷��̾ ��ġ

	this->addChild(player); // �÷��̾ ���� ����

	///////////////////////////////////////////
	// ī�޶� ��ǥ
	cameraTarget = Sprite::create(); // ī�޶� ��ü ����
	cameraTarget->setPositionX(player->getPosition().x); // ĳ������ x��ǥ ����
	cameraTarget->setPositionY(player->getPosition().y); // ��� ����

	cameraTarget->retain(); // ī�޶� Ÿ�� �޸� �Ҵ�

	cameraSpeed = 0.1f; // 0.1f�� �ӵ��� ī�޶� ����
	cameraOffset = player->getContentSize().width * 8; // �÷��̾� ũ���� 8�踸ŭ �÷��̾ �ٶ󺸴� ������ ���濡 ��ġ�Ϸ���

	this->addChild(cameraTarget);
	////////////////////////////////////////////
	// ī�޶�
	camera = Follow::create(cameraTarget, Rect::ZERO); // ī�޶� ��ǥ�� ���������� ����
	camera->retain(); // ī�޶� �޸𸮿� ����

	this->runAction(camera);
	////////////////////////////////////////////
	// ���
	// BackGround��� �Լ��� ���� �����Ͽ� �з����� ��� �ý����� �����Ͽ����ϴ�.
	// �� ���ں��� �Ұ��ϰڽ��ϴ�.
	// 1 : �з����� ����� ����ٴϴ� ��ǥ
	// 2 : �з����� ����� ������ ����
	// 3 : �з����� ����� ���� Y����ġ
	// 4 : �з����� ����� ��ǥ�� ���󰡴� �ӵ�

	BackGround *BG0 = BackGround::create(cameraTarget, "BackGround/Industrial_layer/1.png",
		visibleSize.height * 0.3f, 0.4f);
	this->addChild(BG0, -1);

	BackGround *BG1 = BackGround::create(cameraTarget, "BackGround/Industrial_layer/2.png",
		visibleSize.height * 0.5f, 0.1f);
	this->addChild(BG1, -2);

	BackGround *BG2 = BackGround::create(cameraTarget, "BackGround/Industrial_layer/3.png",
		visibleSize.height * 0.7f, -0.2f);
	this->addChild(BG2, -3);

	BackGround *BG3 = BackGround::create(cameraTarget, "BackGround/Industrial_layer/4.png",
		visibleSize.height * 0.9f, 0.2f);
	this->addChild(BG3, -4);

	////////////////////////////////////////////
	// �ؽ�Ʈ ����
	// ���ں� ����
	// 1 : TILED���α׷����� ������ ��ġ �� Movement��� ��ü ��ġ�� ����
	// 2 : ���� �ý�Ʈ�� �����ϰ� ����

	addText("Movement", "Press\n\"LEFT ARROW\" and \"RIGHT ARROW\"\nto MOVE");
	addText("Jump", "Press \"SPACE\"\nto JUMP");
	addText("Shoot", "Press \"Z\"\nto SHOOT");

	////////////////////////////////////////////
	// �浹 üũ
	// ���ں� ����
	// 1 : �÷��̾� ��������Ʈ
	// 2 : �÷��̾��� ü��
	collision = new Collision(player, 4);

	////////////////////////////////////////////
	// ��ȯ
	// TILED���� ������ Spawn�̶� ������Ʈ�� ���� ���� ��ü���� ��ġ�� �о� �ش� ��ġ�� ���͸� ��ȯ
	addMonster("Spawn1");
	addMonster("Spawn2");
	addMonster("Spawn2");
	addMonster("Spawn3");
	addMonster("Spawn3");

	// ���� �����ϸ� fly���͸� ��ȯ
	addFly("fly1");
	addFly("fly2");
	addFly("fly3");
	addFly("fly4");

	/////////////////////////////////////////////

	count = 0;
	duration = 0.0f;
	spawn = false;

	// �ε����� ���͸� ��ȯ�ϴ� ��ü ����
	raidPoint = Sprite::create();
	raidPoint->setContentSize(Size(2.0f, 50.f));
	raidPoint->setTag(9);

	// Ÿ�� ������Ʈ �� Start��� ��Ī�� ������Ʈ�� ������
	CCTMXObjectGroup *objectGroup = level->getMap()->objectGroupNamed("Start");
	// �ش� ������Ʈ�� startSpawn1�̶�� ������Ʈ�� ��ġ�� ����
	ValueMap spawnPoint = objectGroup->getObject("startSpawn1");

	// �ش� ��ġ�� ����
	float x = spawnPoint["x"].asInt() * SCALE_FACTOR;
	float y = spawnPoint["y"].asInt() * SCALE_FACTOR;

	// �ش� ��ġ�� raidPoint�� ����
	raidPoint->setPosition(Vec2(x, y));
	this->addChild(raidPoint);

	//////////////////////////////////////////////

	// ������Ʈ�� ����
	this->scheduleUpdate();

	return true;
}


void Stage1::update(float f) {

	// �÷��̾ �����ϴ� �±װ� NULL�� �ƴϸ� ����
	if (getChildByTag(3) != NULL) { // �÷��̾ �����ϸ� ����

		if (shotgunRate <= 0) { // ���� ������ �ð��� 0�ʰ� �Ǹ�
			shotgunRate = 0.5f; // �������ð� 0.5�� �ٽ� ����
			fireRate = true; // �Ѿ� �߻縦 �����ϰ� ����
		}

		if (!fireRate) // �Ѿ� �߻簡 �Ұ����ϸ�
			shotgunRate -= f; // �Ѿ� �������ð��� ����

		float playerX = player->getPositionX();
		float cameraX = cameraTarget->getPositionX();
		float playerY = player->getPositionY();
		float cameraY = cameraTarget->getPositionY();

		// ī�޶� ���� ������ �̵��ϴ� ���� �����ϴ� ����� 
		if (player->getPositionX() < 700.0f) 
			cameraTarget->setPositionX(cameraTarget->getPositionX());
		else if (player->getPositionX() > 10420.0f)
			cameraTarget->setPositionX(cameraTarget->getPositionX());
		else
			cameraTarget->setPositionX(((playerX + cameraOffset) - cameraX)	* cameraSpeed + cameraX);

		if (player->getPositionY() < visibleSize.height/2) {
			cameraTarget->setPositionY(visibleSize.height / 2);
		} else if(player->getPositionY() > 665.0f){
			cameraTarget->setPositionY(cameraTarget->getPositionY());
		}
		else {
			cameraTarget->setPositionY((playerY - cameraY)	* 0.6f + cameraY);
		}

		// �浹 üũ ����
		collision->collisionDetection();

		// Ű�� �޴� �Լ�
		getKeys();

		// ��ȯ ��Ұ� �����ϸ� ����
		if (getChildByTag(9) != NULL && !spawn) {
			// ��ȯ��Ұ� �÷��̾�� �浹�ϸ� ����
			if (raidPoint->getBoundingBox().intersectsRect(player->getBoundingBox())) {
				
				//���� ��ȯ ����
				spawn = true;
				count = 5;

				// ���� ���� ��ȯ
				addFly("fly5");
				addFly("fly6");

				// ��ȯ��Ҵ� �ߺ� �浹�� �����ϱ� ���� ����
				this->removeChild(raidPoint, true);
				raidPoint->release();
			}
		}
		
		if (spawn) {
			// ������ true�̸� ����
			if (count > 0) {
				// �ش� ���ڸ�ŭ ���͸� ��ȯ
				if (duration <= 0) {
					// ��ȯ�� ������ 0�ʰ� �Ǹ� ��ȯ
					duration = 1.0f; // ��ȯ������ 1�ʷ� �ʱ�ȭ

					count--; // ��ȯ Ƚ�� ����
					addMonster("Spawn4");
					addMonster("Spawn5");
				}
				duration -= f;
			}
			else {
				spawn = false;
			}
		}
	}
	else {

		AudioEngine::stopAll();

		Stage1::gameover(this);
	}
}

void Stage1::getKeys() {

	if (std::find(heldKeys.begin(), heldKeys.end(), SPACEBAR) != heldKeys.end()) {
		// �����̽� �ٸ� ��������
		if (player->grounded && player->velocityY <= 0) {
			// �÷��̾ grounded�����̸� Y�� ���ӵ��� 0����(���� �浹)�϶�

			player->velocityY = PLAYER_JUMP_VELOCITY;
			player->jumping = true;
			player->grounded = false;
		}
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), RIGHT_ARROW) != heldKeys.end()) {
		// ����Ű�� ��������

		player->velocityX = PLAYER_MAX_VELOCITY; // x���� �������� �÷��̾� �̵�
		cameraOffset = abs(cameraOffset); // ī�޶�� �׻� �÷��̾��� ��ġ���� 8���� ��ġ�� �־���ϱ⿡ �� �÷��̾� ��ġ���� �ٽ� ����

		player->facing_right = true;

	}

	if (std::find(heldKeys.begin(), heldKeys.end(), LEFT_ARROW) != heldKeys.end()) {
		// ����Ű�� ��������

		player->velocityX = -PLAYER_MAX_VELOCITY; // x���� �������� �÷��̾� �̵�
		cameraOffset = abs(cameraOffset) * -1; // ���� ����

		player->facing_right = false;

	}

	player->velocityY -= GRAVITY; // �÷��̾��� �߷� ����
}

//Listener
void Stage1::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == ATTACK && fireRate) // zŰ�� ������ �Ѿ� ����
		addBullet();
	else if (keyCode == RESET) // rŰ�� ������ �����
		restart(this);
	else if (keyCode == ESC) // escŰ�� ������ �ɼǾ� ȣ��
		Option(this);
	else if (std::find(heldKeys.begin(), heldKeys.end(), keyCode) == heldKeys.end()) // ���� Ű�� �о �Ź� �ش� ������ ����
		heldKeys.push_back(keyCode);
}
void Stage1::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	heldKeys.erase(std::remove(heldKeys.begin(), heldKeys.end(), keyCode), heldKeys.end());
}


//Add
void Stage1::addBullet() {

	fireRate = false;

	Bullet *bullet = Bullet::create(player->gun_point, player->direction);
	collision->addPlayerB(bullet);

	this->addChild(bullet);

	AudioProfile effect;
	effect.name = "bullet";
	effect.maxInstances = 1000;

	sounds[2] = AudioEngine::play2d("Sounds/effect/gun-gunshot-01.mp3", false, EVOLUM, &effect);
}
void Stage1::addText(string name, string text) {
	LabelTTF *Text = LabelTTF::create(text, "fonts/invasion2000.ttf", 20);
	Text->setColor(Color3B(255, 0, 150)); // ���� ��� ����
	Text->retain();

	TMXObjectGroup *objectGroup = level->getMap()->objectGroupNamed("Texts");

	ValueMap spawnPoint = objectGroup->getObject(name);

	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();
	x *= SCALE_FACTOR;
	y *= SCALE_FACTOR;

	Text->setPosition(Vec2(x, y));

	this->addChild(Text);
	Text->autorelease();
}

void Stage1::addMonster(string name, int num, float turn) {

	int count = num;

	while (count > 0) {

		Enemy01 *enemy = Enemy01::create(level, player);

		TMXObjectGroup *objectGroup = level->getMap()->objectGroupNamed("Spawn");

		ValueMap spawnPoint = objectGroup->getObject(name);

		int x = spawnPoint["x"].asInt();
		int y = spawnPoint["y"].asInt();
		x *= SCALE_FACTOR;
		y *= SCALE_FACTOR;

		enemy->setScale(SCALE_FACTOR);
		enemy->setPosition(Vec2(x, y));

		this->addChild(enemy);

		collision->addEnemy(enemy);

		--count;
	}
}
void Stage1::addFly(string name, int num, float turn) {

	Enemy02 *enemy = Enemy02::create(level, player, collision);

	TMXObjectGroup *objectGroup = level->getMap()->objectGroupNamed("Fly");

	ValueMap spawnPoint = objectGroup->getObject(name);

	int x = spawnPoint["x"].asInt();
	int y = spawnPoint["y"].asInt();
	x *= SCALE_FACTOR;
	y *= SCALE_FACTOR;

	enemy->setScale(SCALE_FACTOR);
	enemy->setPosition(Vec2(x, y));

	this->addChild(enemy);
	enemy->setMove();

	collision->addEnemy(enemy);

}