//
//  HistoryLayer.cpp
//  Test
//
//  Created by KJTang on 15/10/18.
//
//

#include "HistoryLayer.h"
#include "GameScene.h"

const int blackOpacity = 200;

HistoryLayer::HistoryLayer(){}

HistoryLayer::~HistoryLayer(){}

bool HistoryLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    historyBoard = nullptr;
    isHistoryShowing = false;
    
    blackLayer = LayerColor::create(Color4B::BLACK);
    this->addChild(blackLayer, 0);
    blackLayer->setOpacity(0);
    
    screenTouchListener = EventListenerTouchOneByOne::create();
    screenTouchListener->setSwallowTouches(false);
    
    screenTouchListener->onTouchBegan = [&](Touch *touch, Event *event) {
        touchStart = touch->getLocation();
        if (isHistoryShowing) {
            screenTouchListener->setSwallowTouches(true);
            return true;
        } else if (touchStart.y > visibleSize.height*0.8) {
            screenTouchListener->setSwallowTouches(true);
            this->createHistoryBoard();
            this->setHistory(GameScene::getInstance()->historyText);
            return true;
        }
        return false;
    };
    screenTouchListener->onTouchMoved = [&](Touch *touch, Event *event) {
        auto delta = touch->getLocation().y - touchStart.y;
        auto maxHeight = -static_cast<int>(GameScene::getInstance()->historyText.size())*300.0-150;
        if (static_cast<int>(GameScene::getInstance()->historyText.size()) == 0) {
            maxHeight = -450;
        }
        historyBoard->setPositionY(historyBoard->getPositionY()+delta);
        if (historyBoard->getPositionY() < maxHeight) {
            historyBoard->setPositionY(maxHeight);
        }
        if (historyBoard->getPositionY() > -300 && historyBoard->getPositionY() < 0) {
            blackLayer->setOpacity(historyBoard->getPositionY()/(-300) * blackOpacity);
        } else if (historyBoard->getPositionY() <= -300) {
            blackLayer->setOpacity(blackOpacity);
        } else if (historyBoard->getPositionY() >= 0) {
            blackLayer->setOpacity(0);
        }
        touchStart = touch->getLocation();
        log("pos=%.2f", historyBoard->getPositionY());
        return true;
    };
    screenTouchListener->onTouchEnded = [&](Touch *touch, Event *event) {
        if (historyBoard->getPositionY() >= -300) {
            historyBoard->runAction(MoveTo::create(0.1, Vec2(0, 0)));
            isHistoryShowing = false;
            screenTouchListener->setSwallowTouches(false);
            historyBoard->removeFromParentAndCleanup(true);
            historyBoard = nullptr;
            blackLayer->setOpacity(0);
        } else {
            isHistoryShowing = true;
        }
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(screenTouchListener, this);
    
    return true;
}

void HistoryLayer::createHistoryBoard()
{
    if (historyBoard) {
        historyBoard->removeFromParentAndCleanup(true);
    }
    historyBoard = Layer::create();
    this->addChild(historyBoard);
}

void HistoryLayer::setHistory(const std::vector<std::string> &history)
{
    std::string fontFile = "fonts/PingFang_1.ttf";
    float fontSize = 55;
    Size textBoxSize = Size(1600, 300);
    auto textHeight = 300.0;
    
    if (history.size() == 0) {
        auto text = Label::createWithTTF("No History", fontFile, fontSize, textBoxSize);
        historyBoard->addChild(text);
        text->setPosition(visibleSize.width*0.5, textHeight+visibleSize.height-150);
    } else {
        for (int i = static_cast<int>(history.size()); i != 0; --i) {
            log("info:%s", history[i-1].c_str());
            auto text = Label::createWithTTF(history[i-1], fontFile, fontSize, textBoxSize);
            historyBoard->addChild(text);
            text->setPosition(visibleSize.width*0.5, textHeight*(history.size()-i+1)+visibleSize.height-150);
        }
    }
}