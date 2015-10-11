//
//  ActionBlur.h
//  Test
//
//  Created by KJTang on 15/9/3.
//
//

#ifndef ActionBlur_cpp
#define ActionBlur_cpp

#include "cocos2d.h"

using namespace cocos2d;

const int NONE = 0;

class ActionBlur : public ActionInterval
{
private:
    int count, step;
    int startLevel, endLevel;
    int delta;
    GLProgram *blur;
public:
    ActionBlur();
    ~ActionBlur();
    virtual bool init(float duration, int startLevel, int endLevel);
    virtual void update(float dt);
    static ActionBlur* create(float duration, int startLevel, int endLevel);
};

#endif /* ActionBlur_cpp */
