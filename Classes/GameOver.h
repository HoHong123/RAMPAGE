#pragma once
#pragma execution_character_set("utf-8")

#include "cocos2d.h"
#include "defines.h"
#include "setValues.h"
#include "Scene1.h"
#include "Stage1.h"

using namespace cocos2d;

class GameOver : public Scene {
private:

	LabelTTF *count;
	LabelTTF *press;
	float time;

	int last;
	int num;

	Animate *pug;

public:
	static Scene* createScene(int sceneNum);

	GameOver();
	GameOver(int sceneNum);
	~GameOver();

	void startScene(cocos2d::Ref *pSender);
	void stage1(cocos2d::Ref *pSender);

	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);

	CREATE_FUNC(GameOver);

	void Timer(float dt);
};