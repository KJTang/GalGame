//
//  BackgroundLayer.h
//  Test
//
//  Created by KJTang on 15/7/28.
//
//

#ifndef BackgroundLayer_cpp
#define BackgroundLayer_cpp

#include "cocos2d.h"
#include "TouchableLayer.h"

using namespace cocos2d;

class BackgroundLayer : public TouchableLayer
{
private:
    
public:
    BackgroundLayer();
    ~BackgroundLayer();
    
    virtual bool init();
    CREATE_FUNC(BackgroundLayer);
    
    bool enableClickListener;
    virtual void onClick();
};

#endif /* BackgroundLayer_cpp */
