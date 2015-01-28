#include "GameLayer.h"
#include "Tower.h"
#include "DataModel.h"
#include "GameOverScene.h"
#include "TopMenu.h"
#include <Vector>
#include <string>
#include "GameData.h"
#include "GameState.h"


USING_NS_CC;


void GameLayer::FollowPath(Node* sender)
{
	Creep *creep = (Creep *)sender;

	WayPoint * waypoint = creep->getNextWaypoint();

	int moveDuration = creep->moveDuration;
	auto actionMove = MoveTo::create(moveDuration,waypoint->getPosition());
	auto actionMoveDone = CallFuncN::create(this,callfuncN_selector(GameLayer::FollowPath));
	creep->stopAllActions();
	creep->runAction(Sequence::create(actionMove,actionMoveDone,NULL));
}

bool GameLayer::init()
{
	if (!Layer::init()) 
	{
		return false;
	}

	//add topMenu to GameLayer

	this->tileMap = TMXTiledMap::create(UserDefault::getInstance()->getStringForKey("nextLevelFile"));
	this->background = tileMap->layerNamed("Background");
	this->background->setAnchorPoint(ccp(0, 0));
	this->addChild(tileMap, 0);

	GAMEDATA::getInstance()->initLevelInfo(GAMEDATA::getInstance()->getCurrentLevel());
	TopMenu* TopMenu = TopMenu::getInstance();
	this->addChild(TopMenu,2);
	this->addWaypoint();
	this->addWaves();

	this->scheduleUpdate();
	this->schedule(schedule_selector(GameLayer::gameLogic), 1.0f);
	this->currentLevel = 0;
	this->position = ccp(-228, -122);

	return true;
}

void GameLayer::addWaves()
{
	DataModel *m = DataModel::getModel();

	Wave *wave = NULL;
	wave = Wave::create()->initWithCreep(FastRedCreep::creep(), 0.3, 50);
	m->waves.pushBack(wave);
	wave = NULL;
	wave = Wave::create()->initWithCreep(StrongGreenCreep::creep(),1.0,5);
	m->waves.pushBack(wave);
	wave = NULL;
}

Wave* GameLayer::getCurrentWave()
{
	DataModel *m = DataModel::getModel();
	Wave * wave = (Wave *)m->waves.at(this->currentLevel);

	return wave;
}

Wave* GameLayer::getNextWave()
{
	DataModel *m = DataModel::getModel();

	this->currentLevel++;

	if (this->currentLevel > 1)
		this->currentLevel = 0;

	Wave * wave = (Wave *)m->waves.at(this->currentLevel);

	return wave;
}

void GameLayer::addWaypoint()
{
	DataModel *m = DataModel::getModel();
	auto *objects = this->tileMap->objectGroupNamed("Objects");
	WayPoint *wp = NULL;
	std::string stringWithFormat = "Waypoint";
	int wayPointCounter = 0;
	ValueMap wayPoint;
	wayPoint = objects->objectNamed(stringWithFormat + std::to_string(wayPointCounter));
	while (wayPoint.begin()!= wayPoint.end())
	{
		int x = wayPoint.at("x").asInt();
		int y = wayPoint.at("y").asInt();
		wp = WayPoint::create();
		wp->setPosition(ccp(x, y));
		m->waypoints.pushBack(wp);
		wayPointCounter++;
		wayPoint = objects->objectNamed(stringWithFormat + std::to_string(wayPointCounter));
	}
	wp = NULL;
}

void GameLayer::addTarget()
{

	DataModel *m = DataModel::getModel();
	Wave* wave = this->getCurrentWave();
	if (wave->totalCreeps < 0) {
		return;
	}
	wave->totalCreeps--;

	Creep *target = NULL;
	int random = CCRANDOM_0_1() * 2;
	if (random == 0)
	{
		target = FastRedCreep::creep();
	}
	else
	{
		target = StrongGreenCreep::creep();
	}

	WayPoint *waypoint = target->getCurrentWaypoint();
	target->setPosition(waypoint->getPosition());
	waypoint = target->getNextWaypoint();
	this->addChild(target, 1);

	int moveDuration = target->moveDuration;
	auto actionMove = CCMoveTo::create(moveDuration, waypoint->getPosition());
	auto actionMoveDone = CallFuncN::create(this, callfuncN_selector(GameLayer::FollowPath));
	target->runAction(CCSequence::create(actionMove, actionMoveDone, NULL));
	target->tag = 1;
	m->targets.pushBack(target);
}

