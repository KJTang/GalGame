//
//  StartScene.cpp
//  Test
//
//  Created by KJTang on 15/7/14.
//
//

#include "StartScene.h"

StartScene::StartScene(){}

StartScene::~StartScene(){}

bool StartScene::init()
{
    if (!Scene::init())
        return false;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    backgroundLayer = Layer::create();
    this->addChild(backgroundLayer);
    
    auto pic = GyroBackground::create("HelloWorld.png", 2);
    backgroundLayer->addChild(pic, -1);
    
    auto startBtn = ButtonSprite::create("CloseNormal.png");
    backgroundLayer->addChild(startBtn);
    startBtn->setScale(3.5);
    startBtn->setPosition(Point(visibleSize.width*0.25, visibleSize.height*0.75));
    startBtn->setCallbackFunc([](){
        log("start Game");
        GameController::getInstance()->enterGameScene();
    });
    auto loadBtn = ButtonSprite::create("CloseNormal.png");
    backgroundLayer->addChild(loadBtn);
    loadBtn->setScale(3.5);
    loadBtn->setPosition(Point(visibleSize.width*0.25, visibleSize.height*0.25));
    loadBtn->setCallbackFunc([](){
        log("load Game");
        GameController::getInstance()->enterGameScene("test");
    });
    auto configBtn = ButtonSprite::create("CloseNormal.png");
    backgroundLayer->addChild(configBtn);
    configBtn->setScale(3.5);
    configBtn->setPosition(Point(visibleSize.width*0.50, visibleSize.height/2));
    configBtn->setCallbackFunc([](){
        log("enter ConfigScene");
        GameController::getInstance()->enterConfigScene();
    });
    auto exitBtn = ButtonSprite::create("CloseNormal.png");
    backgroundLayer->addChild(exitBtn);
    exitBtn->setScale(3.5);
    exitBtn->setPosition(Point(visibleSize.width*0.75, visibleSize.height/2));
    exitBtn->setCallbackFunc([](){
        log("exit");
        GameController::getInstance()->exitGame();
    });

    // test
    DataController::getInstance()->test();
    
    return true;
}
