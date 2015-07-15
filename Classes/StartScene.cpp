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
    
    auto pic = GyroBackground::create("HelloWorld.png", 2);
    background->addChild(pic, -1);
    
    auto configBtn = ButtonSprite::create("CloseNormal.png");
    background->addChild(configBtn);
    configBtn->setScale(3);
    configBtn->setPosition(Point(visibleSize.width*0.25, visibleSize.height/2));
    configBtn->setCallbackFunc([](){
        log("try to enter ConfigScene");
        GameController::getInstance()->enterConfigScene();
    });
    auto button2 = ButtonSprite::create("CloseNormal.png");
    background->addChild(button2);
    button2->setScale(3);
    button2->setPosition(Point(visibleSize.width*0.5, visibleSize.height/2));
    button2->setCallbackFunc([](){
        log("test2");
    });
    auto button3 = ButtonSprite::create("CloseNormal.png");
    background->addChild(button3);
    button3->setScale(3);
    button3->setPosition(Point(visibleSize.width*0.75, visibleSize.height/2));
    button3->setCallbackFunc([](){
        log("test3");
    });
    
    return true;
}
