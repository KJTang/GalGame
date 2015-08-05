
//
//  CharacterLayer.cpp
//  Test
//
//  Created by KJTang on 15/7/28.
//
//

#include "CharacterLayer.h"

CharacterLayer::CharacterLayer(){}

CharacterLayer::~CharacterLayer(){}

bool CharacterLayer::init()
{
    if (!TouchableLayer::init()) {
        return false;
    }
    
    enableTouchListener = false;
    
    return true;
}

void CharacterLayer::onClick()
{
    if (!enableTouchListener) {
        return;
    }
//    log("------------------characterlayer is clicked");
}