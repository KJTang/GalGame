//
//  PromptBoxSprite.cpp
//  Test
//
//  Created by KJTang on 15/10/18.
//
//

#include "PromptBoxSprite.h"

PromptBoxSprite::PromptBoxSprite(){}

PromptBoxSprite::~PromptBoxSprite(){}

bool PromptBoxSprite::init()
{
    if (!Sprite::init()) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    
    bg = Sprite::create("frame/Prompt.png");
    this->addChild(bg);
    bg->setPosition(this->getPosition());
    
    std::string fontFile = "fonts/PingFang_1.ttf";
    float fontSize = 55/(Director::getInstance()->getContentScaleFactor());
    Size textBoxSize = Size(500, 200)/(Director::getInstance()->getContentScaleFactor());
    text = Label::createWithTTF("", fontFile, fontSize, textBoxSize, TextHAlignment::LEFT, TextVAlignment::CENTER);
    this->addChild(text, 5);
    text->setTextColor(Color4B::WHITE);
    Point position[4] = {Point(1, 0), Point(-1, 0), Point(0, -1), Point(0, 1)};
    for (int i = 0; i != 4; ++i) {
        outline[i] = Label::createWithTTF("", fontFile, fontSize, textBoxSize, TextHAlignment::LEFT, TextVAlignment::CENTER);
        this->addChild(outline[i], i);
        outline[i]->setPosition(text->getPosition()+position[i]);
        outline[i]->setOpacity(100);
        outline[i]->setColor(Color3B::RED);
    }
    
    return true;
}

void PromptBoxSprite::setText(const std::string &t)
{
    text->setString(t);
    for (int i = 0; i != 4; ++i) {
        outline[i]->setString(t);
    }
}

void PromptBoxSprite::start()
{
    this->runAction(Sequence::create(MoveBy::create(0.3, Vec2(bg->getContentSize().width, 0)),
                                     DelayTime::create(2),
                                     MoveBy::create(0.3, Vec2(-bg->getContentSize().width, 0)),
                                     CallFunc::create([&]()
                                                          {
                                                              this->removeFromParentAndCleanup(true);
                                                          }),
                                     NULL));
}