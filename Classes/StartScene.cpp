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
#include "MenuLayer.h"

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
    // menu
    auto layer = MenuLayer::create();
    this->addChild(layer);
    // black
    black = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);
    this->addChild(black);
    black->setOpacity(0);

//    // data test
//    DataController::getInstance()->test();
    
//    // test
//    auto sprite = Sprite::create("ch01.png");
//    this->addChild(sprite);
//    sprite->setScale(0.5);
//    sprite->setPosition(visibleSize.width*0.5, visibleSize.height*0.5);
//    sprite->setOpacity(0);
//    sprite->runAction(Sequence::create(
//                                       FadeIn::create(3),
//                                       FadeOut::create(3),
//                                       CallFunc::create([=]()
//                                                        {
//                                                            sprite->removeFromParentAndCleanup(true);
//                                                        }),
//                                       NULL));
    
    return true;
}
