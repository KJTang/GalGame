//
//  GallaryLayer.cpp
//  Test
//
//  Created by idream on 15/11/8.
//
//

#include "GallaryLayer.h"

/***************
 GallaryContent
 ***************/
GallaryContent::GallaryContent(){}

GallaryContent::~GallaryContent(){}

bool GallaryContent::init()
{
    if (!Layer::init()) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    
    auto pic = Sprite::create("HelloWorld.png");
    this->addChild(pic);
    pic->setPosition(visibleSize.width*0.5, visibleSize.height*1.5);
    
    return true;
}

/**************
 GallaryLayer
 *************/
GallaryLayer::GallaryLayer(){}

GallaryLayer::~GallaryLayer(){}

bool GallaryLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    inTouchEvent = false;
    
    blackLayer = LayerColor::create(Color4B::BLACK);
    this->addChild(blackLayer);
    blackLayer->setOpacity(0);
    
    contentLayer = GallaryContent::create();
    this->addChild(contentLayer);
    
    touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [&](Touch *touch, Event *event) {
        touchStart = touch->getLocation();
        if (inTouchEvent) {
            return true;
        } else if (touchStart.y > visibleSize.height*0.8) {
            return true;
        }
        return false;
    };
    touchListener->onTouchMoved = [&](Touch *touch, Event *event) {
        auto touchCurrent = touch->getLocation();
        contentLayer->setPositionY(contentLayer->getPositionY() + touchCurrent.y - touchStart.y);
        
        if (contentLayer->getPositionY() >= 0) {
            blackLayer->setOpacity(0);
        } else if (contentLayer->getPositionY() < -visibleSize.height*0.50) {
            blackLayer->setOpacity(200);
        } else {
            blackLayer->setOpacity((-contentLayer->getPositionY())/(visibleSize.height*0.5)*200);
        }
        touchStart = touchCurrent;
        return true;
    };
    touchListener->onTouchEnded = [&](Touch *touch, Event *event) {
        if (contentLayer->getPositionY() < -visibleSize.height*0.5) {
            contentLayer->runAction(MoveTo::create(0.2, Vec2(0, -visibleSize.height)));
            inTouchEvent = true;
        } else {
            contentLayer->runAction(MoveTo::create(0.1, Vec2(0, 0)));
            blackLayer->runAction(FadeOut::create(0.1));
            inTouchEvent = false;
        }
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}