//
//  ButtonSprite.h
//  Test
//
//  Created by KJTang on 15/7/15.
//
//

#ifndef ButtonSprite_cpp
#define ButtonSprite_cpp

#include "cocos2d.h"

using namespace cocos2d;

class ButtonSprite : public Sprite
{
private:
    cocos2d::Size visibleSize;
    EventListenerTouchOneByOne* touchListener;

    void *m_motionManager;
    float currentYaw, currentRoll, currentPitch;
    std::vector<float> yawAngle, rollAngle, pitchAngle;
    // 速度及速度对应放大到屏幕上所乘的系数
    float xSpeed, ySpeed;
    float xSpeedRate, ySpeedRate;
    // 阻力
    float resistanceX, resistanceY;
    // 初始位置及最大位移
    bool isOriginSetted;
    float originX, originY;
    float maxX, maxY;
    
    void (*callbackFunc)();
public:
    ButtonSprite();
    ~ButtonSprite();
    
    static ButtonSprite* create(std::string filename);
    
    virtual bool initWithFile(std::string filename);
    virtual void onEnter();
    
    virtual void update(float dt);
    virtual void onClicked();
    void setCallbackFunc(void (*func)());
};

#endif /* ButtonSprite_cpp */
