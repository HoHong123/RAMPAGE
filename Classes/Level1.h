#pragma once
#include "cocos2d.h"
#include <vector>

using namespace std;
using namespace cocos2d;

class Level1 : public CCObject
{
public:

	CCTMXTiledMap* map; // Ÿ�ϼ�

	void loadMap(const char* name); // Ÿ�ϼ� ���� �� �޸𸮿� ����
	CCTMXTiledMap *getMap(); // ������ �� ��ȯ

	Point tileCoordinateToPosition(Point point); // ������ ��ġ�� ���� ��������Ʈ�� ũ�⸸ŭ ������ �־� �� ���� ��ġ��Ų��.
	Point positionToTileCoordinate(Point point); // Ÿ���� ��ġ�� �̵�

	vector<Rect> getCollisionTilesX(Point point, int direction); // X�� �浹 ����
	vector<Rect> getCollisionTilesY(Point point, int direction); // Y�� �浹 ����

	bool getCollisionTilesEdge(Point point, int direction); // Ÿ���� ���������� ����

	// �����ҿ��� �浹����
	bool getCollisionTilesHazardsX(Point point, int direction); 
	bool getCollisionTilesHazardsY(Point point, int direction);

	Level1(void);
	virtual ~Level1(void);
};