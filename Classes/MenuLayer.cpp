//
//  MenuLayer.cpp
//  Test
//
//  Created by KJTang on 15/9/26.
//
//

#include "MenuLayer.h"

MenuLayer::MenuLayer(){}

MenuLayer::~MenuLayer(){}

bool MenuLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    // screen touch listener
    screenTouchListener = EventListenerTouchOneByOne::create();
    screenTouchListener->setSwallowTouches(true);
    screenTouchListener->onTouchBegan = [&](Touch* touch, Event* event){
        log("touch begin");
        return true;
    };
    screenTouchListener->onTouchMoved = [&](Touch* touch, Event* event){
        log("touch moving");
        return true;
    };
    screenTouchListener->onTouchEnded = [&](Touch* touch, Event* event){
        log("touch end");
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(screenTouchListener, this);
    
    return true;
}
