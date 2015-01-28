#include "GameScene.h"
#include "GameLayer.h"
#include "DataModel.h"

bool GameScene::init(){
	if(!Scene::init()){
		return false;
	}
	auto layer=GameLayer::create();
	this->addChild(layer);
    auto myGameHUD = GameHUD::shareHUD();
	this->addChild(myGameHUD, 1);
	DataModel* m = DataModel::getModel();
	m->_gameLayer = layer;
	m->_gameHUDLayer = myGameHUD;
	return true;
} 