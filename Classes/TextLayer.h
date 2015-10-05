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
    Label *outline[4];
    Sprite *bgChosen, *bgUnchosen;
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
    void onClick();
    
    // blur
    void blurIn();
    void blurOut();
};

#endif /* TextLayer_cpp */
