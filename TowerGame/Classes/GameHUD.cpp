#include "GameHUD.h"
#include "GameData.h"


GameHUD* GameHUD::create(GameLayer* layer){
	GameHUD* ret = new GameHUD();
	if(ret && ret->init(layer)){
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}


bool GameHUD::init(GameLayer* layer)
{
	if (!Node::init()) 
	{
		return false;
	}
	m_layer = layer;
	Size winSize = CCDirector::getInstance()->getWinSize();
	// Draw the background of the game HUD
	CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_RGB565);
	background = Sprite::create("hud.png");
	background->setScaleX (2);
	background->setAnchorPoint(ccp(0, 0));
	this->addChild(background);
	CCTexture2D::setDefaultAlphaPixelFormat(kCCTexture2DPixelFormat_Default);

	// Load the images of the towers we'll have and draw them to the game HUD layer
	Vector<String*> images;
	images.pushBack(StringMake("machinegunturret.png"));
	images.pushBack(StringMake("machinegunturret.png"));
	images.pushBack(StringMake("tower_damage.png"));
	images.pushBack(StringMake("tower_damage.png"));
	for (int i = 0; i < images.size(); ++i)
	{
		String* image = images.at(i);
		auto *sprite = Sprite::create(image->getCString());
		sprite->setName(image->getCString());
		float offsetFraction = ((float)(i + 1)) / (images.size() + 1);
		sprite->setPosition(ccp(winSize.width*offsetFraction, 35));
		this->addChild(sprite);
		movableSprites.pushBack(sprite);
	}
	return true;
}


void GameHUD::onEnter()
{
	Node::onEnter();

	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameHUD::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameHUD::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameHUD::onTouchEnded, this);

	auto dispatcher = Director::getInstance()->getEventDispatcher();

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	
}

bool GameHUD::onTouchBegan(Touch *touch, Event *event)
{
	if(!background->getBoundingBox().containsPoint(touch->getLocation())){
	    return false; 
	}
	Point touchLocation = this->convertToWorldSpace(this->convertTouchToNodeSpace(touch));

	Sprite * newSprite = NULL;
	for (Sprite* sprite : this->movableSprites)
	{
		Rect pos_rect = Rect((sprite->getPositionX()-sprite->getContentSize().width/2), (sprite->getPositionY()-sprite->getContentSize().height/2), sprite->getContentSize().width, sprite->getContentSize().height);
		float xMin = pos_rect.getMinX();
		float xMax = pos_rect.getMaxX();
		float yMIn = pos_rect.getMinY();
		float yMax = pos_rect.getMaxY();
		if (pos_rect.containsPoint(touchLocation))
		{
			GAMEDATA *m = GAMEDATA::getInstance();
			//m.gestureRecognizer.enabled = NO;
			selSpriteRange = Sprite::create("range.png");
			selSpriteRange->setScale(4);
			this->addChild(selSpriteRange, -1);
			selSpriteRange->setPosition(sprite->getPosition());

			newSprite = Sprite::createWithTexture(sprite->getTexture()); //sprite;
			newSprite->setPosition(sprite->getPosition());
			selSprite = newSprite;
			selSprite->setName(sprite->getName());
			this->addChild(newSprite);
		}
	}	
	return true;
}

void GameHUD::onTouchMoved(Touch* touch,Event* event) 
{
	Point touchLocation = this->convertToWorldSpace(this->convertTouchToNodeSpace(touch));

	Point oldTouchLocation = touch->getPreviousLocationInView();
	oldTouchLocation = Director::getInstance()->convertToGL(oldTouchLocation);
	oldTouchLocation = this->convertToNodeSpace(oldTouchLocation);

	Point translation = ccpSub(touchLocation,oldTouchLocation);

	if (selSprite) 
	{
		Point newPos = selSprite->getPosition()+translation;
		selSprite->setPosition(newPos);
		selSpriteRange->setPosition(newPos);

		Point touchLocationInGameLayer = m_layer->convertTouchToNodeSpace(touch);

		BOOL isBuildable =m_layer->canBuildOnTilePosition(touchLocationInGameLayer);
		if (isBuildable) 
		{
			selSprite->setOpacity(200);
		}
		else 
		{
			selSprite->setOpacity(50);
		}
	}
}

void GameHUD::onTouchEnded(Touch* touch, Event* event)
{
	
	Point touchLocation = this->convertTouchToNodeSpace(touch);
	if (selSprite) 
	{
		Rect backgroundRect = Rect(background->getPositionX(),
			background->getPositionY(),
			background->getContentSize().width,
		 	background->getContentSize().height);

		if (!backgroundRect.containsPoint(touchLocation) && m_layer->canBuildOnTilePosition(touchLocation))
		{
			Point touchLocationInGameLayer = m_layer->convertTouchToNodeSpace(touch);
			m_layer->addTower(touchLocationInGameLayer,selSprite->getName());
		}

		this->removeChild(selSprite,true);
		selSprite = NULL;
		this->removeChild(selSpriteRange,true);
		selSpriteRange = NULL;
	}
}

 