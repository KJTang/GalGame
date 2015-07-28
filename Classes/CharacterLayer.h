//
//  CharacterLayer.h
//  Test
//
//  Created by KJTang on 15/7/28.
//
//

#ifndef CharacterLayer_cpp
#define CharacterLayer_cpp

#include "cocos2d.h"
#include "TouchableLayer.h"

using namespace cocos2d;

class CharacterLayer : public TouchableLayer
{
private:
    
public:
    CharacterLayer();
    ~CharacterLayer();
    
    virtual bool init();
    CREATE_FUNC(CharacterLayer);
    
    bool enableTouchListener;
    virtual void onClick();
};

#endif /* CharacterLayer_cpp */
