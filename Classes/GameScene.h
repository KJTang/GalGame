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
#include "DataController.h"

#include "TextLayer.h"
#include "HistoryLayer.h"
#include "ChoiceTableLayer.h"
#include "MenuLayer.h"
#include "GyroBackground.h"

using namespace cocos2d;

class GameScene : public Scene
{
private:
    static GameScene* sharedGameScene;
    Size visibleSize;
    Layer *backgroundLayer;
    Layer *characterLayer;
    LayerColor *blackLayer;
    MenuLayer *menuLayer;
    // game mode
    int gameMode;
    enum {
        MODE_NORMAL,
        MODE_AUTO,
        MODE_SKIP
    };
    
    // bgp
    GyroBackground *bgp;
    std::string bgpFilename;
    float bgpScale;
    float bgpDuration;
    float bgpPositionX, bgpPositionY;
    // characters
    Sprite* characters[4];
    std::string characterFilename[4];
    float characterScale[4];
    float characterDuration[4];
    float characterPositionX[4], characterPositionY[4];
    Action *characterEffect[4];
    // text
    TextLayer *textLayer;
    std::string textToShow;
    HistoryLayer *historyLayer;
public:
    std::vector<std::string> historyText;
private:
    // choices
    ChoiceTableLayer *choiceTable;

    // event listener
    EventListenerTouchOneByOne *screenTouchListener;
    bool enableGetTouch;
public:
    GameScene();
    ~GameScene();
    
    virtual bool init();
    virtual void update(float dt);
    static GameScene* getInstance()
    {
        if (!sharedGameScene) {
            sharedGameScene = new GameScene();
//            sharedGameScene->init();
        }
        return sharedGameScene;
    }
    void clear();
    
    // mission flag
    bool isMissionCompleted;
    // current focus
    int focus;
    enum {
        NONE,
        BACKGROUND,
        CHARACTER,
        TEXT
    };
    // different way to start game
    void startNewGame();
    void startSavedGame(std::string datafile);
    // game mode
    void enterSkipMode();
    void enterAutoMode();
    // user data
    struct
    {
        // record the position in script
        std::string scriptPath;
        int pos, lineID;
        int gobackPos, gobackLineID;
        bool isConditionFullFilled;
        // bgm
        std::string bgmFilename;
        // bgp
        std::string bgpFilename;
        float bgpScale;
        float bgpPositionX, bgpPositionY;
        // characters
        std::string characterFilename[4];
        float characterScale[4];
        float characterPositionX[4], characterPositionY[4];
        // text
        std::string textContent;
        int textPos, textLineID;
        // choice table
        int choiceTablePos, choiceTableLineID;
    }UserData;
    void saveFlags();
    /**
     * set
     */
    // bgp
    void setBgpFilename(std::string filename);
    void setBgpDuration(float d);
    void setBgpScale(float scale);
    void setBgpPosition(float x, float y);
    void setBgpStart();
    // characters
    void setCharacterFilename(int id, std::string filename);
    void setCharacterDuration(int id, float d);
    void setCharacterScale(int id, float scale);
    void setCharacterPosition(int id, float x, float y);
    void setCharacterEffect(int id, std::string effect);
    void setCharacterClear(int id);
    void setCharacterStart(int id);
    // text
    void setTextShow();
    void setTextStop();
    void setTextContent(std::string str);
    void setTextUpdate(const std::string &str);
    void setTextSpeed(float sp);
    void setTextClear();
    // choices
    void setChoiceNumber(int number);
    void setChoiceContent(int id, std::string content);
    void setChoiceChoosable(int id, bool choosable);
    void setChoiceShow();
    // wait
    void setWaitTime(float time);
    /**
     * get
     */
    // get.touch
    void enableScreenTouchEventListener(bool btouch, float delay=0);
    // get.choice
    void getChoiceResult();
    void waitForChoiceResult(float dt);

};

#endif /* GameScene_cpp */
