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
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
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
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->runAction(MoveBy::create(0.05, Vec2(-10, 10)));
        for (int i = 0; i != choiceNumber; ++i) {
            if (target == choices.at(i)) {
                setChoiceResult(i);
                // TODO
                return true;
            }
        }
        return true;
    };
    
    return true;
}

void ChoiceTableLayer::setChoiceNumber(int number)
{
    CCASSERT(number > 0 && number <= MAX_CHOICE_NUMBER, "choice number is not at the right range");
    
    choiceNumber = number;
    std::string fontFile = "fonts/PingFang_1.ttf";
    float fontSize = 60;
    Size textBoxSize = Size(500, 60);
    
    double origin = 0.0;
    if (choiceNumber%2) {
        origin = -0.5 - choiceNumber/2*0.05;
    } else {
        origin = -0.5 - choiceNumber/2*0.05 + 0.025;
    }
    for (int i = 0; i != choiceNumber; ++i) {
        Sprite *newChoice = Sprite::create("frame/ChoiceTable-Unchosen.png");
        choices.pushBack(newChoice);
        newChoice->setPosition(visibleSize.width*(origin+0.05*i), visibleSize.height*(0.80-0.10*i));
        
        Label *label = Label::createWithTTF("", fontFile, fontSize, textBoxSize, TextHAlignment::CENTER);
        newChoice->addChild(label, 5, "label");
        label->setPosition(Point(newChoice->getContentSize()*0.5) + Point(0, 15));

        Point position[4] = {Point(1, 0), Point(-1, 0), Point(0, -1), Point(0, 1)};
        for (int i = 0; i != 4; ++i) {
            auto outline = Label::createWithTTF("", fontFile, fontSize, textBoxSize, TextHAlignment::CENTER);
            newChoice->addChild(outline);
            outline->setPosition(label->getPosition()+position[i]);
            outline->setOpacity(100);
            outline->setColor(Color3B::RED);
        }
        
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
    auto choiceList = choices.at(id)->getChildren();
    for (int i = 0; i != choiceList.size(); ++i) {
        static_cast<Label*>(choiceList.at(i))->setString(content);
    }
}

void ChoiceTableLayer::setChoiceChoosable(int id, bool choosable)
{
    if (id >= choiceNumber || id < 0) {
        return;
    }
    listeners.at(id)->setEnabled(choosable);
    static_cast<Label*>(choices.at(id)->getChildByName("label"))->setTextColor(Color4B::GRAY);
}

void ChoiceTableLayer::showChoiceTable()
{
    for (int i = 0; i != choices.size(); ++i) {
        this->addChild(choices.at(i));
        choices.at(i)->runAction(MoveBy::create(1.2-0.1*i, Vec2(visibleSize.width, 0)));
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