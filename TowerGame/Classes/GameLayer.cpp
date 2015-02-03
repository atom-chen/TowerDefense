#include "GameLayer.h"
#include "TowerBase.h"
#include "TowerSpeed.h"
#include "TowerDamage.h"
#include "GameOverScene.h"
#include "TopMenu.h"
#include <Vector>
#include <string>
#include "GameData.h"
#include "GameState.h"
#include "GamePauseLayer.h"


USING_NS_CC;


bool GameLayer::init()
{
	if (!Layer::init()) 
	{
		return false;
	}
	GAMEDATA::getInstance()->initLevelInfo(GAMEDATA::getInstance()->getCurrentLevel());
	GAMESTATE::getInstance()->reset();
	GAMEDATA::getInstance()->clean();
	//add HUD and init DataModle
	auto myGameHUD = GameHUD::create(this);
	this->addChild(myGameHUD, 1);
	std::string strName ="map_level_"+cocos2d::String::createWithFormat("%d",GAMEDATA::getInstance()->getCurrentLevel())->_string+".tmx";
	this->tileMap = TMXTiledMap::create(strName);
	this->background = tileMap->layerNamed("Background");
	this->background->setAnchorPoint(ccp(0, 0));
	this->addChild(tileMap, 0);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	//add topMenu to GameLayer
	auto TopMenu = TopMenu::getInstance();
	this->addChild(TopMenu,2);

	//add waypoint and waves
	this->addWaypoint();
	this->addWaves();

	//add prop bomb
	auto bomb = MenuItemImage::create("bomb.png","bomb.png",CC_CALLBACK_0(GameLayer::usePropBomb,this));
	auto  bombBtn =  Menu::create(bomb,NULL);
	bombBtn->setPosition(Point(visibleSize.width/2,visibleSize.height/2-200));
	this->addChild(bombBtn,2);

	//add game pause button
	auto pause = MenuItemImage::create("pause.png","pause.png",CC_CALLBACK_0(GameLayer::showPauseLayer,this));
	auto pauseBtn =Menu::create(pause,NULL);
	pauseBtn->setPosition(Point(visibleSize.width/2-350,visibleSize.height/2+200));
	this->addChild(pauseBtn,2);

	this->scheduleUpdate();
	this->schedule(schedule_selector(GameLayer::gameLogic), 1.0f);
	this->position = ccp(-228, -122);

	return true;
}

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


void GameLayer::addWaves()
{
	GAMEDATA *m = GAMEDATA::getInstance();
	Wave *wave = NULL;
	wave = Wave::create()->initWithCreep(FastRedCreep::creep(), 0.3, 2);
	m->waves.pushBack(wave);
	wave = NULL;
	wave = Wave::create()->initWithCreep(StrongGreenCreep::creep(),1.0,5);
	m->waves.pushBack(wave);
	wave = NULL;
}

Wave* GameLayer::getCurrentWave()
{
	GAMEDATA *m = GAMEDATA::getInstance();
	Wave * wave = (Wave *)m->waves.at(m->getCurrentWave());
	return wave;
}


void GameLayer::addWaypoint()
{
	GAMEDATA *m = GAMEDATA::getInstance();
	auto *objects = this->tileMap->objectGroupNamed("Objects");
	WayPoint *wp = NULL;
	std::string stringWithFormat = "Waypoint";
	int wayPointCounter = 0;
	ValueMap wayPointMap;
	char countBuf[16] = "";
    sprintf(countBuf, "%d", wayPointCounter);
	wayPointMap = objects->objectNamed(stringWithFormat + countBuf);
	while (wayPointMap.begin()!= wayPointMap.end())
	{
		int x = wayPointMap.at("x").asInt();
		int y = wayPointMap.at("y").asInt();
		wp = WayPoint::create();
		wp->setPosition(Point(x, y));
		m->waypoints.pushBack(wp);
		wayPointCounter++;
		char countBuf2[16] = "";
        sprintf(countBuf2, "%d", wayPointCounter);
		wayPointMap = objects->objectNamed(stringWithFormat + countBuf2);
	}
	wp = NULL;
}

