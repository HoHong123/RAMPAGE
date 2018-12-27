#include "Stage1.h"

USING_NS_CC;


extern int sounds[]; // 모든 음악 ID리스트
extern float VOLUM; // 배경음 볼륨
extern float EVOLUM; // 이펙트 볼륨

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
	//게임 오버씬 호출 함수
	//0.3초의 Fade가 발생하는 전환함수 호출
	Scene *gameover = TransitionCrossFade::create(1.2f, GameOver::createScene(1));
	//Director::sharedDirector()->pause();

	Director::getInstance()->pushScene(gameover);
}
void Stage1::Option(Ref *pSender) {
	// 옵션씬 준비
	Scene* option = Option::createScene();

	Director::sharedDirector()->pushScene(option);
}

Stage1::Stage1() {
	setKeyboardEnabled(true); // 키리스너 활성화
}
Stage1::~Stage1() {
	player->release(); // 종료시 플레이어를 메모리에서 제거
	camera->release(); // 카메라를 메모리에서 제거
	level->release(); // 레벨을 메모리에서 제거
	collision->release(); // 충돌객체를 메모리에서 제거
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

	// 샷건의 발사 속도 제한
	shotgunRate = 0.5f; // 0.5초마다 발사 가능
	fireRate = true; // 발사의 유/무 선정

	////////////////////////////////////

	AudioEngine::stopAll(); // 이미 시작되고 있는 음악 모두 취소

	// 새로운 배경음악 삽입
	AudioProfile bgm;
	bgm.name = "BG";
	bgm.maxInstances = 1000;

	sounds[0] = AudioEngine::play2d("Sounds/bgm/Battle Theme.mp3", true, VOLUM, &bgm);
	
	//////////////////////////////////////////

	// 맵 
	level = new Level1(); // 새 맵 생성
	level->loadMap("level1.tmx"); // tmx파일을 불러옴
	level->retain(); // level을 메모리에 할당
	level->getMap()->setScale(SCALE_FACTOR); // level1.tmx의 크기를 선언

	this->addChild(level->getMap()); // level1.tmx 할당

	/////////////////

	//플레이어
	player = Player1::create(level); // 플레이어 새 객체 생성 및 플레이어가 읽을 맵 포인터 전달
	player->retain(); // 메모리에 상주
	player->setPosition(level->tileCoordinateToPosition(Point(10, 4))); // 최초 맵의 10,4포인터에 플레이어를 위치

	this->addChild(player); // 플레이어를 씬에 생성

	///////////////////////////////////////////
	// 카메라 목표
	cameraTarget = Sprite::create(); // 카메라 객체 생성
	cameraTarget->setPositionX(player->getPosition().x); // 캐릭터의 x좌표 선언
	cameraTarget->setPositionY(player->getPosition().y); // 가운데 선언

	cameraTarget->retain(); // 카메라 타겟 메모리 할당

	cameraSpeed = 0.1f; // 0.1f의 속도로 카메라를 따라감
	cameraOffset = player->getContentSize().width * 8; // 플레이어 크기의 8배만큼 플레이어가 바라보는 방향의 전방에 위치하려함

	this->addChild(cameraTarget);
	////////////////////////////////////////////
	// 카메라
	camera = Follow::create(cameraTarget, Rect::ZERO); // 카메라 목표를 지속적으로 따라감
	camera->retain(); // 카메라를 메모리에 상주

	this->runAction(camera);
	////////////////////////////////////////////
	// 배경
	// BackGround라는 함수를 직접 제작하여 패럴랙스 배경 시스템을 제작하였습니다.
	// 각 인자별로 소개하겠습니다.
	// 1 : 패럴랙스 배경이 따라다니는 목표
	// 2 : 패럴랙스 배경이 가지는 파일
	// 3 : 패럴랙스 배경의 최초 Y축위치
	// 4 : 패럴랙스 배경이 목표를 따라가는 속도

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
	// 텍스트 삽입
	// 인자별 설명
	// 1 : TILED프로그램에서 지정한 위치 중 Movement라는 객체 위치를 읽음
	// 2 : 다음 택스트를 생성하고 붙임

	addText("Movement", "Press\n\"LEFT ARROW\" and \"RIGHT ARROW\"\nto MOVE");
	addText("Jump", "Press \"SPACE\"\nto JUMP");
	addText("Shoot", "Press \"Z\"\nto SHOOT");

	////////////////////////////////////////////
	// 충돌 체크
	// 인자별 설명
	// 1 : 플레이어 스프라이트
	// 2 : 플레이어의 체력
	collision = new Collision(player, 4);

	////////////////////////////////////////////
	// 소환
	// TILED에서 선정한 Spawn이란 오브젝트에 속한 하위 객체들의 위치를 읽어 해당 위치에 몬스터를 소환
	addMonster("Spawn1");
	addMonster("Spawn2");
	addMonster("Spawn2");
	addMonster("Spawn3");
	addMonster("Spawn3");

	// 위와 동일하며 fly몬스터를 소환
	addFly("fly1");
	addFly("fly2");
	addFly("fly3");
	addFly("fly4");

	/////////////////////////////////////////////

	count = 0;
	duration = 0.0f;
	spawn = false;

	// 부딛히면 몬스터를 소환하는 객체 생성
	raidPoint = Sprite::create();
	raidPoint->setContentSize(Size(2.0f, 50.f));
	raidPoint->setTag(9);

	// 타일 오브젝트 중 Start라는 명칭의 오브젝트를 가져옴
	CCTMXObjectGroup *objectGroup = level->getMap()->objectGroupNamed("Start");
	// 해당 오브젝트의 startSpawn1이라는 오브젝트의 위치를 받음
	ValueMap spawnPoint = objectGroup->getObject("startSpawn1");

	// 해당 위치를 저장
	float x = spawnPoint["x"].asInt() * SCALE_FACTOR;
	float y = spawnPoint["y"].asInt() * SCALE_FACTOR;

	// 해당 위치를 raidPoint에 선언
	raidPoint->setPosition(Vec2(x, y));
	this->addChild(raidPoint);

	//////////////////////////////////////////////

	// 업데이트문 실행
	this->scheduleUpdate();

	return true;
}


