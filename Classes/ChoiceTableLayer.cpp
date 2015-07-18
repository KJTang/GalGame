//
//  ChoiceTableLayer.cpp
//  Test
//
//  Created by KJTang on 15/7/18.
//
//

#include "ChoiceTableLayer.h"

ChoiceTableLayer::ChoiceTableLayer(){}

ChoiceTableLayer::~ChoiceTableLayer(){}

bool ChoiceTableLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
 
    visibleSize = Director::getInstance()->getVisibleSize();
    choiceNumber = 0;
    choiceResult = -1;
    
    touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [](Touch *touch, Event *event) {
        auto target = static_cast<Label*>(event->getCurrentTarget());
        // relative position
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
        if (rect.containsPoint(locationInNode))
        {
            target->runAction(MoveBy::create(0.05, Vec2(10, -10)));
            return true;
        }
        return false;
    };
    touchListener->onTouchEnded = [&](Touch* touch, Event* event){
        auto target = static_cast<Label*>(event->getCurrentTarget());
        target->runAction(MoveBy::create(0.05, Vec2(-10, 10)));
        for (int i = 0; i != choiceNumber; ++i) {
            if (target == choices.at(i)) {
                setChoiceResult(i);
                return true;
            }
        }
        return true;
    };

    
    return true;
}

void ChoiceTableLayer::setChoiceNumber(int number)
{
    if (number < 0) {
        return;
    }
    choiceNumber = number;
    for (int i = 0; i != choiceNumber; ++i) {
        Label *newChoice = Label::createWithTTF("", "fonts/PingFang_5.ttf", visibleSize.height/10);
        choices.pushBack(newChoice);
        newChoice->setPosition(visibleSize.width*0.5, visibleSize.height*(0.90-0.10*i));
        
        auto newTouchListener = touchListener->clone();
        listeners.pushBack(newTouchListener);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(newTouchListener, newChoice);
    }
}

void ChoiceTableLayer::setChoiceContent(int id, std::string content)
{
    if (id >= choiceNumber || id < 0) {
        return;
    }
    choices.at(id)->setString(content);
}

void ChoiceTableLayer::setChoiceChoosable(int id, bool choosable)
{
    if (id >= choiceNumber || id < 0) {
        return;
    }
    listeners.at(id)->setEnabled(choosable);
}

void ChoiceTableLayer::showChoiceTable()
{
    for (int i = 0; i != choices.size(); ++i) {
        this->addChild(choices.at(i));
    }
}

void ChoiceTableLayer::setChoiceResult(int result)
{
    choiceResult = result;
    for (int i = 0; i != listeners.size(); ++i) {
        listeners.at(i)->setEnabled(false);
    }
}

int ChoiceTableLayer::getChoiceReuslt()
{
    return choiceResult;
}