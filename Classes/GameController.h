//
//  GameController.h
//  Test
//
//  Created by KJTang on 15/7/14.
//
//

#ifndef GameController_cpp
#define GameController_cpp

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#include "StartScene.h"
#include "GameScene.h"
#include "ConfigScene.h"

using namespace cocos2d;

class GameController
{
private:
    static GameController* sharedGameController;
    bool init();
    //bgm
    std::string bgmFilename;
    // shaders
    void LoadShader();
    
    // state
    int currentState;
    enum
    {
        STATE_PREPARING,
        STATE_START_SCENE,
        STATE_GAME_SCENE,
        STATE_CONFIG_SCENE,
        STATE_MEMORY_SCENE,
        STATE_DATA_SAVE_SCENE,
        STATE_DATA_LOAD_SCENE
    };

private:
    GameController();
public:
    ~GameController();
    
public:
    static GameController* getInstance() {
        if (!sharedGameController) {
            sharedGameController = new GameController();
            sharedGameController->init();
        }
        return sharedGameController;
    }
    
    // Data
    void saveData(std::string dataname);
    void loadData();
    
    // Scene Control
    void enterStartScene();
    void enterGameScene(std::string dataFilename = "");
    void enterConfigScene();
    void enterMemoryScene();
    void enterDataLoadScene();
    void enterDataSaveScene();
    void exitGame();
    
    // Audio Control
    void loadBGM(std::string filename);
    void playBGM();
    void pauseBGM();
    void resumeBGM();
    void stopBGM();
    void setBGMVolume(float v);
};

#endif /* GameController_cpp */
