//
//  ButtonSprite.cpp
//  Test
//
//  Created by KJTang on 15/7/15.
//
//

#include "ButtonSprite.h"

ButtonSprite::ButtonSprite(){}

ButtonSprite::~ButtonSprite(){}

ButtonSprite* ButtonSprite::create(std::string filename)
{
    ButtonSprite *pRet = new(std::nothrow) ButtonSprite();
    if (pRet && pRet->initWithFile(filename) && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = 0;
        return 0;
    }
}

bool ButtonSprite::init()
{
    // don't know why when add this, the sprite will not show on screen
//    if (!Sprite::init()) {
//        return false;
//    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    callbackFunc = nullptr;
    
    touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    
    touchListener->onTouchBegan = [](Touch* touch, Event* event){
        auto target = static_cast<ButtonSprite*>(event->getCurrentTarget());
        // relative position
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
        if (rect.containsPoint(locationInNode))
        {
            target->runAction(ScaleTo::create(0.05, 2));
            return true;
        }
        return false;
    };
    
    touchListener->onTouchMoved = [](Touch* touch, Event* event){};
    
    touchListener->onTouchEnded = [](Touch* touch, Event* event){
        auto target = static_cast<ButtonSprite*>(event->getCurrentTarget());
        target->runAction(ScaleTo::create(0.05, 3.5));
        target->onClicked();
        return true;
    };
    
    /* when use popScene to go back to the scene which add ButtonSprite,
     * it'll call ButtonSprite::onEnter once more,
     * so we should add eventlistener in ButtonSprite::init()
     * to make sure eventlistener only is registered once
     */
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void ButtonSprite::onEnter()
{
    Sprite::onEnter();
    // when enter ButtonSprite, enable the eventlistener
    touchListener->setEnabled(true);
}

void ButtonSprite::onClicked()
{
    if (callbackFunc) {
        callbackFunc();
        touchListener->setEnabled(false);
    }
}

void ButtonSprite::setCallbackFunc(void (*func)())
{
    callbackFunc = func;
}