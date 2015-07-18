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
    startBtn->setPosition(Point(visibleSize.width*0.25, visibleSize.height/2));
    startBtn->setCallbackFunc([](){
        log("start Game");
        GameController::getInstance()->enterGameScene();
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
    auto choiceTable = ChoiceTableLayer::create();
    this->addChild(choiceTable);
    
    choiceTable->setChoiceNumber(4);
    
    choiceTable->setChoiceContent(0, "选项一");
    choiceTable->setChoiceContent(1, "选项二");
    choiceTable->setChoiceContent(2, "选项三");
    choiceTable->setChoiceContent(3, "选项四");
    
    choiceTable->setChoiceChoosable(2, false);
    
    choiceTable->showChoiceTable();
    return true;
}
