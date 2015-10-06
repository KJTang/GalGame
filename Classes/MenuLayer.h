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

using namespace cocos2d;

class ListItem : public Sprite
{
private:
    Size visibleSize;
    Label *textLabel;
    Sprite *chosen, *unchosen;
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
    
    Layer *greyLayer;
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
public:
    MenuLayer();
    ~MenuLayer();
    virtual bool init();
    CREATE_FUNC(MenuLayer);
    
    void loadData(const std::string &filename);
    void deleteData(const std::string &filename);
    void sortDataList();
};

#endif /* MenuLayer_cpp */
