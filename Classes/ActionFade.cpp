//
//  ActionFade.cpp
//  Test
//
//  Created by KJTang on 15/10/3.
//
//

#include "ActionFade.h"

/**
 *     FadeIn
 */
ActionFadeIn::ActionFadeIn(){}

ActionFadeIn::~ActionFadeIn(){}

ActionFadeIn* ActionFadeIn::create(float duration, int op)
{
    ActionFadeIn* temp = new ActionFadeIn();
    temp->init(duration, op);
    temp->autorelease();
    
    return temp;
}

bool ActionFadeIn::init(float duration, int op)
{
    if(ActionInterval::initWithDuration(duration))
    {
        step = duration / Director::getInstance()->getAnimationInterval() / 5;
        count = 0;
        opacity = op;
        return true;
    }
    return false;
}

void ActionFadeIn::update(float dt)
{
    if (!(count % step)) {
        int newOpacity = (opacity-_target->getOpacity()) / 5.0 * (count/step) + _target->getOpacity();
        if (newOpacity > opacity) {
            newOpacity = opacity;
        }
        _target->setOpacity(newOpacity);
    }
    ++count;
}

/**
 *     FadeOut
 */
ActionFadeOut::ActionFadeOut(){}

ActionFadeOut::~ActionFadeOut(){}

ActionFadeOut* ActionFadeOut::create(float duration, int op)
{
    ActionFadeOut* temp = new ActionFadeOut();
    temp->init(duration, op);
    temp->autorelease();
    
    return temp;
}

bool ActionFadeOut::init(float duration, int op)
{
    if(ActionInterval::initWithDuration(duration))
    {
        step = duration / Director::getInstance()->getAnimationInterval() / 5;
        count = 0;
        opacity = op;
        return true;
    }
    return false;
}

void ActionFadeOut::update(float dt)
{
    if (!(count % step)) {
        int newOpacity = opacity / 5.0 * (5 - count/step);
        if (newOpacity < 0) {
            newOpacity = 0;
        }
        _target->setOpacity(newOpacity);
    }
    ++count;
}