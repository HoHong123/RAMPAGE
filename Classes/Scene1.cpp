#include "Scene1.h"

USING_NS_CC;

extern int sounds[];
extern float VOLUM;
extern float EVOLUM;

Scene* Scene1::createScene() {
	
	Scene1 *s = new Scene1();
	s = Scene1::create();

	return s;
}
void Scene1::stage1(Ref *pSender) {
	Scene *stage1 = TransitionCrossFade::create(0.3f, Stage1::createScene());

	Director::getInstance()->replaceScene(stage1);
}
void Scene1::Option(Ref *pSender) {
	Scene* option = Option::createScene();

	Director::sharedDirector()->pushScene(option);
}


Scene1::Scene1() {}
Scene1::~Scene1() {}


bool Scene1::init() {

	if (!Scene::init())
	{
		return false;
	}

	// 배경화면 스프라이트
	Sprite *bg = Sprite::create("Buttons/Menu/STAGE/border_bg.png");
	bg->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));

	this->addChild(bg, 0);

	//////////////////////////////////////////

	// 메뉴 보더 생성
	Sprite* menu = Sprite::create("Buttons/Menu/STAGE/border.png");
	menu->setContentSize(Size(600, 600));
	menu->setPosition(Vec2(visibleSize.width/2, visibleSize.height / 2));

	// 스테이지1 버튼 생성
	MenuItemImage* stage1 = MenuItemImage::create("Buttons/Menu/STAGE/stage1.png",
		"Buttons/Menu/STAGE/stage1_pressed.png",CC_CALLBACK_1(Scene1::stage1, this));

	stage1->setPosition(Vec2(menu->getContentSize().width * 0.8f, menu->getContentSize().height * 0.75f));

	Menu* stage1_press = Menu::create(stage1, NULL);
	stage1_press->setPosition(Vec2::ZERO);

	menu->addChild(stage1_press);
	/////////////////////////////////////////////

	MenuItemImage* option = MenuItemImage::create("Buttons/Menu/TITLE/option.png",
		"Buttons/Menu/TITLE/optionpress.png", CC_CALLBACK_1(Scene1::Option, this));

	option->setPosition(Vec2(menu->getContentSize().width / 3, menu->getContentSize().height * 0.2f));

	Menu* option_press = Menu::create(option, NULL);
	option_press->setPosition(Vec2::ZERO);

	menu->addChild(option_press);

	/////////////////////////////////////////////
	this->addChild(menu);
	this->scheduleUpdate();

	return true;
}