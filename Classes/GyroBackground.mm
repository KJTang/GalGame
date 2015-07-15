//
//  GyroBackground.mm
//  Test
//
//  Created by KJTang on 15/7/10.
//

#include "GyroBackground.h"

#include <CoreMotion/CoreMotion.h>
#import <CoreFoundation/CoreFoundation.h>

GyroBackground* GyroBackground::create(std::string filename, float scaleRate)
{
    GyroBackground *p = new GyroBackground();
    p->init(filename, scaleRate);
    p->autorelease();
    
    return p;
}

bool GyroBackground::init(std::string filename, float scaleRate)
{
    if(!Layer::init())
        return false;
    // Objective-C代码，用以获取陀螺仪参数
    CMMotionManager *motionManager = [[CMMotionManager alloc] init];
    motionManager.deviceMotionUpdateInterval = 1.0/60.0;
    if (motionManager.isDeviceMotionAvailable) {
        [motionManager startDeviceMotionUpdates];
    }
    m_motionManager = (void*)motionManager;
    
    visibleSize = Director::getInstance()->getVisibleSize();
    this->setPosition(0, 0);
    
    currentXSpeed = 0.0, currentYSpeed = 0.0;
    initialXSpeed = 0.0, initialYSpeed = 0.0;
    resistanceX = 5, resistanceY = 5;
    
    bg = Sprite::create(filename);
    this->addChild(bg);
    
    // 放缩bg到屏幕大小的scaleRate倍， 并计算X方向和Y方向分别为屏幕多少倍
    bg->setScale(visibleSize.width/bg->getContentSize().width * scaleRate);
    scaleX = bg->getContentSize().width*bg->getScaleX()/visibleSize.width,
    scaleY = bg->getContentSize().height*bg->getScaleY()/visibleSize.height;
    bg->setPosition(visibleSize.width/2, visibleSize.height/2);
    
    this->schedule(schedule_selector(GyroBackground::bgMove), 1.0/120);
    return true;
}

void GyroBackground::bgMove(float dt)
{
    CMAttitude *currentAttitude = static_cast<CMMotionManager*>(m_motionManager).deviceMotion.attitude;
    
    currentYaw = roundf((float)(CC_RADIANS_TO_DEGREES(currentAttitude.yaw)));
    currentRoll = roundf((float)(CC_RADIANS_TO_DEGREES(currentAttitude.roll)));
    currentPitch = roundf((float)(CC_RADIANS_TO_DEGREES(currentAttitude.pitch)));
    
    yawAngle.push_back(currentYaw);
    rollAngle.push_back(currentRoll);
    pitchAngle.push_back(currentPitch);
    
    int number = 6;
    // 定义小范围移动时角度差值的最大值
    float maxRange = 5.0;
    if (yawAngle.size() == number) {
        /*
         * X方向的速度来自于yaw和picth两个数据
         * Y方向的速度来自于roll的数据
         *
         */
        bool ignoreY = false;
        float yawRange = yawAngle[number-1]-yawAngle[0];
        float rollRange = rollAngle[number-1]-rollAngle[0];
        float pitchRange = pitchAngle[number-1]-pitchAngle[0];
        
        // X Speed from yaw
        if (yawRange > -maxRange && yawRange < maxRange) {
            resistanceX = 0;
            initialXSpeed = yawRange*2.5;
        }
        else {
            resistanceX = 1;
            initialXSpeed = yawRange*4;
            ignoreY = true;
        }
        // X Speed from picth
        if (pitchRange > -maxRange && pitchRange < maxRange) {
            resistanceX = 0;
            initialXSpeed += pitchRange*2.5;
        }
        else {
            resistanceX = 1;
            initialXSpeed += pitchRange*4;
            ignoreY = true;
        }
        directionX = (initialXSpeed > 0);
        // X方向为主要运动时忽略Y方向
        if (!ignoreY) {
            // Y Speed
            if (rollRange > -maxRange && rollRange < maxRange) {
                resistanceY = 0;
                initialYSpeed = rollRange*2;
            }
            else {
                resistanceY = 1;
                initialYSpeed = rollRange*3;
                // Y方向为主要运动时忽略X方向
                resistanceX = 0;
                initialXSpeed = 0;
            }
            directionY = (initialYSpeed > 0);
        }
        
        yawAngle.clear();
        rollAngle.clear();
        pitchAngle.clear();
    }
    // 计算X方向速度
    if (directionX) {
        // 赋予初始速度，并赋予相反方向的加速度，即阻力
        currentXSpeed = initialXSpeed;
        initialXSpeed -= resistanceX;
        // 若速度已经减小到0，修改参数使停止运动
        if (currentXSpeed < 0) {
            currentXSpeed = 0;
            initialXSpeed = 0;
        }
    }
    else
    {
        currentXSpeed = initialXSpeed;
        initialXSpeed += resistanceX;
        
        if (currentXSpeed > 0) {
            currentXSpeed = 0;
            initialXSpeed = 0;
        }
    }
    bg->setPositionX(bg->getPositionX()+currentXSpeed);
    // 限制X方向移动范围，避免图像移动出界
    if (bg->getPositionX()+visibleSize.width*scaleX/2 < visibleSize.width) {
        bg->setPositionX(visibleSize.width*(1-scaleX/2));
    }
    if (bg->getPositionX()-visibleSize.width*scaleX/2 > 0) {
        bg->setPositionX(visibleSize.width*scaleX/2);
    }
    // 计算Y方向速度
    if (directionY) {
        currentYSpeed = initialYSpeed;
        initialYSpeed -= resistanceY;
        
        if (currentYSpeed < 0) {
            currentYSpeed = 0;
            initialYSpeed = 0;
        }
    }
    else
    {
        currentYSpeed = initialYSpeed;
        initialYSpeed += resistanceY;
        
        if (currentYSpeed > 0) {
            currentYSpeed = 0;
            initialYSpeed = 0;
        }
    }
    bg->setPositionY(bg->getPositionY()+currentYSpeed);
    // 限制Y方向移动范围，避免图像移动出界
    if (bg->getPositionY()+visibleSize.height*scaleY/2 < visibleSize.height) {
        bg->setPositionY(visibleSize.height*(1-scaleY/2));
    }
    if (bg->getPositionY()-visibleSize.height*scaleY/2 > 0) {
        bg->setPositionY(visibleSize.height*scaleY/2);
    }
    
    // 如果图片尺寸小于屏幕则不移动
    if (scaleX <= 1.0) {
        bg->setPositionX(visibleSize.width/2);
    }
    if (scaleY <= 1.0) {
        bg->setPositionY(visibleSize.height/2);
    }
}