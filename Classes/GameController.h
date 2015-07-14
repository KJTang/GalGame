//
//  GameController.h
//  Test
//
//  Created by KJTang on 15/7/14.
//
//

#ifndef GameController_cpp
#define GameController_cpp

#include "cocos2d.h"

#include "StartScene.h"

using namespace cocos2d;

class GameController
{
private:
    static GameController* sharedGameController;
    bool init();

private:
    GameController();
public:
    ~GameController();
    
public:
    static GameController* getInstance() {
        if (!sharedGameController) {
            sharedGameController = new GameController();
            sharedGameController->init();
        }
        return sharedGameController;
    }
    
    StartScene* createStartScene();
};

#endif /* GameController_cpp */
