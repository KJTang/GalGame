//
//  ActionFade.h
//  Test
//
//  Created by KJTang on 15/10/3.
//
//

#ifndef ActionFade_cpp
#define ActionFade_cpp

#include "cocos2d.h"

using namespace cocos2d;

class ActionFadeIn : public ActionInterval
{
private:
    int step;
    int count;
    int opacity;
public:
    ActionFadeIn();
    ~ActionFadeIn();
    virtual bool init(float duration, int opacity);
    virtual void update(float dt);
    static ActionFadeIn* create(float duration, int opacity);
};

class ActionFadeOut : public ActionInterval
{
private:
    int step;
    int count;
    int opacity;
public:
    ActionFadeOut();
    ~ActionFadeOut();
    virtual bool init(float duration, int opacity);
    virtual void update(float dt);
    static ActionFadeOut* create(float duration, int opacity);
};

#endif /* ActionFade_cpp */
