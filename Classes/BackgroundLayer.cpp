//
//  BackgroundLayer.cpp
//  Test
//
//  Created by KJTang on 15/7/28.
//
//

#include "BackgroundLayer.h"
#include "GameScene.h"

BackgroundLayer::BackgroundLayer(){}

BackgroundLayer::~BackgroundLayer(){}

bool BackgroundLayer::init()
{
    if (!TouchableLayer::init()) {
        return false;
    }
    
    enableClickListener = false;
    
    return true;
}

void BackgroundLayer::onClick()
{
    if (!enableClickListener) {
        return;
    }
//    log("------------------background is clicked");
    enableClickListener = false;
    GameScene::getInstance()->isMissionCompleted = true;
}