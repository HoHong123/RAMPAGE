#pragma once
#include "cocos2d.h"
#include "defines.h"
#include <cstdlib>
#include <ctime>

using namespace cocos2d;

namespace setting {
	class setValues {
	public:
		static void setSpriteValue(Sprite *object, Vec2 pos, Size scale = Size(1,1));

		static void setLabel(Label *label, Vec2 Pos, Size size, Color4B color = ccc4(0, 0, 0, 100), Vec2 AnchorPoint = Vec2(0.5, 0.5));

		static void setMenuImageValue(MenuItemImage *object, Vec2 pos);
		static void setMenuImageValue(MenuItemImage *object, Vec2 pos, float scale);
		static void setMenuImageValue(MenuItemImage *object, Vec2 pos, float scaleX, float scaleY, float scaleZ = 1);


		void SetAddress(cocos2d::Sprite* Sprite, std::string Add);
		void SetAddress(cocos2d::MenuItemImage* MenuItemLabel, std::string NormalAdd, std::string SelectedAdd);

		void SetSize(cocos2d::Sprite* Sprite, Size Size);
		void SetSize(cocos2d::Sprite* Sprite, float Scale);
		void SetSize(cocos2d::MenuItemImage* MenuItemLabel, Size Size);
		void SetSize(cocos2d::MenuItemImage* MenuItemLabel, float Scale);

		void SetPos(cocos2d::Sprite * Sprite, Vec2 Pos);

		void SetAnchorPoint(Sprite * Sprite, Vec2 AnchorPoint);

	};

	class setBackGround {
	public:
		static void setBackGroundLayer(Scene *Scene, std::string add, Vec2 Pos, Size Size, int Layer = 0, Vec2 Anchor = Vec2(0.5,0.5));
	};
}