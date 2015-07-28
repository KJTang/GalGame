
//
//  TouchableLayer.cpp
//  Test
//
//  Created by KJTang on 15/7/28.
//
//

#include "TouchableLayer.h"

TouchableLayer::TouchableLayer(){}

TouchableLayer::~TouchableLayer(){}

bool TouchableLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    return true;
}

void TouchableLayer::onClick()
{
    log("touchable layer is touched");
}