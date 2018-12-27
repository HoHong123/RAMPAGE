#include "Slider.h"

USING_NS_CC;

void Slider::sliderChangeValue(cocos2d::Ref* pSender, cocos2d::ui::Slider::EventType type) {
	if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED) {
		auto slider = (ui::Slider*)pSender;

		//VOLUM = ((float)slider->getPercent()) / 100;
		//experimental::AudioEngine::setVolume(id, VOLUM);
	}
}
