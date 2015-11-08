//
//  GallaryLayer.hpp
//  Test
//
//  Created by idream on 15/11/8.
//
//

#ifndef GallaryLayer_cpp
#define GallaryLayer_cpp

#include "cocos2d.h"

using namespace cocos2d;

class GallaryLayer : public Layer
{
private:
    Size visibleSize;
    Layer *blackLayer, *contentLayer;
    EventListenerTouchOneByOne *touchListenner;
    Point touchStart;
    bool inTouchEvent;
public:
    GallaryLayer();
    ~GallaryLayer();
    virtual bool init();
    CREATE_FUNC(GallaryLayer);
};

#endif /* GallaryLayer_cpp */
