//
//  StartScene.h
//  Test
//
//  Created by KJTang on 15/7/14.
//
//

#ifndef StartScene_cpp
#define StartScene_cpp

#include "cocos2d.h"

using namespace cocos2d;

class StartScene : public Scene
{
private:
    Size visibleSize;
    Layer *backgroundLayer, *touchLayer;
    EventListenerTouchOneByOne *touchListener;
    Point touchStart, touchEnd;
public:
    StartScene();
    ~StartScene();
    
    virtual bool init();
    CREATE_FUNC(StartScene);
    
    Label* text;
};

#endif /* StartScene_cpp */
