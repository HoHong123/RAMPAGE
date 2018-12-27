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

	target = player; // ����ٴ� ��ǥ
	targetX = target->getPositionX(); // Ÿ���� X��
	lastCameraX = target->getPositionX(); // Ÿ���� X��

	Scrolling = parallax = checkLayer = true; // �з������� �̵��� ��ȯ, �̵��ϴ����� ���θ� ������ �� �ִ� bool���� true ����

	paralaxSpeed = parallaxSpeed;

	for (int i = 0; i < 3; i++) {
		BGs[i] = Sprite::create(fileName); // �� ��� ����
		BGs[i]->setPosition(Vec2((((i) * BGs[i]->getContentSize().width) + targetX), 0)); // ��ǥ�� ����� ��ġ�� ����Ͽ� ����� ��ġ��ŵ�ϴ�

		addChild(BGs[i],-1);
	}
	BgSize = BGs[0]->getContentSize().width;
	
	left = 0; // BGs �迭 �ּҰ�
	right = 2; // BGs �迭 �ִ밪
	viewPoint = 10.0f; // �� ��������Ʈ ������ ���� ����

	scheduleUpdate();
}
BackGround::~BackGround(void){}

void BackGround::update(float f) {

	targetX = target->getPositionX(); // ��ǥ�� x��

	if (parallax) {
		float deltaX = targetX - lastCameraX;

		// ��� ����� �ش� �ӵ���ŭ ��ǥ�� �����̴� ����� ���� ���ݾ� �ڿ������� �̵�
		for (int i = 0; i < 3; i++)
			BGs[i]->setPositionX(BGs[i]->getPositionX() + (deltaX * paralaxSpeed));
	}

	lastCameraX = targetX;

	if (Scrolling) {
		// ��ǥ�� ����� ���� �� ��ư��� ��ٸ� ����� ������ �̵���Ų��.
		if (targetX < ((BGs[left]->getPositionX() + (BgSize/2)) + viewPoint))
			ScrollLeft();
		if (targetX > ((BGs[right]->getPositionX() - (BgSize/2)) - viewPoint))
			ScrollRight();
	}
}

void BackGround::ScrollLeft() {
	
	// �������� ����� ������ �������� �̵�
	BGs[right]->setPositionX((BGs[left]->getPositionX() - BgSize));
	
	left = right;
	
	right--;

	if (right < 0)
		right = 2;

}

void BackGround::ScrollRight() {

	// ������ ����� ������ ���������� �̵�
	BGs[left]->setPositionX((BGs[right]->getPositionX() + BgSize));

	right = left;
	left++;

	if (left == 3)
		left = 0;

}