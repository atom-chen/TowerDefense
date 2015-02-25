#ifndef __ENEMYBASE_H__
#define __ENEMYBASE_H__

#include <iostream>
#include "cocos2d.h"

USING_NS_CC;

class EnemyBase : public Sprite3D
{
public:
    EnemyBase();
    ~EnemyBase();
    virtual bool init() override;
    CREATE_FUNC(EnemyBase);
    
	virtual void update(float delta);
    Animation* createAnimation(std::string prefixName, int framesNum, float delay);
    virtual void changeDirection(float dt){};
    virtual void enemyExpload(){};
    Node* currPoint();
    Node* nextPoint();
    void runFllowPoint();
	Sprite * getHpBarBg();
    void setPointsVector(Vector<Node*> points);
	void createAndSetHpBar();
private:
    Vector<Node*> pointsVector;
    
protected:
    int pointCounter;
    Animation *animationRight;
    Animation *animationLeft;
    Animation *animationExplode;
    CC_SYNTHESIZE(float, runSpeed, RunSpeed);
    CC_SYNTHESIZE(float, maxHp, MaxHp);
    CC_SYNTHESIZE(float, vaule, Vaule);
    CC_SYNTHESIZE(float, currHp, CurrHp);
	CC_SYNTHESIZE(float, hpPercentage, HpPercentage);
    CC_SYNTHESIZE_READONLY(ProgressTimer*, hpBar, HpBar);
    CC_SYNTHESIZE(bool, enemySuccessful, EnemySuccessful);
	Sprite* sprite;
    Sprite * hpBgSprite;
};



#endif 
