#include "LevelSelectScene.h"
#include "LevelSelectLayer.h"

bool LevelSelectScene::init(){
	if(!Scene::init()){
		return false;
	}
	auto layer=LevelSelectLayer::create();
	this->addChild(layer);
	return true;
} 