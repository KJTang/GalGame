//
//  ChoiceTableLayer.h
//  Test
//
//  Created by KJTang on 15/7/18.
//
//

#ifndef ChoiceTableLayer_cpp
#define ChoiceTableLayer_cpp

#include "cocos2d.h"

using namespace cocos2d;

class ChoiceTableLayer : public Layer
{
private:
    Label *choice01, *choice02, *choice03, *choice04;
public:
    ChoiceTableLayer();
    ~ChoiceTableLayer();
    
    virtual bool init();
    CREATE_FUNC(ChoiceTableLayer);
};

#endif /* ChoiceTableLayer_cpp */
