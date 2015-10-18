#include "ButtonSprite.h"

ButtonSprite::ButtonSprite() {}

ButtonSprite::~ButtonSprite() {}

ButtonSprite* ButtonSprite::create(const std::string &filename)
{
    ButtonSprite *pRet = new(std::nothrow) ButtonSprite();
    if (pRet && pRet->initWithFile(filename)) {
        pRet->autorelease();
        return pRet;
    }
    else {
        delete pRet;
        pRet = 0;
        return 0;
    }
}

bool ButtonSprite::initWithFile(const std::string &filename)
{
    if (!Sprite::initWithFile(filename)) {
        return false;
    }

    visibleSize = Director::getInstance()->getVisibleSize();

    callbackFunc = nullptr;

    touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);

    touchListener->onTouchBegan = [&](Touch* touch, Event* event) {
        startPoint = touch->getLocation();
        auto target = static_cast<ButtonSprite*>(event->getCurrentTarget());
        // relative position
        cocos2d::Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        cocos2d::Rect rect = cocos2d::Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
        if (rect.containsPoint(locationInNode)) {
            target->runAction(MoveBy::create(0.05, Vec2(10, -10)));
            return true;
        }
        return false;
    };

    touchListener->onTouchEnded = [&](Touch* touch, Event* event) {
        endPoint = touch->getLocation();
        auto target = static_cast<ButtonSprite*>(event->getCurrentTarget());
        target->runAction(MoveBy::create(0.05, Vec2(-10, 10)));
        if (endPoint.x - startPoint.x > -10 && endPoint.x - startPoint.x < 10 &&
            endPoint.y - startPoint.y > -10 && endPoint.y - startPoint.y < 10) {
            target->onClicked();
        }
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
        //        touchListener->setEnabled(false);
    }
}

void ButtonSprite::setCallbackFunc(const std::function<void()> &func)
{
    callbackFunc = func;
}