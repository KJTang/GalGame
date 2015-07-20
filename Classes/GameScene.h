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
//#include "VariableController.h"
#include "DataController.h"

#include "TextLayer.h"
#include "ChoiceTableLayer.h"
#include "GyroBackground.h"

using namespace cocos2d;

class GameScene : public Scene
{
private:
    static GameScene* sharedGameScene;
    Size visibleSize;
    Layer *backgroundLayer, *characterLayer, *menuLayer;
    // game mode
    int gameMode;
    enum {
        MODE_NORMAL,
        MODE_AUTO,
        MODE_SKIP
    };
    
    // bgp
//    Sprite *bgp;
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
    // user data
    struct
    {
        // record the position in script
        int pos, lineID;
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
    }UserData;
    void saveData();
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
    void setCharacterClear(int id);
    void setCharacterStart(int id);
    // text
    void setTextShow();
    void setTextStop();
    void setTextContent(std::string str);
    void setTextSpeed(float sp);
    void setTextClear();
    bool isTextShowing;
    void enableTextFinishedEventListener(bool btext);
    // choices
    void setChoiceNumber(int number);
    void setChoiceContent(int id, std::string content);
    void setChoiceChoosable(int id, bool choosable);
    void setChoiceShow();
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
