//
//  BasicScene.h
//  Test
//
//  Created by KJTang on 15/8/3.
//
//

#ifndef BasicScene_cpp
#define BasicScene_cpp

#include "cocos2d.h"

using namespace cocos2d;

class BasicScene : public Scene
{
private:
    Layer *topLayer, *midLayer, *bottomLayer;
public:
    BasicScene();
    ~BasicScene();
    virtual bool init();
    CREATE_FUNC(BasicScene);
};

#endif /* BasicScene_cpp */
