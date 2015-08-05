//
//  AutoBlurSprite.h
//  Test
//
//  Created by KJTang on 15/8/4.
//
//

#ifndef AutoBlurSprite_cpp
#define AutoBlurSprite_cpp

#include "cocos2d.h"
#include "BlurInAndOut.h"

using namespace cocos2d;

class AutoBlurSprite : public Sprite
{
private:
    int depth;
    EventListenerTouchOneByOne *touchListener;
public:
    AutoBlurSprite();
    ~AutoBlurSprite();

    virtual bool initWithFile(std::string filename);
    static AutoBlurSprite* create(std::string filename);
    
    int getDepth() {return depth;}
    void BlurIn();
    void BlurOut();
};

#endif /* AutoBlurSprite_cpp */
