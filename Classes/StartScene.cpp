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
    
    auto pic = GyroBackground::create("title/title", 1.5);
    backgroundLayer->addChild(pic, -1);
    
    auto startBtn = ButtonSprite::create("title/start");
    backgroundLayer->addChild(startBtn);
//    startBtn->setScale(1.5);
    startBtn->setAnchorPoint(Point(0, 0));
    startBtn->setPosition(Point(visibleSize.width*0.75, visibleSize.height*0.40));
    startBtn->setCallbackFunc([](){
        log("start Game");
        GameController::getInstance()->enterGameScene();
    });
    auto loadBtn = ButtonSprite::create("title/load");
    backgroundLayer->addChild(loadBtn);
//    loadBtn->setScale(1.5);
    loadBtn->setAnchorPoint(Point(0, 0));
    loadBtn->setPosition(Point(visibleSize.width*0.75, visibleSize.height*0.30));
    loadBtn->setCallbackFunc([](){
        log("load Game");
        GameController::getInstance()->enterGameScene("test");
    });
    auto gallaryBtn = ButtonSprite::create("title/gallary");
    backgroundLayer->addChild(gallaryBtn);
//    gallaryBtn->setScale(1.5);
    gallaryBtn->setAnchorPoint(Point(0, 0));
    gallaryBtn->setPosition(Point(visibleSize.width*0.75, visibleSize.height*0.20));
    gallaryBtn->setCallbackFunc([](){
        log("enter GallaryScene");
    });
    auto configBtn = ButtonSprite::create("title/config");
    backgroundLayer->addChild(configBtn);
//    configBtn->setScale(1.5);
    configBtn->setAnchorPoint(Point(0, 0));
    configBtn->setPosition(Point(visibleSize.width*0.75, visibleSize.height*0.10));
    configBtn->setCallbackFunc([](){
        log("enter ConfigScene");
        GameController::getInstance()->enterConfigScene();
    });
    auto infoBtn = ButtonSprite::create("title/info");
    backgroundLayer->addChild(infoBtn);
//    infoBtn->setScale(1.5);
    infoBtn->setAnchorPoint(Point(0, 0));
    infoBtn->setPosition(Point(visibleSize.width*0.0, visibleSize.height*0.0));
    infoBtn->setCallbackFunc([](){
        log("enter InfoScene");
    });

    
//    // test
    DataController::getInstance()->test();
    
    return true;
}
