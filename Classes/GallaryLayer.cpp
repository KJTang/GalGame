//
//  GallaryLayer.cpp
//  Test
//
//  Created by idream on 15/11/8.
//
//

#include "GallaryLayer.h"

#include <fstream>
#include <string>

/***************
 GallaryList
 ***************/
GallaryList::GallaryList(){}
GallaryList::~GallaryList(){}

bool GallaryList::init()
{
    if (!Layer::init()) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    
    auto test = Sprite::create("HelloWorld.png");
    this->addChild(test);
    test->setScale(1, visibleSize.height/test->getContentSize().height*0.3);
    
    GallaryLayer::setGallaryState(5, true);
    GallaryLayer::setGallaryState(9, true);
    
    log("get %d", GallaryLayer::getGallaryState(5));
    log("get %d", GallaryLayer::getGallaryState(6));
    
    touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(false);
    touchListener->onTouchBegan = [&, test](Touch *touch, Event *event) {
        startPoint = touch->getLocation();
        // relative position
        auto locationInNode = test->convertToNodeSpace(touch->getLocation());
        auto rect = cocos2d::Rect(0, 0, test->getContentSize().width, test->getContentSize().height);
        if (rect.containsPoint(locationInNode)) {
            touchListener->setSwallowTouches(true);
            return true;
        }
        return false;
    };
    touchListener ->onTouchMoved = [&](Touch *touch, Event *event) {
        auto currentPoint = touch->getLocation();
        this->setPositionX(this->getPositionX() + currentPoint.x - startPoint.x);
        startPoint = currentPoint;
        return true;
    };
    touchListener->onTouchEnded = [&](Touch *touch, Event *event) {
        touchListener->setSwallowTouches(false);
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

/***************
 GallaryContent
 ***************/
GallaryContent::GallaryContent(){}

GallaryContent::~GallaryContent(){}

bool GallaryContent::init()
{
    if (!Layer::init()) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    
    auto pic = Sprite::create("HelloWorld.png");
    this->addChild(pic);
    pic->setPosition(visibleSize.width*0.5, visibleSize.height*1.8);
    
    auto list = GallaryList::create();
    this->addChild(list);
    list->setPosition(visibleSize.width/2, visibleSize.height*1.3);
    
    return true;
}

/**************
 GallaryLayer
 *************/
GallaryLayer::GallaryLayer(){}

GallaryLayer::~GallaryLayer(){}

bool GallaryLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    inTouchEvent = false;
    
    blackLayer = LayerColor::create(Color4B::BLACK);
    this->addChild(blackLayer);
    blackLayer->setOpacity(0);
    
    contentLayer = GallaryContent::create();
    this->addChild(contentLayer);
    
    touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [&](Touch *touch, Event *event) {
        touchStart = touch->getLocation();
        if (inTouchEvent) {
            return true;
        } else if (touchStart.y > visibleSize.height*0.8) {
            return true;
        }
        return false;
    };
    touchListener->onTouchMoved = [&](Touch *touch, Event *event) {
        auto touchCurrent = touch->getLocation();
        contentLayer->setPositionY(contentLayer->getPositionY() + touchCurrent.y - touchStart.y);
        
        if (contentLayer->getPositionY() >= 0) {
            blackLayer->setOpacity(0);
        } else if (contentLayer->getPositionY() < -visibleSize.height*0.50) {
            blackLayer->setOpacity(200);
        } else {
            blackLayer->setOpacity((-contentLayer->getPositionY())/(visibleSize.height*0.5)*200);
        }
        touchStart = touchCurrent;
        return true;
    };
    touchListener->onTouchEnded = [&](Touch *touch, Event *event) {
        if (contentLayer->getPositionY() < -visibleSize.height*0.5) {
            contentLayer->runAction(MoveTo::create(0.2, Vec2(0, -visibleSize.height)));
            inTouchEvent = true;
        } else {
            contentLayer->runAction(MoveTo::create(0.1, Vec2(0, 0)));
            blackLayer->runAction(FadeOut::create(0.1));
            inTouchEvent = false;
        }
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    return true;
}

void GallaryLayer::setGallaryState(int id, bool state)
{
    std::string path = FileUtils::getInstance()->getWritablePath()+"Gallary.txt";
    int picCount = 10; // TODO: gallary pic count, as a temp var here
    if (!FileUtils::getInstance()->isFileExist(path)) {
        log("file not exist");
        std::ofstream fout(path);
        std::string str(picCount, '0');
        fout<<str;
        fout.close();
    }
    
    log("file exist");
    std::string str = FileUtils::getInstance()->getStringFromFile(path);
    log("file: %s\n------", str.c_str());
    if (state) {
        str.replace(str.begin()+id, str.begin()+id+1, "1");
    } else {
        str.replace(str.begin()+id, str.begin()+id+1, "0");
    }
    log("file: %s\n------", str.c_str());
    std::ofstream fout(path);
    fout<<str;
    fout.close();
}

bool GallaryLayer::getGallaryState(int id)
{
    std::string path = FileUtils::getInstance()->getWritablePath()+"Gallary.txt";
    int picCount = 10; // TODO: gallary pic count, as a temp var here
    if (!FileUtils::getInstance()->isFileExist(path)) {
        log("file not exist");
        std::ofstream fout(path);
        std::string str(picCount, '0');
        fout<<str;
        fout.close();
        return false;
    }
    
    std::string str = FileUtils::getInstance()->getStringFromFile(path);
    return str.at(id) == '1' ? 1 : 0;
}