void Stage1::update(float f) {

	// 플레이어가 존재하는 태그가 NULL이 아니면 실행
	if (getChildByTag(3) != NULL) { // 플레이어가 존재하면 실행

		if (shotgunRate <= 0) { // 총의 재장전 시간이 0초가 되면
			shotgunRate = 0.5f; // 재장전시간 0.5초 다시 선언
			fireRate = true; // 총알 발사를 가능하게 선언
		}

		if (!fireRate) // 총알 발사가 불가능하면
			shotgunRate -= f; // 총알 재장전시간이 감소

		float playerX = player->getPositionX();
		float cameraX = cameraTarget->getPositionX();
		float playerY = player->getPositionY();
		float cameraY = cameraTarget->getPositionY();

		// 카메라가 맵의 밖으로 이동하는 것을 방지하는 선언들 
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

		// 충돌 체크 실행
		collision->collisionDetection();

		// 키를 받는 함수
		getKeys();

		// 소환 장소가 존재하면 실행
		if (getChildByTag(9) != NULL && !spawn) {
			// 소환장소가 플레이어와 충돌하면 실행
			if (raidPoint->getBoundingBox().intersectsRect(player->getBoundingBox())) {
				
				//몬스터 소환 가능
				spawn = true;
				count = 5;

				// 공중 몬스터 소환
				addFly("fly5");
				addFly("fly6");

				// 소환장소는 중복 충돌을 방지하기 위해 제거
				this->removeChild(raidPoint, true);
				raidPoint->release();
			}
		}
		
		if (spawn) {
			// 스폰이 true이면 실행
			if (count > 0) {
				// 해당 숫자만큼 몬스터를 소환
				if (duration <= 0) {
					// 소환의 간격이 0초가 되면 소환
					duration = 1.0f; // 소환간격을 1초로 초기화

					count--; // 소환 횟수 감소
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
		// 스페이스 바를 눌렀을때
		if (player->grounded && player->velocityY <= 0) {
			// 플레이어가 grounded상태이며 Y축 가속도가 0이하(땅과 충돌)일때

			player->velocityY = PLAYER_JUMP_VELOCITY;
			player->jumping = true;
			player->grounded = false;
		}
	}

	if (std::find(heldKeys.begin(), heldKeys.end(), RIGHT_ARROW) != heldKeys.end()) {
		// 우측키를 눌렀을때

		player->velocityX = PLAYER_MAX_VELOCITY; // x축의 우측으로 플레이어 이동
		cameraOffset = abs(cameraOffset); // 카메라는 항상 플레이어의 위치보다 8배의 위치에 있어야하기에 매 플레이어 위치에서 다시 연산

		player->facing_right = true;

	}

	if (std::find(heldKeys.begin(), heldKeys.end(), LEFT_ARROW) != heldKeys.end()) {
		// 좌측키를 눌렀을때

		player->velocityX = -PLAYER_MAX_VELOCITY; // x축의 좌측으로 플레이어 이동
		cameraOffset = abs(cameraOffset) * -1; // 위와 동일

		player->facing_right = false;

	}

	player->velocityY -= GRAVITY; // 플레이어의 중력 구현
}

//Listener
void Stage1::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == ATTACK && fireRate) // z키가 눌리면 총알 생성
		addBullet();
	else if (keyCode == RESET) // r키가 눌리면 재시작
		restart(this);
	else if (keyCode == ESC) // esc키가 눌리면 옵션씬 호출
		Option(this);
	else if (std::find(heldKeys.begin(), heldKeys.end(), keyCode) == heldKeys.end()) // 받은 키를 읽어서 매번 해당 동작을 실행
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
	Text->setColor(Color3B(255, 0, 150)); // 색상 흰색 설정
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