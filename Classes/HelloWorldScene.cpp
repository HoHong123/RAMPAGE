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
	// 0.5초의 페이드 효과를 받으며 다음 씬으로 전환

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


	// 키리스너 생성
	auto dispatcher = Director::sharedDirector()->getEventDispatcher();
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	dispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	///////////////////////////////

	// 종료 버튼 생성
    auto closeItem = MenuItemImage::create(
                                           "Buttons/Menu/TITLE/close.png",
                                           "Buttons/Menu/TITLE/closepress.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setAnchorPoint(Vec2(1, 0));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - 10 , origin.y + 10));

	// 종료버튼의 메뉴 생성
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////

	// 배경 스프라이트
    auto sprite = Sprite::create("BackGround/Main/title_pug_PRESS_final.png");
    sprite->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 + 30.0f));
	this->addChild(sprite, 0);

	//////////////////////////////

	// 기본 볼륨 설정
	EVOLUM = 0.5f; // 0~1까지의 볼륨 중 0.5로 초기화
	VOLUM = 0.5f;
	sounds[10] = { NULL }; // 현재 재생되는 음악이 없으므로 NULL로 리스트 ID 초기화

	// 배경음 선언 및 무한 루프로 실행되며 VOLUM의 값을 VOLUM으로 받는다.
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