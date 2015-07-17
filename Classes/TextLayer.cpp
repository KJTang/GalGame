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
    
    text = Label::createWithSystemFont("", "AppleGothic", 50, Size(800, 200));
    text->setAnchorPoint(Point(0, 0));
    text->setPosition(Point(0, 0));
    this->addChild(text);
    
    return true;
}

void TextLayer::showText(float interval)
{
    this->schedule(schedule_selector(TextLayer::textUpdate), interval);
}

void TextLayer::stopText()
{
    this->unschedule(schedule_selector(TextLayer::textUpdate));
    // show all the text immediately
    text->setString(strSave);
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
}