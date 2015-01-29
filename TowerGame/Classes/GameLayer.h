#pragma  once
#include "cocos2d.h"
#include "Creep.h"
#include "WayPoint.h"
#include "Wave.h"
#include "GameHUD .h"

USING_NS_CC;

class GameLayer: public Layer
{
public:
	TMXTiledMap* tileMap;
	TMXLayer* background;
	int currentLevel;
	Point position;
	void addWaypoint();
	void addWaves();
	void addTower(Point pos,String imageName);
	Point tileCoordForPosition(Point position);
	bool canBuildOnTilePosition(Point pos);
	virtual bool init();
	virtual void update(float dt);
	void FollowPath(Node* sender);
	Wave* getCurrentWave();
	Wave* getNextWave();
	void gameLogic(float dt);
	void addTarget();
	Point boundLayerPos(Point newPos);
	CREATE_FUNC(GameLayer);
};