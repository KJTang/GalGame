//
//  HistoryLayer.hpp
//  Test
//
//  Created by KJTang on 15/10/18.
//
//

#ifndef HistoryLayer_cpp
#define HistoryLayer_cpp

#include "cocos2d.h"

using namespace cocos2d;

class HistoryLayer : public Layer
{
private:
    Size visibleSize;
    EventListenerTouchOneByOne *screenTouchListener;
    Point touchStart, touchMoving, touchEnd;
    float startTime, endTime, deltaTime;
    Layer *historyBoard, *blackLayer;
    bool isHistoryShowing;
public:
    HistoryLayer();
    ~HistoryLayer();
    virtual bool init();
    CREATE_FUNC(HistoryLayer);
private:
    void createHistoryBoard();
    void autoMove(bool b);
public:
    void setHistory(const std::vector<std::string> &history);
};

#endif /* HistoryLayer_cpp */
