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
    this->addChild(background);
    
    auto pic = Sprite::create("HelloWorld.png");
    background->addChild(pic);
    pic->setPosition(Point(visibleSize.width/2, visibleSize.height/2));
    pic->setScale(visibleSize.width/pic->getContentSize().width);
    
    auto button1 = ButtonSprite::create("CloseNormal.png");
    background->addChild(button1);
    button1->setScale(3.5);
    button1->setPosition(Point(visibleSize.width*0.75, visibleSize.height/2));
    button1->setCallbackFunc([](){
        log("back to StartScene");
        GameController::getInstance()->enterStartScene();
    });
    
    this->setVisible(false);
    
    return true;
}