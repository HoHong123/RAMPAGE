#include "setValues.h"

namespace setting {

	void setValues::setSpriteValue(Sprite *object, Vec2 pos, Size scale) {
		object->setPosition(pos);
		object->setContentSize(scale);
	}


	void setValues::setMenuImageValue(MenuItemImage *object, Vec2 pos) {
		object->setPosition(pos);
	}
	void setValues::setMenuImageValue(MenuItemImage *object, Vec2 pos, float scale) {
		object->setScale(scale);
		object->setPosition(pos);
	}
	void setValues::setMenuImageValue(MenuItemImage *object, Vec2 pos, float scaleX, float scaleY, float scaleZ) {
		object->setScaleX(scaleX);
		object->setScaleY(scaleY);
		object->setScaleZ(scaleZ);
		object->setPosition(pos);
	}

	void setValues::setLabel(Label *label , Vec2 Pos, Size size, Color4B color, Vec2 AnchorPoint) {
		label->setContentSize(size); 
		label->setPosition(Pos);
		label->setTextColor(color);
		label->setAnchorPoint(AnchorPoint);
	}


	void setValues::SetAddress(Sprite* Sprite, std::string Add) {
		Sprite->setTexture(Add);
	}
	void setValues::SetAddress(MenuItemImage* MenuItemLabel, std::string NormalAdd, std::string SelectedAdd) {
		MenuItemLabel->setNormalImage(cocos2d::Sprite::create(NormalAdd));
		MenuItemLabel->setSelectedImage(cocos2d::Sprite::create(SelectedAdd));
	}

	void setValues::SetSize(Sprite* Sprite, Size Size) {
		Sprite->setContentSize(Size);
	}
	void setValues::SetSize(Sprite* Sprite, float Scale) {
		Sprite->setScale(Scale);
	}
	void setValues::SetSize(MenuItemImage* MenuItemLabel, Size Size) {
		MenuItemLabel->setContentSize(Size);
	}
	void setValues::SetSize(MenuItemImage* MenuItemLabel, float Scale) {
		MenuItemLabel->setScale(Scale);
	}

	void setValues::SetPos(Sprite * Sprite, Vec2 Pos) {
		Sprite->setPosition(Pos);
	}

	void setValues::SetAnchorPoint(Sprite * Sprite, Vec2 AnchorPoint) {
		Sprite->setAnchorPoint(AnchorPoint);
	}


	void setBackGround::setBackGroundLayer(Scene *Scene, std::string add, Vec2 Pos, Size size, int Layer, Vec2 Anchor) {

		auto bg = Sprite::create(add);

		setValues::setSpriteValue(bg, Pos, size);

		bg->setAnchorPoint(Anchor);

		Scene->addChild(bg, Layer);
	}
}