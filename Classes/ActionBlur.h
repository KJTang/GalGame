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

enum {
    NONE_TO_LITTLE,
    NONE_TO_MUCH,
    LITTLE_TO_NONE,
    LITTLE_TO_MUCH,
    MUCH_TO_NONE,
    MUCH_TO_LITTLE
};

class ActionBlur : public ActionInterval
{
private:
    int count, step;
    int blurType;
    int blurValue[11];
    GLProgram *blur;
public:
    ActionBlur();
    ~ActionBlur();
    virtual bool init(float duration, int type);
    virtual void update(float dt);
    static ActionBlur* create(float duration, int type);
};

#endif /* ActionBlur_cpp */
