//
//  ConfigScene.h
//  Test
//
//  Created by KJTang on 15/7/15.
//
//

#ifndef ConfigScene_cpp
#define ConfigScene_cpp

#include "cocos2d.h"
#include "GameController.h"
#include "ButtonSprite.h"

using namespace cocos2d;

class ConfigScene : public Scene
{
private:
    Size visibleSize;
    Layer *background;
public:
    ConfigScene();
    ~ConfigScene();
    
    virtual bool init();
    CREATE_FUNC(ConfigScene);
};

#endif /* ConfigScene_cpp */
