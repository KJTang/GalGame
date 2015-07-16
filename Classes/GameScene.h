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

using namespace cocos2d;

class GameScene : public Scene
{
private:
    Size visibleSize;
    
    Layer *background;
    Sprite *bgp;
    Sprite *ch01, *ch02, *ch03, *ch04;
public:
    GameScene();
    ~GameScene();
    
    virtual bool init();
    CREATE_FUNC(GameScene);
    
    void startNewGame();
    void startSavedGame();
    
    bool setBackgroundPicture(std::string filename);
    bool setCh01Picture(std::string filename);
    bool setCh02Picture(std::string filename);
    bool setCh03Picture(std::string filename);
    bool setCh04Picture(std::string filename);
};

#endif /* GameScene_cpp */
