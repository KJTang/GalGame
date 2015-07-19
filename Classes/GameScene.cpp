
//
//  GameScene.cpp
//  Test
//
//  Created by KJTang on 15/7/16.
//
//

#include "GameScene.h"

GameScene* GameScene::sharedGameScene = nullptr;

GameScene::GameScene(){}

GameScene::~GameScene(){}

bool GameScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    isMissionCompleted = true;
    isTextShowing = false;
    
    gameMode = MODE_NORMAL;
    
    backgroundLayer = Layer::create();
    this->addChild(backgroundLayer);
    
    characterLayer = Layer::create();
    this->addChild(characterLayer);
    
    menuLayer = Layer::create();
    this->addChild(menuLayer);
    
    // text
    textLayer = nullptr;
    // bgp
    bgp = nullptr;
    bgpDuration = 0, bgpScale = 1, bgpPositionX = 0.5, bgpPositionY = 0.5;
    // characters
    for (int i = 0; i != 4; ++i) {
        characters[i] = nullptr;
        characterDuration[i] = 0;
        characterScale[i] = 0.2;
        characterPositionX[i] = 0.5;
        characterPositionY[i] = 0.5;
    }
    // choices
    choiceTable = nullptr;
    
    // temp
    auto button1 = ButtonSprite::create("CloseNormal.png");
    menuLayer->addChild(button1);
    button1->setScale(3.5);
    button1->setPosition(Point(visibleSize.width*0.75, visibleSize.height/2));
    button1->setCallbackFunc([](){
        log("back to StartScene");
        GameController::getInstance()->enterStartScene();
    });
    
    // touch listener
    touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [](Touch* touch, Event* event){
        return true;
    };
    touchListener->onTouchEnded = [&](Touch* touch, Event* event){
        auto target = static_cast<GameScene*>(event->getCurrentTarget());
        // got touch
        switch (gameMode) {
            case MODE_NORMAL:
                // if text is showing, stop it right now
                if (target->isTextShowing) {
                    // post a "TextFinished" event
                    target->isTextShowing = false;
                    target->setTextStop();
                    target->enableTextFinishedEventListener(false);
                }
                target->isMissionCompleted = true;
                target->enableScreenTouchEventListener(false);
                break;
            case MODE_SKIP:
                gameMode = MODE_NORMAL;
                target->enableScreenTouchEventListener(false);
                break;
            case MODE_AUTO:
                gameMode = MODE_NORMAL;
                target->enableScreenTouchEventListener(false);
                break;
            default:
                break;
        }
        return false;
    };
    touchListener->setEnabled(false);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    // text finish listener
    textFinishListener = EventListenerCustom::create("TextFinished", [&](Event* event){
        auto target = static_cast<GameScene*>(event->getCurrentTarget());
        target->isTextShowing = false;
        target->setTextStop();
        target->isMissionCompleted = true;
        target->enableScreenTouchEventListener(false);
        target->enableTextFinishedEventListener(false);
    });
    textFinishListener->setEnabled(false);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(textFinishListener, this);
    
    return true;
}

void GameScene::update(float dt)
{
    if (!isMissionCompleted) {
        return;
    }
    isMissionCompleted = false;
    ScriptController::getInstance()->stateBegin();
}

void GameScene::clear()
{
    this->removeAllChildren();
    this->unscheduleUpdate();
    _eventDispatcher->removeEventListener(touchListener);
    _eventDispatcher->removeEventListener(textFinishListener);
    this->init();
}

void GameScene::startNewGame()
{
    this->clear();
    VariableController::getInstance()->readFromScript();
    ScriptController::getInstance()->runWithFile("file.txt", 1);
    
    this->scheduleUpdate();
}

void GameScene::startSavedGame()
{
    log("load saved game");
}

void GameScene::enterSkipMode()
{
    gameMode = MODE_SKIP;
}

void GameScene::enterAutoMode()
{
    gameMode = MODE_AUTO;
}

/**
 *   bgp
 */
void GameScene::setBgpFilename(std::string filename)
{
    bgpFilename = filename;
    isMissionCompleted = true;
}

void GameScene::setBgpStart()
{
    if (bgp) {
        bgp->removeFromParentAndCleanup(true);
    }
    bgp = Sprite::create(bgpFilename);
    backgroundLayer->addChild(bgp);
    
    bgp->setScale(visibleSize.width/bgp->getContentSize().width*bgpScale);
    bgp->setPosition(Point(visibleSize.width*bgpPositionX, visibleSize.height*bgpPositionY));
    
    switch (gameMode) {
        case MODE_NORMAL:
            isMissionCompleted = true;
            break;
        case MODE_SKIP:
            this->runAction(Sequence::create(DelayTime::create(bgpDuration*0.2),
                                             CallFunc::create([&](){isMissionCompleted=true;}),
                                             NULL));
            break;
        case MODE_AUTO:
            this->runAction(Sequence::create(DelayTime::create(bgpDuration),
                                             CallFunc::create([&](){isMissionCompleted=true;}),
                                             NULL));
            break;
        default:
            break;
    }
    
    // set default
    bgpScale = 1;
    bgpDuration = 0;
    bgpPositionX = 0.5, bgpPositionY = 0.5;
}

void GameScene::setBgpDuration(float d)
{
    bgpDuration = d;
    isMissionCompleted = true;
}

void GameScene::setBgpScale(float scale)
{
    bgpScale = scale;
    isMissionCompleted = true;
}

