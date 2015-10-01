//
//  MenuLayer.cpp
//  Test
//
//  Created by KJTang on 15/9/26.
//
//

#include "MenuLayer.h"
#include "DataController.h"

/**
 *   DataSprite
 */
DataSprite::DataSprite(){}
DataSprite::~DataSprite(){};

bool DataSprite::init()
{
    if (!Sprite::init()) {
        return false;
    }
    
    auto sprite = Sprite::create("frame/Data-Unchosen.png");
    this->addChild(sprite);
    return true;
}

/**
 *   MenuLayer
 */
MenuLayer::MenuLayer(){}
MenuLayer::~MenuLayer(){}

bool MenuLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();
    // create datalist
    dataList = Layer::create();
    this->addChild(dataList);
    listItemCount = 7;
    listItemHeight = visibleSize.height*0.3;
    currentListItemID = -1;
    for (int i = 0; i != listItemCount; ++i) {
        auto data = DataSprite::create();
        dataList->addChild(data);
        data->setPosition(visibleSize.width*0.75, -visibleSize.height*0.5 - listItemHeight*i);
    }
    // touch event
    enum TOUCH_TYPE
    {
        NONE,
        LEFT,
        RIGHT,
        BOTTOM,
        LEFT_VIEWING,
        RIGHT_VIEWING,
        DATA_VIEWING,
    };
    touchType = NONE;
    // screen touch listener
    screenTouchListener = EventListenerTouchOneByOne::create();
    screenTouchListener->setSwallowTouches(true);
    screenTouchListener->onTouchBegan = [&](Touch* touch, Event* event){
        startPoint = touch->getLocation();
        // already in some event
        if (dataList->getPositionY() > 0) {
            touchType = DATA_VIEWING;
            return true;
        }
        
        // new event
        if (touch->getLocation().x < visibleSize.width*0.1 &&
            touch->getLocation().y > visibleSize.height*0.3 &&
            touch->getLocation().y < visibleSize.height*0.7) {
            touchType = LEFT;
            log("touch begin left");
        } else if (touch->getLocation().x > visibleSize.width*0.9 &&
                   touch->getLocation().y > visibleSize.height*0.3 &&
                   touch->getLocation().y < visibleSize.height*0.7) {
            touchType = RIGHT;
            log("touch begin right");
        } else if (touch->getLocation().y < visibleSize.height*0.1) {
            touchType = BOTTOM;
            dataList->setPositionY(visibleSize.height*0.5);
            log("touch begin bottom");
        }
        return true;
    };
    screenTouchListener->onTouchMoved = [&](Touch* touch, Event* event){
        switch (touchType) {
            case BOTTOM:
                dataList->setPositionY(dataList->getPositionY()+touch->getLocation().y-startPoint.y);
                startPoint = touch->getLocation();
                break;
            case DATA_VIEWING:
                dataList->setPositionY(dataList->getPositionY()+touch->getLocation().y-startPoint.y);
                startPoint = touch->getLocation();
                break;
            default:
                break;
        }
        return true;
    };
    screenTouchListener->onTouchEnded = [&](Touch* touch, Event* event){
        touchType = NONE;
        for (int i = 0; i != listItemCount; ++i) {
            auto pos = visibleSize.height+listItemHeight*i;
            if (dataList->getPositionY() > pos - listItemHeight*0.5 &&
                dataList->getPositionY() < pos + listItemHeight*0.5)
            {
                currentListItemID = i;
                dataList->runAction(MoveTo::create(0.1, Vec2(0, pos)));
                return false;
            }
        }
        // end of the list
        if (dataList->getPositionY() > visibleSize.height+listItemHeight*(listItemCount-1)) {
            dataList->runAction(MoveTo::create(0.1, Vec2(0, visibleSize.height+listItemHeight*(listItemCount-1))));
        }
        // head of the list
        else if (dataList->getPositionY() > visibleSize.height*0.7) {
            dataList->runAction(MoveTo::create(0.1, Vec2(0, visibleSize.height)));
        } else if (dataList->getPositionY() < visibleSize.height*0.7) {
             dataList->runAction(MoveTo::create(0.1, Vec2(0, 0)));
             currentListItemID = -1;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(screenTouchListener, this);
    
    return true;
}
