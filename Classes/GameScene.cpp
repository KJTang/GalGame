//
//  GameScene.cpp
//  Test
//
//  Created by KJTang on 15/7/16.
//
//

#include "GameScene.h"
#include "ActionFade.h"
#include "ActionBlur.h"

const int choicetableOrder = 9;
const int blacklayerOrder = 10;
const int menulayerOrder = 11;

GameScene* GameScene::sharedGameScene = nullptr;

GameScene::GameScene(){}

GameScene::~GameScene(){}

bool GameScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    isMissionCompleted = false;
    enableGetTouch = false;
    focus = TEXT;
    
    gameMode = MODE_NORMAL;
    // Layers
    backgroundLayer = Layer::create();
    this->addChild(backgroundLayer);
    characterLayer = Layer::create();
    this->addChild(characterLayer);
    // text
    textLayer = TextLayer::create();
    this->addChild(textLayer);
    textLayer->setVisible(false);
    // black layer
    blackLayer = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);
    this->addChild(blackLayer, blacklayerOrder);
    blackLayer->setOpacity(0);
    // menu
    menuLayer = MenuLayer::create();
    this->addChild(menuLayer, menulayerOrder);
    // bgp
    bgp = nullptr;
    bgpDuration = 0, bgpScale = 1.5, bgpPositionX = 0, bgpPositionY = 0;
    // characters
    for (int i = 0; i != 4; ++i) {
        characters[i] = nullptr;
        characterDuration[i] = 0;
        characterScale[i] = 0.5;
        characterPositionX[i] = 0.5;
        characterPositionY[i] = 0.5;
        characterEffect[i] = nullptr;
    }
    // choices
    choiceTable = nullptr;
    
    // buttons
    quitButton = ButtonSprite::create("title/start");
    menuLayer->addChild(quitButton);
    quitButton->setScale(1.5);
    quitButton->setPosition(Point(visibleSize.width*0.75, visibleSize.height*0.25));
    quitButton->setCallbackFunc([](){
        log("back to StartScene");
        GameController::getInstance()->enterStartScene();
        // when quit GameScene, we should clear it
        GameScene::getInstance()->clear();
    });
    
    saveButton = ButtonSprite::create("title/load");
    menuLayer->addChild(saveButton);
    saveButton->setScale(1.5);
    saveButton->setPosition(Point(visibleSize.width*0.75, visibleSize.height*0.75));
    saveButton->setCallbackFunc([](){
        char datafile[50];
        time_t curtime=time(0);
        tm time =*localtime(&curtime);
        sprintf(datafile, "%d年%02d月%02d日%02d时%02d分%02d秒", time.tm_year+1900, time.tm_mon+1, time.tm_mday, time.tm_hour, time.tm_min, time.tm_sec);
        log("save data: %s", datafile);
        DataController::getInstance()->saveData(datafile);
    });
    
    // screen touch listener
    screenTouchListener = EventListenerTouchOneByOne::create();
    screenTouchListener->setSwallowTouches(false);
    screenTouchListener->onTouchBegan = [&](Touch* touch, Event* event){
        return true;
    };
    screenTouchListener->onTouchEnded = [&](Touch* touch, Event* event){
        if (textLayer && textLayer->isVisible()) {
            auto textRect = new Rect(0, 0, visibleSize.width, visibleSize.height * 0.3);
            if (textRect->containsPoint(touch->getLocation())) {
                log("text area touched!");
                if (focus == CHARACTER) {
                    textLayer->blurOut();
                    for (int j = 0; j != 4; ++j) {
                        if (characters[j]) {
//                            characters[j]->runAction(ActionBlur2::create(0.5, NONE_TO_MUCH));
                            characters[j]->runAction(ActionBlur::create(0.5, 2000, 300));
                        }
                    }
                    auto bgs = bgp->getChildren();
                    for (int j = 0; j != bgs.size(); ++j) {
//                        bgs.at(j)->runAction(ActionBlur2::create(0.5, LITTLE_TO_MUCH));
                        bgs.at(j)->runAction(ActionBlur::create(0.5, 1500, 1000));
                    }
                } else if (focus == BACKGROUND) {
                    textLayer->blurOut();
                    auto bgs = bgp->getChildren();
                    for (int j = 0; j != bgs.size(); ++j) {
                        if (!characterLayer->getChildren().size()) {
//                            bgs.at(j)->runAction(ActionBlur2::create(0.5, NONE_TO_LITTLE));
                            bgs.at(j)->runAction(ActionBlur::create(0.5, 2000, 1500));
                        } else {
//                            bgs.at(j)->runAction(ActionBlur2::create(0.5, NONE_TO_MUCH));
                            bgs.at(j)->runAction(ActionBlur::create(0.5, 1500, 1000));
                        }
                    }
                }
                else {
                    if (enableGetTouch) {
                        isMissionCompleted = true;
                    }
                    textLayer->onClick();
                }
                focus = TEXT;
                return false;
            }
        }
        for (int i = 0; i != 4; ++i) {
            if (characters[i] && characters[i]->getBoundingBox().containsPoint(touch->getLocation())) {
                log("character %d area touched!", i);
                if (focus == TEXT) {
                    textLayer->blurIn();
                    for (int j = 0; j != 4; ++j) {
                        if (characters[j]) {
//                            characters[j]->runAction(ActionBlur2::create(0.5, MUCH_TO_NONE));
                            characters[j]->runAction(ActionBlur::create(0.5, 300, 0));
                        }
                    }
                    auto bgs = bgp->getChildren();
                    for (int j = 0; j != bgs.size(); ++j) {
//                        bgs.at(j)->runAction(ActionBlur2::create(0.5, MUCH_TO_LITTLE));
                        bgs.at(j)->runAction(ActionBlur::create(0.5, 1000, 1500));
                    }
                } else if (focus == BACKGROUND) {
                    for (int j = 0; j != 4; ++j) {
                        if (characters[j]) {
//                            characters[j]->runAction(ActionBlur2::create(0.5, MUCH_TO_NONE));
                            characters[j]->runAction(ActionBlur::create(0.5, 300, 0));
                        }
                    }
                    auto bgs = bgp->getChildren();
                    for (int j = 0; j != bgs.size(); ++j) {
//                        bgs.at(j)->runAction(ActionBlur2::create(0.5, NONE_TO_LITTLE));
                        bgs.at(j)->runAction(ActionBlur::create(0.5, 2000, 1500));
                    }
                }
                focus = CHARACTER;
                return false;
            }
        }
        log("background area touched!");
        if (focus == TEXT) {
            textLayer->blurIn();
            auto bgs = bgp->getChildren();
            for (int j = 0; j != 4; ++j) {
                if (characters[j]) {
//                    characters[j]->runAction(ActionBlur2::create(0.5, NONE_TO_MUCH));
                    characters[j]->runAction(ActionBlur::create(0.5, 2000, 300));
                }
            }
            for (int j = 0; j != bgs.size(); ++j) {
//                bgs.at(j)->runAction(ActionBlur2::create(0.5, MUCH_TO_NONE));
                bgs.at(j)->runAction(ActionBlur::create(0.5, 1000, 0));
            }
            focus = BACKGROUND;
            return false;
        } else if (focus == CHARACTER) {
            for (int j = 0; j != 4; ++j) {
                if (characters[j]) {
//                    characters[j]->runAction(ActionBlur2::create(0.5, NONE_TO_MUCH));
                    characters[j]->runAction(ActionBlur::create(0.5, 2000, 300));
                }
            }
            auto bgs = bgp->getChildren();
            for (int j = 0; j != bgs.size(); ++j) {
//                bgs.at(j)->runAction(ActionBlur2::create(0.5, LITTLE_TO_NONE));
                bgs.at(j)->runAction(ActionBlur::create(0.5, 1500, 0));
            }
            focus = BACKGROUND;
            return false;
        }
        
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(screenTouchListener, this);
    
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

void GameScene::saveFlags()
{
    if (!ScriptController::getInstance()->isChoiceTableShowing) {
        UserData.pos = ScriptController::getInstance()->getPos();
        UserData.lineID = ScriptController::getInstance()->getLineID();
    } else {
        UserData.pos = ScriptController::getInstance()->choiceTablePos;
        UserData.lineID = ScriptController::getInstance()->choiceTableLineID;
    }
    UserData.gobackPos = ScriptController::getInstance()->getGoBackPosMark();
    UserData.gobackLineID = ScriptController::getInstance()->getGoBackLineMark();
    UserData.isConditionFullFilled = ScriptController::getInstance()->isConditionFullFilled;
    UserData.choiceTablePos = ScriptController::getInstance()->choiceTablePos;
    UserData.choiceTableLineID = ScriptController::getInstance()->choiceTableLineID;
}

void GameScene::clear()
{
//    log("GameScene clearing");
    this->removeAllChildren();
    backgroundLayer = nullptr, characterLayer = nullptr, menuLayer = nullptr;
    textLayer = nullptr;
    choiceTable = nullptr;
    
    GameController::getInstance()->stopBGM();

//    if (this->isScheduled(schedule_selector(GameScene::update))) {   // this 'if' is no use
        this->unscheduleUpdate();
//    }
    if (screenTouchListener) {
        _eventDispatcher->removeEventListener(screenTouchListener);
        screenTouchListener = nullptr;
    }

//    log("GameScene cleared");
}

void GameScene::startNewGame()
{
    this->init();
    DataController::getInstance()->readFromScript();
    ScriptController::getInstance()->runNew("file.txt");
    
    isMissionCompleted = true;
    this->scheduleUpdate();
}

void GameScene::startSavedGame(std::string datafile)
{
    log("GameScene::startSavedGame");
    this->init();
    // variables
    DataController::getInstance()->readFromData(datafile);
    // flags and scene
    std::string path = FileUtils::getInstance()->getWritablePath()+datafile;
    std::ifstream fin(path.c_str());
    // used later
    std::string scriptpath;
    int choicetable = -1;
    
    std::string str;
    fin>>str;
    bool bgp = false, text = false;
    bool character[4] = {false, false, false, false};
    while (str.size()) {
        if (str == "scriptpath") {
            fin>>scriptpath;
            UserData.scriptPath = scriptpath;
        } else if (str == "pos") {
            int dataPos;
            fin>>dataPos;
            ScriptController::getInstance()->setPos(dataPos);
        } else if (str == "lineID") {
            int dataLineID;
            fin>>dataLineID;
            ScriptController::getInstance()->setLineID(dataLineID);
        } else if (str == "gobackPos") {
            int gobackPos;
            fin>>gobackPos;
            ScriptController::getInstance()->setGoBackPosMark(gobackPos);
        } else if (str == "gobackLineID") {
            int gobackLineID;
            fin>>gobackLineID;
            ScriptController::getInstance()->setGoBackLineMark(gobackLineID);
        } else if (str == "condition") {
            bool condition;
            fin>>condition;
            ScriptController::getInstance()->isConditionFullFilled = condition;
        } else if (str == "choicetablePos") {
            int pos;
            fin>>pos;
            choicetable = pos;
            ScriptController::getInstance()->choiceTablePos = pos;
        } else if (str == "choicetableLine") {
            int line;
            fin>>line;
            ScriptController::getInstance()->choiceTableLineID = line;
        } else if (str == "bgm") {
            fin>>str;
            if (str == "filename") {
                fin>>str;
                GameController::getInstance()->loadBGM(str);
                GameController::getInstance()->playBGM();
                log("load bgm =%s", str.c_str());
            }
        } else if (str == "bgp") {
            bgp = true;
            fin>>str;
            if (str == "filename") {
                fin>>bgpFilename;
            } else if (str == "scale") {
                fin>>bgpScale;
            } else if (str == "positionx") {
                fin>>bgpPositionX;
            } else if (str == "positiony") {
                fin>>bgpPositionY;
            }
        } else if (str == "character") {
            int id;
            fin>>id;
            character[id] = true;
            fin>>str;
            if (str == "filename") {
                fin>>characterFilename[id];
            } else if (str == "scale") {
                fin>>characterScale[id];
            } else if (str == "positionx") {
                fin>>characterPositionX[id];
            } else if (str == "positiony") {
                fin>>characterPositionY[id];
            }
        } else if (str == "text") {
            text = true;
            fin>>str;
            if (str == "content") {
                fin>>str;
                log("load text =%s", str.c_str());
            } else if (str == "pos") {
                int pos;
                fin>>pos;
                ScriptController::getInstance()->textPos = pos;
                log("set text pos = %d", ScriptController::getInstance()->textPos);
            } else if (str == "lineid") {
                int lineid;
                fin>>lineid;
                ScriptController::getInstance()->textLineID = lineid;
            }
        } else {
            break;
        }
        fin>>str;
    }
    fin.close();
    
    // show
    if (bgp) {
        this->setBgpStart();
        log("load bgp =%s", bgpFilename.c_str());
    }
    for (int i = 0; i != 4; ++i) {
        if (character[i]) {
            this->setCharacterStart(i);
            log("load character %d =%s", i, characterFilename[i].c_str());
        }
    }
    
    // load
    this->runAction(Sequence::create(DelayTime::create(0.3),  // wait, make sure bgp, character... are loaded,
                                                              // and they will not modify 'isMissionCompleted'
                                     CallFunc::create([=]()
                                                      {
                                                          isMissionCompleted = true;
                                                          ScriptController::getInstance()->runSaved(scriptpath);
                                                          this->scheduleUpdate();
                                                      }),
                                     NULL));
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
    blackLayer->runAction(Sequence::create(FadeIn::create(0.15),
                                           CallFunc::create([&]() {
        if (bgp) {
            bgp->removeFromParentAndCleanup(true);
            bgp = nullptr;
        }
        bgp = GyroBackground::create(bgpFilename, bgpScale);
        backgroundLayer->addChild(bgp);
        
        bgp->setScale(visibleSize.width/bgp->getContentSize().width*bgpScale);
        bgp->setPosition(Point(visibleSize.width*bgpPositionX, visibleSize.height*bgpPositionY));
        
        if (focus == TEXT) {
            auto bgs = bgp->getChildren();
            for (int j = 0; j != bgs.size(); ++j) {
                bgs.at(j)->runAction(ActionBlur::create(0.5, 2000, 1000));
            }
        } else if (focus == CHARACTER) {
            auto bgs = bgp->getChildren();
            for (int j = 0; j != bgs.size(); ++j) {
                bgs.at(j)->runAction(ActionBlur::create(0.5, 2000, 1500));
            }
        }
        isMissionCompleted = true;
        
        // save data
        UserData.bgpFilename = bgpFilename;
        UserData.bgpScale = bgpScale;
        UserData.bgpPositionX = bgpPositionX;
        UserData.bgpPositionY = bgpPositionY;
        
        // set default
        bgpScale = 1.5;
        bgpDuration = 0;
        bgpPositionX = 0, bgpPositionY = 0;
    }),
                                           DelayTime::create(0.2),
                                           FadeOut::create(0.15),
                                           NULL));
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

void GameScene::setCharacterEffect(int id, std::string effect)
{
    if (id > 3 || id < 0) {
        log("character id wrong");
        return;
    }
    if (effect == "fade") {
        characterEffect[id] = Sequence::create(FadeIn::create(1), NULL);
    } else if (effect == "wave") {
        characterEffect[id] = Spawn::create(MoveTo::create(1, Point(characterPositionX, characterPositionY)), NULL);
    }
    
    isMissionCompleted = true;
}

void GameScene::setCharacterClear(int id)
{
    if (id > 3 || id < 0) {
        log("character id wrong");
        return;
    }
    if (characters[id]) {
        log("delete character%02d", id);
        // cause "FadeOut" used default shader, so we should set it back
        characters[id]->setGLProgramState(GLProgramState::getOrCreateWithGLProgramName(GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR_NO_MVP));
        characters[id]->runAction(Sequence::create(FadeOut::create(0.2),
                                                   CallFunc::create([=]()
                                                                    {
                                                                        characters[id]->removeFromParentAndCleanup(true);
                                                                        characters[id] = nullptr;
                                                                    }),
                                                   NULL));
    }
    isMissionCompleted = true;
    
    // clear data
    UserData.characterFilename[id] = "";
    UserData.characterScale[id] = 0.5;
    UserData.characterPositionX[id] = 0.5;
    UserData.characterPositionY[id] = 0.5;
}

void GameScene::setCharacterStart(int id)
{
    if (id > 3 || id < 0) {
        log("character id wrong");
        return;
    }
    if (characters[id]) {
        characters[id]->removeFromParentAndCleanup(true);
        characters[id] = nullptr;
    }
    characters[id] = Sprite::create(characterFilename[id]);
    characterLayer->addChild(characters[id]);
    characters[id]->setScale(characterScale[id]);
    characters[id]->setPosition(visibleSize.width * characterPositionX[id],
                                visibleSize.height * characterPositionY[id]);
    
//    if (characterEffect[id]) {
//        log("characterEffect sth.");
//        characters[id]->runAction(characterEffect[id]);
//        characterEffect[id] = nullptr;
//    } else {
//        log("characterEffect none");
////        characters[id]->runAction(FadeIn::create(5));
//    }
    
    // enter effect
    characters[id]->setOpacity(0);
    if (focus != CHARACTER) {
        characters[id]->runAction(Sequence::create(FadeIn::create(0.5),
                                                   ActionBlur::create(0.5, 2000, 300),
                                                   NULL));
    } else {
        characters[id]->runAction(FadeIn::create(0.5));
    }
    isMissionCompleted = true;
    
    //save data
    UserData.characterFilename[id] = characterFilename[id];
    UserData.characterScale[id] = characterScale[id];
    UserData.characterPositionX[id] = characterPositionX[id];
    UserData.characterPositionY[id] = characterPositionY[id];
    
    // set default
    characterScale[id] = 0.5;
    characterDuration[id] = 0;
    characterPositionX[id] = 0.5, characterPositionY[id] = 0.5;
}

/**
 * text
 */
void GameScene::setTextShow()
{
    textLayer->setText(textToShow);
    textLayer->setVisible(true);
    //
    
    switch (gameMode) {
        case MODE_NORMAL:
            textLayer->showText();
            break;
        case MODE_SKIP:
            textLayer->setSpeed(0.01);
            textLayer->showText();
            break;
        case MODE_AUTO:
            textLayer->setSpeed(0.2);
            textLayer->showText();
            break;
        default:
            break;
    }
    
    textLayer->enableTouchListener = true;
    // save data
    UserData.textContent = textToShow;
    UserData.textPos = ScriptController::getInstance()->textPos;
    UserData.textLineID = ScriptController::getInstance()->textLineID;
}

void GameScene::setTextStop()
{
    textLayer->stopText();
}

void GameScene::setTextUpdate(const std::string &str)
{
    textToShow = str;
    textLayer->setText(textToShow);
    textLayer->setVisible(true);
    
    switch (gameMode) {
        case MODE_NORMAL:
            textLayer->showText();
            break;
        case MODE_SKIP:
            textLayer->setSpeed(0.01);
            textLayer->showText();
            break;
        case MODE_AUTO:
            textLayer->setSpeed(0.2);
            textLayer->showText();
            break;
        default:
            break;
    }
    
    textLayer->enableTouchListener = true;
    // save data
    UserData.textContent = textToShow;
    UserData.textPos = ScriptController::getInstance()->textPos;
    UserData.textLineID = ScriptController::getInstance()->textLineID;
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
    textLayer->clearText();
    textLayer->setVisible(false);
    isMissionCompleted = true;
    // clear data
    UserData.textContent.clear();
    UserData.textPos = -1;
    UserData.textLineID = -1;
}
//
//void GameScene::enableTextFinishedEventListener(bool b)
//{
//    textFinishListener->setEnabled(b);
//}

/**
 * choices
 */
void GameScene::setChoiceNumber(int number)
{
    choiceTable = ChoiceTableLayer::create();
    this->addChild(choiceTable, choicetableOrder);
    
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
    // initalize the choose result
    DataController::getInstance()->setInt("choiceresult", -1);
    isMissionCompleted = true;
}

/**
 * wait
 */

void GameScene::setWaitTime(float time)
{
    this->runAction(Sequence::create(DelayTime::create(time),
                                     CallFunc::create([&](){isMissionCompleted = true;}),
                                     NULL));
}

/**
 * get Touch
 */
void GameScene::enableScreenTouchEventListener(bool btouch, float delay)
{
    if (btouch) {
        switch (gameMode) {
            case MODE_NORMAL:
                enableGetTouch = true;
                break;
            case MODE_SKIP:
                this->runAction(Sequence::create(DelayTime::create(delay * 0.2),
                                                 CallFunc::create([&](){isMissionCompleted=true;}),
                                                 NULL));
                break;
            case MODE_AUTO:
                this->runAction(Sequence::create(DelayTime::create(delay),
                                                 CallFunc::create([&](){isMissionCompleted=true;}),
                                                 NULL));
            default:
                break;
        }
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
    if (!choiceTable) {
        return;
    }
    int result = choiceTable->getChoiceReuslt();
    if (result == -1) {
        return;
    }
    DataController::getInstance()->setInt("choiceresult", result);
    log("get choice result = %d", result);
    // set default
    ScriptController::getInstance()->isChoiceTableShowing = false;
    ScriptController::getInstance()->choiceTablePos = -1;
    ScriptController::getInstance()->choiceTableLineID = -1;
    
    choiceTable->removeFromParentAndCleanup(true);
    choiceTable = nullptr;
    this->unschedule(schedule_selector(GameScene::waitForChoiceResult));

    isMissionCompleted = true;
}