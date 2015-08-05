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
#include "TouchableLayer.h"

using namespace cocos2d;

class TextLayer : public TouchableLayer
{
private:
    Size visibleSize;
    Label *text;
    Label *outline01, *outline02, *outline03, *outline04;
    Sprite *background;
    std::string strSave, strShow;
    int pos;
    float textSpeed;
public:
    TextLayer();
    ~TextLayer();
    
    virtual bool init();
    CREATE_FUNC(TextLayer);
    
    void setText(std::string s) {strSave = s; strShow.clear();}
    void setSpeed(float sp) {textSpeed = sp;}
    void showText();
    void stopText();
    void clearText();
    
    void textUpdate(float dt);
    
    bool enableTouchListener;
    virtual void onClick();
    
    // blur
    void blurIn();
    void blurOut();
};

#endif /* TextLayer_cpp */
