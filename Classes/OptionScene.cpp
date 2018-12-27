#include "OptionScene.h"

USING_NS_CC;


extern int sounds[];
extern float VOLUM;
extern float EVOLUM;

Scene* Option::createScene() {

	return Option::create();
}

void Option::startScene(cocos2d::Ref *pSender) {
	Scene *scene1 = TransitionCrossFade::create(0.5f, Scene1::createScene());

	AudioEngine::stopAll();

	AudioProfile bgm;
	bgm.name = "Guilty";
	bgm.maxInstances = 1000;

	sounds[0] = AudioEngine::play2d("Sounds/bgm/Guilty.mp3", true, VOLUM, &bgm);

	Director::getInstance()->replaceScene(scene1);
}
void Option::popScene(cocos2d::Ref *pSender) {
	Director::sharedDirector()->popScene();
}

bool Option::init() {
	if (!Scene::init()) {
		return false;
	}

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2(Option::onKeyPressed, this);
	keyListener->onKeyReleased = CC_CALLBACK_2(Option::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);

	///////////////////////

	// 메뉴 보더 생성
	Sprite* menu = Sprite::create("Buttons/Menu/STAGE/border.png");
	menu->setContentSize(Size(600, 600));
	menu->setPosition(Vec2(visibleSize.width / 2, visibleSize.height * 0.3f));

	///////////////////////

	auto startIcon = MenuItemImage::create(
		"Buttons/Menu/TITLE/menu.png",
		"Buttons/Menu/TITLE/menupress.png",
		CC_CALLBACK_1(Option::startScene, this));

	startIcon->setPosition(Vec2(visibleSize.width/2, visibleSize.height * 0.2f));

	Menu* start_press = Menu::create(startIcon, NULL);
	start_press->setPosition(Vec2::ZERO);

	this->addChild(start_press, 10);

	///////////////////////

	auto BGMvolumText = Label::create("BGM SOUND", "fonts/invasion2000.ttf", 24);
	auto EffectvolumText = Label::createWithTTF("EFFECT SOUND", "fonts/invasion2000.ttf", 24);
	
	///////////////////////

	// BGM 슬라이더 텍스트 생성
	BGMvolumText->setAnchorPoint(Vec2(0.5f, 0.0f));
	BGMvolumText->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2 + 50.0f));

	// BGM 슬라이더 생성
	bgmSlider = ui::Slider::create("Buttons/Menu/SoundSlide/BackLine.png", "Buttons/Menu/SoundSlide/BGMCircle.png");
	bgmSlider->setScale(0.5f);
	bgmSlider->setAnchorPoint(Vec2(0.5f, 1.0f));
	bgmSlider->setPosition(Vec2(visibleSize.width / 2, BGMvolumText->getPositionY() - 50.0f));
	bgmSlider->setPercent((VOLUM * 100));
	
	bgmSlider->loadProgressBarTexture("Buttons/Menu/SoundSlide/Line.png");
	bgmSlider->addEventListener(CC_CALLBACK_2(Option::sliderChangeValue, this, 0));

	this->addChild(BGMvolumText, 1);
	this->addChild(bgmSlider, 1);

	////////////////////////

	// 이펙트 슬라이더 텍스트 생성
	EffectvolumText->setAnchorPoint(Vec2(0.5f, 0.0f));
	EffectvolumText->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50.0f));

	// 이펙트 슬라이더 생성
	effectSlider = ui::Slider::create("Buttons/Menu/SoundSlide/BackLine.png", "Buttons/Menu/SoundSlide/EffectCircle.png");
	effectSlider->setScale(0.5f);
	effectSlider->setAnchorPoint(Vec2(0.5f, 1.0f));
	effectSlider->setPosition(Vec2(visibleSize.width/2, EffectvolumText->getPositionY() - 50.0f));
	effectSlider->setPercent((EVOLUM * 100));

	effectSlider->loadProgressBarTexture("Buttons/Menu/SoundSlide/Line.png");
	effectSlider->addEventListener(CC_CALLBACK_2(Option::sliderChangeValue, this, 1));

	this->addChild(EffectvolumText, 1);
	this->addChild(effectSlider, 1);

	return true;
}

void Option::sliderChangeValue(cocos2d::Ref* pSender, cocos2d::ui::Slider::EventType type, int i) {
	if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
		auto slider = (ui::Slider*)pSender;

		// 슬라이더가 움직이면 해당하는 슬라이더가 각 오디오 ID값의 소리를 변경

		if (i == 0) {
			VOLUM = ((float)slider->getPercent()) / 100;
			experimental::AudioEngine::setVolume(sounds[0], VOLUM);
		}
		else {
			EVOLUM = ((float)slider->getPercent()) / 100;
			for(int j = 1; j < 10; j++)
				experimental::AudioEngine::setVolume(sounds[j], EVOLUM);
		}

	}
}

void Option::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
	if (keyCode == ESC)
	{
		popScene(this);
	}
}
void Option::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event) {
}
