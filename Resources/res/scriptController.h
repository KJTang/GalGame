//
//  scriptController.hpp
//  Test
//
//  Created by KJTang on 15/7/13.
//
//

#ifndef scriptController_cpp
#define scriptController_cpp

#include <cstdio>

#include "cocos2d.h"

using namespace cocos2d;

class scriptController
{
private:
    static scriptController *sharedScriptController;
    
public:
    scriptController();
    ~scriptController();
    
    static scriptController* getInstance()
    {
        if(!sharedScriptController)
        {
            sharedScriptController = new scriptController();
        }
        sharedScriptController->init();
        
        return sharedScriptController;
    }
    
    virtual bool init();
    
    void test();
};

#endif /* scriptController_cpp */
