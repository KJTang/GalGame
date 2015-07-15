//
//  ConfigScene.cpp
//  Test
//
//  Created by KJTang on 15/7/15.
//
//

#include "ConfigScene.h"

ConfigScene::ConfigScene(){}

ConfigScene::~ConfigScene(){}

bool ConfigScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    background = Layer::create();
    
    auto pic = Sprite::create("HelloWorld.png");
    background->addChild(pic);
    pic->setScale(visibleSize.width/pic->getContentSize().width);
    
    return true;
}
