//
//  GameController.cpp
//  Test
//
//  Created by KJTang on 15/7/14.
//
//

#include "GameController.h"

GameController* GameController::sharedGameController = NULL;

GameController::GameController(){}

GameController::~GameController(){}

bool GameController::init()
{
    currentState = STATE_PREPARING;
    return true;
}

void GameController::enterStartScene()
{
    switch (currentState) {
        case STATE_PREPARING:
            Director::getInstance()->runWithScene(StartScene::create());
            break;
        case STATE_START_SCENE:
            break;
        case STATE_CONFIG_SCENE:
            Director::getInstance()->popScene();
            break;
        default:
            //
            break;
    }
    currentState = STATE_START_SCENE;
}

void GameController::enterConfigScene()
{
//    Director::getInstance()->purgeCachedData();
    Director::getInstance()->pushScene(TransitionFade::create(1, ConfigScene::create()));
    currentState = STATE_CONFIG_SCENE;
}