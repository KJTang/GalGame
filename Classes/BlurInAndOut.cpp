//
//  BlurInAndOut.cpp
//  Test
//
//  Created by KJTang on 15/8/4.
//
//

#include "BlurInAndOut.h"

/*
 * Blur In: blur the target
 */

BlurIn::BlurIn(){}

BlurIn::~BlurIn(){}

BlurIn* BlurIn::create(float duration)
{
    BlurIn* temp = new BlurIn();
    temp->init(duration);
    temp->autorelease();
    
    return temp;
}

bool BlurIn::init(float duration)
{
    if(ActionInterval::initWithDuration(duration))
    {
        countFlag = duration / Director::getInstance()->getAnimationInterval() / 3;
        count = 0;
        return true;
    }
    return false;
}

void BlurIn::update(float dt)
{
    ++count;
    if (count == countFlag) {
        _target->setGLProgram(GLProgramCache::getInstance()->getGLProgram("blur1"));
    } else if (count == countFlag * 2) {
        _target->setGLProgram(GLProgramCache::getInstance()->getGLProgram("blur2"));
    } else if (count == countFlag * 3) {
        _target->setGLProgram(GLProgramCache::getInstance()->getGLProgram("blur3"));
    }
}

/*
 * Blur Out: clear the target
 */

BlurOut::BlurOut(){}

BlurOut::~BlurOut(){}

BlurOut* BlurOut::create(float duration)
{
    BlurOut* temp = new BlurOut();
    temp->init(duration);
    temp->autorelease();
    
    return temp;
}

bool BlurOut::init(float duration)
{
    if(ActionInterval::initWithDuration(duration))
    {
        countFlag = duration / Director::getInstance()->getAnimationInterval() / 3;
        count = 0;
        return true;
    }
    return false;
}

void BlurOut::update(float dt)
{
    ++count;
    if (count == countFlag) {
        _target->setGLProgram(GLProgramCache::getInstance()->getGLProgram("blur3"));
    } else if (count == countFlag * 2) {
        _target->setGLProgram(GLProgramCache::getInstance()->getGLProgram("blur2"));
    } else if (count == countFlag * 3) {
        _target->setGLProgram(GLProgramCache::getInstance()->getGLProgram("blur1"));
    }
}