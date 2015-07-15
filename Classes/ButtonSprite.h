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
    Size visibleSize;
    EventListenerTouchOneByOne* touchListener;
public:
    ButtonSprite();
    ~ButtonSprite();
    
    static ButtonSprite* create(std::string filename);
    
    virtual bool init();
    virtual void onEnter();
    
    bool clicked;
};

#endif /* ButtonSprite_cpp */
