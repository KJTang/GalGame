
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
    
    backgroundLayer = Layer::create();
    this->addChild(backgroundLayer, -1);
    
    menuLayer = Layer::create();
    this->addChild(menuLayer, 1);
    
    bgp = nullptr, ch01 = nullptr, ch02 = nullptr, ch03 = nullptr, ch04 = nullptr;
    
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
    isTouched = false;

    touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    
    touchListener->onTouchBegan = [](Touch* touch, Event* event){
        return true;
    };
    
    touchListener->onTouchEnded = [](Touch* touch, Event* event){
        log("Touch Ended");
        auto target = static_cast<GameScene*>(event->getCurrentTarget());
        target->isTouched = true;
        return false;
    };
    touchListener->setEnabled(false);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, backgroundLayer);
    
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
    backgroundLayer->addChild(bgp);
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

void GameScene::waitForAScreenTouch()
{
    isTouched = false;
    touchListener->setEnabled(true);
}