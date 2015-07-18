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

class ChoiceTableLayer : public Layer
{
private:
    Size visibleSize;
    Label *choice01, *choice02, *choice03, *choice04;
    EventListenerTouchOneByOne *touchListener01, *touchListener02, *touchListener03, *touchListener04;
    
    bool showChoice01, showChoice02, showChoice03, showChoice04;
    bool enableChoice01, enableChoice02, enableChoice03, enableChoice04;
public:
    ChoiceTableLayer();
    ~ChoiceTableLayer();
    
    virtual bool init();
    CREATE_FUNC(ChoiceTableLayer);
    
    void showChoiceTable();
    
    void setChoice01Content(std::string str);
    void setChoice01Choosable(bool b);
    
    void setChoice02Content(std::string str);
    void setChoice02Choosable(bool b);
    
    void setChoice03Content(std::string str);
    void setChoice03Choosable(bool b);
    
    void setChoice04Content(std::string str);
    void setChoice04Choosable(bool b);
};

#endif /* ChoiceTableLayer_cpp */