Point GameLayer::tileCoordForPosition(Point position)
{
	int x = position.x / this->tileMap->getTileSize().width;
	int y = ((this->tileMap->getMapSize().height * this->tileMap->getTileSize().height) - position.y) / this->tileMap->getTileSize().height;
	return ccp(x, y);
}

bool GameLayer::canBuildOnTilePosition(Point pos)
{
	Point towerLoc = this->tileCoordForPosition(pos);
	int tileGid = this->background->getTileGIDAt(towerLoc);
	CCLOG("tileGid %d",tileGid);
	Value props = this->tileMap->getPropertiesForGID(tileGid);
	if(props.isNull()){
		return false;
	}
	ValueMap map = props.asValueMap();

	int type_int;
	if (map.size() == 0)
	{
		type_int = 0;
	}
	else
	{
		type_int = map.at("buildable").asInt();
	}

	if (1 == type_int)
	{
		return true;
	}
	return false;
}

void GameLayer::addTower(Point pos,String imageName)
{
	DataModel *m = DataModel::getModel();
	Tower *target = NULL ;
	Point towerLoc = this->tileCoordForPosition(pos);

	int tileGid = this->background->tileGIDAt(towerLoc);
	Value props = this->tileMap->propertiesForGID(tileGid);
	ValueMap map = props.asValueMap();

	int type_int = map.at("buildable").asInt();

	if (1 == type_int) 
	{   
		if(imageName.compare("MachineGunTurret.png")==0){
			target = TowerSpeed::towerSpeed();
			target->setPosition(ccp((towerLoc.x * 32) + 16, this->tileMap->getContentSize().height - (towerLoc.y * 32) - 16));
			this->addChild(target,1);
			target->setTag(1);
			m->towers.pushBack(target);
		}else{
			target = TowerDamage::towerDamage();
			target->setPosition(ccp((towerLoc.x * 32) + 16, this->tileMap->getContentSize().height - (towerLoc.y * 32) - 16));
			this->addChild(target,1);
			target->setTag(1);
			m->towers.pushBack(target);

		}

	}
	else 
	{
		log("Tile Not Buildable");
	}
}

void GameLayer::gameLogic(float dt)
{
	DataModel *m = DataModel::getModel();
	Wave * wave = this->getCurrentWave();
	static double lastTimeTargetAdded = 0;

	double now = 0;
	if (lastTimeTargetAdded == 0 || now - lastTimeTargetAdded >= wave->spawnRate) 
	{
		this->addTarget();
		lastTimeTargetAdded = now;
	}
}

void GameLayer::update(float dt)
{
	DataModel *m = DataModel::getModel();
	Vector<Projectile*> projectilesToDelete;

	for (Projectile *projectile : m->projectiles) 
	{
		Rect projectileRect = Rect(projectile->getPositionX() - (projectile->getContentSize().width / 2),
			projectile->getPositionY() - (projectile->getContentSize().height / 2),
			projectile->getContentSize().width,
			projectile->getContentSize().height);

		Vector<Creep*> targetsToDelete;

		for (Creep *target : m->targets) 
		{
			Rect targetRect = Rect(target->getPositionX() - (target->sprite->getContentSize().width / 2),
				target->getPositionY() - (target->sprite->getContentSize().height / 2),
				target->sprite->getContentSize().width,
				target->sprite->getContentSize().height);

			if (projectileRect.intersectsRect(targetRect)) 
			{
				projectilesToDelete.pushBack(projectile);

				Creep *creep = target;
				creep->curHp -= 1;

				if (creep->curHp <= 0) 
				{
					targetsToDelete.pushBack(creep);
					//kill one creep get gold
					GAMEDATA::getInstance()->setPlayerGold(GAMEDATA::getInstance()->getPlayerGold()+10);
				}
				break;
			}
		}

		for (Creep *target : targetsToDelete)
		{
			m->targets.eraseObject(target);
			this->removeChild(target, true);
		}		
	}

	for (Projectile *projectile : projectilesToDelete)
	{
		m->projectiles.eraseObject(projectile);
		this->removeChild(projectile,true);
	}

	if(GAMESTATE::getInstance()->getGameOver()==true){
		Director::getInstance()->replaceScene(TransitionFade::create(1,GameOverScene::create()));
	}
}

Point GameLayer::boundLayerPos(Point newPos)
{
	Size winSize = CCDirector::getInstance()->getWinSize();
	Point retval = newPos;
	retval.x = MIN(retval.x, 0);
	retval.x = MAX(retval.x, tileMap->getContentSize().width + winSize.width);
	retval.y = MIN(0, retval.y);
	retval.y = MAX(tileMap->getContentSize().height + winSize.height, retval.y);
	return retval;
}