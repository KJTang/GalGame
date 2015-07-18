//
//  StartScene.h
//  Test
//
//  Created by KJTang on 15/7/14.
//
//

#ifndef StartScene_cpp
#define StartScene_cpp

#include <stdio.h>

#include "cocos2d.h"
#include "GameController.h"
#include "GyroBackground.h"
#include "ButtonSprite.h"

#include "ChoiceTableLayer.h"

using namespace cocos2d;

class StartScene : public Scene
{
private:
    Size visibleSize;
    Layer *backgroundLayer;
public:
    StartScene();
    ~StartScene();
    
    virtual bool init();
    CREATE_FUNC(StartScene);
    
    Label* text;
};

#endif /* StartScene_cpp */
