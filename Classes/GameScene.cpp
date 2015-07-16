
//
//  GameScene.cpp
//  Test
//
//  Created by KJTang on 15/7/16.
//
//

#include "GameScene.h"

GameScene* GameScene::sharedGameScene = nullptr;

GameScene::GameScene(){}

GameScene::~GameScene(){}

bool GameScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    isMissionCompleted = true;
    
    backgroundLayer = Layer::create();
    this->addChild(backgroundLayer, -1);
    
    menuLayer = Layer::create();
    this->addChild(menuLayer, 1);
    
    bgp = nullptr;
    bgpDuration = 0, bgpScale = 1, bgpPositionX = 0.5, bgpPositionY = 0.5;
    
    ch01 = nullptr, ch02 = nullptr, ch03 = nullptr, ch04 = nullptr;
    
    // temp
    auto button1 = ButtonSprite::create("CloseNormal.png");
    menuLayer->addChild(button1);
    button1->setScale(3.5);
    button1->setPosition(Point(visibleSize.width*0.75, visibleSize.height/2));
    button1->setCallbackFunc([](){
        log("back to StartScene");
        GameController::getInstance()->enterStartScene();
    });
    
    // touch listener
    touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    
    touchListener->onTouchBegan = [](Touch* touch, Event* event){
        return true;
    };
    
    touchListener->onTouchEnded = [](Touch* touch, Event* event){
        auto target = static_cast<GameScene*>(event->getCurrentTarget());
        // got touch
        target->isMissionCompleted = true;
        target->enableScreenTouchEventListener(false);
        return false;
    };
    touchListener->setEnabled(false);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void GameScene::startNewGame()
{
    this->clear();
    std::thread scriptControl(&GameScene::scriptControlThread, this);
    scriptControl.detach();
}

void GameScene::scriptControlThread()
{
    VariableController::getInstance()->readFromScript();
    ScriptController::getInstance()->runWithFile("file.txt", 1);
}

void GameScene::startSavedGame()
{
    log("load saved game");
}

bool GameScene::setBgpStart()
{
    if (bgp) {
        bgp->removeFromParentAndCleanup(true);
    }
    bgp = Sprite::create(bgpFilename);
    if (!bgp) {
        bgpDuration = 0;
        bgpScale = 1;
        return false;
    }
    bgp->setScale(visibleSize.width/bgp->getContentSize().width*bgpScale);
    bgp->setPosition(Point(visibleSize.width*bgpPositionX, visibleSize.height*bgpPositionY));
    backgroundLayer->addChild(bgp);
    this->runAction(Sequence::create(DelayTime::create(bgpDuration),
                                     CallFunc::create([&](){isMissionCompleted=true;}),
                                     NULL));
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
    backgroundLayer->addChild(ch01);
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
    backgroundLayer->addChild(ch02);
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
    backgroundLayer->addChild(ch03);
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
    backgroundLayer->addChild(ch04);
    return true;
}

void GameScene::enableScreenTouchEventListener(bool b)
{
    touchListener->setEnabled(b);
}