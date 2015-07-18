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
    
    choice01 = Label::createWithTTF("", "fonts/PingFang_5.ttf", 80);
    choice01->setPosition(visibleSize.width*0.5, visibleSize.height*0.9);
    choice01->setVisible(false);
    this->addChild(choice01);
    
    choice02 = Label::createWithTTF("", "fonts/PingFang_5.ttf", 80);
    choice02->setPosition(visibleSize.width*0.5, visibleSize.height*0.80);
    choice02->setVisible(false);
    this->addChild(choice02);
    
    choice03 = Label::createWithTTF("", "fonts/PingFang_5.ttf", 80);
    choice03->setPosition(visibleSize.width*0.5, visibleSize.height*0.70);
    choice03->setVisible(false);
    this->addChild(choice03);
    
    choice04 = Label::createWithTTF("", "fonts/PingFang_5.ttf", 80);
    choice04->setPosition(visibleSize.width*0.5, visibleSize.height*0.60);
    choice04->setVisible(false);
    this->addChild(choice04);
    
    
    touchListener01 = EventListenerTouchOneByOne::create();
    touchListener01->setSwallowTouches(true);
    touchListener01->onTouchBegan = [](Touch *touch, Event *event) {
        auto target = static_cast<Label*>(event->getCurrentTarget());
        // relative position
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
        if (rect.containsPoint(locationInNode))
        {
//            target->runAction(ScaleTo::create(0.05, 2));
            log("TOUCHED");
            return true;
        }
        return false;
    };
    touchListener01->onTouchEnded = [](Touch* touch, Event* event){
        auto target = static_cast<Label*>(event->getCurrentTarget());

        log("TOUCH ENDED");
        return true;
    };
    
    touchListener02 = touchListener01->clone();
    touchListener03 = touchListener01->clone();
    touchListener04 = touchListener01->clone();
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener01, choice01);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener02, choice02);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener03, choice03);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener04, choice04);
    
    return true;
}

void ChoiceTableLayer::showChoiceTable()
{
    choice01->setVisible(showChoice01);
    choice02->setVisible(showChoice02);
    choice03->setVisible(showChoice03);
    choice04->setVisible(showChoice04);
}

// choice01
void ChoiceTableLayer::setChoice01Content(std::string str)
{
    choice01->setString(str);
    showChoice01 = true;
}

void ChoiceTableLayer::setChoice01Choosable(bool b)
{
    touchListener01->setEnabled(b);
}

// choice02
void ChoiceTableLayer::setChoice02Content(std::string str)
{
    choice02->setString(str);
    showChoice02 = true;
}

void ChoiceTableLayer::setChoice02Choosable(bool b)
{
    touchListener02->setEnabled(b);
}

// choice03
void ChoiceTableLayer::setChoice03Content(std::string str)
{
    choice03->setString(str);
    showChoice03 = true;
}

void ChoiceTableLayer::setChoice03Choosable(bool b)
{
    touchListener03->setEnabled(b);
}

// choice04
void ChoiceTableLayer::setChoice04Content(std::string str)
{
    choice04->setString(str);
    showChoice04 = true;
}

void ChoiceTableLayer::setChoice04Choosable(bool b)
{
    touchListener04->setEnabled(b);
}