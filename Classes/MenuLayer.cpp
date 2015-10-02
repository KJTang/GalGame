//
//  MenuLayer.cpp
//  Test
//
//  Created by KJTang on 15/9/26.
//
//

#include "MenuLayer.h"
#include "DataController.h"
#include "ButtonSprite.h"

/**
 *   ListItem
 */
ListItem::ListItem(){}
ListItem::~ListItem(){};

bool ListItem::init()
{
    if (!Sprite::init()) {
        return false;
    }
    
    auto sprite = Sprite::create("frame/Data-Unchosen.png");
    this->addChild(sprite);
    
    return true;
}

void ListItem::setText(std::string str)
{
    std::string fontFile = "fonts/PingFang_1.ttf";
    float fontSize = 60;
    
    text = Label::createWithTTF(str, fontFile, fontSize, Size(200, 200));
    this->addChild(text);
}

void ListItem::setActive(bool active)
{
    if (active) {
        this->runAction(ScaleTo::create(0.1, 1.1));
    } else {
        this->runAction(ScaleTo::create(0.1, 1));
    }
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
    // create greylayer
    greyLayer = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);
    this->addChild(greyLayer);
    greyLayer->setOpacity(0);
    // create menu
    leftMenu = Layer::create();
    this->addChild(leftMenu);
    auto infoBtn = ButtonSprite::create("title/info");
    leftMenu->addChild(infoBtn);
    infoBtn->setScale(visibleSize.height/infoBtn->getContentSize().height/10);
    infoBtn->setAnchorPoint(Point(0, 0));
    infoBtn->setPosition(Point(-visibleSize.width*0.3, visibleSize.height*0.0));
    infoBtn->setCallbackFunc([](){
        log("enter InfoScene");
    });
    
    rightMenu = Layer::create();
    this->addChild(rightMenu);
    auto startBtn = ButtonSprite::create("title/start");
    rightMenu->addChild(startBtn);
    startBtn->setScale(visibleSize.height/startBtn->getContentSize().height/15);
    startBtn->setAnchorPoint(Point(0, 0));
    startBtn->setPosition(Point(visibleSize.width, visibleSize.height*0.40));
    startBtn->setCallbackFunc([](){
        log("start Game");
        GameController::getInstance()->enterGameScene();
    });
    auto loadBtn = ButtonSprite::create("title/load");
    rightMenu->addChild(loadBtn);
    loadBtn->setScale(visibleSize.height/loadBtn->getContentSize().height/15);
    loadBtn->setAnchorPoint(Point(0, 0));
    loadBtn->setPosition(Point(visibleSize.width, visibleSize.height*0.30));
    loadBtn->setCallbackFunc([](){
        log("load Game");
        GameController::getInstance()->enterGameScene("test");
    });
    auto gallaryBtn = ButtonSprite::create("title/gallary");
    rightMenu->addChild(gallaryBtn);
    gallaryBtn->setScale(visibleSize.height/gallaryBtn->getContentSize().height/15);
    gallaryBtn->setAnchorPoint(Point(0, 0));
    gallaryBtn->setPosition(Point(visibleSize.width, visibleSize.height*0.20));
    gallaryBtn->setCallbackFunc([](){
        log("enter GallaryScene");
    });
    auto configBtn = ButtonSprite::create("title/config");
    rightMenu->addChild(configBtn);
    configBtn->setScale(visibleSize.height/configBtn->getContentSize().height/15);
    configBtn->setAnchorPoint(Point(0, 0));
    configBtn->setPosition(Point(visibleSize.width, visibleSize.height*0.10));
    configBtn->setCallbackFunc([](){
        log("enter ConfigScene");
        GameController::getInstance()->enterConfigScene();
    });

    // create datalist
    dataList = Layer::create();
    this->addChild(dataList);
    listItemCount = DataController::getInstance()->dataCount;
    listItemHeight = visibleSize.height*0.3;
    currentListItemID = -1;
    for (int i = 0; i != listItemCount; ++i) {
        auto data = ListItem::create();
        dataList->addChild(data);
        data->setPosition(visibleSize.width*0.75, -visibleSize.height*0.5 - listItemHeight*i);
        data->setText(DataController::getInstance()->dataName[i]);
    }
    dataPic = nullptr;
    // touch event
    enum TOUCH_TYPE
    {
        NONE,
        LEFT,
        RIGHT,
        BOTTOM,
    };
    touchType = NONE;
    // screen touch listener
    screenTouchListener = EventListenerTouchOneByOne::create();
    screenTouchListener->setSwallowTouches(true);
    screenTouchListener->onTouchBegan = [&](Touch* touch, Event* event){
        originPoint = touch->getLocation();
        startPoint = touch->getLocation();
        
        touchType = NONE;
        // clear dataPic
        if (dataPic) {
            dataPic->runAction(Sequence::create(FadeOut::create(0.2),
                                                CallFunc::create([&]()
                                                                 {
                                                                     dataPic->removeFromParentAndCleanup(true);
                                                                     dataPic = nullptr;
                                                                 }),
                                                NULL));
        }
        
        // already in some event
        if (leftMenu->getPositionX() > 0) {
            touchType = LEFT;
        }
        if (rightMenu->getPositionX() < 0) {
            touchType = RIGHT;
            return true;
        } else if (dataList->getPositionY() > 0) {
            touchType = BOTTOM;
            return true;
        }

        // new event
        if (touch->getLocation().x < visibleSize.width*0.1 &&
            touch->getLocation().y > visibleSize.height*0.1 &&
            touch->getLocation().y < visibleSize.height*0.9) {
            touchType = LEFT;
            log("touch begin left");
            greyLayer->setOpacity(100);
        } else if (touch->getLocation().x > visibleSize.width*0.9 &&
                   touch->getLocation().y > visibleSize.height*0.1 &&
                   touch->getLocation().y < visibleSize.height*0.9) {
            touchType = RIGHT;
            log("touch begin right");
            greyLayer->setOpacity(100);
        } else if (touch->getLocation().y < visibleSize.height*0.1) {
            touchType = BOTTOM;
            dataList->runAction(MoveTo::create(0.1, Vec2(0, visibleSize.height*0.5)));
            log("touch begin bottom");
            greyLayer->setOpacity(100);
        }
        return true;
    };
    screenTouchListener->onTouchMoved = [&](Touch* touch, Event* event){
        switch (touchType) {
            case LEFT:
                leftMenu->setPositionX(leftMenu->getPositionX()+touch->getLocation().x-startPoint.x);
                if (leftMenu->getPositionX() > visibleSize.width*0.3) {
                    leftMenu->setPositionX(visibleSize.width*0.3);
                }
                startPoint = touch->getLocation();
                break;
            case RIGHT:
                rightMenu->setPositionX(rightMenu->getPositionX()+touch->getLocation().x-startPoint.x);
                if (rightMenu->getPositionX() < -visibleSize.width*0.3) {
                    rightMenu->setPositionX(-visibleSize.width*0.3);
                }
                startPoint = touch->getLocation();
                break;
            case BOTTOM:
                dataList->setPositionY(dataList->getPositionY()+touch->getLocation().y-startPoint.y);
                startPoint = touch->getLocation();
                break;
            default:
                break;
        }
        return true;
    };
    screenTouchListener->onTouchEnded = [&](Touch* touch, Event* event){
        endPoint = touch->getLocation();
        switch (touchType) {
            case LEFT:
            {
                if (leftMenu->getPositionX() > visibleSize.width*0.15) {
                    leftMenu->runAction(MoveTo::create(0.1, Vec2(visibleSize.width*0.3, 0)));
                } else {
                    leftMenu->runAction(MoveTo::create(0.1, Vec2(0, 0)));
                    greyLayer->setOpacity(0);
                }
                break;
            }
            case RIGHT:
            {
                if (rightMenu->getPositionX() < -visibleSize.width*0.15) {
                    rightMenu->runAction(MoveTo::create(0.1, Vec2(-visibleSize.width*0.3, 0)));
                } else {
                    rightMenu->runAction(MoveTo::create(0.1, Vec2(0, 0)));
                    greyLayer->setOpacity(0);
                }
                break;
            }
            case BOTTOM:
            {
                // click on list item
                if (endPoint.x - originPoint.x > -20 && endPoint.x - originPoint.x < 20 &&
                    endPoint.y - originPoint.y > -20 && endPoint.y - originPoint.y < 20 &&
                    endPoint.x > visibleSize.width*0.5 && endPoint.x < visibleSize.width &&
                    endPoint.y > visibleSize.height*0.5-listItemHeight*0.5 && endPoint.y < visibleSize.height*0.5+listItemHeight*0.5) {
                    log("click on item %d", currentListItemID);
                }
                // hide list
                if (dataList->getPositionY() < visibleSize.height*0.7) {
                    dataList->runAction(MoveTo::create(0.1, Vec2(0, 0)));
                    currentListItemID = -1;
                    auto list = dataList->getChildren();
                    static_cast<ListItem*>(list.at(0))->setActive(false);
                    greyLayer->setOpacity(0);
                    return false;
                }
                // focus on the item at middle of screen
                bool flag = false;
                for (int i = 0; i != listItemCount; ++i) {
                    auto pos = visibleSize.height+listItemHeight*i;
                    if (dataList->getPositionY() > pos - listItemHeight*0.5 &&
                        dataList->getPositionY() < pos + listItemHeight*0.5)
                    {
                        currentListItemID = i;
                        dataList->runAction(MoveTo::create(0.1, Vec2(0, pos)));
                        auto list = dataList->getChildren();
                        static_cast<ListItem*>(list.at(i))->setActive(true);
                        if (i > 0) {
                            static_cast<ListItem*>(list.at(i-1))->setActive(false);
                        }
                        if (i < list.size()-1) {
                            static_cast<ListItem*>(list.at(i+1))->setActive(false);
                        }
                        flag = true;
                    }
                }
                if (!flag) {
                    // focus on the item at end of the list
                    if (dataList->getPositionY() > visibleSize.height+listItemHeight*(listItemCount-1)) {
                        dataList->runAction(MoveTo::create(0.1, Vec2(0, visibleSize.height+listItemHeight*(listItemCount-1))));
                        auto list = dataList->getChildren();
                        static_cast<ListItem*>(list.at(list.size()-1))->setActive(true);
                        static_cast<ListItem*>(list.at(list.size()-2))->setActive(false);
                    }
                    // focus on the item at head of the list
                    else if (dataList->getPositionY() > visibleSize.height*0.7) {
                        dataList->runAction(MoveTo::create(0.1, Vec2(0, visibleSize.height)));
                        auto list = dataList->getChildren();
                        static_cast<ListItem*>(list.at(0))->setActive(true);
                        if (list.size() > 1) {
                            static_cast<ListItem*>(list.at(1))->setActive(false);
                        }
                    }
                }
                // draw data-pic
                if (dataPic) {
                    dataPic->removeFromParentAndCleanup(true);
                    dataPic = nullptr;
                }
                dataPic = Sprite::create("frame/Data-Pic.png");
                this->addChild(dataPic);
                dataPic->setPosition(visibleSize.width*0.25, visibleSize.height*0.5);
                dataPic->setOpacity(0);
                dataPic->runAction(FadeIn::create(0.2));
                break;
            }
            default:
                break;
        }
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(screenTouchListener, this);
    
    return true;
}
