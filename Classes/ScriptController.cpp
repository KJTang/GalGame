//
//  ScriptController.cpp
//  Test
//
//  Created by KJTang on 15/7/13.
//
//

#include "ScriptController.h"

ScriptController* ScriptController::sharedScriptController = NULL;

ScriptController::ScriptController(){}

ScriptController::~ScriptController(){}

bool ScriptController::init()
{
    pos = 0, lineID = 1;
    goBackPosMark = -1, goBackLineMark = -1;
    choiceTablePos = -1, choiceTableLineID = -1;
    textPos = -1;
    isChoiceTableShowing = false;
    isConditionFullFilled = false;
    hasErr = false;
    return true;
}

void ScriptController::runNew(const std::string &filename)
{
    GameScene::getInstance()->UserData.scriptPath = filename;
    pos = 0, lineID = 1;
    goBackPosMark = -1, goBackLineMark = -1;
    isConditionFullFilled = false;
    hasErr = false;
    data = FileUtils::getInstance()->getStringFromFile(filename.c_str());
}

void ScriptController::runSaved(const std::string &filename)
{
    GameScene::getInstance()->UserData.scriptPath = filename;
    if (textPos != -1) {
        pos = textPos;
        lineID = textLineID;
    }
    if (choiceTablePos != -1) {
        pos = choiceTablePos;
        lineID = choiceTableLineID;
    }
    data = FileUtils::getInstance()->getStringFromFile(filename.c_str());
    DataController::getInstance()->test(filename);
}

std::string ScriptController::getString()
{
    std::string str;
    while (true) {
        // is it the end of script
        if (pos == data.size()) {
            return "";
        }
        // shift the blanks
        if (data[pos] == ' ') {
            ++pos;
            continue;
        }
        if (data[pos] == '.') {
            ++pos;
            continue;
        }
        if (data[pos] == '=') {
            ++pos;
            continue;
        }
        if (data[pos] == '\n') {
            ++pos;
            ++lineID;
            continue;
        }
        // shift the text
        if (data[pos] == '/') {
            if (data[pos+1] == '/') {
                while (data[pos] != '\n') {
                    ++pos;
                }
                ++pos;
                ++lineID;
                continue;
            } else {
                showError(UNRECOGNIZED_CHARACTOR);
                return "";
            }
        }
        else if (data[pos] == '#') {
            str += data[pos];
            ++pos;
            while (isalpha(data[pos]) || isnumber(data[pos])) {
                str += data[pos];
                ++pos;
            }
            return str;
        }
        // get string between " "
        else if (data[pos] == '\"') {
            while (true) {
                ++pos;
                if (pos==data.size() || data[pos]=='\n') {
                    showError(MISSED_ANOTHER_QUATATION_MARK);
                    return "";
                }
                if (data[pos] != '\"') {
                    str += data[pos];
                } else {
                    ++pos;
                    return str;
                }
            }
        }
        // get string beside '.'
        else if (isalpha(data[pos]) || isnumber(data[pos]))
        {
            while (true) {
                if (pos == data.size()) {
                    return str;
                }
                if (isalpha(data[pos]) || isnumber(data[pos])) {
                    str += data[pos];
                    ++pos;
                    continue;
                } else {
                    ++pos;
                    return str;
                }
//                if (data[pos] == '.' || data[pos] == '=' || data[pos] == '\n') {
//                    ++pos;
//                    return str;
//                } else {
//                    showError(INVALID_EXPRESSION);
//                    return "";
//                }
            }
        }
        else {
            showError(UNRECOGNIZED_CHARACTOR);
            return "";
        }
    }
}

int ScriptController::transStringToInt(const std::string &num)
{
    int result = 0;
    for (int i = 0; i != num.size(); ++i) {
        result *= 10;
        result += num[i]-'0';
    }
    return result;
}

float ScriptController::transStringToFloat(const std::string &num)
{
    float result = 0;
    int dot = 0;
    for (int i = 0; i != num.size(); ++i) {
        if (num[i] == '.') {
            dot = 1;
            continue;
        }
        dot *= 10;
        result *= 10;
        result += num[i]-'0';
    }
    return dot?result/dot:result;
}

void ScriptController::stateBegin()
{
    std::string str = getString();
    if (str.size()) {
        if (str[0] == '#') {
            stateJump(str);
        } else if (str == "set" || str == "get") {
            stateCommand(str);
        } else if (str == "if" || str == "elif" || str == "else" || str == "endif") {
            stateCondition(str);
        } else if (str == "log") {
            log("scriptlog: %s", getString().c_str());
            GameScene::getInstance()->isMissionCompleted = true;
        } else {
            showError(UNKNOWN_COMMAND);
        }
    }
    else {
        stateEnd();
    }
}

