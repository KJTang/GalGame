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

using namespace cocos2d;

class GyroBackground : public Layer
{
private:
    cocos2d::Size visibleSize;
    Sprite *bg;
    float scaleX, scaleY;
    
    void *m_motionManager;
    float initialYaw, initialRoll, initialPitch;
    float currentYaw, currentRoll, currentPitch;
    
    std::vector<float> yawAngle, rollAngle, pitchAngle;
    float currentXSpeed, currentYSpeed;
    
    // 初始速度和阻力
    float initialXSpeed, initialYSpeed;
    float resistanceX, resistanceY;
    // 运动方向
    bool directionX, directionY;
public:
    GyroBackground(){};
    ~GyroBackground(){};
    
    virtual bool init(std::string filename, float scaleRate);
    static GyroBackground* create(std::string filename, float scaleRate);
    
    void bgMove(float dt);
};

#endif /* GyroBackground_h */