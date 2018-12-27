#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

using namespace cocos2d;

USING_NS_CC;


class GameUI : public ui::Layout {
public:

	static GameUI* create();

	virtual bool init();
};