void GameLayer::addTarget()
{

	GAMEDATA *m = GAMEDATA::getInstance();
	Wave* wave = this->getCurrentWave();
	if (wave->totalCreeps <= 0) {
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
	GAMEDATA *m = GAMEDATA::getInstance();
	TowerBase *target = NULL ;
	Point towerLoc = this->tileCoordForPosition(pos);

	int tileGid = this->background->tileGIDAt(towerLoc);
	Value props = this->tileMap->propertiesForGID(tileGid);
	ValueMap map = props.asValueMap();
	int type_int = map.at("buildable").asInt();
	if (1 == type_int) 
	{   
		if(imageName.compare("machinegunturret.png")==0){
			target = TowerSpeed::create();
			target->setPosition(ccp((towerLoc.x * 32) + 16, this->tileMap->getContentSize().height - (towerLoc.y * 32) - 16));
			this->addChild(target,1);
			target->setTag(1);
			m->towers.pushBack(target);

		}else{
			target = TowerDamage::create();
			target->setPosition(ccp((towerLoc.x * 32) + 16, this->tileMap->getContentSize().height - (towerLoc.y * 32) - 16));
			this->addChild(target,1);
			target->setTag(1);
			m->towers.pushBack(target);
		}
		auto money=GAMEDATA::getInstance()->getPriceByImageName(imageName);
		GAMEDATA::getInstance()->setPlayerGold( GAMEDATA::getInstance()->getPlayerGold()-money);
		GAMESTATE::getInstance()->setNeedRefesh(true);
	}
	else 
	{
		log("Tile Not Buildable");
	}
}

void GameLayer::gameLogic(float dt)
{
	GAMEDATA *m = GAMEDATA::getInstance();
	Wave * wave = this->getCurrentWave();
	static double lastTimeTargetAdded = 0;
	double now = 0;
	if (lastTimeTargetAdded == 0 || now - lastTimeTargetAdded >= wave->spawnRate) 
	{
		this->addTarget();
		lastTimeTargetAdded = now;
	}
	if(m->targets.size()==0&&!GAMESTATE::getInstance()->getGameOver()){
		auto num=m->getCurrentWave();
		num++;
		if(num>=(m->waves.size())){
			GAMESTATE::getInstance()->setGameOver(true);
			GAMESTATE::getInstance()->setLevelResult(true);
			return;
		}
		m->setCurrentWave(num);
	}
}

void GameLayer::update(float dt)
{
	GAMEDATA *m = GAMEDATA::getInstance();
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
				if(projectile->getBulletType()==BulletType::SPEED){
					creep->curHp -= 1;
				}
				else if(projectile->getBulletType()==BulletType::DAMAGE){
					creep->curHp -= 10;
				}
				if (creep->curHp <= 0) 
				{
					targetsToDelete.pushBack(creep);
					//kill one creep get gold
					GAMEDATA::getInstance()->setPlayerGold(GAMEDATA::getInstance()->getPlayerGold()+10);
					GAMESTATE::getInstance()->setNeedRefesh(true);
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



//use prop bomb
void GameLayer::usePropBomb(){
	clearAllCreep();
}

//show pause game layer
void GameLayer::showPauseLayer(){
	auto pauseLayer = GamePauseLayer::create();
	this->addChild(pauseLayer,3);

}

//player revive
void GameLayer::playerRevive(){
	clearAllCreep();
	GAMEDATA::getInstance()->initLifeValue(GAMEDATA::getInstance()->getCurrentLevel());
	GAMESTATE::getInstance()->setNeedRefesh(true);
}


//clear all creep in scene
void GameLayer::clearAllCreep(){

	GAMEDATA *m = GAMEDATA::getInstance();
	Vector<Creep*> targetsToDelete=m->targets;
	for (Creep *target : targetsToDelete)
	{
		m->targets.eraseObject(target);
		this->removeChild(target, true);
	}		

}

// tower levelup
void GameLayer::towerLevelUp(){
	GAMEDATA::getInstance()->doubleTowerFrequency();
	GAMEDATA::getInstance()->doubleTowerRange();
}
