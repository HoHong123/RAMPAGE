#pragma once
#pragma execution_character_set("utf-8")

#include "cocos2d.h"
#include "defines.h"
#include "Scene1.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"

using namespace cocos2d;
using namespace ui;


class Option : public Scene {

	int id;
	Slider *bgmSlider, *effectSlider;

public:
	static Scene* createScene();
	void popScene(cocos2d::Ref *pSender);
	void startScene(cocos2d::Ref *pSender);

	virtual bool init();

	void sliderChangeValue(cocos2d::Ref* pSender, cocos2d::ui::Slider::EventType type, int i);

	void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

	CREATE_FUNC(Option);
};
