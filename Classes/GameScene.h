#pragma once

#include "cocos2d.h"
#include "ScriptController.h"
#include "GameController.h"

using namespace cocos2d;

class GameScene : public Scene
{
private:
	Size visibleSize;
public:
	GameScene();
	~GameScene();

	virtual bool init();
    CREATE_FUNC(GameScene);
};