void GameScene::setBgpPosition(float x, float y)
{
    bgpPositionX = x, bgpPositionY = y;
    isMissionCompleted = true;
}

/**
 * characters
 */
void GameScene::setCharacterFilename(int id, std::string filename)
{
    if (id > 3 || id < 0) {
        log("character id wrong");
        return;
    }
    characterFilename[id] = filename;
    isMissionCompleted = true;
}

void GameScene::setCharacterDuration(int id, float duration)
{
    if (id > 3 || id < 0) {
        log("character id wrong");
        return;
    }
    characterDuration[id] = duration;
    isMissionCompleted = true;
}

void GameScene::setCharacterScale(int id, float scale)
{
    if (id > 3 || id < 0) {
        log("character id wrong");
        return;
    }
    characterScale[id] = scale;
    isMissionCompleted = true;
}

void GameScene::setCharacterPosition(int id, float x, float y)
{
    if (id > 3 || id < 0) {
        log("character id wrong");
        return;
    }
    characterPositionX[id] = x;
    characterPositionY[id] = y;
    isMissionCompleted = true;
}

void GameScene::setCharacterClear(int id)
{
    if (id > 3 || id < 0) {
        log("character id wrong");
        return;
    }
    if (characters[id]) {
        characters[id]->removeFromParentAndCleanup(true);
    }
    characters[id] = nullptr;
    isMissionCompleted = true;
}

void GameScene::setCharacterStart(int id)
{
    if (id > 3 || id < 0) {
        log("character id wrong");
        return;
    }
    if (characters[id]) {
        characters[id]->removeFromParentAndCleanup(true);
    }
    characters[id] = Sprite::create(characterFilename[id]);
    characterLayer->addChild(characters[id]);
    characters[id]->setScale(visibleSize.width/characters[id]->getContentSize().width * characterScale[id]);
    characters[id]->setPosition(visibleSize.width * characterPositionX[id],
                                visibleSize.height * characterPositionY[id]);
    
    isMissionCompleted = true;
    
    // set default
    characterScale[id] = 0.2;
    characterDuration[id] = 0;
    characterPositionX[id] = 0.5, characterPositionY[id] = 0.5;
}

/**
 * text
 */
void GameScene::setTextShow()
{
    if (textLayer) {
        textLayer->removeFromParentAndCleanup(true);
    }
    textLayer = TextLayer::create();
    this->addChild(textLayer);
    textLayer->setText(textToShow);
    
    switch (gameMode) {
        case MODE_NORMAL:
            textLayer->showText();
            isTextShowing = true;
            touchListener->setEnabled(true);
            textFinishListener->setEnabled(true);
            break;
        case MODE_SKIP:
            textLayer->setSpeed(0.01);
            textLayer->showText();
            isTextShowing = true;
            touchListener->setEnabled(true);
            textFinishListener->setEnabled(true);
            break;
        case MODE_AUTO:
            textLayer->setSpeed(0.2);
            textLayer->showText();
            isTextShowing = true;
            touchListener->setEnabled(true);
            textFinishListener->setEnabled(true);
            break;
        default:
            break;
    }
}

void GameScene::setTextStop()
{
    textLayer->stopText();
}

void GameScene::setTextContent(std::string content)
{
    textToShow = content;
    isMissionCompleted = true;
}

void GameScene::setTextSpeed(float sp)
{
    textLayer->setSpeed(sp);
    isMissionCompleted = true;
}

void GameScene::setTextClear()
{
    if (textLayer) {
        textLayer->removeFromParentAndCleanup(true);
    }
    textLayer = nullptr;
    
    isMissionCompleted = true;
}

void GameScene::enableTextFinishedEventListener(bool b)
{
    textFinishListener->setEnabled(b);
}

/**
 * choices
 */
void GameScene::setChoiceNumber(int number)
{
    choiceTable = ChoiceTableLayer::create();
    this->addChild(choiceTable);
    
    choiceTable->setChoiceNumber(number);
    isMissionCompleted = true;
}

void GameScene::setChoiceContent(int id, std::string content)
{
    choiceTable->setChoiceContent(id, content);
    isMissionCompleted = true;
}

void GameScene::setChoiceChoosable(int id, bool choosable)
{
    choiceTable->setChoiceChoosable(id, choosable);
    isMissionCompleted = true;
}

void GameScene::setChoiceShow()
{
    choiceTable->showChoiceTable();
    VariableController::getInstance()->setInt("choiceresult", -1);
    isMissionCompleted = true;
}

/**
 * get Touch
 */
void GameScene::enableScreenTouchEventListener(bool btouch)
{
    if (btouch) {
        touchListener->setEnabled(true);
        switch (gameMode) {
            case MODE_SKIP:
                isMissionCompleted = true;
                break;
            case MODE_AUTO:
                isMissionCompleted = true;
            default:
                break;
        }
    }
    else {
        touchListener->setEnabled(false);
    }
}

/**
 * get Choice
 */
void GameScene::getChoiceResult()
{
    this->schedule(schedule_selector(GameScene::waitForChoiceResult), 1.0/60);
}

void GameScene::waitForChoiceResult(float dt)
{
    int result = choiceTable->getChoiceReuslt();
    if (result == -1) {
        return;
    }
    VariableController::getInstance()->setInt("choiceresult", result);
    log("get choice result = %d", result);
    isMissionCompleted = true;
    choiceTable->removeFromParentAndCleanup(true);
    this->unschedule(schedule_selector(GameScene::waitForChoiceResult));
}