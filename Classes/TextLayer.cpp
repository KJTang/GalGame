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
    textSpeed = 0.1;
    
    std::string fontFile = "fonts/PingFang_1.ttf";
    float fontSize = 50;
    Size textBoxSize = Size(1500, 300);
    
    text = Label::createWithTTF("", fontFile, fontSize, textBoxSize);
    text->setPosition(Point(visibleSize.width*0.5, visibleSize.height*0.16));
    this->addChild(text, 5);
    
    outline01 = Label::createWithTTF("", fontFile, fontSize, textBoxSize);
    outline01->setOpacity(100);
    outline01->setPosition(text->getPosition()+Point(1, 0));
    outline01->setColor(Color3B::RED);
    this->addChild(outline01, 1);
    
    outline02 = Label::createWithTTF("", fontFile, fontSize, textBoxSize);
    outline02->setOpacity(100);
    outline02->setPosition(text->getPosition()+Point(-1, 0));
    outline02->setColor(Color3B::RED);
    this->addChild(outline02, 2);
    
    outline03 = Label::createWithTTF("", fontFile, fontSize, textBoxSize);
    outline03->setOpacity(100);
    outline03->setPosition(text->getPosition()+Point(0, 1));
    outline03->setColor(Color3B::RED);
    this->addChild(outline03, 3);
    
    outline04 = Label::createWithTTF("", fontFile, fontSize, textBoxSize);
    outline04->setOpacity(100);
    outline04->setPosition(text->getPosition()+Point(0, -1));
    outline04->setColor(Color3B::RED);
    this->addChild(outline04, 4);
    
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
    
    outline01->setString(strShow);
    outline02->setString(strShow);
    outline03->setString(strShow);
    outline04->setString(strShow);
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