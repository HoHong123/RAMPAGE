#include "HelloWorldScene.h"
#include "Scene1.h"
#include "audio/include/AudioEngine.h"

USING_NS_CC;



float VOLUM;
float EVOLUM;
int sounds[10];

Scene* HelloWorld::createScene()
{
	Director::getInstance()->getOpenGLView()->setFrameSize(980, 840);
	Director::getInstance()->getOpenGLView()->setDesignResolutionSize(980, 840, ResolutionPolicy::FIXED_WIDTH);

    return HelloWorld::create();
}

void HelloWorld::startScene(cocos2d::Ref *pSender) {
	Scene *scene1 = TransitionCrossFade::create(0.5f, Scene1::createScene());
	// 0.5���� ���̵� ȿ���� ������ ���� ������ ��ȯ

	Director::getInstance()->replaceScene(scene1);
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }


	// Ű������ ����
	auto dispatcher = Director::sharedDirector()->getEventDispatcher();
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	///////////////////////////////

	// ���� ��ư ����
    auto closeItem = MenuItemImage::create(
                                           "Buttons/Menu/TITLE/close.png",
                                           "Buttons/Menu/TITLE/closepress.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setAnchorPoint(Vec2(1, 0));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - 10 , origin.y + 10));

	// �����ư�� �޴� ����
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////

	// ��� ��������Ʈ
    auto sprite = Sprite::create("BackGround/Main/title_pug_PRESS_final.png");
    sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 + 30.0f));
	this->addChild(sprite, 0);

	//////////////////////////////

	// �⺻ ���� ����
	EVOLUM = 0.5f; // 0~1������ ���� �� 0.5�� �ʱ�ȭ
	VOLUM = 0.5f;
	sounds[10] = { NULL }; // ���� ����Ǵ� ������ �����Ƿ� NULL�� ����Ʈ ID �ʱ�ȭ

	// ����� ���� �� ���� ������ ����Ǹ� VOLUM�� ���� VOLUM���� �޴´�.
	AudioProfile bgm;
	bgm.name = "Guilty";
	bgm.maxInstances = 1000;
	bgm.minDelay = 1.0f;

	sounds[0] = AudioEngine::play2d("Sounds/bgm/Guilty.mp3", true, 0.5f, &bgm);


    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::onKeyPressed(EventKeyboard::KeyCode key, Event *event) { HelloWorld::startScene(this); }