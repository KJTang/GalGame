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
    
    
    //////////////////////////////////////////////////////
    std::string str1 = "中abca,，文中文中文";
    std::string str2;
    
    text = Label::createWithSystemFont(str2, "AppleGothic", 50, Size(100, 300));
    text->setPosition(Point(visibleSize.width*0.25, visibleSize.height*0.50));
    text->setColor(Color3B::BLACK);
    background->addChild(text, 5);
    
    for (int i = 0; i != str1.size(); ) {
        if (str1[i] <= 127 && str1[i] >= 0) {
            str2 += str1[i];
            ++i;
        }
        else {
            str2 += str1[i];
            str2 += str1[i+1];
            str2 += str1[i+2];
            i += 3;
        }
        log("str=%s，size=%d", str2.c_str(), (int)str2.size());
    }

//    this->runAction(DelayTime::create(5));
//    this->runAction(CallFunc::create([&](){text->setString("中文中文测试中文");}));
//    
//    this->runAction(Sequence::create(DelayTime::create(1),
//                                     CallFunc::create([&](){text->setString("中");}),
//                                     DelayTime::create(1),
//                                     CallFunc::create([&](){text->setString("中文");}),
//                                     DelayTime::create(1),
//                                     CallFunc::create([&](){text->setString("中文测");}),
//                                     DelayTime::create(1),
//                                     CallFunc::create([&](){text->setString("中文测试");}),
//                                     NULL));
    
    return true;
}