void ScriptController::stateJump(const std::string &cmd)
{
    if (cmd == "#goback") {
        if (goBackPosMark == -1) {
            showError(GO_BACK_MARK_DOES_NOT_EXIST);
        }
        else {
            pos = goBackPosMark;
            lineID = goBackLineMark;
            // when we goback, we need break the "if"
            isConditionFullFilled = false;
            stateBegin();
        }
    } else if (cmd == "#gobackmark") {
        goBackPosMark = pos;
        goBackLineMark = lineID;
        stateBegin();
    } else if (cmd == "#") {
        std::string id = getString();
        std::string next = getString();
        while (next != ("#"+id)) {
            next = getString();
        }
        stateBegin();
    } else if (cmd == "#newfile") {
        // switch to another script file
        std::string filename = getString();
        runNew(filename);
        GameScene::getInstance()->isMissionCompleted = true;
    } else {
        // do nothing
        stateEnd();
    }
}

void ScriptController::stateCommand(const std::string &cmd)
{
    /** **********************
     *          set
     * **********************
     */
    if (cmd == "set") {
        std::string str = getString();
        log("-------------------------------------------%s----", str.c_str());
        // setting bgp
        if (str == "bgp") {
            std::string str = getString();
            if (str == "name") {
                std::string str = getString();
                log("set bgp name = %s", str.c_str());
                GameScene::getInstance()->setBgpFilename(str);
            } else if (str == "effect") {
                std::string str = getString();
                log("set bgp effect = %s", str.c_str());
            } else if (str == "scale") {
                std::string str = getString();
                log("set bgp scale = %s", str.c_str());
                GameScene::getInstance()->setBgpScale(transStringToFloat(str));
            } else if (str == "duration") {
                std::string str = getString();
                log("set bgp duration = %s", str.c_str());
                GameScene::getInstance()->setBgpDuration(transStringToFloat(str));
            } else if (str == "position") {
                std::string x = getString();
                std::string y = getString();
                log("set bgp position = %s, %s", x.c_str(), y.c_str());
                GameScene::getInstance()->setBgpPosition(transStringToFloat(x), transStringToFloat(y));
            } else if (str == "start") {
                log("set bgp start");
                GameScene::getInstance()->setBgpStart();
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // setting cg
        else if (str == "cg") {
            std::string str = getString();
            if (str == "name") {
                std::string str = getString();
                log("set cg name = %s", str.c_str());
            } else if (str == "effect") {
                std::string str = getString();
                log("set cg effect = %s", str.c_str());
            } else if (str == "Xscale") {
                std::string str = getString();
                log("set cg xscale = %s", str.c_str());
            } else if (str == "Yscale") {
                std::string str = getString();
                log("set cg yscale = %s", str.c_str());
            } else if (str == "Xposition") {
                std::string str = getString();
                log("set cg xposition = %s", str.c_str());
            } else if (str == "Yposition") {
                std::string str = getString();
                log("set cg yposition = %s", str.c_str());
            } else if (str == "flowable") {
                std::string str = getString();
                log("set cg flowable = %s", str.c_str());
            } else if (str == "start") {
                std::string str = getString();
                log("set cg start = %s", str.c_str());
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // setting text
        else if (str == "text") {
            textPos = pos - 9;
            textLineID = lineID;
            std::string str = getString();
            if (str == "update") {
                GameScene::getInstance()->setTextUpdate(getString());
            } else if (str == "content") {
                std::string str = getString();
                log("set text content = %s", str.c_str());
                GameScene::getInstance()->setTextContent(str);
            } else if (str == "start") {
                GameScene::getInstance()->setTextShow();
            } else if (str == "speed") {
                GameScene::getInstance()->setTextSpeed(transStringToFloat(getString()));
            } else if (str == "clear") {
                GameScene::getInstance()->setTextClear();
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // setting bgm
        else if (str == "bgm") {
            std::string str = getString();
            if (str == "name") {
                std::string str = getString();
                GameController::getInstance()->loadBGM(str);
                GameScene::getInstance()->UserData.bgmFilename = str;
                GameScene::getInstance()->isMissionCompleted = true;
            } else if (str == "start") {
                log("set bgm start");
                GameController::getInstance()->playBGM();
                GameScene::getInstance()->isMissionCompleted = true;
            } else if (str == "pause") {
                log("set bgm pause");
                GameController::getInstance()->pauseBGM();
                GameScene::getInstance()->isMissionCompleted = true;
            } else if (str == "resume") {
                log("set bgm resume");
                GameController::getInstance()->resumeBGM();
                GameScene::getInstance()->isMissionCompleted = true;
            } else if (str == "stop") {
                log("set bgm stop");
                GameController::getInstance()->stopBGM();
                GameScene::getInstance()->isMissionCompleted = true;
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // setting sound effect
        else if (str == "se") {
            std::string str = getString();
            if (str == "name") {
                std::string str = getString();
                log("set se name = %s", str.c_str());
                GameController::getInstance()->loadSE(str);
                GameScene::getInstance()->isMissionCompleted = true;
            } else if (str == "start") {
                std::string str = getString();
                log("set se start = %s", str.c_str());
                GameController::getInstance()->playSE(str);
                GameScene::getInstance()->isMissionCompleted = true;
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // setting characters
        else if (str == "character") {
            int id = transStringToInt(getString());
            std::string str = getString();
            if (str == "name") {
                GameScene::getInstance()->setCharacterFilename(id, getString());
            } else if (str == "scale") {
                GameScene::getInstance()->setCharacterScale(id, transStringToFloat(getString()));
            } else if (str == "position") {
                GameScene::getInstance()->setCharacterPosition(id, transStringToFloat(getString()), transStringToFloat(getString()));
            } else if (str == "effect") {
                GameScene::getInstance()->setCharacterEffect(id, getString());
            } else if (str == "clear") {
                GameScene::getInstance()->setCharacterClear(id);
            } else if (str == "start") {
                GameScene::getInstance()->setCharacterStart(id);
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // variables
        else if (str == "globalint") {
            std::string var = getString();
            std::string opr = getString();
            int num = transStringToInt(getString());
            if (opr == "equal") {
                DataController::getInstance()->setInt(var, num);
                // for variables calculations, we don't need to wait
                GameScene::getInstance()->isMissionCompleted = true;
            } else if (opr == "add") {
                int temp = DataController::getInstance()->getInt(var);
                DataController::getInstance()->setInt(var, temp+num);
                GameScene::getInstance()->isMissionCompleted = true;
            } else if (opr == "minus") {
                int temp = DataController::getInstance()->getInt(var);
                DataController::getInstance()->setInt(var, temp-num);
                GameScene::getInstance()->isMissionCompleted = true;
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // choices
        else if (str == "choice") {
            // save data
            if (!isChoiceTableShowing) {
                choiceTablePos = pos - 11;
                choiceTableLineID = lineID;
                isChoiceTableShowing = true;
            }
            
            std::string str = getString();
            if (str == "number") {
                GameScene::getInstance()->setChoiceNumber(transStringToInt(getString()));
            } else if (str == "content") {
                GameScene::getInstance()->setChoiceContent(transStringToInt(getString()), getString());
            } else if (str == "choosable") {
                int id = transStringToInt(getString());
                std::string choosable = getString();
                if (choosable == "true") {
                    GameScene::getInstance()->setChoiceChoosable(id, true);
                } else if (choosable == "false") {
                    GameScene::getInstance()->setChoiceChoosable(id, false);
                } else {
                    showError(UNKNOWN_COMMAND);
                }
            } else if (str == "show") {
                GameScene::getInstance()->setChoiceShow();
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // wait
        else if (str == "wait") {
            GameScene::getInstance()->setWaitTime(transStringToFloat(getString()));
        }
        // enable/disable gallary pictures
        else if (str == "gallary") {
            int id = transStringToInt(getString());
            std::string choosable = getString();
            if (choosable == "true") {
                GallaryLayer::setGallaryState(id, true);
                GameScene::getInstance()->isMissionCompleted = true;
            } else if (choosable == "false") {
                GallaryLayer::setGallaryState(id, false);
                GameScene::getInstance()->isMissionCompleted = true;
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        else {
            showError(UNKNOWN_COMMAND);
        }
    }
    /** **********************
     *          get   
     * (except "choices" and "variables", gets are not finished)
     * **********************
     */
    else if (cmd == "get") {
        std::string str = getString();
        log("-------------------------------------------%s----", str.c_str());
        // touch event
        if (str == "touch") {
            log("waiting for a screen touch");
            GameScene::getInstance()->enableScreenTouchEventListener(true, 0);
        }
        // get info of bgp
        else if (str == "bgp") {
            std::string str = getString();
            if (str == "name") {
                log("bgp name");
            } else if (str == "effect") {
                log("bgp effect");
            } else if (str == "Xscale") {
                log("bgp xscale");
            } else if (str == "Yscale") {
                log("bgp yscale");
            } else if (str == "Xposition") {
                log("bgp xposition");
            } else if (str == "Yposition") {
                log("bgp yposition");
            } else if (str == "start") {
                log("bgp start");
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // get info of cg
        else if (str == "cg") {
            std::string str = getString();
            if (str == "name") {
                log("cg name");
            } else if (str == "effect") {
                log("cg effect");
            } else if (str == "Xscale") {
                log("cg xscale");
            } else if (str == "Yscale") {
                log("cg yscale");
            } else if (str == "Xposition") {
                log("cg xposition");
            } else if (str == "Yposition") {
                log("cg yposition");
            } else if (str == "flowable") {
                log(" cg flowable");
            } else if (str == "start") {
                log("cg start");
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // get info of text
        else if (str == "text") {
            std::string str = getString();
            if (str == "content") {
                log("text content");
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // get info of bgm
        else if (str == "bgm") {
            std::string str = getString();
            if (str == "name") {
                log("bgm name");
            } else if (str == "start") {
                log("bgm start");
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // get info of se
        else if (str == "se") {
            std::string str = getString();
            if (str == "name") {
                log("se name");
            } else if (str == "start") {
                log("se start");
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // get info of character
        else if (str == "characters") {
            std::string str = getString();
            if (str == "name") {
                log("ch01 name");
            } else if (str == "effect") {
                log("ch01 effect");
            } else if (str == "Xscale") {
                log("ch01 xscale");
            } else if (str == "Yscale") {
                log("ch01 yscale");
            } else if (str == "Xposition") {
                log("ch01 xposition");
            } else if (str == "Yposition") {
                log("ch01 yposition");
            } else if (str == "start") {
                log("ch01 start");
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        // variables
        else if (str == "globalint") {
            std::string var = getString();
            int value = DataController::getInstance()->getInt(var);
            log("%s = %d", var.c_str(), value);
            GameScene::getInstance()->isMissionCompleted = true;
        }
        // choices
        else if (str == "choice") {
            std::string str = getString();
            if (str == "result") {
                GameScene::getInstance()->getChoiceResult();
            } else {
                showError(UNKNOWN_COMMAND);
            }
        }
        else {
            showError(UNKNOWN_COMMAND);
        }
    }
}

void ScriptController::stateCondition(const std::string &cmd)
{   
    std::string str = cmd;
    if (isConditionFullFilled) {
        while (str != "endif") {
            str = getString();
        }
        isConditionFullFilled = false;
        stateBegin();
        return;
    }
    
    // if the condition is not fullfilled, keep judge utill it's fullfilled
    if (str == "if" || str == "elif") {
        std::string type = getString();
        if (type == "globalint") {
            int value = DataController::getInstance()->getInt(getString());
            if (value == -2) {
                showError(VARIABLE_DOES_NOT_EXIST);
                return;
            }
            std::string str = getString();
            if (str == "equalto") {
                if (value == transStringToInt(getString())) {
                    isConditionFullFilled = true;
                    stateBegin();
                } else {
                    std::string str;
                    while (true) {
                        str = getString();
                        if (str == "elif" || str == "else" || str == "endif") {
                            stateCondition(str);
                            return;
                        }
                    }
                }
            } else if (str == "biggerthan") {
                if (value > transStringToInt(getString())) {
                    isConditionFullFilled = true;
                    stateBegin();
                } else {
                    std::string str;
                    while (true) {
                        str = getString();
                        if (str == "elif" || str == "else" || str == "endif") {
                            stateCondition(str);
                            return;
                        }
                    }
                }
            } else if (str == "lessthan") {
                if (value < transStringToInt(getString())) {
                    isConditionFullFilled = true;
                    stateBegin();
                } else {
                    std::string str;
                    while (true) {
                        str = getString();
                        if (str == "elif" || str == "else" || str == "endif") {
                            stateCondition(str);
                            return;
                        }
                    }
                }
            } else {
                showError(UNKNOWN_COMMAND);
            }
        } else {
            showError(UNKNOWN_COMMAND);
        }
    } else if (str == "else") {
        isConditionFullFilled = true;
        stateBegin();
    }
}

void ScriptController::stateEnd()
{
    log("stateEnd");
}

void ScriptController::showError(int errID)
{
    hasErr = true;
    switch (errID) {
        case UNRECOGNIZED_CHARACTOR:
            log("err: unrecognized charactor, line %d", lineID);
            break;
        case MISSED_ANOTHER_QUATATION_MARK:
            log("err: missed another quatation mark, line %d", lineID);
            break;
        case INVALID_EXPRESSION:
            log("err: invalid expression, line %d", lineID);
            break;
        case UNKNOWN_COMMAND:
            log("err: unknown command, line %d", lineID);
            break;
        case VARIABLE_DOES_NOT_EXIST:
            log("err: variable does not exist, line %d", lineID);
            break;
        case GO_BACK_MARK_DOES_NOT_EXIST:
            log("err: gobackmark does not exist, line %d", lineID);
            break;
        case XXX:
            log("XXX");
            break;
        default:
            break;
    }
    //
    stateEnd();
}
