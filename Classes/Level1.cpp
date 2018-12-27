#include "Level1.h"
#include "defines.h"



CCTMXTiledMap * Level1::getMap() {
	return map;
}

void Level1::loadMap(const char* mapname) {
	map = CCTMXTiledMap::create(mapname); // 타일맵 생성
	map->retain(); // 수동으로 메모리 참조 addChild와 동일
}


Point Level1::tileCoordinateToPosition(Point point) {

	// 레벨의 바닥의 위치를 받아 반환
	float x = floor(point.x * map->getTileSize().width * SCALE_FACTOR);
	float y = floor(point.y * map->getTileSize().height * SCALE_FACTOR);

	return Point(x, y);

}

Point Level1::positionToTileCoordinate(Point point) {
	// 받은 스프라이트를 위치시킬 위치 Vec2 point

	float x = floor(point.x / (map->getTileSize().width * SCALE_FACTOR));
	float y = floor(point.y / (map->getTileSize().height * SCALE_FACTOR));

	return Point((int)x, (int)y);

}



vector<Rect> Level1::getCollisionTilesX(Point point, int direction) {

	vector<Rect> list;

	// 타일맵의 walls라는 레이어를 받아옵니다
	CCTMXLayer *walls = map->getLayer("walls");

	int mapheight = (int)map->getMapSize().height - 1;

	for (int b = -1; b < 2; b++) {

		Sprite *tile = walls->getTileAt(Point((int)point.x + direction, mapheight - ((int)point.y + b)));
		// direction = 1 전방, -1 후방
		// 캐릭터 위치 + 방향, 맵의 높이 - (캐릭터 위치 + (-1~1))
		// -1 : 캐릭터 아래, 0 : 캐릭터, 1 : 캐릭터 위

		if (tile != NULL) {
			// 타일의 Rect를 받아옵니다.
			Rect tileRect = Rect();

			Point tmp = walls->positionAt(Point((int)point.x + direction, mapheight - ((int)point.y + b)));
			tileRect.setRect(tmp.x * SCALE_FACTOR, tmp.y * SCALE_FACTOR,
				map->getTileSize().width * SCALE_FACTOR, map->getTileSize().height * SCALE_FACTOR);

			list.push_back(tileRect);
		}

	}

	return list;
}

vector<Rect> Level1::getCollisionTilesY(Point point, int direction) {

	vector<Rect> list;

	CCTMXLayer *walls = map->getLayer("walls");

	int mapheight = (int)map->getMapSize().height - 1;

	for (int b = -1; b < 2; b++) {
		// 캐릭터 기준 -1(뒤), 0(캐릭터), 1(앞)를 탐색

		Sprite *tile = walls->getTileAt(Point((int)point.x + b, mapheight - ((int)point.y + direction)));

		if (tile != NULL) {

			Rect tileRect = Rect();

			Point tmp = walls->positionAt(Point((int)point.x + b, mapheight - ((int)point.y + direction)));
			tileRect.setRect(tmp.x * SCALE_FACTOR, tmp.y * SCALE_FACTOR,
				map->getTileSize().width * SCALE_FACTOR, map->getTileSize().height * SCALE_FACTOR);

			list.push_back(tileRect);
		}

	}

	return list;

}


bool Level1::getCollisionTilesEdge(Point point, int direction) {

	CCTMXLayer *walls = map->getLayer("walls");

	int mapheight = (int)map->getMapSize().height - 1;

	// 전방 아래의 타일이 없는지 확인
	Sprite *tile = walls->getTileAt(Point((int)point.x + direction, mapheight - ((int)point.y - 1)));

	// 타일이 없으면 실행
	if (tile == NULL)
		return true; // 방향을 바꾸는 true반환
	else
		return false; // 그렇지 않으면 false
}

bool Level1::getCollisionTilesHazardsX(Point point, int direction) {

	// 타일맵의 위험요소 레이어를 받아옵니다
	CCTMXLayer *hazard = map->getLayer("hazards");

	int mapheight = (int)map->getMapSize().height - 1;

	// 타일과 부딛히는지 확인
	Sprite *tile = hazard->getTileAt(Point((int)point.x + direction, mapheight - ((int)point.y)));

	// 부딛히면 제거하는 bool형 반환
	if (tile == NULL)
		return false;
	else
		return true;
}
bool Level1::getCollisionTilesHazardsY(Point point, int direction) {

	CCTMXLayer *hazard = map->getLayer("hazards");

	int mapheight = (int)map->getMapSize().height - 1;

	Sprite *tile = hazard->getTileAt(Point((int)point.x, mapheight - ((int)point.y + direction)));

	if (tile == NULL)
		return false;
	else
		return true;
}

Level1::Level1(void) {}
Level1::~Level1(void)
{
	map->release(); // 메모리 수동 해제
}