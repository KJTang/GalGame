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
    
    float btnMoveSpeed = 0.5;
    auto startBtn = ButtonSprite::create("title/start");
    backgroundLayer->addChild(startBtn);
//    startBtn->setScale(1.5);
    startBtn->setAnchorPoint(Point(0, 0));
    startBtn->setPosition(Point(visibleSize.width, visibleSize.height*0.40));
    startBtn->setCallbackFunc([](){
        log("start Game");
        GameController::getInstance()->enterGameScene();
    });
    startBtn->runAction(Sequence::create(DelayTime::create(0.5),
                                         MoveBy::create(btnMoveSpeed, Point(-visibleSize.width*0.25, 0)),
                                         NULL));
    
    auto loadBtn = ButtonSprite::create("title/load");
    backgroundLayer->addChild(loadBtn);
//    loadBtn->setScale(1.5);
    loadBtn->setAnchorPoint(Point(0, 0));
    loadBtn->setPosition(Point(visibleSize.width, visibleSize.height*0.30));
    loadBtn->setCallbackFunc([](){
        log("load Game");
        GameController::getInstance()->enterGameScene("test");
    });
    loadBtn->runAction(Sequence::create(DelayTime::create(0.5+btnMoveSpeed*0.5),
                                        MoveBy::create(btnMoveSpeed, Point(-visibleSize.width*0.25, 0)),
                                        NULL));
    
    auto gallaryBtn = ButtonSprite::create("title/gallary");
    backgroundLayer->addChild(gallaryBtn);
//    gallaryBtn->setScale(1.5);
    gallaryBtn->setAnchorPoint(Point(0, 0));
    gallaryBtn->setPosition(Point(visibleSize.width, visibleSize.height*0.20));
    gallaryBtn->setCallbackFunc([](){
        log("enter GallaryScene");
    });
    gallaryBtn->runAction(Sequence::create(DelayTime::create(0.5+btnMoveSpeed*1),
                                           MoveBy::create(btnMoveSpeed, Point(-visibleSize.width*0.25, 0)),
                                           NULL));
    
    auto configBtn = ButtonSprite::create("title/config");
    backgroundLayer->addChild(configBtn);
//    configBtn->setScale(1.5);
    configBtn->setAnchorPoint(Point(0, 0));
    configBtn->setPosition(Point(visibleSize.width, visibleSize.height*0.10));
    configBtn->setCallbackFunc([](){
        log("enter ConfigScene");
        GameController::getInstance()->enterConfigScene();
    });
    configBtn->runAction(Sequence::create(DelayTime::create(0.5+btnMoveSpeed*1.5),
                                          MoveBy::create(btnMoveSpeed, Point(-visibleSize.width*0.25, 0)),
                                          NULL));
    
    auto infoBtn = ButtonSprite::create("title/info");
    backgroundLayer->addChild(infoBtn);
//    infoBtn->setScale(1.5);
    infoBtn->setAnchorPoint(Point(0, 0));
    infoBtn->setPosition(Point(-visibleSize.width*0.3, visibleSize.height*0.0));
    infoBtn->setCallbackFunc([](){
        log("enter InfoScene");
    });
    infoBtn->runAction(Sequence::create(DelayTime::create(0.5+btnMoveSpeed*2.0),
                                        MoveBy::create(btnMoveSpeed, Point(visibleSize.width*0.3, 0)),
                                        NULL));

    
//    // test
    DataController::getInstance()->test();
    
    return true;
}
