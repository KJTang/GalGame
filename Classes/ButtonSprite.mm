//
//  ButtonSprite.mm
//  Test
//
//  Created by KJTang on 15/7/15.
//
//

#include "ButtonSprite.h"

#include <CoreMotion/CoreMotion.h>
#import <CoreFoundation/CoreFoundation.h>

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
   
    CMMotionManager *motionManager = [[CMMotionManager alloc] init];
    motionManager.deviceMotionUpdateInterval = 1.0/60.0;
    if (motionManager.isDeviceMotionAvailable) {
        [motionManager startDeviceMotionUpdates];
    }
    m_motionManager = (void*)motionManager;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    xSpeed = 0.0, ySpeed = 0.0;
    xSpeedRate = 0.1, ySpeedRate = 0.1;
    resistanceX = 0.4, resistanceY = 0.4;
    
    callbackFunc = nullptr;
    
    touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    
    touchListener->onTouchBegan = [](Touch* touch, Event* event){
        auto target = static_cast<ButtonSprite*>(event->getCurrentTarget());
        // relative position
        cocos2d::Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        cocos2d::Rect rect = cocos2d::Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
        if (rect.containsPoint(locationInNode))
        {
            target->runAction(MoveBy::create(0.05, Vec2(10, -10)));
            return true;
        }
        return false;
    };
    
    touchListener->onTouchMoved = [](Touch* touch, Event* event){};
    
    touchListener->onTouchEnded = [](Touch* touch, Event* event){
        auto target = static_cast<ButtonSprite*>(event->getCurrentTarget());
        target->runAction(MoveBy::create(0.05, Vec2(-10, 10)));
        target->onClicked();
        return true;
    };
    
    isOriginSetted = false;
    maxX = 20, maxY = 20;
//    this->scheduleUpdate();
    
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

void ButtonSprite::update(float dt)
{
    if (!isOriginSetted) {
        isOriginSetted = true;
        originX = this->getPositionX(), originY = this->getPositionY();
//        log("setPosition %f, %f", originX, originY);
    }
    CMAttitude *currentAttitude = static_cast<CMMotionManager*>(m_motionManager).deviceMotion.attitude;
    
    currentYaw = roundf((float)(CC_RADIANS_TO_DEGREES(currentAttitude.yaw)));
    currentRoll = roundf((float)(CC_RADIANS_TO_DEGREES(currentAttitude.roll)));
    currentPitch = roundf((float)(CC_RADIANS_TO_DEGREES(currentAttitude.pitch)));
    
    yawAngle.push_back(currentYaw);
    rollAngle.push_back(currentRoll);
    pitchAngle.push_back(currentPitch);
    
    int number = 6;
    if (yawAngle.size() == number) {
        float yawAcc = yawAngle[number-1]-yawAngle[0];
        float rollAcc = rollAngle[number-1]-rollAngle[0];
        float pitchAcc = pitchAngle[number-1]-pitchAngle[0];
        for (int i = 1; i != number; ++i) {
            yawAcc += yawAngle[i]-yawAngle[i-1];
            rollAcc += rollAngle[i]-rollAngle[i-1];
            pitchAcc += pitchAngle[i]-pitchAngle[i-1];
        }
        yawAngle.clear(), rollAngle.clear(), pitchAngle.clear();
        yawAcc /= (number-1);
        rollAcc /= (number-1);
        pitchAcc /= (number-1);
        
        float xAcc = yawAcc + pitchAcc, yAcc = rollAcc;
        
        if (xSpeed == 0.0) {
            if (xAcc > resistanceX || xAcc < -resistanceX) {
                xSpeed += xAcc;
            } else {
                xSpeed = 0;
            }
        } else if (xSpeed > 0.0) {
            xSpeed += xAcc - resistanceX;
        } else {
            xSpeed += xAcc + resistanceX;
        }
        if (ySpeed == 0.0) {
            if (yAcc > resistanceY || yAcc < -resistanceY) {
                ySpeed += yAcc;
            } else {
                ySpeed = 0;
            }
        } else if (ySpeed > 0.0) {
            ySpeed += yAcc - resistanceY;
        } else {
            ySpeed += yAcc + resistanceY;
        }
    }
    
    float newX = this->getPositionX() + xSpeed * xSpeedRate;
    if (newX > originX+maxX) {
        newX = originX + maxX;
    } else if (newX < originX - maxX) {
        newX = originX - maxX;
    }
    float newY = this->getPositionY() + ySpeed * ySpeedRate;
    if (newY > originY + maxY) {
        newY = originY + maxY;
    } else if (newY < originY - maxY) {
        newY = originY - maxY;
    }
    this->setPosition(Vec2(newX, newY));
    // 速度受阻力影响而变化
    if (xSpeed >= 0.0) {
        xSpeed = xSpeed-resistanceX>0 ? xSpeed-resistanceX : 0;
    } else {
        xSpeed = xSpeed+resistanceX<0 ? xSpeed+resistanceX : 0;
    }
    if (ySpeed >= 0.0) {
        ySpeed = ySpeed-resistanceY>0 ? ySpeed-resistanceY : 0;
    } else {
        ySpeed = ySpeed+resistanceY<0 ? ySpeed+resistanceY : 0;
    }
}

void ButtonSprite::onClicked()
{
    if (callbackFunc) {
        callbackFunc();
//        touchListener->setEnabled(false);
    }
}

void ButtonSprite::setCallbackFunc(void (*func)())
{
    callbackFunc = func;
}