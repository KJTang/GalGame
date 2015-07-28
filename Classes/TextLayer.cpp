//
//  TextLayer.cpp
//  Test
//
//  Created by KJTang on 15/7/17.
//
//

#include "TextLayer.h"

TextLayer::TextLayer(){}

TextLayer::~TextLayer(){}

bool TextLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    pos = 0;
    textSpeed = 0.1;
    
    std::string fontFile = "fonts/PingFang_7.ttf";
    
    text = Label::createWithTTF("", fontFile, 40, Size(800, 200));
    text->setAnchorPoint(Point(0, 0));
    text->setPosition(Point(0, 0));
    this->addChild(text, 5);
    
    outline01 = Label::createWithTTF("", fontFile, 40, Size(800, 200));
    outline01->setAnchorPoint(Point(0, 0));
    outline01->setPosition(Point(1, 0));
    outline01->setColor(Color3B::RED);
    this->addChild(outline01, 1);
    
    outline02 = Label::createWithTTF("", fontFile, 40, Size(800, 200));
    outline02->setAnchorPoint(Point(0, 0));
    outline02->setPosition(Point(-1, 0));
    outline02->setColor(Color3B::RED);
    this->addChild(outline02, 2);
    
    outline03 = Label::createWithTTF("", fontFile, 40, Size(800, 200));
    outline03->setAnchorPoint(Point(0, 0));
    outline03->setPosition(Point(0, 1));
    outline03->setColor(Color3B::RED);
    this->addChild(outline03, 3);
    
    outline04 = Label::createWithTTF("", fontFile, 40, Size(800, 200));
    outline04->setAnchorPoint(Point(0, 0));
    outline04->setPosition(Point(0, -1));
    outline04->setColor(Color3B::RED);
    this->addChild(outline04, 4);
    
//    background = Sprite::create();
//    this->addChild(background);
    
    return true;
}

void TextLayer::showText()
{
    if (textSpeed <= 0) {
        text->setString(strSave);
        outline01->setString(strSave);
        outline02->setString(strSave);
        outline03->setString(strSave);
        outline04->setString(strSave);
        return;
    }
    pos = 0;
    this->schedule(schedule_selector(TextLayer::textUpdate), textSpeed);
}

void TextLayer::stopText()
{
    this->unschedule(schedule_selector(TextLayer::textUpdate));
    // show all the text immediately
    text->setString(strSave);
    
    outline01->setString(strSave);
    outline02->setString(strSave);
    outline03->setString(strSave);
    outline04->setString(strSave);
}

void TextLayer::clearText()
{
    pos = 0;
    text->setString("");
    outline01->setString("");
    outline02->setString("");
    outline03->setString("");
    outline04->setString("");
}

void TextLayer::postStopedMsg()
{
    EventCustom event("TextFinished");
    _eventDispatcher->dispatchEvent(&event);
}

void TextLayer::textUpdate(float dt)
{
    if (pos == strSave.size()) {
        stopText();
        // post a "TextFinished" event
        postStopedMsg();
        this->unscheduleUpdate();
        return;
    }
    
    if (strSave[pos] <= 127 && strSave[pos] >= 0) {
        strShow += strSave[pos];
        ++pos;
    }
    else {
        strShow += strSave[pos];
        strShow += strSave[pos+1];
        strShow += strSave[pos+2];
        pos += 3;
    }
    
//    log("string = %s", strShow.c_str());
    text->setString(strShow);
    
    outline01->setString(strShow);
    outline02->setString(strShow);
    outline03->setString(strShow);
    outline04->setString(strShow);
}