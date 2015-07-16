
//
//  GameScene.cpp
//  Test
//
//  Created by KJTang on 15/7/16.
//
//

#include "GameScene.h"

GameScene::GameScene(){}

GameScene::~GameScene(){}

bool GameScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    bgp = nullptr, ch01 = nullptr, ch02 = nullptr, ch03 = nullptr, ch04 = nullptr;
    
    background = Layer::create();
    this->addChild(background);
    
    // temp
    auto button1 = ButtonSprite::create("CloseNormal.png");
    background->addChild(button1);
    button1->setScale(3.5);
    button1->setPosition(Point(visibleSize.width*0.75, visibleSize.height/2));
    button1->setCallbackFunc([](){
        log("back to StartScene");
        GameController::getInstance()->enterStartScene();
    });

    return true;
}

void GameScene::startNewGame()
{
    VariableController::getInstance()->readFromScript();
    ScriptController::getInstance()->runWithFile("file.txt");
}

void GameScene::startSavedGame()
{
    log("load saved game");
}

bool GameScene::setBackgroundPicture(std::string filename)
{
    if (bgp) {
        log("remove bgp");
        bgp->removeFromParentAndCleanup(true);
    }
    bgp = Sprite::create(filename);
    if (!bgp) {
        return false;
    }
    background->addChild(bgp);
    return true;
}

bool GameScene::setCh01Picture(std::string filename)
{
    if (ch01) {
        ch01->removeFromParentAndCleanup(true);
    }
    ch01 = Sprite::create(filename);
    if (!ch01) {
        return false;
    }
    background->addChild(ch01);
    return true;
}

bool GameScene::setCh02Picture(std::string filename)
{
    if (ch02) {
        ch02->removeFromParentAndCleanup(true);
    }
    ch02 = Sprite::create(filename);
    if (!ch02) {
        return false;
    }
    background->addChild(ch02);
    return true;
}

bool GameScene::setCh03Picture(std::string filename)
{
    if (ch03) {
        ch03->removeFromParentAndCleanup(true);
    }
    ch03 = Sprite::create(filename);
    if (!ch03) {
        return false;
    }
    background->addChild(ch03);
    return true;
}

bool GameScene::setCh04Picture(std::string filename)
{
    if (ch04) {
        ch04->removeFromParentAndCleanup(true);
    }
    ch04 = Sprite::create(filename);
    if (!ch04) {
        return false;
    }
    background->addChild(ch04);
    return true;
}