//
//  MenuLayer.h
//  Test
//
//  Created by KJTang on 15/9/26.
//
//

#ifndef MenuLayer_cpp
#define MenuLayer_cpp

#include "cocos2d.h"
#include "ButtonSprite.h"

using namespace cocos2d;

class ListItem : public Sprite
{
private:
    Size visibleSize;
    Label *textLabel;
    Sprite *chosen, *unchosen;
    ButtonSprite *deleteBtnUnchosen, *deleteBtnChosen;
public:
    std::string text;
public:
    ListItem();
    ~ListItem();
    virtual bool init();
    CREATE_FUNC(ListItem);
    
    void setText(const std::string &time, const std::string &chaptername);
    void setActive(bool active);
};

class MenuLayer : public Layer
{
private:
    Size visibleSize;
    
    Layer *blackLayer;
    // event
    EventListenerTouchOneByOne *screenTouchListener;
    int touchType;
    Point originPoint, startPoint, endPoint;
    // menu
    Layer *leftMenu, *rightMenu;
    // data list
    ListItem *currentData;
    Layer *dataList;
    Sprite *dataPic;
    int listItemCount;
    float listItemHeight;
    int currentListItemID;
    
    void createDataList();
    void sortDataList();
    void loadData(const std::string &filename);
public:
    void deleteData(const std::string &filename);
public:
    MenuLayer();
    ~MenuLayer();
    virtual bool init();
    CREATE_FUNC(MenuLayer);
};

#endif /* MenuLayer_cpp */
