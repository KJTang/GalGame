//
//  GameScene.h
//  Test
//
//  Created by KJTang on 15/7/16.
//
//

#ifndef GameScene_cpp
#define GameScene_cpp

#include "cocos2d.h"

#include "GameController.h"
#include "ScriptController.h"
#include "VariableController.h"

#include "TextLayer.h"
#include "ChoiceTableLayer.h"

using namespace cocos2d;

class GameScene : public Scene
{
private:
    static GameScene* sharedGameScene;
    Size visibleSize;
    Layer *backgroundLayer, *menuLayer;
    // game mode
    int gameMode;
    enum {
        MODE_NORMAL,
        MODE_AUTO,
        MODE_SKIP
    };
    
    // bgp
    Sprite *bgp;
    std::string bgpFilename;
    float bgpScale;
    float bgpDuration;
    float bgpPositionX, bgpPositionY;
    // charactors
    Sprite *ch01, *ch02, *ch03, *ch04;
    // text
    TextLayer *textLayer;
    std::string textToShow;
    // choices
    ChoiceTableLayer *choiceTable;
    
    EventListenerTouchOneByOne *touchListener;
    EventListenerCustom *textFinishListener;
public:
    GameScene();
    ~GameScene();
    
    virtual bool init();
    virtual void update(float dt);
    static GameScene* getInstance()
    {
        if (!sharedGameScene) {
            sharedGameScene = new GameScene();
            sharedGameScene->init();
        }
        return sharedGameScene;
    }
    void clear();
    
    // mission completed
    bool isMissionCompleted;
    // different way to start game
    void startNewGame();
    void startSavedGame();
    // game mode
    void enterSkipMode();
    void enterAutoMode();
    /**
     * set
     */
    // bgp
    bool setBgpStart();
    void setBgpClear();
    void setBgpFilename(std::string filename) { bgpFilename = filename; isMissionCompleted = true;}
    void setBgpDuration(float d) {bgpDuration = d; isMissionCompleted = true;}
    void setBgpScale(float scale) { bgpScale = scale; isMissionCompleted = true;}
    void setBgpPosition(float x, float y) {
        bgpPositionX = x, bgpPositionY = y;
        isMissionCompleted = true;
    }
    // ch01-ch04
    bool setCh01Picture(std::string filename);
    bool setCh02Picture(std::string filename);
    bool setCh03Picture(std::string filename);
    bool setCh04Picture(std::string filename);
    // text
    bool isTextShowing;
    void setTextShow();
    void setTextSpeed(float sp) { textLayer->setSpeed(sp); isMissionCompleted = true;}
    void setTextStop() { textLayer->stopText();}
    void setTextContent(std::string str) { textToShow = str; isMissionCompleted = true;}
    void setTextClear();
    void enableTextFinishedEventListener(bool btext);
    // choices
    void setChoiceNumber(int number);
    void setChoiceContent(int id, std::string content);
    void setChoiceChoosable(int id, bool choosable);
    void setChoiceShow();
    void getChoiceResult();
    void waitForChoiceResult(float dt);
    /**
     * get
     */
    void enableScreenTouchEventListener(bool btouch);
};

#endif /* GameScene_cpp */
