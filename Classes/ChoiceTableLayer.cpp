//
//  ChoiceTableLayer.cpp
//  Test
//
//  Created by KJTang on 15/7/18.
//
//

#include "ChoiceTableLayer.h"
#include "GameScene.h"

ChoiceTableLayer::ChoiceTableLayer(){}

ChoiceTableLayer::~ChoiceTableLayer(){}

bool ChoiceTableLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
 
    visibleSize = Director::getInstance()->getVisibleSize();
    choiceNumber = 0;
    tempResult = -1;
    choiceResult = -1;
    moved = false;
    
    touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [&](Touch *touch, Event *event) {
        startPoint = touch->getLocation();
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        // relative position
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
        if (rect.containsPoint(locationInNode)) {
            for (int i = 0; i != choiceNumber; ++i) {
                if (target == choices.at(i*2)) {
                    tempResult = i;
                    choices.at(i*2+1)->setVisible(true);
                } else {
                    choices.at(i*2+1)->setVisible(false);
                }
            }
            return true;
        }
        return false;
    };
    touchListener->onTouchMoved = [&](Touch *touch, Event *event) {
        if ((touch->getLocation()-startPoint).length() >= 100) {
            moved = true;
            choices.at(tempResult*2+1)->setVisible(false);
            return false;
        }
        return true;
    };
    touchListener->onTouchEnded = [&](Touch* touch, Event* event) {
        choices.at(tempResult*2+1)->setVisible(false);
        endPoint = touch->getLocation();
        if (!moved && std::abs(endPoint.x - startPoint.x) < 50 && std::abs(endPoint.y - startPoint.y) < 50) {
            this->runAction(Sequence::create(CallFunc::create([&]()
                                                              {
                                                                  for (int i = 0; i != choices.size(); i += 2) {
                                                                      choices.at(i)->runAction(Sequence::create(DelayTime::create(0.05*i),
                                                                                                                MoveBy::create(0.3, Vec2(visibleSize.width*0.8, 0)),
                                                                                                                NULL));
                                                                      choices.at(i+1)->runAction(Sequence::create(DelayTime::create(0.05*i),
                                                                                                                MoveBy::create(0.3, Vec2(visibleSize.width*0.8, 0)),
                                                                                                                NULL));
                                                                  }
                                                              }),
                                             DelayTime::create(0.5),
                                             CallFunc::create([&]()
                                                              {
                                                                  this->setChoiceResult(tempResult);
                                                              }),
                                             NULL));
            return false;
        }
        moved = false;

        return true;
    };
    touchListener->onTouchCancelled = [&](Touch *touch, Event *event) {
        log("touch canceled");
        return false;
    };
    
    return true;
}

void ChoiceTableLayer::setChoiceNumber(int number)
{
    CCASSERT(number > 0 && number <= MAX_CHOICE_NUMBER, "choice number is not at the right range");
    
    choiceNumber = number;
    std::string fontFile = "fonts/PingFang_1.ttf";
    float fontSize = 60/(Director::getInstance()->getContentScaleFactor());
    Size textBoxSize = Size(500, 60)/(Director::getInstance()->getContentScaleFactor());
    
    double origin = 0.0;
    if (choiceNumber%2) {
        origin = -0.5 - choiceNumber/2*0.05;
    } else {
        origin = -0.5 - choiceNumber/2*0.05 + 0.025;
    }
    for (int i = 0; i != choiceNumber; ++i) {
        Sprite *newChoice = Sprite::create("frame/ChoiceTable-Unchosen.png");
        choices.pushBack(newChoice);
        newChoice->setPosition(visibleSize.width*1.5, visibleSize.height*(0.30+0.10*i));
        
        Sprite *chosen = Sprite::create("frame/ChoiceTable-Chosen.png");
        choices.pushBack(chosen);
        chosen->setPosition(newChoice->getPosition());
        chosen->setVisible(false);
        
        Label *label = Label::createWithTTF("", fontFile, fontSize, textBoxSize, TextHAlignment::CENTER);
        newChoice->addChild(label, 5, "label");
        label->setPosition(Point(newChoice->getContentSize()*0.5) + Point(0, 15)/Director::getInstance()->getContentScaleFactor());

        Point position[4] = {Point(1, 0), Point(-1, 0), Point(0, -1), Point(0, 1)};
        for (int i = 0; i != 4; ++i) {
            auto outline = Label::createWithTTF("", fontFile, fontSize, textBoxSize, TextHAlignment::CENTER);
            newChoice->addChild(outline, i+1);
            outline->setPosition(label->getPosition()+position[i]);
            outline->setOpacity(100);
            outline->setColor(Color3B::RED);
        }
        
        auto newTouchListener = touchListener->clone();
        listeners.pushBack(newTouchListener);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(newTouchListener, newChoice);
    }
}

void ChoiceTableLayer::setChoiceContent(int id, const std::string& content)
{
    if (id >= choiceNumber || id < 0) {
        return;
    }
    auto choiceList = choices.at(id*2)->getChildren();
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
    static_cast<Label*>(choices.at(id*2)->getChildByName("label"))->setTextColor(Color4B::GRAY);
}

void ChoiceTableLayer::showChoiceTable()
{
    for (int i = 0; i != choices.size(); i += 2) {
        this->addChild(choices.at(i));
        this->addChild(choices.at(i+1));
        choices.at(i)->runAction(Sequence::create(DelayTime::create(0.05*i),
                                                  MoveBy::create(0.5, Vec2(-visibleSize.width*0.8, 0)),
                                                  NULL));
        choices.at(i+1)->runAction(Sequence::create(DelayTime::create(0.05*i),
                                                  MoveBy::create(0.5, Vec2(-visibleSize.width*0.8, 0)),
                                                  NULL));
        choices.at(i+1)->setVisible(false);
    }
}

void ChoiceTableLayer::setChoiceResult(int result)
{
    choiceResult = result;
    for (int i = 0; i != listeners.size(); ++i) {
        listeners.at(i)->setEnabled(false);
    }
    // record choice result
    if (GameScene::getInstance()->historyText.size() >= 30) {
        GameScene::getInstance()->historyText.erase(GameScene::getInstance()->historyText.begin());
    }
    GameScene::getInstance()->historyText.push_back("@choice@"+static_cast<Label*>(choices.at(result*2)->getChildByName("label"))->getString());
}

int ChoiceTableLayer::getChoiceReuslt()
{
    return choiceResult;
}