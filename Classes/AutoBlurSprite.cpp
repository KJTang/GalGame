//
//  AutoBlurSprite.cpp
//  Test
//
//  Created by KJTang on 15/8/4.
//
//

#include "AutoBlurSprite.h"

AutoBlurSprite::AutoBlurSprite(){}

AutoBlurSprite::~AutoBlurSprite(){}

AutoBlurSprite* AutoBlurSprite::create(std::string filename)
{
    AutoBlurSprite *pRet = new(std::nothrow) AutoBlurSprite();
    if (pRet && pRet->initWithFile(filename))
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

bool AutoBlurSprite::initWithFile(std::string filename)
{
    if (!Sprite::initWithFile(filename)) {
        return false;
    }
    
    touchListener = EventListenerTouchOneByOne::create();
    
    
    return true;
}

void AutoBlurSprite::BlurIn()
{
    this->runAction(BlurIn::create(1));
}

void AutoBlurSprite::BlurOut()
{
    this->runAction(BlurOut::create(1));
}