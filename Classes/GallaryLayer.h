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
#include <vector>

using namespace cocos2d;

class GallaryList : public Layer
{
private:
    Size visibleSize;
    EventListenerTouchOneByOne *touchListener;
    Point startPoint, endPoint;
    std::vector<bool> picAvailable;
public:
    GallaryList();
    ~GallaryList();
    virtual bool init();
    CREATE_FUNC(GallaryList);
};

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
    
    static void setGallaryState(int id, bool state);
    static bool getGallaryState(int id);
};

#endif /* GallaryLayer_cpp */
