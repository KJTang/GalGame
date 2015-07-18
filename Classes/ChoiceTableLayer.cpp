//
//  ChoiceTableLayer.cpp
//  Test
//
//  Created by KJTang on 15/7/18.
//
//

#include "ChoiceTableLayer.h"

ChoiceTableLayer::ChoiceTableLayer(){}

ChoiceTableLayer::~ChoiceTableLayer(){}

bool ChoiceTableLayer::init()
{
    if (!Layer::init()) {
        return false;
    }
 
//    choice01 = Label::createWithTTF(<#const std::string &text#>, <#const std::string &fontFilePath#>, <#float fontSize#>);
    
    return true;
}
