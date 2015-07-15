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
            currentState = STATE_START_SCENE;
            break;
        case STATE_START_SCENE:
            break;
        default:
            //
            break;
    }
}

void GameController::enterConfigScene()
{
    switch (currentState) {
        case STATE_GAME_SCENE:
            // pop game scene
            currentState = STATE_CONFIG_SCENE;
            break;
        default:
            Director::getInstance()->replaceScene(ConfigScene::create());
            currentState = STATE_CONFIG_SCENE;
            break;
    }
}