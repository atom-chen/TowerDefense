#include "DataModel.h"

USING_NS_CC;

DataModel* DataModel::m_pInstance=nullptr;

DataModel* DataModel::getModel()
{
	if (m_pInstance == NULL)
		m_pInstance = new DataModel();
	return m_pInstance;
}

void DataModel::clean(){
	waypoints.clear();
	targets.clear();
	waves.clear();
	towers.clear();
	projectiles.clear();

}