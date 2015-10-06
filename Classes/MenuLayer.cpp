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

#include "ActionFade.h"

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
    
    unchosen = Sprite::create("frame/Data-Unchosen.png");
    this->addChild(unchosen);
    chosen = Sprite::create("frame/Data-Chosen.png");
    this->addChild(chosen);
    chosen->setOpacity(0);
    
    return true;
}

void ListItem::setText(const std::string &time, const std::string &chaptername)
{
    text = time;
    std::string fontFile = "fonts/PingFang_1.ttf";
    float fontSize = 50;
    Size textBoxSize = Size(800, 300);

    textLabel = Label::createWithTTF(text+"\n"+chaptername, fontFile, fontSize, textBoxSize);
    Point position[4] = {Point(1, 0), Point(-1, 0), Point(0, -1), Point(0, 1)};
    for (int i = 0; i != 4; ++i) {
        auto outline = Label::createWithTTF(text+"\n"+chaptername, fontFile, fontSize, textBoxSize);
        this->addChild(outline);
        outline->setPosition(textLabel->getPosition()+position[i]);
        outline->setOpacity(100);
        outline->setColor(Color3B::RED);
    }
    this->addChild(textLabel);
}

void ListItem::setActive(bool active)
{
    if (active) {
        this->runAction(ScaleTo::create(0.1, 1.1));
        chosen->runAction(FadeIn::create(0.1));
        unchosen->runAction(FadeOut::create(0.1));
    } else {
        this->runAction(ScaleTo::create(0.1, 1));
        unchosen->runAction(FadeIn::create(0.1));
        chosen->runAction(FadeOut::create(0.1));
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
        GameController::getInstance()->enterGameScene();
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
        data->setPosition(visibleSize.width*0.67, -visibleSize.height*0.5 - listItemHeight*i);
        data->setText(DataController::getInstance()->dataInfoList[i].dataName,
                      DataController::getInstance()->dataInfoList[i].chapterName);
    }
    if (!listItemCount) {
        auto data = ListItem::create();
        dataList->addChild(data);
        data->setPosition(visibleSize.width*0.67, -visibleSize.height*0.5);
        data->setText("No Data", "");
        listItemCount = 1;
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
    screenTouchListener->onTouchBegan = [&](Touch* touch, Event* event) {
        originPoint = touch->getLocation();
        startPoint = touch->getLocation();
        
        touchType = NONE;
        // clear dataPic
        if (dataPic) {
            auto dataPicChildren = dataPic->getChildren();
            for (int i = 0; i != dataPicChildren.size(); ++i) {
                static_cast<Sprite*>(dataPicChildren.at(i))->runAction(FadeOut::create(0.2));
            }
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
            return true;
        } else if (rightMenu->getPositionX() < 0) {
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
        } else if (touch->getLocation().x > visibleSize.width*0.9 &&
                   touch->getLocation().y > visibleSize.height*0.1 &&
                   touch->getLocation().y < visibleSize.height*0.9) {
            touchType = RIGHT;
            log("touch begin right");
        } else if (touch->getLocation().y < visibleSize.height*0.1) {
            touchType = BOTTOM;
            dataList->runAction(MoveTo::create(0.1, Vec2(0, visibleSize.height*0.5)));
            log("touch begin bottom");
        }
        return true;
    };
    screenTouchListener->onTouchMoved = [&](Touch* touch, Event* event) {
        switch (touchType) {
            case LEFT:
            {
                leftMenu->setPositionX(leftMenu->getPositionX()+touch->getLocation().x-startPoint.x);
                if (leftMenu->getPositionX() > visibleSize.width*0.3) {
                    leftMenu->setPositionX(visibleSize.width*0.3);
                }
                startPoint = touch->getLocation();
                
                float relativePos = leftMenu->getPositionX();
                if (relativePos < 0) {
                    relativePos = 0;
                }
                greyLayer->setOpacity(relativePos / (visibleSize.width*0.3) * 150);
                break;
            }
            case RIGHT:
            {
                rightMenu->setPositionX(rightMenu->getPositionX()+touch->getLocation().x-startPoint.x);
                if (rightMenu->getPositionX() < -visibleSize.width*0.3) {
                    rightMenu->setPositionX(-visibleSize.width*0.3);
                }
                startPoint = touch->getLocation();
                
                float relativePos = -rightMenu->getPositionX();
                if (relativePos < 0) {
                    relativePos = 0;
                }
                greyLayer->setOpacity(relativePos / (visibleSize.width*0.3) * 150);
                break;
            }
            case BOTTOM:
            {
                dataList->setPositionY(dataList->getPositionY()+touch->getLocation().y-startPoint.y);
                startPoint = touch->getLocation();
                
                float relativePos = dataList->getPositionY()-visibleSize.height*0.5;
                if (relativePos > visibleSize.height*0.5) {
                    relativePos = visibleSize.height*0.5;
                } else if (relativePos < 0)
                {
                    relativePos = 0;
                }
                greyLayer->setOpacity(relativePos / (visibleSize.height*0.5) * 150);
                break;
            }
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
                    greyLayer->runAction(ActionFadeIn::create(0.1, 150));
                } else {
                    leftMenu->runAction(MoveTo::create(0.1, Vec2(0, 0)));
                    greyLayer->runAction(ActionFadeOut::create(0.1, greyLayer->getOpacity()));
                }
                break;
            }
            case RIGHT:
            {
                if (rightMenu->getPositionX() < -visibleSize.width*0.15) {
                    rightMenu->runAction(MoveTo::create(0.1, Vec2(-visibleSize.width*0.3, 0)));
                    greyLayer->runAction(ActionFadeIn::create(0.1, 150));
                } else {
                    rightMenu->runAction(MoveTo::create(0.1, Vec2(0, 0)));
                    greyLayer->runAction(ActionFadeOut::create(0.1, greyLayer->getOpacity()));
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
                    auto list = dataList->getChildren();
                    auto filename = static_cast<ListItem*>(list.at(currentListItemID))->text;
                    log("click on item %d: %s", currentListItemID, filename.c_str());
                    if (filename != "No Data") {
                        this->runAction(Sequence::create(CallFunc::create([&]()
                                                                          {
                                                                              greyLayer->getChildByName("dataPic")->runAction(MoveBy::create(0.3, Vec2(-visibleSize.width*0.7, 0)));
                                                                              dataList->runAction(MoveBy::create(0.3, Vec2(visibleSize.width*0.7, 0)));
                                                                          }),
                                                         DelayTime::create(0.3),
                                                         CallFunc::create([&]()
                                                                          {
                                                                              auto dark = LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height);
                                                                              this->addChild(dark);
                                                                              dark->setOpacity(0);
                                                                              dark->runAction(FadeIn::create(0.3));
                                                                          }),
                                                         DelayTime::create(0.3),
                                                         CallFunc::create([&, filename]()
                                                                          {
                                                                              GameController::getInstance()->enterGameScene(filename);
                                                                          }),
                                                         NULL));
                    }
                }
                // hide list
                if (dataList->getPositionY() < visibleSize.height*0.7) {
                    dataList->runAction(MoveTo::create(0.1, Vec2(0, 0)));
                    currentListItemID = -1;
                    auto list = dataList->getChildren();
                    static_cast<ListItem*>(list.at(0))->setActive(false);
                    greyLayer->runAction(ActionFadeOut::create(0.1, greyLayer->getOpacity()));
                    return false;
                }
                // focus on the item at middle of screen
                bool flag = false;
                auto dataListChildren = dataList->getChildren();
                for (int i = 0; i != listItemCount; ++i) {
                    auto pos = visibleSize.height+listItemHeight*i;
                    if (dataList->getPositionY() > pos - listItemHeight*0.5 &&
                        dataList->getPositionY() < pos + listItemHeight*0.5)
                    {
                        currentListItemID = i;
                        dataList->runAction(MoveTo::create(0.1, Vec2(0, pos)));
                        static_cast<ListItem*>(dataListChildren.at(i))->setActive(true);
                        flag = true;
                    } else {
                        static_cast<ListItem*>(dataListChildren.at(i))->setActive(false);
                    }
                }
                if (!flag) {
                    // focus on the item at end of the list
                    if (dataList->getPositionY() > visibleSize.height+listItemHeight*(listItemCount-1)) {
                        dataList->runAction(MoveTo::create(0.1, Vec2(0, visibleSize.height+listItemHeight*(listItemCount-1))));
                        static_cast<ListItem*>(dataListChildren.at(dataListChildren.size()-1))->setActive(true);
                        if (dataListChildren.size() > 1) {
                            static_cast<ListItem*>(dataListChildren.at(dataListChildren.size()-2))->setActive(false);
                        }
                        currentListItemID = static_cast<int>(dataListChildren.size())-1;
                    }
                    // focus on the item at head of the list
                    else if (dataList->getPositionY() > visibleSize.height*0.7) {
                        dataList->runAction(MoveTo::create(0.1, Vec2(0, visibleSize.height)));
                        greyLayer->runAction(ActionFadeIn::create(0.1, 150));
                        static_cast<ListItem*>(dataListChildren.at(0))->setActive(true);
                        if (dataListChildren.size() > 1) {
                            static_cast<ListItem*>(dataListChildren.at(1))->setActive(false);
                        }
                        currentListItemID = 0;
                    }
                }
                // draw data-pic
                if (dataPic) {
                    dataPic->removeFromParentAndCleanup(true);
                    dataPic = nullptr;
                }
                auto filename = static_cast<ListItem*>(dataListChildren.at(currentListItemID))->text;
                if (filename != "No Data") {
                    dataPic = Sprite::create();
                    auto pic = Sprite::create(FileUtils::getInstance()->getWritablePath()+filename+".png");
//                    CCASSERT(pic, "pic musn't be nullptr!!!");
                    if (pic == nullptr) {
                        pic = Sprite::create("frame/Data-Pic.png");
                        pic->setScale(visibleSize.width/dataPic->getContentSize().width*0.6);
                    } else {
                        pic->setScale(0.58);
                    }
                    dataPic->addChild(pic);
                    auto frame = Sprite::create("frame/Data-Pic.png");
                    frame->setScale(visibleSize.width/frame->getContentSize().width*0.6);
                    dataPic->addChild(frame);
                } else {
                    dataPic = Sprite::create("frame/Data-Pic.png");
                    dataPic->setScale(visibleSize.width/dataPic->getContentSize().width*0.6);
                }
                greyLayer->addChild(dataPic, 1, "dataPic");
                dataPic->setPosition(visibleSize.width*0.33, visibleSize.height*0.5);
                dataPic->setOpacity(0);
                dataPic->runAction(ActionFadeIn::create(0.2, 200));
                auto dataPicChildren = dataPic->getChildren();
                for (int i = 0; i != dataPicChildren.size(); ++i) {
                    static_cast<Sprite*>(dataPicChildren.at(i))->setOpacity(0);
                    static_cast<Sprite*>(dataPicChildren.at(i))->runAction(ActionFadeIn::create(0.2, 200));
                }
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
