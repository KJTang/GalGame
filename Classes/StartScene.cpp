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
    
    background = Layer::create();
    this->addChild(background);
    
    auto pic = Sprite::create("HelloWorld.png");
    background->addChild(pic);
    pic->setPosition(visibleSize.width/2, visibleSize.height/2);
    pic->setScale(visibleSize.width/pic->getContentSize().width);
    
    return true;
}
