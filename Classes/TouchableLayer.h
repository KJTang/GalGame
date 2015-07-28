//
//  TouchableLayer.h
//  Test
//
//  Created by KJTang on 15/7/28.
//
//

#ifndef TouchableLayer_cpp
#define TouchableLayer_cpp

#include "cocos2d.h"

using namespace cocos2d;

class TouchableLayer : public Layer
{
private:
    
public:
    TouchableLayer();
    ~TouchableLayer();
    
    virtual bool init();
    CREATE_FUNC(TouchableLayer);
    
    virtual void onClick();
};

#endif /* TouchableLayer_cpp */
