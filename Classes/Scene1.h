#pragma once
#pragma execution_character_set("utf-8")

#include "cocos2d.h"
#include "setValues.h"
#include "action.h"
#include "defines.h";
#include "Stage1.h"
#include "OptionScene.h"

using namespace cocos2d;



class Scene1 : public Scene {
private:

public:

	Scene1();
	~Scene1();

	static Scene* createScene();
	void stage1(Ref *pSender);
	void Option(Ref *pSender);

	virtual bool init();

	CREATE_FUNC(Scene1);
};