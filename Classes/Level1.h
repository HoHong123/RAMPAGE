#pragma once
#include "cocos2d.h"
#include <vector>

using namespace std;
using namespace cocos2d;

class Level1 : public CCObject
{
public:

	CCTMXTiledMap* map; // 타일셋

	void loadMap(const char* name); // 타일셋 제작 및 메모리에 저장
	CCTMXTiledMap *getMap(); // 생성한 맵 반환

	Point tileCoordinateToPosition(Point point); // 지정된 위치에 받은 스프라이트의 크기만큼 여유를 주어 맵 위에 위치시킨다.
	Point positionToTileCoordinate(Point point); // 타일의 위치에 이동

	vector<Rect> getCollisionTilesX(Point point, int direction); // X축 충돌 감지
	vector<Rect> getCollisionTilesY(Point point, int direction); // Y축 충돌 감지

	bool getCollisionTilesEdge(Point point, int direction); // 타일의 낭떠러지를 감지

	// 위험요소와의 충돌감지
	bool getCollisionTilesHazardsX(Point point, int direction); 
	bool getCollisionTilesHazardsY(Point point, int direction);

	Level1(void);
	virtual ~Level1(void);
};