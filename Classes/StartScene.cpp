//
//  StartScene.cpp
//  Test
//
//  Created by KJTang on 15/7/14.
//
//

#include "StartScene.h"

#include "GameController.h"
#include "DataController.h"

#include "GyroBackground.h"

StartScene::StartScene(){}

StartScene::~StartScene(){}

bool StartScene::init()
{
    if (!Scene::init())
        return false;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    log("visibleSize = %.2f, %.2f", visibleSize.width, visibleSize.height);
    
    backgroundLayer = Layer::create();
    this->addChild(backgroundLayer);
    
    auto pic = GyroBackground::create("bg/HelloWorld.png", 1.5);
    backgroundLayer->addChild(pic, -1);
    
    // menu
    menuLayer = MenuLayer::create();
    this->addChild(menuLayer);
    menuLayer->startSceneType();
    // black
    black = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);
    this->addChild(black);
    black->setOpacity(0);
    
    gallaryLayer = GallaryLayer::create();
    this->addChild(gallaryLayer);
        
//    // data test
//    DataController::getInstance()->test();
    
    return true;
}
