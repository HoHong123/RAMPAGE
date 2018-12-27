#pragma once
#pragma execution_character_set("utf-8")

// std
#include <vector>
#include <algorithm>
#include <string>

// cocos
#include "cocos2d.h"

// Definition, ���������� ������ �����
#include "defines.h" // ���� ����
#include "setValues.h" // ���� Node�� �ʱ�ȭ�ϴ� �Լ��� 

// Lib
#include "action.h" // Lerp���� ���
#include "CollisionCheck.h" // ��� �浹�� Ȯ���ϴ� ��ü ���
#include "audio/include/AudioEngine.h" // �⺻ audioEngine ���

// Player
#include "Bullet.h" // �÷��̾��� �Ѿ� ���
#include "Player1.h" // �÷��̾��� ���

// Enemy
#include "Enemy01.h" // �⺻ ��1
#include "Enemy02.h" // �⺻ ��2

// Scene
#include "Level1.h" // �ʰ� �� �浹�� ����ϴ� ���
#include "GameOver.h" // ���ӿ��� ���� ����ϴ� ���
#include "BackGround.h" // ����� ����ϴ� ���

// Option
#include "OptionScene.h" // �ɼǾ��� ����ϴ� ���


using namespace std;
using namespace cocos2d;
using namespace experimental;


class Stage1 : public Layer {
private:

	// fire rate
	bool fireRate; // ���� �߻��ϴ� ��/���� �����ϴ� ����
	float shotgunRate; // ������ �������ð�
	
	//Level
	Level1 * level; // �� ��ü

	//objects
	Player1 *player; // �÷��̾� ��ü
	
	//camera
	Sprite *cameraTarget; // ī�޶� ���󰡴� ��ü
	float cameraSpeed; // ī�޶� ī�޶� ��ǥ�� ���󰡴� �ӵ�
	float cameraOffset; // ī�޶� ���� �̵����� ���� ������ ������ ���󰡴��� �����ϴ� ����

	Follow *camera; // ī�޶� ����
	// Follow ������ Action�� ����

	//key input
	vector<EventKeyboard::KeyCode> heldKeys; // ���� �������ִ� Ű�� Ȯ���� ����

	//Collision Detection
	Collision *collision; // ��� �浹�� Ȯ���ϴ� ��ü

	// ���� ������ ��ȯ ���� ����
	Sprite *raidPoint; // �÷��̾�� �浹�� ���͸� ��ȯ�ϴ� ��ü
	// ���� Ƚ���� �ð�
	bool spawn;
	int count;
	float num, duration;

public:

	Stage1();
	~Stage1();

	static Scene* createScene();
	void restart(Ref *pSender); // ������� �ϴ� �Լ�
	void Option(Ref *pSender); // �ɼǾ��� �θ��� �Լ�

	virtual bool init();
	
	void addText(string name, string text); // Ư�� ��ҿ� �ؽ�Ʈ�� ��ȯ�ϴ� �Լ�
	void addBullet(); // �Ѿ��� �ִ� �Լ�
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event); 
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void update(float f);

	void getKeys(); // �Ź� �÷��̾ �Է��� Ű�� Ȯ���ϴ� ������

	void addMonster(string name, int num = 1, float turn = 1.0f); // ���͸� ��ȯ�ϴ� �Լ�
	void addFly(string name, int num = 1, float turn = 1.0f); // ���� ���͸� ��ȯ�ϴ� �Լ�

	void gameover(Ref *pSender); // ���ӿ������� �θ��� �Լ�
	void menuCloseCallback(Ref* pSender);

	CREATE_FUNC(Stage1);
};
