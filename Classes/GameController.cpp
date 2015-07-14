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
    return true;
}

StartScene* GameController::createStartScene()
{
    return StartScene::create();
}