//
//  PromptBoxSprite.cpp
//  Test
//
//  Created by KJTang on 15/10/18.
//
//

#ifndef PromptBoxSprite_cpp
#define PromptBoxSprite_cpp

#include "cocos2d.h"

using namespace cocos2d;

class PromptBoxSprite : public Sprite
{
private:
    Size visibleSize;
    Sprite *bg;
    Label *text, *outline[4];
public:
    PromptBoxSprite();
    ~PromptBoxSprite();
    virtual bool init();
    CREATE_FUNC(PromptBoxSprite);
    
    void setText(const std::string &text);
    void start();
    
    Size getContentSize() { return bg->getContentSize();}
};

#endif /* PromptBoxSprite_cpp */
