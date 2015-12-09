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

#include "GyroBackground.h"

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
    thumbWidth = visibleSize.width/4;
    thumbSpace = visibleSize.width/3.5;
    currentThumb = 0;
    isClick = false;
    
//    GallaryLayer::setGallaryState(0, true);
//    GallaryLayer::setGallaryState(1, true);
//    GallaryLayer::setGallaryState(3, true);
//    GallaryLayer::setGallaryState(4, true);
//    GallaryLayer::setGallaryState(5, true);
//    GallaryLayer::setGallaryState(9, true);

    for (int i = 0; i != picCount; ++i) {
        char name[30];
        sprintf(name, "gallary/gallary%d.png", i);
        
        auto listItem = Sprite::create(name);
        this->addChild(listItem);
        thumbs.push_back(listItem);
        listItem->setScale(thumbWidth/listItem->getContentSize().width, visibleSize.height/listItem->getContentSize().height/4);
        listItem->setPosition(Vec2(visibleSize.width/2+thumbSpace*i, 0));
        if (!GallaryLayer::getGallaryState(i)) {
            listItem->setOpacity(100);
        }
        
        touchListener = EventListenerTouchOneByOne::create();
        touchListener->setSwallowTouches(true);
        touchListener->onTouchBegan = [&, listItem](Touch *touch, Event *event) {
            isClick = true;
            event->getCurrentTarget()->stopActionByTag(tag_loadPic);
            startPoint = touch->getLocation();
            movePoint = startPoint;
            // relative position
            auto locationInNode = listItem->convertToNodeSpace(touch->getLocation());
            auto rect = cocos2d::Rect(0, 0, listItem->getContentSize().width, listItem->getContentSize().height);
            if (rect.containsPoint(locationInNode)) {
                touchListener->setSwallowTouches(true);
                return true;
            }
            return false;
        };
        touchListener ->onTouchMoved = [&](Touch *touch, Event *event) {
            auto currentPoint = touch->getLocation();
            this->setPositionX(this->getPositionX() + currentPoint.x - movePoint.x);
            if (currentPoint.x - movePoint.x > 50 || currentPoint.x - movePoint.x < 100) {
                isClick = false;
            }
            movePoint = currentPoint;
            return true;
        };
        touchListener->onTouchEnded = [&](Touch *touch, Event *event) {
            touchListener->setSwallowTouches(false);
            auto target = static_cast<GallaryList*>(event->getCurrentTarget());
            currentThumb = static_cast<int>((event->getCurrentTarget()->getPositionX()-thumbSpace/2)/thumbSpace);
//            log("posx: %d", currentThumb);
            if (-currentThumb >= picCount) {
                currentThumb = -picCount + 1;
            }
            if (isClick) {
                log("clicked: %d", currentThumb);
                cocos2d::Point locationInNode = target->thumbs.at(-currentThumb)->convertToNodeSpace(touch->getLocation());
                cocos2d::Rect rect = cocos2d::Rect(0, 0, target->thumbs.at(-currentThumb)->getContentSize().width, target->thumbs.at(-currentThumb)->getContentSize().height);
                // open display mode
                if (rect.containsPoint(locationInNode) && GallaryLayer::getGallaryState(-currentThumb)) {
                    target->onPicClick(-currentThumb);
                }
            } else {
                if (currentThumb >= 0) {
                    target->runAction(MoveTo::create(0.2, Vec2(0, target->getPositionY())));
                } else if (currentThumb < -picCount+1) {
                    target->runAction(MoveTo::create(0.2, Vec2(thumbSpace*(-picCount+1), target->getPositionY())));
                } else {
                    target->runAction(MoveTo::create(0.2, Vec2(thumbSpace*currentThumb, target->getPositionY())));
                }
//                target->thumbs.at(-currentThumb)->runAction();
                // change pic
                target->onPicChange(-currentThumb);
            }
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    }
    
    return true;
}

void GallaryList::onPicClick(int id) {
    // TODO:
    auto displayScene = Scene::create();
    Director::getInstance()->pushScene(displayScene);
    
    char filename[30];
    sprintf(filename, "gallary/gallary%d.png", id);
    auto newPic = GyroBackground::create(filename, 1.5);
    
    displayScene->addChild(newPic);
    newPic->setOpacity(0);
    newPic->runAction(FadeIn::create(0.5));
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [&](Touch *touch, Event *event) {
        Director::getInstance()->popScene();
        return false;
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, displayScene);
}

void GallaryList::onPicChange(int id) {
    char filename[30];
    sprintf(filename, "gallary/gallary%d.png", id);
    auto newPic = Sprite::create(filename);
    newPic->retain();
    auto loadPicAction = Sequence::create(DelayTime::create(0.5),
                                          CallFunc::create([&, newPic]
                                                           {
                                                               static_cast<GallaryContent*>(this->getParent())->setDisplayPic(newPic);
                                                           }),
                                          NULL);
    loadPicAction->setTag(tag_loadPic);
    this->runAction(loadPicAction);
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
    currentPic = nullptr;
    
    currentPic = Sprite::create("HelloWorld.png");
    this->addChild(currentPic);
    currentPic->setPosition(visibleSize.width*0.5, visibleSize.height*1.7);
    
    auto list = GallaryList::create();
    this->addChild(list);
    list->setPosition(0, visibleSize.height*1.2);
    
    return true;
}

void GallaryContent::setDisplayPic(Sprite *pic) {
    if (currentPic) {
        currentPic->removeFromParent();
    }
    currentPic = pic;
    this->addChild(currentPic);
    currentPic->setPosition(visibleSize.width*0.5, visibleSize.height*1.7);
    currentPic->setOpacity(0);
    currentPic->runAction(FadeIn::create(0.5));
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