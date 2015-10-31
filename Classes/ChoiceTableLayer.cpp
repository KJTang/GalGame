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
    chosen = nullptr;
    
    touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [&](Touch *touch, Event *event) {
        startPoint = touch->getLocation();
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        // relative position
        Point locationInNode = target->convertToNodeSpace(touch->getLocation());
        Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
        if (rect.containsPoint(locationInNode))
        {
            for (int i = 0; i != choiceNumber; ++i) {
                if (target == choices.at(i)) {
                    tempResult = i;
                    target->setOpacity(0);
                    chosen = Sprite::create("frame/ChoiceTable-Chosen.png");
                    this->addChild(chosen, -1);
                    chosen->setPosition(target->getPosition());
                    break;
                }
            }
            
//            for (int i = 0; i != choiceNumber; ++i) {
//                if (target == choices.at(i)) {
//                    tempResult = i;
//                    target->setOpacity(0);
//                    chosen = Sprite::create("frame/ChoiceTable-Chosen.png");
//                    this->addChild(chosen, -1);
//                    chosen->setPosition(target->getPosition());
//                    continue;
//                } else {
//                    log("++++++++++++++++++++++++++    %d", i);
//                    choices.at(i)->runAction(Sequence::create(DelayTime::create(0.05*(choiceNumber - i)),
//                                                              MoveTo::create(0.8, position[i]+Point(visibleSize.width*2, 0)),
//                                                              NULL));
//                }
//            }
            
            
            return true;
        }
        return false;
    };
    touchListener->onTouchEnded = [&](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setOpacity(255);
        if (chosen) {
            chosen->removeFromParentAndCleanup(true);
            chosen = nullptr;
        }
        endPoint = touch->getLocation();
        // relative position
        Point locationInNode = target->convertToNodeSpace(endPoint);
        Rect rect = Rect(0, 0, target->getContentSize().width, target->getContentSize().height);
        if (rect.containsPoint(locationInNode))
        {
            this->runAction(Sequence::create(CallFunc::create([&]()
                                                              {
                                                                  for (int i = 0; i != choices.size(); ++i) {
                                                                      choices.at(i)->runAction(FadeOut::create(0.5));
                                                                      auto children = choices.at(i)->getChildren();
                                                                      for (int j = 0; j != children.size(); ++j) {
                                                                          children.at(j)->runAction(FadeOut::create(0.5));
                                                                      }
                                                                  }
                                                              }),
                                             DelayTime::create(0.5),
                                             CallFunc::create([&]()
                                                              {
                                                                  this->setChoiceResult(tempResult);
                                                              }),
                                             NULL));
//            setChoiceResult(tempResult);
            return false;
        }

//        if (tempResult != -1) {
//            if ((tempResult && static_cast<Sprite*>(choices.at(0))->getPositionX() > visibleSize.width) ||
//                (tempResult == 0 && static_cast<Sprite*>(choices.at(1))->getPositionX() > visibleSize.width)) {
//                setChoiceResult(tempResult);
//                return false;
//            }
//            for (int i = 0; i != choices.size(); ++i) {
//                if (i != tempResult) {
//                    choices.at(i)->stopAllActions();
//                    choices.at(i)->runAction(Sequence::create(DelayTime::create(0.05*(choiceNumber - i)),
//                                                              MoveTo::create(0.5, position[i]+Point(visibleSize.width, 0)),
//                                                              NULL));
//                }
//            }
//        }
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
        position.push_back(Point(visibleSize.width*(origin+0.05*i), visibleSize.height*(0.80-0.10*i)));
        
        Label *label = Label::createWithTTF("", fontFile, fontSize, textBoxSize, TextHAlignment::CENTER);
        newChoice->addChild(label, 6, "label");
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
        choices.at(i)->runAction(Sequence::create(DelayTime::create(0.05*(choiceNumber - i)),
                                                  MoveBy::create(0.8, Vec2(visibleSize.width, 0)),
                                                  NULL));
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
    GameScene::getInstance()->historyText.push_back("@choice@"+static_cast<Label*>(choices.at(result)->getChildByName("label"))->getString());
}

int ChoiceTableLayer::getChoiceReuslt()
{
    return choiceResult;
}