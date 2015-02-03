#pragma  once
#include "cocos2d.h"
#include "Creep.h"
#include "WayPoint.h"
#include "Wave.h"
#include "GameHUD.h"

USING_NS_CC;

class GameLayer: public Layer
{
public:
	TMXTiledMap* tileMap;
	TMXLayer* background;
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
	void gameLogic(float dt);
	void addTarget();
	void usePropBomb();
	void showPauseLayer();
	void playerRevive();
	void clearAllCreep();
	void towerLevelUp();
	Point boundLayerPos(Point newPos);
	CREATE_FUNC(GameLayer);
};