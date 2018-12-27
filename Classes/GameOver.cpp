#include "GameOver.h"

USING_NS_CC;


extern int sounds[];
extern float VOLUM;
extern float EVOLUM;

Scene* GameOver::createScene(int sceneNum) {

	GameOver* pScene = new GameOver(sceneNum);

	if (pScene != NULL) {
		return pScene;
	}
	
	return NULL;
}

GameOver::GameOver() {}
GameOver::GameOver(int sceneNum) {
	experimental::AudioEngine::stopAll();

	last = 10; // ī��Ʈ �ٿ�
	num = sceneNum; // �ٽ� �Ѿ ����ȣ

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(GameOver::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	// �ʱ� 10�� �ؽ�Ʈ
	count = LabelTTF::create("10", "fonts/invasion2000.ttf", 80);
	count->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.85f));

	press = LabelTTF::create("Press \"R\" to Start", "fonts/invasion2000.ttf", 80);
	press->setPosition(Vec2(visibleSize.width * 0.5f, visibleSize.height * 0.7f));

	this->addChild(press);
	this->addChild(count);


	// ȣ���� ���� �ִϸ��̼�
	Sprite* pSprite = Sprite::create();
	pSprite->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.4f));

	Animation *over = Animation::create();
	over->setDelayPerUnit(0.8f);
	over->addSpriteFrameWithFileName("Character/Pug/gameover1.png");
	over->addSpriteFrameWithFileName("Character/Pug/gameover2.png");
	over->setLoops(-1);

	pug = Animate::create(over);

	pSprite->runAction(pug);
	pSprite->setScale(2.0f);
	this->addChild(pSprite);

	time = 10;

	schedule(schedule_selector(GameOver::Timer), 0.01); // Ÿ�̸Ӹ� 0.01�� �ڿ� ����
	Sleep(1.0f);
}
GameOver::~GameOver(){
	press->release();
	count->release();
	pug->release();
}

void GameOver::startScene(cocos2d::Ref *pSender) {
	Scene *scene1 = TransitionCrossFade::create(0.8f, Scene1::createScene());
	// ���� ������ ��ȯ�� �ٽ� ����� ���
	AudioEngine::stopAll();

	AudioProfile bgm;
	bgm.name = "Guilty";
	bgm.maxInstances = 1000;

	sounds[0] = AudioEngine::play2d("Sounds/bgm/Guilty.mp3", true, VOLUM, &bgm);

	Director::getInstance()->replaceScene(scene1);
}
void GameOver::stage1(cocos2d::Ref *pSender) {
	Scene *stage1 = TransitionCrossFade::create(0.3f, Stage1::createScene());

	Director::getInstance()->replaceScene(stage1);
}

void GameOver::Timer(float dt) {
	if (time <= 0) { // �ð��� 0�� ���� ������ ����
		startScene(this);
	}

	// ������ �ð��� time���� ũ�� 1�ʰ� �����ٴ� �ǹ�
	if (last > (int)time) {

		// �Ҹ� ���
		AudioProfile effect;
		effect.name = "phit";
		effect.maxInstances = 1000;

		sounds[9] = AudioEngine::play2d("Sounds/effect/beep.mp3", false, EVOLUM, &effect);

		// �ؽ�Ʈ ����
		__String* displayTime = __String::createWithFormat("%.0f", time);
		count->setString(displayTime->getCString());
		
		last = (int)time;
	}

	time -= dt;
}


void GameOver::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == RESET)
	{
		switch (num) {
		case 1:
			stage1(this);
			break;
		case 2:
			//bossScene(this);
			break;
		}
	}
}