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

class GallaryContent : public Layer
{
private:
    Size visibleSize;
    EventListenerTouchOneByOne *touchListener;
public:
    GallaryContent();
    ~GallaryContent();
    virtual bool init();
    CREATE_FUNC(GallaryContent);
};

class GallaryLayer : public Layer
{
private:
    Size visibleSize;
    Layer *blackLayer, *contentLayer;
    EventListenerTouchOneByOne *touchListener;
    Point touchStart;
    bool inTouchEvent;
public:
    GallaryLayer();
    ~GallaryLayer();
    virtual bool init();
    CREATE_FUNC(GallaryLayer);
};

#endif /* GallaryLayer_cpp */
