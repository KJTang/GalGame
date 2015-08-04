//
//  BasicScene.cpp
//  Test
//
//  Created by KJTang on 15/8/3.
//
//

#include "BasicScene.h"

BasicScene::BasicScene(){}

BasicScene::~BasicScene(){}

bool BasicScene::init()
{
    if (!Scene::init()) {
        return false;
    }
    
    return true;
}
