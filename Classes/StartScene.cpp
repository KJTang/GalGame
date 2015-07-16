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
    
    auto startBtn = ButtonSprite::create("CloseNormal.png");
    background->addChild(startBtn);
    startBtn->setScale(3.5);
    startBtn->setPosition(Point(visibleSize.width*0.25, visibleSize.height/2));
    startBtn->setCallbackFunc([](){
        log("start Game");
        GameController::getInstance()->enterGameScene();
    });
    auto configBtn = ButtonSprite::create("CloseNormal.png");
    background->addChild(configBtn);
    configBtn->setScale(3.5);
    configBtn->setPosition(Point(visibleSize.width*0.50, visibleSize.height/2));
    configBtn->setCallbackFunc([](){
        log("enter ConfigScene");
        GameController::getInstance()->enterConfigScene();
    });
    auto exitBtn = ButtonSprite::create("CloseNormal.png");
    background->addChild(exitBtn);
    exitBtn->setScale(3.5);
    exitBtn->setPosition(Point(visibleSize.width*0.75, visibleSize.height/2));
    exitBtn->setCallbackFunc([](){
        log("exit");
        GameController::getInstance()->exitGame();
    });
    
    auto text = Label::createWithSystemFont("wenzi文字", "AppleGothic", 200);
    text->setPosition(Point(visibleSize.width/2, visibleSize.height/4));
    background->addChild(text);
    text->enableShadow(Color4B::BLACK, Size(10, -10));
//    text->enableOutline(Color4B::GREEN, -10);
//    text->enableGlow(Color4B::YELLOW);
    
    auto text2 = Label::createWithTTF("ABCabc", "fonts/arial.ttf", 200);
    text2->setPosition(Point(visibleSize.width/2, visibleSize.height*0.75));
    background->addChild(text2);
//    text2->enableOutline(Color4B::BLACK, -10);
    text2->enableGlow(Color4B::YELLOW);
    
    return true;
}
