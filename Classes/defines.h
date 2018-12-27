#pragma once

#include "time.h"
#include "audio/include/AudioEngine.h"


using namespace cocos2d;

#define visibleSize cocos2d::Director::getInstance()->getVisibleSize()
#define origin cocos2d::Director::getInstance()->getVisibleOrigin()
#define center Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y)
#define PI 3.14f
#define SOUND_SIZE 10

// �̺�Ʈ
const EventKeyboard::KeyCode RESET = EventKeyboard::KeyCode::KEY_R;
const EventKeyboard::KeyCode ENTER = EventKeyboard::KeyCode::KEY_KP_ENTER;
const EventKeyboard::KeyCode ESC = EventKeyboard::KeyCode::KEY_ESCAPE;

// Ű ���� ����
const EventKeyboard::KeyCode SPACEBAR = EventKeyboard::KeyCode::KEY_SPACE;
const EventKeyboard::KeyCode UP_ARROW = EventKeyboard::KeyCode::KEY_UP_ARROW;
const EventKeyboard::KeyCode DOWN_ARROW = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
const EventKeyboard::KeyCode LEFT_ARROW = EventKeyboard::KeyCode::KEY_LEFT_ARROW;
const EventKeyboard::KeyCode RIGHT_ARROW = EventKeyboard::KeyCode::KEY_RIGHT_ARROW;

// �׼� ���� ����
const EventKeyboard::KeyCode ATTACK = EventKeyboard::KeyCode::KEY_Z;
const EventKeyboard::KeyCode ULTIMATE = EventKeyboard::KeyCode::KEY_X;
const EventKeyboard::KeyCode ULTIMATE_CHANGE = EventKeyboard::KeyCode::KEY_C;


// �÷��̾� ��ü
const float SCALE_FACTOR = 2.6f; // Object Scale
const float PLAYER_MAX_VELOCITY = 8.0f; // �÷��̾� �ִ� �ӵ�
const float PLAYER_JUMP_VELOCITY = 17.0f; // �÷��̾� ����
const float PLAYER_BULLET_VELOCITY = .2f; // �Ѿ� �ӵ�
const float PLAYER_INVINCIBILITY_DURATION = 1.0f;


// �� ��ü
const float ENEMY_SCALE_FACTOR = 2.8f;
const float ENEMY_MAX_VELOCITY = 5.5f; // �� �ִ� �ӵ�
const float ENEMY_JUMP_VELOCITY = 15.0f; // �� ����
const float ENEMY_BULLET_VELOCITY = 0.8f; // �Ѿ� �ӵ�


// ȯ��
const float DAMPING = 0.87f;
const float GRAVITY = 0.77f;



static void wait(float seconds) // �ٸ� �Լ� �Ͻ����� �Լ�
{
	float endwait;
	endwait = clock() + seconds * CLOCKS_PER_SEC;
	while (clock() < endwait) {}
};
