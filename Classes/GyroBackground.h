//
//  GyroBackground.h
//  Test
//
//  Created by KJTang on 15/7/10.
//
//

#ifndef GyroBackground_h
#define GyroBackground_h

#include "cocos2d.h"
#include <vector>

// test
#include "BlurInAndOut.h"

using namespace cocos2d;

class GyroBackground : public Layer
{
private:
    cocos2d::Size visibleSize;
    Sprite *bg;
    float scaleX, scaleY;
    
    void *m_motionManager;
    float currentYaw, currentRoll, currentPitch;
    
    std::vector<float> yawAngle, rollAngle, pitchAngle;
    // 速度及速度对应放大到屏幕上所乘的系数
    float xSpeed, ySpeed;
    float xSpeedRate, ySpeedRate;
    // 阻力
    float resistanceX, resistanceY;
public:
    GyroBackground(){};
    ~GyroBackground(){};
    
    virtual bool init(std::string filename, float scaleRate);
    static GyroBackground* create(std::string filename, float scaleRate);
    
    void bgMove(float dt);
};

#endif /* GyroBackground_h */
