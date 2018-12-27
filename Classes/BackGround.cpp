#include "BackGround.h"

BackGround * BackGround::create(Sprite* player, string fileName , float Y, float parallaxSpeed) {

	 BackGround* pSprite = new BackGround(player, fileName, parallaxSpeed);

	 if (pSprite != NULL) {
		 pSprite->setPosition(Vec2(0, Y));
		 return pSprite;
	 }

	return NULL;
}

BackGround::BackGround(void) {}
BackGround::BackGround(Sprite* player, string fileName, float parallaxSpeed) {

	target = player; // 따라다닐 목표
	targetX = target->getPositionX(); // 타겟의 X축
	lastCameraX = target->getPositionX(); // 타겟의 X축

	Scrolling = parallax = checkLayer = true; // 패럴랙스의 이동과 소환, 이동하는지의 여부를 결정할 수 있는 bool변수 true 선언

	paralaxSpeed = parallaxSpeed;

	for (int i = 0; i < 3; i++) {
		BGs[i] = Sprite::create(fileName); // 각 배경 생성
		BGs[i]->setPosition(Vec2((((i) * BGs[i]->getContentSize().width) + targetX), 0)); // 목표와 배경의 위치를 고려하여 배경을 위치시킵니다

		addChild(BGs[i],-1);
	}
	BgSize = BGs[0]->getContentSize().width;
	
	left = 0; // BGs 배열 최소값
	right = 2; // BGs 배열 최대값
	viewPoint = 10.0f; // 각 스프라이트 사이의 여유 공간

	scheduleUpdate();
}
BackGround::~BackGround(void){}

void BackGround::update(float f) {

	targetX = target->getPositionX(); // 목표의 x축

	if (parallax) {
		float deltaX = targetX - lastCameraX;

		// 모든 배경이 해당 속도만큼 목표가 움직이는 방향과 같이 조금씩 자연스럽게 이동
		for (int i = 0; i < 3; i++)
			BGs[i]->setPositionX(BGs[i]->getPositionX() + (deltaX * paralaxSpeed));
	}

	lastCameraX = targetX;

	if (Scrolling) {
		// 목표가 배경의 끝에 다 닿아가면 배다른 배경을 앞으로 이동시킨다.
		if (targetX < ((BGs[left]->getPositionX() + (BgSize/2)) + viewPoint))
			ScrollLeft();
		if (targetX > ((BGs[right]->getPositionX() - (BgSize/2)) - viewPoint))
			ScrollRight();
	}
}

void BackGround::ScrollLeft() {
	
	// 오른편의 배경을 왼편의 왼쪽으로 이동
	BGs[right]->setPositionX((BGs[left]->getPositionX() - BgSize));
	
	left = right;
	
	right--;

	if (right < 0)
		right = 2;

}

void BackGround::ScrollRight() {

	// 왼편의 배경을 오른편 오른쪽으로 이동
	BGs[left]->setPositionX((BGs[right]->getPositionX() + BgSize));

	right = left;
	left++;

	if (left == 3)
		left = 0;

}