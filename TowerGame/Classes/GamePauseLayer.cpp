#include "GamePauseLayer.h"
#include "CallAndroidMethod.h"
#include "Audio.h"
#include "SimpleAudioEngine.h"
#include "GameData.h"
#include "GameState.h"

using namespace cocos2d;

GamePauseLayer* GamePauseLayer::create(){
	GamePauseLayer* ret = new GamePauseLayer();
	if(ret && ret->init()){
		ret->autorelease();
		return ret;
	}
	CC_SAFE_DELETE(ret);
	return nullptr;
}

bool GamePauseLayer::init(){
	if(!Layer::init()){
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* background = Sprite::create("pause_agem_bg.png");
	background->setPosition(visibleSize.width/2,visibleSize.height/2);
	this->addChild(background,0);

	/*Sprite* prop_des = Sprite::create("props_describe.png");
	prop_des->setPosition(60,650);
	prop_des->setAnchorPoint(Point(0,0.5));
	this->addChild(prop_des,0);*/

	//MenuItemImage* payBtn = MenuItemImage::create(
	//	"game_pause_buy_gold.png","game_pause_buy_gold.png",CC_CALLBACK_0(GamePauseLayer::payProps,this)
	//	);
	//Menu* payMenu = Menu::create(payBtn, NULL);
	//payMenu->alignItemsHorizontally();
	//payMenu->setPosition(240,400);
	//this->addChild(payMenu,0);
	MenuItemImage* exitBtn = MenuItemImage::create(
		"exit_normal.png","exit_click.png",CC_CALLBACK_0(GamePauseLayer::goBack,this)
		);

	//auto scaleSmall = ScaleTo::create(0.8,0.7);
	//auto scaleBig = ScaleTo::create(0.8,1);
	//auto delay = DelayTime::create(0);
	//auto seq2 = Sequence::create(scaleSmall,delay,scaleBig,delay->clone(),NULL);
	//payBtn->runAction(RepeatForever::create(seq2));

	MenuItemImage* soundBtnOn = MenuItemImage::create("sound_effect_on.png","sound_effect_on.png");
	MenuItemImage* soundBtnOff = MenuItemImage::create("sound_effect_close.png","sound_effect_close.png");  
	MenuItemToggle* soundTog = MenuItemToggle::createWithTarget(this,menu_selector(GamePauseLayer::getSoudState),soundBtnOn,soundBtnOff,NULL);  
	/*if (GAMEDATA::getInstance()->getSoundEffect())  
        {  
            soundTog->setSelectedIndex(0);  
        }   
        else  
        {  
            soundTog->setSelectedIndex(1);  
        }  */
	MenuItemImage* musicBtnOn = MenuItemImage::create("bg_music_open.png","bg_music_open.png");
	MenuItemImage* musicBtnOff = MenuItemImage::create("bg_music_close.png","bg_music_close.png");  
	MenuItemToggle* musicTog = MenuItemToggle::createWithTarget(this,menu_selector(GamePauseLayer::getMusicState),musicBtnOn,musicBtnOff,NULL);  
	 if (CocosDenshion::SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())  
        {  
            musicTog->setSelectedIndex(0);  
        }   
        else  
        {  
            musicTog->setSelectedIndex(1);  
        }  

	Menu* otherMenu = Menu::create(soundTog,musicTog,exitBtn, NULL);
	otherMenu->alignItemsHorizontallyWithPadding (25);
	otherMenu->setPosition(visibleSize.width/2+65,visibleSize.height/2);
	this->addChild(otherMenu,2);

		MenuItemImage* resumeBtn = MenuItemImage::create(
		"continue_normal.png","continue_click.png",CC_CALLBACK_0(GamePauseLayer::ResumeGame,this)
		);
	auto scale1 = ScaleTo::create(1,1.25);
	auto scale2 = ScaleTo::create(1,1);
	auto seq =Sequence::create(scale1,scale2,nullptr);
	resumeBtn->runAction(RepeatForever::create(seq));
	Menu* resumeMenu = Menu::create(resumeBtn, NULL);
	resumeMenu->alignItemsHorizontallyWithPadding (50);
	resumeMenu->setPosition(visibleSize.width/2-130,visibleSize.height/2);
	this->addChild(resumeMenu,2);
	return true;
}

void GamePauseLayer::payProps(){
	Audio::getInstance()->playSound("sound/click.ogg");
	CallAndroidMethod::getInstance()->pay(11);
}

void GamePauseLayer::goBack(){
	GAMESTATE::getInstance()->setGamePause(false);
	Audio::getInstance()->playSound("sound/click.ogg");
	this->removeFromParentAndCleanup(true);
}

void GamePauseLayer::ResumeGame(){
		GAMESTATE::getInstance()->setGamePause(false);
		Audio::getInstance()->playSound("sound/click.ogg");;
		this->removeFromParentAndCleanup(true);
	}

void GamePauseLayer::getSoudState(CCObject* pSender){
    CCMenuItemToggle* temp=(CCMenuItemToggle*)pSender;  
    if (temp->getSelectedIndex()==1)  
    {   
	    Audio::getInstance()->playSound("sound/click.ogg");
		/*GAMEDATA::getInstance()->setSoundEffect(false);
		GAMEDATA::getInstance()->saveSoundEffect();*/
    }  
    if (temp->getSelectedIndex()==0)  
    {  
	//	GAMEDATA::getInstance()->setSoundEffect(true);
    }  
}

void GamePauseLayer::getMusicState(CCObject* pSender){
    CCMenuItemToggle* temp=(CCMenuItemToggle*)pSender;  
    if (temp->getSelectedIndex()==1)  
    {   
		 Audio::getInstance()->playSound("sound/click.ogg");;
        CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic(); 
		GAMEDATA::getInstance()->setMusicState(false);

    }  
    if (temp->getSelectedIndex()==0)  
    {  
        CocosDenshion::SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic(); 
		GAMEDATA::getInstance()->setMusicState(true);
    }  
}
