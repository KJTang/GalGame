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
    
    xSpeed = 0.0, ySpeed = 0.0;
    xSpeedRate = 2, ySpeedRate = 2;
    resistanceX = 0.4, resistanceY = 0.4;
    
    bg = Sprite::create(filename);
    this->addChild(bg);
    
    // 放缩bg到屏幕大小的scaleRate倍， 并计算X方向和Y方向分别为屏幕多少倍
    bg->setScale(visibleSize.width/bg->getContentSize().width * scaleRate);
    scaleX = bg->getContentSize().width*bg->getScaleX()/visibleSize.width,
    scaleY = bg->getContentSize().height*bg->getScaleY()/visibleSize.height;
    bg->setPosition(visibleSize.width/2, visibleSize.height/2);
    
    this->schedule(schedule_selector(GyroBackground::bgMove), 1.0/60);
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
    if (yawAngle.size() == number) {
        float yawAcc = yawAngle[number-1]-yawAngle[0];
        float rollAcc = rollAngle[number-1]-rollAngle[0];
        float pitchAcc = pitchAngle[number-1]-pitchAngle[0];
        for (int i = 1; i != number; ++i) {
            yawAcc += yawAngle[i]-yawAngle[i-1];
            rollAcc += rollAngle[i]-rollAngle[i-1];
            pitchAcc += pitchAngle[i]-pitchAngle[i-1];
        }
        yawAngle.clear(), rollAngle.clear(), pitchAngle.clear();
        yawAcc /= (number-1);
        rollAcc /= (number-1);
        pitchAcc /= (number-1);
        
        float xAcc = yawAcc + pitchAcc, yAcc = rollAcc;
//        log("Acceleration: %.2f, %.2f", xAcc, yAcc);
        
        if (xSpeed == 0.0) {
            if (xAcc > resistanceX || xAcc < -resistanceX) {
                xSpeed += xAcc;
            } else {
                xSpeed = 0;
            }
        } else if (xSpeed > 0.0) {
            xSpeed += xAcc - resistanceX;
        } else {
            xSpeed += xAcc + resistanceX;
        }
        if (ySpeed == 0.0) {
            if (yAcc > resistanceY || yAcc < -resistanceY) {
                ySpeed += yAcc;
            } else {
                ySpeed = 0;
            }
        } else if (ySpeed > 0.0) {
            ySpeed += yAcc - resistanceY;
        } else {
            ySpeed += yAcc + resistanceY;
        }
    }
    
    bg->setPosition(bg->getPosition()+Vec2(xSpeed*xSpeedRate, ySpeed*ySpeedRate));
    // 速度受阻力影响而变化
    if (xSpeed >= 0.0) {
        xSpeed = xSpeed-resistanceX>0 ? xSpeed-resistanceX : 0;
    } else {
        xSpeed = xSpeed+resistanceX<0 ? xSpeed+resistanceX : 0;
    }
    if (ySpeed >= 0.0) {
        ySpeed = ySpeed-resistanceY>0 ? ySpeed-resistanceY : 0;
    } else {
        ySpeed = ySpeed+resistanceY<0 ? ySpeed+resistanceY : 0;
    }
    
    // 限制X方向移动范围，避免图像移动出界
    if (bg->getPositionX()+visibleSize.width*scaleX/2 < visibleSize.width) {
        bg->setPositionX(visibleSize.width*(1-scaleX/2));
    }
    if (bg->getPositionX()-visibleSize.width*scaleX/2 > 0) {
        bg->setPositionX(visibleSize.width*scaleX/2);
    }
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