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
    
    auto pic = GyroBackground::create("title/title.pic", 1.5);
    backgroundLayer->addChild(pic, -1);
    
    auto startBtn = ButtonSprite::create("title/start.pic");
    backgroundLayer->addChild(startBtn);
    startBtn->setScale(1.5);
    startBtn->setAnchorPoint(Point(0, 0));
    startBtn->setPosition(Point(visibleSize.width*0.70, visibleSize.height*0.70));
    startBtn->setCallbackFunc([](){
        log("start Game");
        GameController::getInstance()->enterGameScene();
    });
    auto loadBtn = ButtonSprite::create("title/load.pic");
    backgroundLayer->addChild(loadBtn);
    loadBtn->setScale(1.5);
    loadBtn->setAnchorPoint(Point(0, 0));
    loadBtn->setPosition(Point(visibleSize.width*0.70, visibleSize.height*0.55));
    loadBtn->setCallbackFunc([](){
        log("load Game");
        GameController::getInstance()->enterGameScene("test");
    });
    auto gallaryBtn = ButtonSprite::create("title/gallary.pic");
    backgroundLayer->addChild(gallaryBtn);
    gallaryBtn->setScale(1.5);
    gallaryBtn->setAnchorPoint(Point(0, 0));
    gallaryBtn->setPosition(Point(visibleSize.width*0.70, visibleSize.height*0.40));
    gallaryBtn->setCallbackFunc([](){
        log("enter GallaryScene");
    });
    auto configBtn = ButtonSprite::create("title/config.pic");
    backgroundLayer->addChild(configBtn);
    configBtn->setScale(1.5);
    configBtn->setAnchorPoint(Point(0, 0));
    configBtn->setPosition(Point(visibleSize.width*0.70, visibleSize.height*0.25));
    configBtn->setCallbackFunc([](){
        log("enter ConfigScene");
        GameController::getInstance()->enterConfigScene();
    });
//    auto exitBtn = ButtonSprite::create("CloseNormal.png");
//    backgroundLayer->addChild(exitBtn);
//    exitBtn->setScale(3.5);
//    exitBtn->setPosition(Point(visibleSize.width*0.75, visibleSize.height/2));
//    exitBtn->setCallbackFunc([](){
//        log("exit");
//        GameController::getInstance()->exitGame();
//    });
//
//    // test
    DataController::getInstance()->test();
    
    return true;
}
