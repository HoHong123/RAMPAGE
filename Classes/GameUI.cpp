#include "GameUI.h"

USING_NS_CC;


GameUI *GameUI::create() {

	ui::Layout *layout = ui::Layout::create();
	ui::ImageView* ult = ui::ImageView::create();

	layout->setLayoutType(ui::Layout::Type::VERTICAL);

	return NULL;
}

bool GameUI::init() {

	return true;
}