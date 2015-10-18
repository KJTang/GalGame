#pragma once

#include "cocos2d.h"

using namespace cocos2d;

class ButtonSprite : public Sprite
{
private:
    cocos2d::Size visibleSize;
    EventListenerTouchOneByOne* touchListener;
    Point startPoint, endPoint;
    std::function<void()> callbackFunc;
public:
    ButtonSprite();
    ~ButtonSprite();

    static ButtonSprite* create(const std::string &filename);

    virtual bool initWithFile(const std::string &filename);
    virtual void onEnter();

    virtual void onClicked();
    void setCallbackFunc(const std::function<void()> &callbackFunc);
};
