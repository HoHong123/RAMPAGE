#include "Level1.h"
#include "defines.h"



CCTMXTiledMap * Level1::getMap() {
	return map;
}

void Level1::loadMap(const char* mapname) {
	map = CCTMXTiledMap::create(mapname); // Ÿ�ϸ� ����
	map->retain(); // �������� �޸� ���� addChild�� ����
}


Point Level1::tileCoordinateToPosition(Point point) {

	// ������ �ٴ��� ��ġ�� �޾� ��ȯ
	float x = floor(point.x * map->getTileSize().width * SCALE_FACTOR);
	float y = floor(point.y * map->getTileSize().height * SCALE_FACTOR);

	return Point(x, y);

}

Point Level1::positionToTileCoordinate(Point point) {
	// ���� ��������Ʈ�� ��ġ��ų ��ġ Vec2 point

	float x = floor(point.x / (map->getTileSize().width * SCALE_FACTOR));
	float y = floor(point.y / (map->getTileSize().height * SCALE_FACTOR));

	return Point((int)x, (int)y);

}



vector<Rect> Level1::getCollisionTilesX(Point point, int direction) {

	vector<Rect> list;

	// Ÿ�ϸ��� walls��� ���̾ �޾ƿɴϴ�
	CCTMXLayer *walls = map->getLayer("walls");

	int mapheight = (int)map->getMapSize().height - 1;

	for (int b = -1; b < 2; b++) {

		Sprite *tile = walls->getTileAt(Point((int)point.x + direction, mapheight - ((int)point.y + b)));
		// direction = 1 ����, -1 �Ĺ�
		// ĳ���� ��ġ + ����, ���� ���� - (ĳ���� ��ġ + (-1~1))
		// -1 : ĳ���� �Ʒ�, 0 : ĳ����, 1 : ĳ���� ��

		if (tile != NULL) {
			// Ÿ���� Rect�� �޾ƿɴϴ�.
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
		// ĳ���� ���� -1(��), 0(ĳ����), 1(��)�� Ž��

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

	// ���� �Ʒ��� Ÿ���� ������ Ȯ��
	Sprite *tile = walls->getTileAt(Point((int)point.x + direction, mapheight - ((int)point.y - 1)));

	// Ÿ���� ������ ����
	if (tile == NULL)
		return true; // ������ �ٲٴ� true��ȯ
	else
		return false; // �׷��� ������ false
}

bool Level1::getCollisionTilesHazardsX(Point point, int direction) {

	// Ÿ�ϸ��� ������ ���̾ �޾ƿɴϴ�
	CCTMXLayer *hazard = map->getLayer("hazards");

	int mapheight = (int)map->getMapSize().height - 1;

	// Ÿ�ϰ� �ε������� Ȯ��
	Sprite *tile = hazard->getTileAt(Point((int)point.x + direction, mapheight - ((int)point.y)));

	// �ε����� �����ϴ� bool�� ��ȯ
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
	map->release(); // �޸� ���� ����
}