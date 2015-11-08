//
//  TextLayer.cpp
//  Test
//
//  Created by KJTang on 15/7/17.
//
//

#include "TextLayer.h"

#include "GameScene.h"
#include "ScriptController.h"

TextLayer::TextLayer(){}

TextLayer::~TextLayer(){}

bool TextLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    pos = 0;
    textSpeed = 0.05;
    
    std::string fontFile = "fonts/PingFang_1.ttf";
    float fontSize = 55/(Director::getInstance()->getContentScaleFactor());
    Size textBoxSize = Size(1600, 300)/(Director::getInstance()->getContentScaleFactor());
    
    text = Label::createWithTTF("", fontFile, fontSize, textBoxSize);
    text->setPosition(Point(visibleSize.width*0.5, visibleSize.height*0.15));
    this->addChild(text, 5);
    
    Point position[4] = {Point(1, 0), Point(-1, 0), Point(0, -1), Point(0, 1)};
    for (int i = 0; i != 4; ++i) {
        outline[i] = Label::createWithTTF("", fontFile, fontSize, textBoxSize);
        this->addChild(outline[i], i+1);
        outline[i]->setPosition(text->getPosition()+position[i]);
        outline[i]->setOpacity(100);
        outline[i]->setColor(Color3B::RED);
    }
    
    bgChosen = Sprite::create("frame/Text-Chosen.png");
    bgUnchosen = Sprite::create("frame/Text-Unchosen.png");
    this->addChild(bgChosen);
    this->addChild(bgUnchosen);
    // add a tag
    bgChosen->setPosition(visibleSize.width/2, visibleSize.height*0.17);
    bgUnchosen->setPosition(visibleSize.width/2, visibleSize.height*0.17);
    bgChosen->setVisible(true);
    bgUnchosen->setVisible(false);
    
    enableTouchListener = false;
    
    return true;
}

void TextLayer::showText()
{
    if (textSpeed <= 0) {
        text->setString(strSave);
        for (int i = 0; i != 4; ++i) {
            outline[i]->setString(strSave);
        }
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
    for (int i = 0; i != 4; ++i) {
        outline[i]->setString(strSave);
    }
}

void TextLayer::clearText()
{
    pos = 0;
    text->setString("");
    for (int i = 0; i != 4; ++i) {
        outline[i]->setString("");
    }
}

void TextLayer::textUpdate(float dt)
{
    if (pos == strSave.size()) {
        stopText();
        enableTouchListener = false;
        
        GameScene::getInstance()->isMissionCompleted = true;
        ScriptController::getInstance()->isChoiceTableShowing = false;
        ScriptController::getInstance()->choiceTablePos = -1;
        ScriptController::getInstance()->choiceTableLineID = -1;
        
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
    
    text->setString(strShow);
    for (int i = 0; i != 4; ++i) {
        outline[i]->setString(strShow);
    }
}

void TextLayer::onClick()
{
    if (!enableTouchListener) {
        return;
    }
//    log("------------------textlayer is clicked");
    stopText();
    enableTouchListener = false;
    
    GameScene::getInstance()->isMissionCompleted = true;
    ScriptController::getInstance()->isChoiceTableShowing = false;
    ScriptController::getInstance()->choiceTablePos = -1;
    ScriptController::getInstance()->choiceTableLineID = -1;
}

void TextLayer::blurIn()
{
    text->setGLProgram(GLProgramCache::getInstance()->getGLProgram("textblur"));
    bgChosen->setVisible(false);
    bgUnchosen->setVisible(true);
}

void TextLayer::blurOut()
{
    text->setGLProgram(GLProgramCache::getInstance()->getGLProgram("textclear"));
    bgChosen->setVisible(true);
    bgUnchosen->setVisible(false);
}