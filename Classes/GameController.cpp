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
        case STATE_PREPARING: {
            Director::getInstance()->runWithScene(StartScene::create());
            break;
        }
        case STATE_GAME_SCENE: {
            Director::getInstance()->purgeCachedData();
            Director::getInstance()->replaceScene(TransitionFade::create(1, StartScene::create()));
            break;
        }
        case STATE_CONFIG_SCENE: {
            Director::getInstance()->popScene();
            break;
        }
        default:
            //
            break;
    }
    currentState = STATE_START_SCENE;
}

void GameController::enterGameScene()
{
    switch (currentState) {
        case STATE_START_SCENE: {
            Director::getInstance()->purgeCachedData();
            GameScene::getInstance()->clear();
            Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::getInstance()));
            GameScene::getInstance()->startNewGame();
            break;
        }
            
        default:
            break;
    }
    currentState = STATE_GAME_SCENE;
}

void GameController::enterConfigScene()
{
//    Director::getInstance()->purgeCachedData();
    Director::getInstance()->pushScene(TransitionFade::create(1, ConfigScene::create()));
    currentState = STATE_CONFIG_SCENE;
}

void GameController::exitGame()
{
    // used on android
//    Director::getInstance()->end();
    // used on iOS
    exit(0);
}

void GameController::playBGM(std::string filename)
{
    CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(filename.c_str());
}

void GameController::pauseBGM()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void GameController::resumeBGM()
{
    CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}