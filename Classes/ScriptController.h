//
//  ScriptController.hpp
//  Test
//
//  Created by KJTang on 15/7/13.
//
//

#ifndef ScriptController_cpp
#define ScriptController_cpp

#include <cstdio>

#include "cocos2d.h"

#include "GameController.h"
#include "VariableController.h"

using namespace cocos2d;

class ScriptController
{
private:
    static ScriptController *sharedScriptController;
    std::string data;
    int pos, lineID;
    int goBackPosMark, goBackLineMark;
    
    std::string getString();
    int transStringToInt(std::string num);
    float transStringToFloat(std::string num);
    
    // error box
    bool hasErr;
    enum errorID
    {
        UNRECOGNIZED_CHARACTOR,
        MISSED_ANOTHER_QUATATION_MARK,
        INVALID_EXPRESSION,
        UNKNOWN_COMMAND,
        VARIABLE_DOES_NOT_EXIST,
        GO_BACK_MARK_DOES_NOT_EXIST,
        XXX
    };
    void showError(int errID);
private:
    ScriptController();
public:
    ~ScriptController();

public:
    bool init();
    static ScriptController* getInstance()
    {
        if(!sharedScriptController)
        {
            sharedScriptController = new ScriptController();
            sharedScriptController->init();
        }
        return sharedScriptController;
    }
    
    void runWithFile(std::string filename, int linePosition);
    
    // state
    void stateBegin();
    
    void stateCommand(std::string cmd);
    
    void stateJump(std::string cmd);
    
    bool isConditionFullFilled;  // used to judge if condition is fullfilled or not
    void stateCondition(std::string cmd);
    
    void stateEnd();
};

#endif /* ScriptController_cpp */
