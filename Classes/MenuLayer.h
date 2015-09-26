//
//  MenuLayer.h
//  Test
//
//  Created by KJTang on 15/9/26.
//
//

#ifndef MenuLayer_cpp
#define MenuLayer_cpp

#include "cocos2d.h"

using namespace cocos2d;

class MenuLayer : public Layer
{
private:
    Size visibleSize;
    EventListenerTouchOneByOne *screenTouchListener;
public:
    MenuLayer();
    ~MenuLayer();
    virtual bool init();
    CREATE_FUNC(MenuLayer);
};

#endif /* MenuLayer_cpp */
