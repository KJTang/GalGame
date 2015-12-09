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

const int picCount = 10; // gallary pic count, as a temp var here
const int tag_loadPic = 0;

using namespace cocos2d;

class GallaryList : public Layer
{
private:
    Size visibleSize;
    float thumbWidth;
    float thumbSpace;
    int currentThumb;
public:
    std::vector<Sprite*> thumbs;
private:
    EventListenerTouchOneByOne *touchListener;
    Point startPoint, movePoint, endPoint;
    bool isClick;
    std::vector<bool> picAvailable;
public:
    GallaryList();
    ~GallaryList();
    virtual bool init();
    CREATE_FUNC(GallaryList);
    
    // callback
    void onPicClick(int id);
    void onPicChange(int id);
};

class GallaryContent : public Layer
{
private:
    Size visibleSize;
    EventListenerTouchOneByOne *touchListener;
    Sprite *currentPic;
public:
    GallaryContent();
    ~GallaryContent();
    virtual bool init();
    CREATE_FUNC(GallaryContent);
    
    // set displaying pic
    void setDisplayPic(Sprite *pic);
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
