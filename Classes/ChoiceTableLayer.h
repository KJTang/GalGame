//
//  ChoiceTableLayer.h
//  Test
//
//  Created by KJTang on 15/7/18.
//
//

#ifndef ChoiceTableLayer_cpp
#define ChoiceTableLayer_cpp

#include "cocos2d.h"

using namespace cocos2d;

const int MAX_CHOICE_NUMBER = 8;

class ChoiceTableLayer : public Layer
{
private:
    Size visibleSize;
    Point startPoint, endPoint;
    bool moved; // judge if the choice is lose focus
    Vector<Sprite*> choices;
    int choiceNumber;
    int tempResult;
    int choiceResult;
    
    EventListenerTouchOneByOne *touchListener;
    Vector<EventListenerTouchOneByOne*> listeners;
public:
    ChoiceTableLayer();
    ~ChoiceTableLayer();
    
    virtual bool init();
    CREATE_FUNC(ChoiceTableLayer);
    
    void setChoiceNumber(int number);
    void setChoiceContent(int id, const std::string& content);
    void setChoiceChoosable(int id, bool choosable);
    
    void showChoiceTable();
    
    void setChoiceResult(int result);
    int getChoiceReuslt();
};

#endif /* ChoiceTableLayer_cpp */
