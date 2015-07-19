//
//  TextLayer.h
//  Test
//
//  Created by KJTang on 15/7/17.
//
//

#ifndef TextLayer_cpp
#define TextLayer_cpp

#include "cocos2d.h"

using namespace cocos2d;

class TextLayer : public Layer
{
private:
    Size visibleSize;
    Label *text;
    Label *outline01, *outline02, *outline03, *outline04;
    std::string strSave, strShow;
    int pos;
    float textSpeed;
public:
    TextLayer();
    ~TextLayer();
    
    virtual bool init();
    CREATE_FUNC(TextLayer);
    
    void setText(std::string s) {strSave = s;}
    void setSpeed(float sp) {textSpeed = sp;}
    void showText();
    void stopText();
    
    void postStopedMsg();
    void textUpdate(float dt);
};

#endif /* TextLayer_cpp */
