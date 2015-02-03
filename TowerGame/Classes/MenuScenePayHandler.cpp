#include "MenuScenePayHandler.h"
#include "GameLayer.h"
#include "GameData.h"

static MenuScenePayHandler* _instance = nullptr;

MenuScenePayHandler* MenuScenePayHandler::getInstance()
{
	if (!_instance)
	{
		_instance = new MenuScenePayHandler();
	}
	return _instance;
}

void MenuScenePayHandler::payCallback(int requestId,int resultId){
	if(resultId == 0){
	//request_id = requestId;
	switch (requestId)
	{
	case 1:

		break;
	case 2:
		
		break;
	case 3:
		
		break;
	case 4:
		
		break;
	case 5:
		break;

		break;
	default:
		break;
	 }
  }
}

