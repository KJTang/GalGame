//
//  BlurInAndOut.h
//  Test
//
//  Created by KJTang on 15/8/4.
//
//

#ifndef BlurInAndOut_cpp
#define BlurInAndOut_cpp

#include "cocos2d.h"

using namespace cocos2d;

class BlurIn : public ActionInterval
{
private:
    int count, countFlag;
public:
    BlurIn();
    ~BlurIn();
    virtual bool init(float duration);
    virtual void update(float dt);
    static BlurIn* create(float duration);
};

class BlurOut : public ActionInterval
{
private:
    int count, countFlag;
public:
    BlurOut();
    ~BlurOut();
    virtual bool init(float duration);
    virtual void update(float dt);
    static BlurOut* create(float duration);
};

#endif /* BlurInAndOut_cpp */
