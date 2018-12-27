#pragma once
#pragma execution_character_set("utf-8")

// std
#include <vector>
#include <algorithm>
#include <string>

// cocos
#include "cocos2d.h"

// Definition, 개인적으로 생성한 헤더들
#include "defines.h" // 각종 선언
#include "setValues.h" // 각종 Node를 초기화하는 함수들 

// Lib
#include "action.h" // Lerp구현 헤더
#include "CollisionCheck.h" // 모든 충돌을 확인하는 객체 헤더
#include "audio/include/AudioEngine.h" // 기본 audioEngine 헤더

// Player
#include "Bullet.h" // 플레이어의 총알 헤더
#include "Player1.h" // 플레이어의 헤더

// Enemy
#include "Enemy01.h" // 기본 적1
#include "Enemy02.h" // 기본 적2

// Scene
#include "Level1.h" // 맵과 맵 충돌을 담당하는 헤더
#include "GameOver.h" // 게임오버 씬을 담당하는 헤더
#include "BackGround.h" // 배경을 담당하는 헤더

// Option
#include "OptionScene.h" // 옵션씬을 담당하는 헤더


using namespace std;
using namespace cocos2d;
using namespace experimental;


class Stage1 : public Layer {
private:

	// fire rate
	bool fireRate; // 총을 발사하는 유/무를 선정하는 변수
	float shotgunRate; // 샷건의 재장전시간
	
	//Level
	Level1 * level; // 맵 객체

	//objects
	Player1 *player; // 플레이어 객체
	
	//camera
	Sprite *cameraTarget; // 카메라가 따라가는 객체
	float cameraSpeed; // 카메라가 카메라 목표를 따라가는 속도
	float cameraOffset; // 카메라가 실제 이동보다 얼마의 간격을 가지고 따라가는지 선정하는 변수

	Follow *camera; // 카메라 변수
	// Follow 변수는 Action의 일종

	//key input
	vector<EventKeyboard::KeyCode> heldKeys; // 현재 눌리고있는 키를 확인할 변수

	//Collision Detection
	Collision *collision; // 모든 충돌을 확인하는 객체

	// 게임 진행중 소환 중점 지역
	Sprite *raidPoint; // 플레이어와 충돌시 몬스터를 소환하는 객체
	// 스폰 횟수와 시간
	bool spawn;
	int count;
	float num, duration;

public:

	Stage1();
	~Stage1();

	static Scene* createScene();
	void restart(Ref *pSender); // 재시작을 하는 함수
	void Option(Ref *pSender); // 옵션씬을 부르는 함수

	virtual bool init();
	
	void addText(string name, string text); // 특정 장소에 텍스트를 소환하는 함수
	void addBullet(); // 총알을 넣는 함수
	virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event); 
	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	void update(float f);

	void getKeys(); // 매번 플레이어가 입력한 키를 확인하는 ㅎ마수

	void addMonster(string name, int num = 1, float turn = 1.0f); // 몬스터를 소환하는 함수
	void addFly(string name, int num = 1, float turn = 1.0f); // 나는 몬스터를 소환하는 함수

	void gameover(Ref *pSender); // 게임오버씬을 부르는 함수
	void menuCloseCallback(Ref* pSender);

	CREATE_FUNC(Stage1);
};
