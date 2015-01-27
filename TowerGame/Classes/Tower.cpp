#include "Tower.h"
#include "DataModel.h"


Creep* Tower::getClosesTarget()
{
	Creep *closestCreep = NULL;
	double maxDistant = 99999;

	DataModel *m = DataModel::getModel();

	for (Sprite *target : m->targets) 
	{
		Creep *creep = (Creep *)target;
		double curDistance = ccpDistance(this->getPosition(), creep->getPosition());

		if (curDistance < maxDistant) {
			closestCreep = creep;
			maxDistant = curDistance;
		}
	}
	if (maxDistant < this->range)
		return closestCreep;
	return NULL;
}