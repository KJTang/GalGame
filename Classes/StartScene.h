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
#include "GyroBackground.h"
#include "ButtonSprite.h"

using namespace cocos2d;

class StartScene : public Scene
{
private:
    Size visibleSize;
    Layer *background;
public:
    StartScene();
    ~StartScene();
    
    virtual bool init();
    CREATE_FUNC(StartScene);
};

#endif /* StartScene_cpp */
