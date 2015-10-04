//
//  ButtonSprite.h
//  Test
//
//  Created by KJTang on 15/7/15.
//
//

#ifndef ButtonSprite_cpp
#define ButtonSprite_cpp

#include "cocos2d.h"

using namespace cocos2d;

class ButtonSprite : public Sprite
{
private:
    cocos2d::Size visibleSize;
    EventListenerTouchOneByOne* touchListener;
    Point startPoint, endPoint;
    void (*callbackFunc)();
public:
    ButtonSprite();
    ~ButtonSprite();
    
    static ButtonSprite* create(std::string filename);
    
    virtual bool initWithFile(std::string filename);
    virtual void onEnter();
    
    virtual void onClicked();
    void setCallbackFunc(void (*func)());
};

#endif /* ButtonSprite_cpp */
