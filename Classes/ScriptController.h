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
#include "DataController.h"

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
    
    void runNew(std::string filename);
    void runSaved(std::string filename);
    
    // state
    void stateBegin();
    
    void stateCommand(std::string cmd);
    
    void stateJump(std::string cmd);
    
    bool isConditionFullFilled;  // used to judge if condition is fullfilled or not
    void stateCondition(std::string cmd);
    
    void stateEnd();
    
    //
    int getPos() {return pos;}
    void setPos(int p) {pos = p;}
    int getLineID() {return lineID;}
    void setLineID(int l) {lineID = l;}
    int getGoBackPosMark() {return goBackPosMark;}
    void setGoBackPosMark(int gb) {goBackPosMark = gb;}
    int getGoBackLineMark() {return goBackLineMark;}
    void setGoBackLineMark(int gb) {goBackLineMark = gb;}
    // used for data saving
    bool isChoiceTableShowing;
    int choiceTablePos, choiceTableLineID;

};

#endif /* ScriptController_cpp */
