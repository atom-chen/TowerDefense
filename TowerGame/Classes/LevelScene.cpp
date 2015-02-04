#include "LevelScene.h"
#include "LevelLayer.h"
#include "LevelSelectPage.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;
using namespace CocosDenshion; 

#define LAYER_NUMBER (3)

LevelScene* LevelScene::instance;

LevelScene *LevelScene::getInstance()
{
    if(instance != NULL){
        return instance;
    }
    return  NULL;
}

bool LevelScene::init()  
{
    if (!Scene::init())
	{
		return false;
	}
    instance = this;
    
    Size size = Director::getInstance()->getWinSize();

	Sprite* spritebg =Sprite::create("playbg.png");
	spritebg->setPosition(Point(size.width / 2,size.height / 2));
	addChild(spritebg);

	//scrollView效果的关卡选择界面
    LevelLayer* scrollView = LevelLayer::create();
    for (int i=0; i<LAYER_NUMBER; ++i) {
        if (0==i) {
            auto page = LevelSelectPage::create("selectLevelbg.png", i);
            page->setTag(i);
            scrollView->addNode(page);
        }else if(1==i){
            auto page = LevelSelectPage::create("selectLevelbg1.png", i);
            page->setTag(i);
            scrollView->addNode(page);
        }else if(2==i){
            auto page = LevelSelectPage::create("selectLevelbg2.png", i);
            page->setTag(i);
            scrollView->addNode(page);
        }
    }                     
    this->addChild(scrollView);
	//气泡背景
    auto width = Sprite::create("page_mark2.png")->getContentSize().width;
    auto posX = (size.width - width * LAYER_NUMBER) / 2;
    for(int i =0; i < LAYER_NUMBER; i++)
    {
        Sprite* sprite =Sprite::create("page_mark2.png");
        sprite->setPosition(Point(posX + i * width, size.height / 7));
        addChild(sprite);
    }
    //当前气泡    
    Sprite* spriteMark =Sprite::create("page_mark1.png");
    spriteMark->setPosition(Point(posX, size.height / 7));
    spriteMark->setTag(888);
    addChild(spriteMark);

    ParticleSystem* m_emitter1 = ParticleSystemQuad::create("snow.plist");
    m_emitter1->retain();
    ParticleBatchNode *batch = ParticleBatchNode::createWithTexture(m_emitter1->getTexture());
    batch->addChild(m_emitter1);
    m_emitter1->setPosition(Point(size.width/2, size.height));
    addChild(batch, 10);
    m_emitter1->release();
      
    return true;
}  