#pragma once
#include "cocos2d.h"
#include "defines.h"
#include "ui/CocosGUI.h"
#include "audio/include/AudioEngine.h"

using namespace cocos2d;

USING_NS_CC;


class Slider : public Layer {
public :
	int id;
	experimental::AudioProfile pAudio;

	void sliderChangeValue(cocos2d::Ref* pSender, cocos2d::ui::Slider::EventType type);
};