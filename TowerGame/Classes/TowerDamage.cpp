#include "TowerDamage.h"
#include "GameData.h"


bool TowerDamage::init()
{
	if (!TowerBase::init()) 
	{
		return false;
	}
	auto tower= Sprite::create("tower_damage.png");
    this->addChild(tower);
	this->range = 200;
    this->schedule(schedule_selector(TowerDamage::towerLogic), 0.8f);
	return true;
}

void TowerDamage::towerLogic(float dt)
{
	this->target = this->getClosesTarget();

	if (this->target != NULL) 
	{
		// Rotate player to face shooting direction
		Point shootVector = this->target->getPosition() - this->getPosition();
		float shootAngle = ccpToAngle(shootVector);
		float cocosAngle = CC_RADIANS_TO_DEGREES(-1 * shootAngle);

		float rotateSpeed = 0.5 / M_PI;
		float rotateDuration = fabs(shootAngle * rotateSpeed);

		this->runAction(Sequence::create(RotateTo::create(rotateDuration,cocosAngle),NULL));

		this->runAction(Sequence::create(RotateTo::create(rotateDuration, cocosAngle), CallFunc::create(this, callfunc_selector(TowerDamage::finishFiring)), NULL));
	}
}

void TowerDamage::finishFiring()
{
	GAMEDATA *m = GAMEDATA::getInstance();

	if (this->target != NULL && this->target->curHp > 0 && this->target->curHp < 100)
	{
		this->nextProjectile = Projectile::projectile(BulletType::DAMAGE);
		this->nextProjectile->setPosition(this->getPosition());

		this->getParent()->addChild(this->nextProjectile, 1);
		m->projectiles.pushBack(this->nextProjectile);

		float delta = 1.0f;
		Point shootVector = -(this->target->getPosition() - this->getPosition());
		Point normalizedShootVector = ccpNormalize(shootVector);
		Point overshotVector = normalizedShootVector * 320;
		Point offscreenPoint = (this->getPosition() - overshotVector);

		this->nextProjectile->runAction(Sequence::create(MoveTo::create(delta, offscreenPoint), CallFuncN::create(this, callfuncN_selector(TowerDamage::creepMoveFinished)), NULL));

		this->nextProjectile->setTag(2);

		this->nextProjectile = NULL;

	}
}

void TowerDamage::creepMoveFinished(Node* sender)
{
	GAMEDATA *m = GAMEDATA::getInstance();
	Sprite *sprite = (Sprite *)sender;
	this->getParent()->removeChild(sprite,true);

	m->projectiles.eraseObject((Projectile*)sprite);
}

